#include "welcomeScreen.h"

Ui_welcomeScreen::Ui_welcomeScreen(QWidget* parent) : 
    QWidget(parent)
{
    centralwidget = new QWidget(this);
    welcomeText = new QLabel(centralwidget);
    startGameButton = new QPushButton(centralwidget);
    nameTextfield = new QLineEdit(centralwidget);
    mainLayout = new QVBoxLayout(centralwidget);
    font = new QFont();

    connect(startGameButton, &QPushButton::clicked, this, &Ui_welcomeScreen::openChooseOpponentScreen);
    connect(nameTextfield, &QLineEdit::textChanged, this, &Ui_welcomeScreen::updateButtonState);

    setupUi(this);
}

Ui_welcomeScreen::~Ui_welcomeScreen() {
    delete centralwidget;
}

void Ui_welcomeScreen::setupUi(QWidget* welcomeScreen)
{
    if (welcomeScreen->objectName().isEmpty())
        welcomeScreen->setObjectName("welcomeScreen");

    welcomeScreen->setMouseTracking(false);

    centralwidget->setObjectName("centralwidget");

    setUpWelcomeText();
    setUpNameTextfield();
    setUpStartGameButton();

    welcomeScreen->setLayout(mainLayout);
    retranslateUi(welcomeScreen);

    QMetaObject::connectSlotsByName(welcomeScreen);
}

void Ui_welcomeScreen::setUpNameTextfield()
{
    nameTextfield->setObjectName("nameTextfield");
    nameTextfield->setFixedHeight(70);
    nameTextfield->setFixedWidth(400);
    nameTextfield->setStyleSheet("background-color: pink; color: black");
    nameTextfield->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    mainLayout->addWidget(nameTextfield, 0, Qt::AlignCenter);
}

void Ui_welcomeScreen::setUpWelcomeText()
{
    welcomeText->setObjectName("welcomeText");
    welcomeText->setFont(setUpFont(MAIN_TEXT_FONT));
    mainLayout->addWidget(welcomeText, 0, Qt::AlignHCenter);
}

void Ui_welcomeScreen::setUpStartGameButton()
{
    startGameButton->setObjectName("startGameButton");
    startGameButton->setFixedSize(200, 100);
    startGameButton->setStyleSheet("background-color: pink; color: black");
    startGameButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    startGameButton->setEnabled(false);
    mainLayout->addWidget(startGameButton, 0, Qt::AlignCenter);
}

QFont Ui_welcomeScreen::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_welcomeScreen::retranslateUi(QWidget* welcomeScreen)
{
    welcomeScreen->setWindowTitle(QCoreApplication::translate("welcomeScreen", "Welcome!", nullptr));
    nameTextfield->setPlaceholderText(QCoreApplication::translate("welcomeScreen", "Insert your name", nullptr));
    welcomeText->setText(QCoreApplication::translate("welcomeScreen", "Welcome in our metaheuristic game!", nullptr));
    startGameButton->setText(QCoreApplication::translate("startGameButton", "Start", nullptr));
}

void Ui_welcomeScreen::openChooseOpponentScreen()
{
    StateController::instance().allGameParameters().setName(nameTextfield->text().toStdString());
    StateController::instance().navigate(ScreensNumber::CHOOSE_OPPONENT);
}

void Ui_welcomeScreen::updateButtonState()
{
    startGameButton->setEnabled(!nameTextfield->text().isEmpty());
}