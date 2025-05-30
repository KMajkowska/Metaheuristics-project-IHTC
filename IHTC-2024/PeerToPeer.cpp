#include "PeerToPeer.h"

PeerToPeer::PeerToPeer(boost::asio::io_context& context, const std::string& ip, int port, bool isHost) :
	_isHost(isHost),
	_socket(context),
	_acceptor(context),
	_connected(false),
	_ip(ip),
	_port(port),
	_retryTimer(context)
{}

PeerToPeer::~PeerToPeer()
{
	tellEndOfTransmission();
	disconnect();
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
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(_ip), _port);

	_acceptor.open(endpoint.protocol());
	_acceptor.set_option(boost::asio::socket_base::reuse_address(true));
	_acceptor.bind(endpoint);
	_acceptor.listen();

	_acceptor.async_accept(
		_socket,
		[this](const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "Failed to accept connection: " << error.message() << std::endl;
				return;
			}

			onSuccesfullConnect();

		});
}


void PeerToPeer::tryConnect()
{
	if (_attemptCount >= MAX_ATTEMPTS)
	{
		return;
	}

	_attemptCount++;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(_ip), _port);

	_socket.open(endpoint.protocol());

	_socket.async_connect(
		endpoint,
		[this](const boost::system::error_code& error)
		{
			if (!error)
			{
				onSuccesfullConnect();
				return;
			}

			_retryTimer.expires_after(std::chrono::milliseconds(_currentRetryDelay));
			_retryTimer.async_wait([this](const boost::system::error_code& timer_error)
				{
					if (!timer_error && !_connected)
					{
						_currentRetryDelay = std::min(_currentRetryDelay * 2, MAX_RETRY_DELAY);
						tryConnect();
					}
				});

		});
}

void PeerToPeer::onSuccesfullConnect()
{
	_connected = true;
	receiveMessage();

	if (_onConnect)
	{
		_onConnect();
	}
}

void PeerToPeer::sendMessage(std::string message)
{
	if (!_connected || !_socket.is_open())
	{
		return;
	}

	if (!message.empty() && message.back() != '\n')
	{
		message += '\n';
	}

	auto message_ptr = std::make_shared<std::string>(std::move(message));

	boost::asio::async_write(
		_socket,
		boost::asio::buffer(*message_ptr),
		[message_ptr](const boost::system::error_code& error, std::size_t bytes_transferred)
		{
			if (error)
			{
				std::cerr << "Error while sending message: " << error.message() << std::endl;
			}
		});
}

void PeerToPeer::receiveMessage()
{
	if (!_connected)
	{
		return;
	}

	boost::asio::async_read_until(
		_socket,
		_receiveBuffer,
		'\n',
		[this](boost::system::error_code error, std::size_t bytes_transferred)
		{
			if (error)
			{
				disconnect();
				return;
			}

			std::istream is(&_receiveBuffer);
			std::string message;
			std::getline(is, message);

			if (message == END_OF_TRANSMISSION)
			{
				if (_onEndTransmission)
				{
					_onEndTransmission();
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
		});
}

void PeerToPeer::disconnect()
{
	if (_connected)
	{
		return;
	}

	_connected = false;

	boost::system::error_code error;
	_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
	_socket.close(error);

	if (error)
	{
		std::cerr << "Error during disconnect: " << error.message() << std::endl;
	}
}

void PeerToPeer::tellEndOfTransmission()
{
	sendMessage(END_OF_TRANSMISSION);
}