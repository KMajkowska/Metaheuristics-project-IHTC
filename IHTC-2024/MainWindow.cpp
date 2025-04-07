#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{

    setWindowIcon(QIcon("uniqrn.png"));

    std::shared_ptr<AllGameParameters> allGameParameters = std::make_shared<AllGameParameters>();

    stackedWidget = new QStackedWidget(this);

    welcomeScreen = new Ui_welcomeScreen(stackedWidget, this, allGameParameters);
    chooseOpponentScreen = new Ui_chooseOpponent(stackedWidget, this, allGameParameters);
    gameParameters = new Ui_gameParameters(stackedWidget, this, allGameParameters);
    sessions = new Ui_sessions(stackedWidget, this);
    waitingScreen = new Ui_waitingScreen(stackedWidget, this);

    addScreensToStackedWidget();

    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(welcomeScreen);

    stackedWidget->showMaximized();
}

void MainWindow::addScreensToStackedWidget()
{
    stackedWidget->addWidget(welcomeScreen);
    stackedWidget->addWidget(chooseOpponentScreen);
    stackedWidget->addWidget(gameParameters);
    stackedWidget->addWidget(sessions);
    stackedWidget->addWidget(waitingScreen);
}

MainWindow::~MainWindow()
{
    delete stackedWidget;
}
