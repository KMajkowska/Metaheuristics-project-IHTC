#include "PeerToPeer.h"

PeerToPeer::PeerToPeer(boost::asio::io_context& context, const std::string& ip, short sendPort, short receivePort, bool isHost) :
	_isHost(isHost),
	_sendSocket(context),
	_receiveSocket(context),
	_acceptor(context),
	_connected(false),
	_ip(ip),
	_sendPort(sendPort),
	_receivePort(receivePort)
{
	std::cout << "PeerToPeer initialized with IP: " << _ip << ", SendPort: " << _sendPort << ", ReceivePort: " << _receivePort << ", isHost: " << _isHost << std::endl;
}

void PeerToPeer::start()
{
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

	std::cout << "Start listening on " << _ip << ":" << _receivePort << std::endl;

	_acceptor.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket)
		{
			if (!error)
			{
				_receiveSocket = std::move(socket);  // Move the accepted socket
				_connected = true;
				std::cout << "Incoming connection accepted on port " << _receivePort << std::endl;

				std::cout << "Is socket open? " << _receiveSocket.is_open() << std::endl;

				receiveMessage();

				if (_isHost)
				{
					tryConnect();
				}
				else
				{
					_onConnect();
				}
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

	std::cout << "Try connecting on " << _ip << ":" << _sendPort << std::endl;

	if (_sendSocket.is_open())
	{
		_sendSocket.close();
	}

	_sendSocket.open(endpoint.protocol());

	_sendSocket.async_connect(endpoint, [this](const boost::system::error_code& error)
		{
			if (!error)
			{
				_connected = true;
				std::cout << "Connected on port " << _sendPort << std::endl;

				if (!_isHost)
				{
					listenForConnections();
				}
				else 
				{
					_onConnect();
				}
			}
			else
			{
				std::cout << "Connection failed: " << error.message() << std::endl;
			}
		});
}

void PeerToPeer::sendMessage(const std::string& message)
{
	if (!_connected)
	{
		return;
	}

	if (!_sendSocket.is_open()) // Ensure socket is open before writing
	{
		std::cout << "Socket is not open. Cannot send message." << std::endl;
		return;
	}

	auto message_ptr = std::make_shared<std::string>(std::move(message + '\n'));

	boost::asio::async_write(
		_sendSocket,
		boost::asio::buffer(*message_ptr),
		[message_ptr](const boost::system::error_code& error, std::size_t bytes_transferred)
		{
			if (!error)
			{
				std::cout << "Message sent." << std::endl;
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
		_receiveSocket,
		_receiveBuffer, // boost::asio::streambuf instead of fixed-size buffer
		'\n',
		[this](boost::system::error_code error, std::size_t bytes_transferred)
		{
			if (!error)
			{
				std::cout << "Message received." << std::endl;

				std::istream is(&_receiveBuffer);
				std::string message;
				std::getline(is, message); // Read until newline

				if (message == END_OF_TRANSMISSION)
				{
					if (_onClose)
					{
						_onClose();
					}
				}
				else
				{
					notify(message);
				}


				// Continue reading next messages
				if (_connected)
				{
					receiveMessage();
				}
			}
			else
			{
				if (error == boost::asio::error::eof) {
					std::cout << "Connection closed by peer. Exiting function." << std::endl;

					if (_onClose)
					{
						_onClose();
					}

					return;
				}
				else if (error)
				{
					throw boost::system::system_error(error);
				}
			}
		});
}

void PeerToPeer::tellEndOfTransmission()
{
	sendMessage(END_OF_TRANSMISSION);
}