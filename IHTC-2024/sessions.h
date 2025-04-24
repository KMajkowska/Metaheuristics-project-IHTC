/********************************************************************************
** Form generated from reading UI file 'sessions.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollArea>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"
#include "enumOperations.h"
#include "string"
#include "gamePlotScreen.h"
#include "endGame.h"
#include "gameStateHandlers.h" 

class Ui_sessions : public QWidget
{

    Q_OBJECT

public:
    Ui_sessions(QWidget* parent = nullptr);
    ~Ui_sessions();

    void updateSessionList(std::unordered_map<std::string, CGameInfo>& sessions);

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

private:
    QWidget* _centralwidget;
    QListWidget* _listOfSessions;
    QPushButton* _createSessionButton;
    QFont* _font;
    QVBoxLayout* _layout;
    QHBoxLayout* _listLayout;
    QHBoxLayout* _buttonLayout;
    QSet<std::string> _addedItems;

    void setUpListOfSessions();
    void setUpCreateSessionButton();
    QFont setUpFont(int points);

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);
    

private slots:
    void onCreateSessionButtonClicked();
    void onItemClicked(QListWidgetItem* item);

};
