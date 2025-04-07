#include "chooseOpponent.h"

Ui_chooseOpponent::Ui_chooseOpponent(QStackedWidget* stackedWidget, QWidget* parent, std::shared_ptr<AllGameParameters> allGameParameters) : 
    QWidget(parent), 
    stackedWidget(stackedWidget), 
    allGameParameters(allGameParameters)
{
    centralwidget = new QWidget(this);
    chooseOpponentLabel = new QLabel(centralwidget);
    computerButton = new QPushButton(centralwidget);
    playerButton = new QPushButton(centralwidget);
    font = new QFont();
    mainLayout = new QVBoxLayout(centralwidget);
    buttonLayout = new QHBoxLayout(centralwidget);

    connect(computerButton, &QPushButton::clicked, this, &Ui_chooseOpponent::onComputerButtonClicked);
    connect(playerButton, &QPushButton::clicked, this, &Ui_chooseOpponent::onPlayerButtonClicked);

    setupUi(this);
}

Ui_chooseOpponent::~Ui_chooseOpponent() {

}

void Ui_chooseOpponent::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    centralwidget->setObjectName("centralwidget");

    setUpChooseOpponentLabel();
    setUpCompterButton();
    setUpPlayerButton();

    mainLayout->addLayout(buttonLayout);

    MainWindow->setLayout(mainLayout);
    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_chooseOpponent::setUpChooseOpponentLabel()
{
    chooseOpponentLabel->setObjectName("chooseOpponentLabel");
    chooseOpponentLabel->setFont(setUpFont(MAIN_TEXT_FONT));
    mainLayout->addWidget(chooseOpponentLabel, 0, Qt::AlignHCenter);
}

void Ui_chooseOpponent::setUpCompterButton()
{
    computerButton->setObjectName("computerButton");
    computerButton->setFixedSize(171, 81); 
    computerButton->setStyleSheet("background-color: pink; color: black");
    computerButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(computerButton, 0, Qt::AlignCenter);
}

void Ui_chooseOpponent::setUpPlayerButton()
{
    playerButton->setObjectName("playerButton");
    playerButton->setFixedSize(171, 81); 
    playerButton->setStyleSheet("background-color: pink; color: black");
    playerButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(playerButton, 0, Qt::AlignCenter);
}

QFont Ui_chooseOpponent::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_chooseOpponent::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose opponent", nullptr));
    chooseOpponentLabel->setText(QCoreApplication::translate("MainWindow", "Choose your opponent", nullptr));
    computerButton->setText(QCoreApplication::translate("MainWindow", "Computer", nullptr));
    playerButton->setText(QCoreApplication::translate("MainWindow", "Player", nullptr));
}

void Ui_chooseOpponent::onComputerButtonClicked()
{
    allGameParameters->setIsPlayerOpponent(false);
    stackedWidget->setCurrentIndex(static_cast<int>(ScreensNumber::GAME_PARAMETERS));
}

void Ui_chooseOpponent::onPlayerButtonClicked()
{
    allGameParameters->setIsPlayerOpponent(true);
    stackedWidget->setCurrentIndex(static_cast<int>(ScreensNumber::SESSIONS));
}