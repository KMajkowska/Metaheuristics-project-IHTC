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
#include <consts.h>
#include <qboxlayout.h>
#include <QtWidgets/QApplication>
#include "StateController.h"
#include "enumOperations.h"

class Ui_sessions : public QWidget
{
public:
    Ui_sessions(QWidget* parent = nullptr);
    ~Ui_sessions() = default;

    void updateSessionList(std::unordered_map<std::string, CGameInfo>& sessions);

private:
    QWidget *centralwidget;
    QListWidget *listOfSessions;
    QPushButton* createSessionButton;
    QFont* font;
    QVBoxLayout* layout;
    QHBoxLayout* listLayout;
    QHBoxLayout* buttonLayout;
    QSet<std::string> addedItems;

    void setUpListOfSessions();
    void setUpCreateSessionButton();
    QFont setUpFont(int points);

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);
    

private slots:
    void onCreateSessionButtonClicked();
    void onItemCLicked();

};
