#pragma once 

#include <QMainWindow>
#include <QStackedWidget>
#include "welcomeScreen.h"
#include "chooseOpponent.h"
#include "gameParameters.h"
#include "metahParameters.h"
#include <sessions.h>
#include <waitingScreen.h>
#include "AllGameParameters.h"
#include <memory>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget* stackedWidget; 
    Ui_welcomeScreen* welcomeScreen;
    Ui_chooseOpponent* chooseOpponentScreen;
    Ui_gameParameters* gameParameters;
    Ui_sessions* sessions;
    Ui_waitingScreen* waitingScreen;

    void addScreensToStackedWidget();
};
