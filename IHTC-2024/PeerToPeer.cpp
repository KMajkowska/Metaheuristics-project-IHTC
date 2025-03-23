#include "PeerToPeer.h"

PeerToPeer::PeerToPeer(const std::string& ip, short sendPort, short receivePort, bool isHost) :
    _isHost(isHost),
    _ioContext(),
    _work_guard(boost::asio::make_work_guard(_ioContext)),
    _socket(_ioContext),
    _acceptor(_ioContext),
    _connected(false),
    _ip(ip),
    _sendPort(sendPort),
    _receivePort(receivePort)
{}

void PeerToPeer::start()
{
    // Run io_context in a separate thread
    std::thread([this]() 
        {
        _ioContext.run();
        }).detach();

    if (_isHost)
    {
        listenForConnections();
    }
    else
    {
        tryConnect();
    }
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

    _socket.async_connect(endpoint, [this](const boost::system::error_code& error) 
        {
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
