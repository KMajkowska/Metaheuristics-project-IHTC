#include "welcomeScreen.h"

Ui_welcomeScreen::Ui_welcomeScreen(QWidget* parent) : 
    QWidget(parent)
{
    _centralwidget = new QWidget(this);
    _welcomeText = new QLabel(_centralwidget);
    _startGameButton = new QPushButton(_centralwidget);
    _nameTextfield = new QLineEdit(_centralwidget);
    _mainLayout = new QVBoxLayout(_centralwidget);
    _font = new QFont();

    connect(_startGameButton, &QPushButton::clicked, this, &Ui_welcomeScreen::openChooseOpponentScreen);
    connect(_nameTextfield, &QLineEdit::textChanged, this, &Ui_welcomeScreen::updateButtonState);

    setupUi(this);
}

Ui_welcomeScreen::~Ui_welcomeScreen() 
{
    delete _centralwidget;
}

void Ui_welcomeScreen::setupUi(QWidget* welcomeScreen)
{
    if (welcomeScreen->objectName().isEmpty()) 
    {
        welcomeScreen->setObjectName("welcomeScreen");
    }

    welcomeScreen->setMouseTracking(false);

    _centralwidget->setObjectName("centralwidget");

    setUpWelcomeText();
    setUpNameTextfield();
    setUpStartGameButton();

    welcomeScreen->setLayout(_mainLayout);
    retranslateUi(welcomeScreen);

    QMetaObject::connectSlotsByName(welcomeScreen);
}

void Ui_welcomeScreen::setUpNameTextfield()
{
    _nameTextfield->setObjectName("nameTextfield");
    _nameTextfield->setFixedHeight(70);
    _nameTextfield->setFixedWidth(400);
    _nameTextfield->setStyleSheet("background-color: pink; color: black");
    _nameTextfield->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _mainLayout->addWidget(_nameTextfield, 0, Qt::AlignCenter);
}

void Ui_welcomeScreen::setUpWelcomeText()
{
    _welcomeText->setObjectName("welcomeText");
    _welcomeText->setFont(setUpFont(MAIN_TEXT_FONT));
    _mainLayout->addWidget(_welcomeText, 0, Qt::AlignHCenter);
}

void Ui_welcomeScreen::setUpStartGameButton()
{
    _startGameButton->setObjectName("startGameButton");
    _startGameButton->setFixedSize(200, 100);
    _startGameButton->setStyleSheet("background-color: pink; color: black");
    _startGameButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _startGameButton->setEnabled(false);
    _mainLayout->addWidget(_startGameButton, 0, Qt::AlignCenter);
}

QFont Ui_welcomeScreen::setUpFont(int points)
{
    _font->setPointSize(points);
    return *_font;
}

void Ui_welcomeScreen::retranslateUi(QWidget* welcomeScreen)
{
    welcomeScreen->setWindowTitle(QCoreApplication::translate("welcomeScreen", "Welcome!", nullptr));
    _nameTextfield->setPlaceholderText(QCoreApplication::translate("welcomeScreen", "Insert your name", nullptr));
    _welcomeText->setText(QCoreApplication::translate("welcomeScreen", "Welcome in our metaheuristic game!", nullptr));
    _startGameButton->setText(QCoreApplication::translate("startGameButton", "Start", nullptr));
}

void Ui_welcomeScreen::openChooseOpponentScreen()
{
    StateController::instance().allGameParameters().setName(_nameTextfield->text().toStdString());
    StateController::instance().navigate(ScreensNumber::CHOOSE_OPPONENT);
}

void Ui_welcomeScreen::updateButtonState()
{
    _startGameButton->setEnabled(!_nameTextfield->text().isEmpty());
}