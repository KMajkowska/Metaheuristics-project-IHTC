#include "CSessionReceiverPeerToPeer.h"

CSessionReceiverPeerToPeer::CSessionReceiverPeerToPeer(boost::asio::io_context& context) :
	_socket(context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), SESSION_PEER_TO_PEER_PORT)),
	_broadcast(false)
{
	_socket.non_blocking(true);
}

CSessionReceiverPeerToPeer::~CSessionReceiverPeerToPeer()
{
	stopChecking();
}

void CSessionReceiverPeerToPeer::startReceivingBroadcast()
{
	_broadcast = true;
	receiveBroadcast();
}

void CSessionReceiverPeerToPeer::receiveBroadcast()
{
    std::vector<char> receiveBuffer(2048);
    boost::asio::ip::udp::endpoint senderEndpoint;

    while (_broadcast)
    {
        std::cout << "RECEIVE" << std::endl;

        boost::system::error_code ec;
        size_t length = _socket.receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint, 0, ec);

        if (ec == boost::asio::error::would_block)
        {
            // No data received, just continue checking
            continue;  // Skip this iteration and continue checking for new data
        }
        else if (ec)
        {
            // Handle other errors
            std::cerr << "Error receiving data: " << ec.message() << std::endl;
            break;
        }

        // If data is received, process it
        std::string message(receiveBuffer.begin(), receiveBuffer.begin() + length);
        std::cout << message << std::endl;

        auto parsed{ nlohmann::json::parse(message) };
        auto gameInfoOpt{ jsonToObject<CGameInfo>(parsed) };

        if (gameInfoOpt)
        {
            notify(gameInfoOpt.value());
        }
    }
}

void CSessionReceiverPeerToPeer::checkForSessions()
{
    startReceivingBroadcast();
}

void CSessionReceiverPeerToPeer::stopChecking()
{
	_broadcast = false;
	_socket.cancel();
}
