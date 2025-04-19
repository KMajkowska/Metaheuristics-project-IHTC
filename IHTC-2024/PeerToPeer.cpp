#include "PeerToPeer.h"

PeerToPeer::PeerToPeer(boost::asio::io_context& context, const std::string& ip, int sendPort, int receivePort, bool isHost) :
	_isHost(isHost),
	_sendSocket(context),
	_receiveSocket(context),
	_acceptor(context),
	_connected(false),
	_ip(ip),
	_sendPort(sendPort),
	_receivePort(receivePort),
	_retryTimer(context)
{}

PeerToPeer::~PeerToPeer()
{
	if (_connected)
	{
		tellEndOfTransmission();
	}

	_sendSocket.close();
	_receiveSocket.close();
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

	_acceptor.async_accept(
		_receiveSocket,
		[this](const boost::system::error_code& error)
		{
			if (!error)
			{
				receiveMessage();

				if (_isHost)
				{
					tryConnect();
				}
				else
				{
					_connected = true;
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
	if (_attemptCount >= MAX_ATTEMPTS)
	{
		return;
	}

	_attemptCount++;

	if (_sendSocket.is_open())
	{
		_sendSocket.close();
	}

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(_ip), _sendPort);

	_sendSocket.open(endpoint.protocol());

	_sendSocket.async_connect(
		endpoint, 
		[this](const boost::system::error_code& error)
		{
			if (!error)
			{

				if (!_isHost)
				{
					listenForConnections();
				}
				else 
				{
					_connected = true;
					_onConnect();
				}
			}
			else
			{
					_retryTimer.expires_after(std::chrono::milliseconds(_currentRetryDelay));
				_retryTimer.async_wait([this](const boost::system::error_code& timer_error)
					{
						if (!timer_error && !_connected)
						{
							_currentRetryDelay = std::min(_currentRetryDelay * 2, MAX_RETRY_DELAY);
							tryConnect();
						}
					});
			}
		});
}

void PeerToPeer::sendMessage(std::string message)
{
	if (!_connected || !_sendSocket.is_open())
	{
		return;
	}

	if (!message.empty() && message.back() != '\n')
	{
		message += '\n';
	}

	auto message_ptr = std::make_shared<std::string>(std::move(message));

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
		_receiveBuffer,
		'\n',
		[this](boost::system::error_code error, std::size_t bytes_transferred)
		{
			if (!error)
			{
				std::cout << "Message received." << std::endl;

				std::istream is(&_receiveBuffer);
				std::string message;
				std::getline(is, message);

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

				if (_connected)
				{
					receiveMessage();
				}
			}
			else
			{
				if (error == boost::asio::error::eof) {
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