#include "sessions.h"

Ui_sessions::Ui_sessions(QWidget* parent) : QWidget(parent)
{
    centralwidget = new QWidget(this);
    listOfSessions = new QListWidget(centralwidget);
    createSessionButton = new QPushButton(centralwidget);
    font = new QFont();
    layout = new QVBoxLayout(centralwidget);
    buttonLayout = new QHBoxLayout(centralwidget);
    listLayout = new QHBoxLayout(centralwidget);

    setupUi(this);
}

void Ui_sessions::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    centralwidget->setParent(MainWindow);

    setUpListOfSessions();
    setUpCreateSessionButton();

    connect(createSessionButton, &QPushButton::clicked, this, &Ui_sessions::onCreateSessionButtonClicked);

    layout->addLayout(listLayout);
    layout->addLayout(buttonLayout);

    MainWindow->setLayout(layout);

    retranslateUi(MainWindow);

    connect(listOfSessions, &QListWidget::itemClicked, this, &Ui_sessions::onItemClicked);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_sessions::setUpListOfSessions()
{
    listOfSessions->setObjectName("listWidget");
    listOfSessions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listOfSessions->setMinimumHeight(700);
    listLayout->addWidget(listOfSessions, 0, Qt::AlignVCenter);
}

void Ui_sessions::setUpCreateSessionButton()
{
    createSessionButton->setObjectName("startGameButton");
    createSessionButton->setStyleSheet("background-color: pink; color: black");
    createSessionButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(createSessionButton, 0, Qt::AlignHCenter);
}

QFont Ui_sessions::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_sessions::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose session", nullptr));
    createSessionButton->setText(QCoreApplication::translate("MainWindow", "Create own session", nullptr));
}

void Ui_sessions::updateSessionList(std::unordered_map<std::string, CGameInfo>& sessions)
{
    for (auto it = sessions.begin(); it != sessions.end(); it++)
    {
        std::string sessionInfo;
        sessionInfo += it->first;
        sessionInfo += " ";
        sessionInfo += it->second.name();
        sessionInfo += " ";
        sessionInfo += it->second.gameTime();
        sessionInfo += " ";
        sessionInfo += enumToString<GameLevel>(it->second.gameLevel());
        sessionInfo += " ";
        sessionInfo += enumToString<WinnerJudgeType>(it->second.judgeType());
        sessionInfo += " ";
        sessionInfo += it->second.roundNumber();
        sessionInfo += " ";
        sessionInfo += enumToString<GameLevel>(it->second.inputParametersLevel());

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(sessionInfo));
        item->setData(Qt::UserRole, QVariant::fromValue(QString::fromStdString(it->first)));

        listOfSessions->addItem(item);
    }
}

void Ui_sessions::showEvent(QShowEvent* event)
{
    StateController::instance().updateSessionList([this](std::unordered_map<std::string, CGameInfo>& sessionsList)
        {
            updateSessionList(sessionsList);
        });

    QWidget::showEvent(event);
}

void Ui_sessions::hideEvent(QHideEvent* event)
{
    StateController::instance().stopUpdatingSessionList();

    QWidget::hideEvent(event);
}

void Ui_sessions::onItemClicked(QListWidgetItem* item)
{
    StateController::instance().setStartGame([item]()
        {
            QString key = item->data(Qt::UserRole).toString();
            std::string stdKey = key.toStdString();

            auto foundGame{ StateController::instance().foundSessions().find(stdKey)};

            if (foundGame == StateController::instance().foundSessions().end())
            {
                return;
            }

            StateController::instance().setAllGameParametersFromJoined(foundGame->second);

            StateController::instance().navigate(ScreensNumber::PLOT_SCREEN);
            StateController::instance().joinSession([]()
                {
                    // TODO: przekierowanie na ekran z wynikiem
                },
                StateController::instance().allGameParameters(),
                foundGame->second);
        });

    StateController::instance().navigate(ScreensNumber::METAH_PARAMETERS);
}


void Ui_sessions::onCreateSessionButtonClicked()
{
    StateController::instance().navigate(ScreensNumber::GAME_PARAMETERS);
}