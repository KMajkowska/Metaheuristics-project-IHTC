#include "waitingScreen.h"

Ui_waitingScreen::Ui_waitingScreen(QWidget* parent) : 
    QWidget(parent)
{
    _centralwidget = new QWidget(this);
    _loadingCircleLabel = new QLabel(_centralwidget);
    _loadingCircleMovie = new QMovie("./loading_circle.gif");
    _font = new QFont();
    _layout = new QVBoxLayout(_centralwidget);

    setupUi(this);
}

Ui_waitingScreen::~Ui_waitingScreen() = default;

void Ui_waitingScreen::setUpLoadingCircle()
{
    _loadingCircleLabel->setMovie(_loadingCircleMovie);
    _loadingCircleLabel->setAlignment(Qt::AlignHCenter); 
    _loadingCircleMovie->start();
    _layout->addWidget(_loadingCircleLabel, 0, Qt::AlignHCenter);
}

QFont Ui_waitingScreen::setUpFont(int points)
{
    _font->setPointSize(points);
    return *_font;
}

void Ui_waitingScreen::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    _centralwidget->setObjectName("centralwidget");

    setUpWaitingForPlayerLabel();
    setUpLoadingCircle();

    MainWindow->setLayout(_layout);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_waitingScreen::setUpWaitingForPlayerLabel()
{
    _waitingForPlayerLabel = new QLabel(_centralwidget);
    _waitingForPlayerLabel->setObjectName("waitingForPlayerLabel");
    _waitingForPlayerLabel->setFont(setUpFont(MAIN_TEXT_FONT));
    _layout->addWidget(_waitingForPlayerLabel, 0, Qt::AlignHCenter);
}

void Ui_waitingScreen::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    _waitingForPlayerLabel->setText(QCoreApplication::translate("MainWindow", "Waiting for other player to join", nullptr));
}