#include "endGame.h"

Ui_endGameScreen::Ui_endGameScreen(QWidget* parent) : 
    QWidget(parent)
{
	_centralWidget = new QWidget(this);
    _font = new QFont();
    _endButton = new QPushButton(_centralWidget);
    _returnButton = new QPushButton(_centralWidget);
    _mainLayout = new QVBoxLayout(_centralWidget);
    _gameResultLabel = new QLabel(_centralWidget);
    _buttonLayout = new QHBoxLayout(_centralWidget);

    setupUi(this);
}

Ui_endGameScreen::~Ui_endGameScreen() = default;

void Ui_endGameScreen::setupUi(QWidget* mainWindow)
{
    if (mainWindow->objectName().isEmpty())
    {
        mainWindow->setObjectName("MainWindow");
    }

    _centralWidget->setParent(mainWindow);
    _centralWidget->setObjectName("centralwidget");

    setUpGameResultLabel();
    setUpReturnButton();
    setUpEndButton();

    _mainLayout->addLayout(_buttonLayout);

    mainWindow->setLayout(_mainLayout);

    connect(_returnButton, &QPushButton::clicked, this, &Ui_endGameScreen::onReturnButtonClicked);
    connect(_endButton, &QPushButton::clicked, this, &QApplication::quit);

    retranslateUi(this);
}

void Ui_endGameScreen::retranslateUi(QWidget* mainWindow)
{
    mainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Your result", nullptr));
    _gameResultLabel->setText(QCoreApplication::translate("MainWindow", "You", nullptr));
    _endButton->setText(QCoreApplication::translate("MainWindow", "End game and close app", nullptr));
    _returnButton->setText(QCoreApplication::translate("MainWindow", "Return to choose opponent", nullptr));
}

void Ui_endGameScreen::setUpEndButton()
{
    _endButton->setObjectName("endButton");
    _endButton->setFixedSize(400, 100);
    _endButton->setStyleSheet("background-color: pink; color: black");
    _endButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _buttonLayout->addWidget(_endButton, 0, Qt::AlignHCenter);
}

QFont Ui_endGameScreen::setUpFont(int points)
{
    _font->setPointSize(points);
    return *_font;
}

void Ui_endGameScreen::setUpReturnButton()
{
    _returnButton->setObjectName("returnButton");
    _returnButton->setFixedSize(400, 100);
    _returnButton->setStyleSheet("background-color: pink; color: black");
    _returnButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _buttonLayout->addWidget(_returnButton, 0, Qt::AlignHCenter);
}

void Ui_endGameScreen::setUpGameResultLabel()
{
    _gameResultLabel->setObjectName("gameResultLabel");
    _gameResultLabel->setFont(setUpFont(MAIN_TEXT_FONT));
    _mainLayout->addWidget(_gameResultLabel, 0, Qt::AlignCenter);
}

void Ui_endGameScreen::onReturnButtonClicked()
{
    StateController::instance().navigate(ScreensNumber::CHOOSE_OPPONENT);
}
