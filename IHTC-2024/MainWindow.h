#pragma once 

#include <QMainWindow>
#include <QStackedWidget>
#include <QtWidgets/QApplication>
#include "welcomeScreen.h"
#include "chooseOpponent.h"
#include "gameParameters.h"
#include "metahParameters.h"
#include "sessions.h"
#include "waitingScreen.h"
#include "StateController.h"
#include "gamePlotScreen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private:
    QStackedWidget* _stackedWidget; 
};
