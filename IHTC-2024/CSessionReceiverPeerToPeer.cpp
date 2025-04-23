#include "CSessionReceiverPeerToPeer.h"

CSessionReceiverPeerToPeer::CSessionReceiverPeerToPeer(boost::asio::io_context& context) :
	_socket(context),
	_socketInitialized(false),
	_broadcast(false),
	_receiveBuffer(65507)
{}

CSessionReceiverPeerToPeer::~CSessionReceiverPeerToPeer()
{
	stopChecking();
}

void CSessionReceiverPeerToPeer::initializeSocket()
{
	if (_socketInitialized)
	{
		return;
	}

	boost::asio::ip::udp::endpoint listenEndpoint(boost::asio::ip::udp::v4(), SESSION_PEER_TO_PEER_PORT);

	boost::system::error_code ec;
	_socket.open(boost::asio::ip::udp::v4(), ec);
	if (ec) 
	{
		std::cerr << "Socket open error: " << ec.message() << std::endl;
		return;
	}

	_socket.set_option(boost::asio::socket_base::reuse_address(true), ec);
	_socket.set_option(boost::asio::socket_base::broadcast(true), ec);
	_socket.bind(listenEndpoint, ec);

	if (ec) 
	{
		std::cerr << "Socket bind error: " << ec.message() << std::endl;
		_socket.close();
		return;
	}

	_socketInitialized = true;
}

void CSessionReceiverPeerToPeer::receiveBroadcast()
{
	if (!_broadcast)
	{
		return;
	}

	if (!_socketInitialized)
	{
		initializeSocket();

		if (!_socketInitialized) 
		{
			return;
		}
	}

	_socket.async_receive_from(
		boost::asio::buffer(_receiveBuffer),
		_senderEndpoint,
		[this](boost::system::error_code ec, std::size_t bytes_recvd)
		{
			if (!_broadcast)
			{
				return;
			}

			if (!ec && bytes_recvd > 0)
			{

				std::string message(_receiveBuffer.begin(), _receiveBuffer.begin() + bytes_recvd);

				try
				{
					auto parsed = nlohmann::json::parse(message);
					auto gameInfoOpt = jsonToObject<CGameInfo>(parsed);

					if (gameInfoOpt)
					{
						notify(gameInfoOpt.value());
					}
				}
				catch (const std::exception& e)
				{
					std::cerr << "JSON parsing error: " << e.what() << std::endl;
				}
			}
			else if (ec)
			{
				if (ec == boost::asio::error::operation_aborted)
				{
					// socket was canceled; normal shutdown
					return;
				}
				std::cerr << "Receive error: " << ec.message() << std::endl;
			}

			// Continue listening
			receiveBroadcast();
		});
}

void CSessionReceiverPeerToPeer::checkForSessions()
{
	_broadcast = true;
	receiveBroadcast();
}

void CSessionReceiverPeerToPeer::stopChecking()
{
	_broadcast = false;
	boost::system::error_code ec;
	_socket.cancel(ec);
	_socket.close(ec);
	_socketInitialized = false;
}
