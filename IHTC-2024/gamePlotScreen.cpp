#include "gamePlotScreen.h"

Ui_gamePlotScreen::Ui_gamePlotScreen(QWidget* parent) :
	QWidget(parent)
{
	centralWidget = new QWidget(this);
	infoLabel = new QLabel(centralWidget);
	plot = new RealTimePlot(centralWidget);
	layout = new QVBoxLayout(centralWidget);
	plotLayout = new QHBoxLayout(centralWidget);
	font = new QFont();

	setupUi(this);
}

void Ui_gamePlotScreen::connectPlot(std::shared_ptr<ICGame> game)
{
	static int idx = 1;
	static int opponnetIdx = 1;

	if (game)
	{
		game->setOnLocal([this](SolutionData solutionData)
			{
				emit requestDrawSeries(idx++, solutionData.fitness());
			});

		game->setOnOpponent([this](SolutionData solutionData)
			{
				emit requestDrawOpponentSeries(opponnetIdx++, solutionData.fitness());
			});

		game->setConsumeScore([this](Winner result, std::shared_ptr<CPlayer> localPlayer, std::shared_ptr<CPlayer> opponentPlayer)
			{
				emit requestResetPlots();

				idx = 0;
				opponnetIdx = 0;

				// TODO: settings score
			});
	}
}

void Ui_gamePlotScreen::setupUi(QWidget* MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

	centralWidget->setParent(MainWindow);
	centralWidget->setObjectName("centralwidget");

	setUpInfoLabel();
	setUpChart();

	layout->addLayout(plotLayout);

	MainWindow->setLayout(layout);
  
    retranslateUi(this);

	connect(this, &Ui_gamePlotScreen::requestDrawSeries,
		this, &Ui_gamePlotScreen::handleDrawSeries,
		Qt::QueuedConnection);
	connect(this, &Ui_gamePlotScreen::requestDrawOpponentSeries,
		this, &Ui_gamePlotScreen::handleOpponentDrawSeries,
		Qt::QueuedConnection);

	connect(this, &Ui_gamePlotScreen::requestResetPlots,
		this, &Ui_gamePlotScreen::handleResetPlots,
		Qt::QueuedConnection);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_gamePlotScreen::setUpInfoLabel()
{
	infoLabel->setObjectName("infoLabel");
	infoLabel->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	layout->addWidget(infoLabel, 0, Qt::AlignHCenter);
}

void Ui_gamePlotScreen::setUpChart()
{
	plot->setUpChart();
	plotLayout->addWidget(plot);
}

void Ui_gamePlotScreen::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game!!", nullptr));
	infoLabel->setText(QCoreApplication::translate("MainWindow", "Game plots:", nullptr));
}

QFont Ui_gamePlotScreen::setUpFont(int points)
{
	font->setPointSize(points);
	return *font;
}

void Ui_gamePlotScreen::handleDrawSeries(double idx, double fitness)
{
	plot->drawSeriesOurResult(idx, fitness);
}

void Ui_gamePlotScreen::handleOpponentDrawSeries(double idx, double fitness)
{
	plot->drawSeriesOpponentResult(idx, fitness);
}

void Ui_gamePlotScreen::handleResetPlots()
{
	plot->clearOpponentPlot();
	plot->clearOurPlot();
}
