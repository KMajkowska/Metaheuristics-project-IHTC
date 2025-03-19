#include "PeerToPeer.h"

PeerToPeer::PeerToPeer(const std::string& ip, short sendPort, short receivePort) :
    _io_context(),
    _work_guard(boost::asio::make_work_guard(_io_context)),
    _socket(_io_context),
    _acceptor(_io_context),
    _connected(false),
    _ip(ip),
    _sendPort(sendPort),
    _receivePort(receivePort)
{}

void PeerToPeer::start()
{
    // Run io_context in a separate thread
    std::thread([this]() {
        _io_context.run();
        }).detach();

    if (_sendPort == 5000)
	listenForConnections();
    else 
	tryConnect();
}

void PeerToPeer::listenForConnections()
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(_ip), _receivePort);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::socket_base::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    _acceptor.async_accept(_socket, [this](const boost::system::error_code& error) 
        {
            if (!error) 
            {
                _connected = true;
                std::cout << "Incoming connection accepted!" << std::endl;

                receiveMessage();
            }
            else 
            {
                std::cout << "Failed to accept connection: " << error.message() << std::endl;
            }
        });
}


void PeerToPeer::tryConnect()
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(_ip), _sendPort);

    _socket.async_connect(endpoint, [this](const boost::system::error_code& error) {
        if (!error)
        {
            _connected = true;
            std::cout << "Connected to Peer!" << std::endl;

            // Start listening for messages
            receiveMessage();
        }
        else
        {
            std::cout << "Connection failed: " << error.message() << std::endl;
        }
        });
}

void PeerToPeer::sendMessage(std::string message)
{
    if (!_connected)
    {
        return;
    }

    message += '\n';

    auto message_ptr = std::make_shared<std::string>(std::move(message));


    boost::asio::async_write(
        _socket,
        boost::asio::buffer(*message_ptr),
        [message_ptr](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                std::cout << "Message sent " << std::endl;
            }
            else
            {
                std::cout << "Error while sending message: " << error.message() << std::endl;
            }
        });
}


void PeerToPeer::receiveMessage()
{
    boost::asio::async_read_until(
        _socket,
        _receive_buffer, // boost::asio::streambuf instead of fixed-size buffer
        '\n',
        [this](boost::system::error_code error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                std::istream is(&_receive_buffer);
                std::string message;
                std::getline(is, message); // Read until newline

                std::cout << "Received message " << std::endl;

                notify(message); // Process message

                // Continue reading next messages
                if (_connected)
                {
                    receiveMessage();
                }
            }
            else
            {
                std::cout << "Error while receiving message: " << error.message() << std::endl;
            }
        });
}
