#include "sessions.h"
#include <gamePlotScreen.h>

Ui_sessions::Ui_sessions(QWidget* parent) : 
    QWidget(parent)
{
    _centralwidget = new QWidget(this);
    _listOfSessions = new QListWidget(_centralwidget);
    _createSessionButton = new QPushButton(_centralwidget);
    _font = new QFont();
    _layout = new QVBoxLayout(_centralwidget);
    _buttonLayout = new QHBoxLayout(_centralwidget);
    _listLayout = new QHBoxLayout(_centralwidget);

    setupUi(this);
}

Ui_sessions::~Ui_sessions() = default;

void Ui_sessions::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
    {
        MainWindow->setObjectName("MainWindow");
    }

    _centralwidget->setParent(MainWindow);

    setUpListOfSessions();
    setUpCreateSessionButton();

    connect(_createSessionButton, &QPushButton::clicked, this, &Ui_sessions::onCreateSessionButtonClicked);

    _layout->addLayout(_listLayout);
    _layout->addLayout(_buttonLayout);

    MainWindow->setLayout(_layout);

    retranslateUi(MainWindow);

    connect(_listOfSessions, &QListWidget::itemClicked, this, &Ui_sessions::onItemClicked);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_sessions::setUpListOfSessions()
{
    _listOfSessions->setObjectName("listWidget");
    _listOfSessions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _listOfSessions->setMinimumHeight(700);
    _listLayout->addWidget(_listOfSessions, 0, Qt::AlignVCenter);
}

void Ui_sessions::setUpCreateSessionButton()
{
    _createSessionButton->setObjectName("startGameButton");
    _createSessionButton->setStyleSheet("background-color: pink; color: black");
    _createSessionButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _buttonLayout->addWidget(_createSessionButton, 0, Qt::AlignHCenter);
}

QFont Ui_sessions::setUpFont(int points)
{
    _font->setPointSize(points);
    return *_font;
}

void Ui_sessions::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose session", nullptr));
    _createSessionButton->setText(QCoreApplication::translate("MainWindow", "Create own session", nullptr));
}

void Ui_sessions::updateSessionList(std::unordered_map<std::string, CGameInfo>& sessions)
{
    for (auto it = sessions.begin(); it != sessions.end(); it++)
    {
        std::string sessionInfo;
        sessionInfo += "Game id: " ;
        sessionInfo += it->first;
        sessionInfo += " Player name : ";
        sessionInfo += it->second.name();
        sessionInfo += " Game time: ";
        sessionInfo += std::to_string(it->second.gameTime());
        sessionInfo += " Game level: ";
        sessionInfo += enumToString<GameLevel>(it->second.gameLevel());
        sessionInfo += " Winner type: ";
        sessionInfo += enumToString<WinnerJudgeType>(it->second.judgeType());
        sessionInfo += " Round number: ";
        sessionInfo += std::to_string(it->second.roundNumber());
        sessionInfo += " Input parameters level: ";
        sessionInfo += enumToString<GameLevel>(it->second.inputParametersLevel());

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(sessionInfo));
        item->setData(Qt::UserRole, QVariant::fromValue(QString::fromStdString(it->first)));

        if (!_addedItems.contains(item->text().toStdString()))
        {
            _listOfSessions->addItem(item);
            _addedItems.insert(item->text().toStdString());
        }

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
            StateController::instance().joinSession(
                [](std::shared_ptr<ICGame> game) 
                {
                    static_cast<Ui_gamePlotScreen*>(StateController::instance().screens()[ScreensNumber::PLOT_SCREEN])->connectPlot(game);
                },
                []()
                {
                    StateController::instance().navigate(ScreensNumber::END_GAME_SCREEN);
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