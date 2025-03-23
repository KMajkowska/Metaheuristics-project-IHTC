#pragma once

#include <thread>
#include <boost/asio.hpp>

#include "CObservable.h"
#include "constants.h"
#include "JSONOperations.h"
#include "CGameInfo.h"
\
/**
 * @brief Class used as a receiver for creating sessions of the game using peer to peer
 */
class CSessionReceiverPeerToPeer : public CObservable<CGameInfo>
{
public:
	CSessionReceiverPeerToPeer();
	~CSessionReceiverPeerToPeer();
	void checkForSessions();

	void stopChecking();

protected:
	std::atomic<bool> _broadcast;  /// Tell the object to keep boradcasting (until this flag is false).
	std::thread _receiverThread;
	boost::asio::io_context _ioContext;
	boost::asio::ip::udp::socket _socket;

	void startReceivingBroadcast();
	void receiveBroadcast();
};