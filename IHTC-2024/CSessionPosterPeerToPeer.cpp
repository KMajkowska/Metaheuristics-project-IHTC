#include "CSessionPosterPeerToPeer.h"

CSessionPosterPeerToPeer::CSessionPosterPeerToPeer(boost::asio::io_context& context, const CGameInfo& gameInfo) :
	_socket(context),
	_gameInfo(gameInfo),
	_context(context),
	_endpoint(boost::asio::ip::address_v4::broadcast(), SESSION_PEER_TO_PEER_PORT),
	_broadcast(false)
{
	_socket.open(boost::asio::ip::udp::v4());
	_socket.set_option(boost::asio::socket_base::broadcast(true));
	_socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));

	auto gameInfoJsonOpt { objectToJson<CGameInfo>(_gameInfo) };

	if (!gameInfoJsonOpt)
	{
		throw std::invalid_argument("Game info couldn't be posted");
	}

	_message = std::move(gameInfoJsonOpt.value());
}

CSessionPosterPeerToPeer::~CSessionPosterPeerToPeer()
{
	stopBroadcast();
}

void CSessionPosterPeerToPeer::postSession()
{
	_broadcast = true;
	broadcastSession();
}

void CSessionPosterPeerToPeer::broadcastSession()
{
	_socket.async_send_to(
		boost::asio::buffer(_message),
		_endpoint,
		[this](boost::system::error_code ec, std::size_t bytes_transferred)
		{
			if (!ec)
			{
				if (_broadcast)
				{
					auto timer = std::make_shared<boost::asio::steady_timer>(_context, std::chrono::seconds(BROADCAST_SESSION_TIMEOUT));

					timer->async_wait([this, timer](const boost::system::error_code& ec)
						{
							if (!ec && _broadcast)
							{
								broadcastSession();  // Recursively call to send the message again
							}
						});
				}
			}
			else
			{
				std::cerr << "Error sending session: " << ec.message() << std::endl;
			}
		});
}

void CSessionPosterPeerToPeer::stopBroadcast()
{	
	_broadcast = false;
	_socket.cancel();
}
