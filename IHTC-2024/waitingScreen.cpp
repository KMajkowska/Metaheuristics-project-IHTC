#include "waitingScreen.h"

Ui_waitingScreen::Ui_waitingScreen(QStackedWidget* stackedWidget, QWidget* parent) : QWidget(parent), stackedWidget(stackedWidget)
{
    centralwidget = new QWidget(this);
    loadingCircleLabel = new QLabel(centralwidget);
    loadingCircleMovie = new QMovie("./loading_circle.gif");
    font = new QFont();
    layout = new QVBoxLayout(centralwidget);

    setupUi(this);
}

Ui_waitingScreen::~Ui_waitingScreen()
{
}

void Ui_waitingScreen::setUpLoadingCircle()
{
    loadingCircleLabel->setMovie(loadingCircleMovie);
    loadingCircleLabel->setAlignment(Qt::AlignHCenter); 
    loadingCircleMovie->start();
    layout->addWidget(loadingCircleLabel, 0, Qt::AlignHCenter);
}

QFont Ui_waitingScreen::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_waitingScreen::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    centralwidget->setObjectName("centralwidget");

    setUpWaitingForPlayerLabel();
    setUpLoadingCircle();

    MainWindow->setLayout(layout);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_waitingScreen::setUpWaitingForPlayerLabel()
{
    waitingForPlayerLabel = new QLabel(centralwidget);
    waitingForPlayerLabel->setObjectName("waitingForPlayerLabel");
    waitingForPlayerLabel->setFont(setUpFont(MAIN_TEXT_FONT));
    layout->addWidget(waitingForPlayerLabel, 0, Qt::AlignHCenter);
}

void Ui_waitingScreen::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    waitingForPlayerLabel->setText(QCoreApplication::translate("MainWindow", "Waiting for other player to join", nullptr));
}