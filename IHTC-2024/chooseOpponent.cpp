#include "chooseOpponent.h"
#include <gamePlotScreen.h>

Ui_chooseOpponent::Ui_chooseOpponent(QWidget* parent) :
	QWidget(parent)
{
	_centralwidget = new QWidget(this);
	_chooseOpponentLabel = new QLabel(_centralwidget);
	_computerButton = new QPushButton(_centralwidget);
	_playerButton = new QPushButton(_centralwidget);
	_font = new QFont();
	_mainLayout = new QVBoxLayout(_centralwidget);
	_buttonLayout = new QHBoxLayout(_centralwidget);

	connect(_computerButton, &QPushButton::clicked, this, &Ui_chooseOpponent::onComputerButtonClicked);
	connect(_playerButton, &QPushButton::clicked, this, &Ui_chooseOpponent::onPlayerButtonClicked);

	setupUi(this);
}

Ui_chooseOpponent::~Ui_chooseOpponent() = default;

void Ui_chooseOpponent::setupUi(QWidget* MainWindow)
{
	if (MainWindow->objectName().isEmpty())
		MainWindow->setObjectName("MainWindow");

	_centralwidget->setObjectName("centralwidget");

	setUpChooseOpponentLabel();
	setUpCompterButton();
	setUpPlayerButton();

	_mainLayout->addLayout(_buttonLayout);

	MainWindow->setLayout(_mainLayout);
	retranslateUi(MainWindow);

	QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_chooseOpponent::setUpChooseOpponentLabel()
{
	_chooseOpponentLabel->setObjectName("chooseOpponentLabel");
	_chooseOpponentLabel->setFont(setUpFont(MAIN_TEXT_FONT));
	_mainLayout->addWidget(_chooseOpponentLabel, 0, Qt::AlignHCenter);
}

void Ui_chooseOpponent::setUpCompterButton()
{
	_computerButton->setObjectName("computerButton");
	_computerButton->setFixedSize(171, 81);
	_computerButton->setStyleSheet("background-color: pink; color: black");
	_computerButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	_buttonLayout->addWidget(_computerButton, 0, Qt::AlignCenter);
}

void Ui_chooseOpponent::setUpPlayerButton()
{
	_playerButton->setObjectName("playerButton");
	_playerButton->setFixedSize(171, 81);
	_playerButton->setStyleSheet("background-color: pink; color: black");
	_playerButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	_buttonLayout->addWidget(_playerButton, 0, Qt::AlignCenter);
}

QFont Ui_chooseOpponent::setUpFont(int points)
{
	_font->setPointSize(points);
	return *_font;
}

void Ui_chooseOpponent::retranslateUi(QWidget* MainWindow)
{
	MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose opponent", nullptr));
	_chooseOpponentLabel->setText(QCoreApplication::translate("MainWindow", "Choose your opponent", nullptr));
	_computerButton->setText(QCoreApplication::translate("MainWindow", "Computer", nullptr));
	_playerButton->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
}

void Ui_chooseOpponent::onComputerButtonClicked()
{
	StateController::instance().setStartGame([]() 
		{
			StateController::instance().navigate(ScreensNumber::PLOT_SCREEN);
			StateController::instance().runComputer(
				[](std::shared_ptr<ICGame> game)
				{
					static_cast<Ui_gamePlotScreen*>(StateController::instance().screens()[ScreensNumber::PLOT_SCREEN])->connectPlot(game);
					StateController::instance().navigate(ScreensNumber::PLOT_SCREEN);
				},
				[](Winner winner)
				{

					StateController::instance().navigate(ScreensNumber::END_GAME_SCREEN);
					
				},
				StateController::instance().allGameParameters());
		});

	StateController::instance().navigate(ScreensNumber::GAME_PARAMETERS);
}

// default is session start!
void Ui_chooseOpponent::onPlayerButtonClicked()
{
	StateController::instance().setStartGame([]()
		{
			StateController::instance().navigate(ScreensNumber::WAITING_SCREEN);
			StateController::instance().createSession(
				[](std::shared_ptr<ICGame> game)
				{
					static_cast<Ui_gamePlotScreen*>(StateController::instance().screens()[ScreensNumber::PLOT_SCREEN])->connectPlot(game);
					StateController::instance().navigate(ScreensNumber::PLOT_SCREEN);
				},
				[](Winner winner) 
				{
					StateController::instance().navigate(ScreensNumber::END_GAME_SCREEN);
				},
				StateController::instance().allGameParameters());
		});

	StateController::instance().navigate(ScreensNumber::SESSIONS);
}