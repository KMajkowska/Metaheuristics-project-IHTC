#include <iostream>

#include "params.h"
#include "ProblemData.h"
#include "CGameComputer.h"
#include "CPlayer.h"
#include "BestOfN.h"
#include "PeerToPeer.h"
#include "CGameNetwork.h"
#include "CSessionReceiverPeerToPeer.h"
#include "CSessionPosterPeerToPeer.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	MainWindow mainWindow;
	
	mainWindow.resize(1100, 800);
	mainWindow.show();
	
	return app.exec();
}
