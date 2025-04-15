#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon("uniqrn.png"));

    _stackedWidget = new QStackedWidget(this);

	auto welcomeScreen = new Ui_welcomeScreen(this);
	auto chooseOpponentScreen = new Ui_chooseOpponent(this);
	auto metahParameters = new Ui_metahParameters(this);
	auto gameParameters = new Ui_gameParameters(this);
	auto sessions = new Ui_sessions(this);
	auto waitingScreen = new Ui_waitingScreen(this);

	_stackedWidget->addWidget(welcomeScreen);
	_stackedWidget->addWidget(chooseOpponentScreen);
	_stackedWidget->addWidget(gameParameters);
	_stackedWidget->addWidget(metahParameters);
	_stackedWidget->addWidget(sessions);
	_stackedWidget->addWidget(waitingScreen);

	StateController::instance().addScreen(ScreensNumber::WELCOME_SCREEN, welcomeScreen);
	StateController::instance().addScreen(ScreensNumber::CHOOSE_OPPONENT, chooseOpponentScreen);
	StateController::instance().addScreen(ScreensNumber::GAME_PARAMETERS, gameParameters);
	StateController::instance().addScreen(ScreensNumber::METAH_PARAMETERS, metahParameters);
	StateController::instance().addScreen(ScreensNumber::SESSIONS, sessions);
	StateController::instance().addScreen(ScreensNumber::WAITING_SCREEN, waitingScreen);

	StateController::instance().setNavigate([&](ScreensNumber screen)
		{
			_stackedWidget->setCurrentIndex(static_cast<int>(screen));
		});

	setCentralWidget(_stackedWidget);
	_stackedWidget->showMaximized();
	_stackedWidget->setCurrentIndex(static_cast<int>(ScreensNumber::WELCOME_SCREEN));
}

MainWindow::~MainWindow()
{
    delete _stackedWidget;
}
