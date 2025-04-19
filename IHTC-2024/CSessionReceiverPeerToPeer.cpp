#include "CSessionReceiverPeerToPeer.h"

CSessionReceiverPeerToPeer::CSessionReceiverPeerToPeer(boost::asio::io_context& context) :
	_socket(context),
	_broadcast(false),
	_receiveBuffer(65507)
{
	boost::asio::ip::udp::endpoint listen_endpoint(boost::asio::ip::udp::v4(), SESSION_PEER_TO_PEER_PORT);

	_socket.open(boost::asio::ip::udp::v4());
	_socket.set_option(boost::asio::socket_base::reuse_address(true));
	_socket.set_option(boost::asio::socket_base::broadcast(true));
	_socket.bind(listen_endpoint);
}

CSessionReceiverPeerToPeer::~CSessionReceiverPeerToPeer()
{
	stopChecking();
}

void CSessionReceiverPeerToPeer::receiveBroadcast()
{
	if (!_broadcast)
	{
		return;
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
				std::cout << "Received from " << _senderEndpoint.address().to_string()
					<< ":" << _senderEndpoint.port() << " => " << message << std::endl;

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
	_socket.cancel();
}
