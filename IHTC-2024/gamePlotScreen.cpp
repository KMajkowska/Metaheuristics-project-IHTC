#include "gamePlotScreen.h"

Ui_gamePlotScreen::Ui_gamePlotScreen(QWidget* parent) :	
	QWidget(parent)
{
	_centralWidget = new QWidget(this);
	_infoLabel = new QLabel(_centralWidget);
	_plot = new RealTimePlot(_centralWidget);
	_layout = new QVBoxLayout(_centralWidget);
	_plotLayout = new QHBoxLayout(_centralWidget);
	_resultInfoLayout = new QHBoxLayout(_centralWidget);
	_ourScoreLabel = new QLabel(_centralWidget);
	_opponentScoreLabel = new QLabel(_centralWidget);
	_separateResultLabel = new QLabel(_centralWidget);
	_font = new QFont();

	setupUi(this);
}

Ui_gamePlotScreen::~Ui_gamePlotScreen() = default;

void Ui_gamePlotScreen::connectPlot(std::shared_ptr<ICGame> game)
{
	static int idx = 1;
	static int opponnetIdx = 1;

	if (!game)
	{
		return;
	}

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

			changeOurScoreLabel(localPlayer->score());
			chaneOpponentScoreLabel(opponentPlayer->score());
		});

}

void Ui_gamePlotScreen::setupUi(QWidget* MainWindow) {
	if (MainWindow->objectName().isEmpty())
	{
		MainWindow->setObjectName("MainWindow");
	}

	_centralWidget->setParent(MainWindow);
	_centralWidget->setObjectName("centralwidget");

	setUpInfoLabel();

	setUpOurResultLabel();

	_resultInfoLayout->addStretch(1);

	_separateResultLabel->setText(":");
	_resultInfoLayout->addWidget(_separateResultLabel);

	_resultInfoLayout->addStretch(1);

	setUpOpponentResultLabel();

	setUpChart();

	_layout->addLayout(_resultInfoLayout);
	_layout->addLayout(_plotLayout);

	MainWindow->setLayout(_layout);

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
	_infoLabel->setObjectName("infoLabel");
	_infoLabel->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	_layout->addWidget(_infoLabel, 0, Qt::AlignHCenter);
}

void Ui_gamePlotScreen::setUpChart()
{
	_plot->setUpChart();
	_plotLayout->addWidget(_plot);
}

void Ui_gamePlotScreen::retranslateUi(QWidget* MainWindow)
{
	MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game!!", nullptr));
	_infoLabel->setText(QCoreApplication::translate("MainWindow", "Game plots:", nullptr));
	_ourScoreLabel->setText(QCoreApplication::translate("Main Window", "0", nullptr));
	_opponentScoreLabel->setText(QCoreApplication::translate("Main Window", "0", nullptr));
}

QFont Ui_gamePlotScreen::setUpFont(int points)
{
	_font->setPointSize(points);
	return *_font;
}

void Ui_gamePlotScreen::setUpOurResultLabel()
{
	_ourScoreLabel->setObjectName("ourScoreLabel");
	_ourScoreLabel->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	_resultInfoLayout->addWidget(_ourScoreLabel, 0, Qt::AlignHCenter);
}

void Ui_gamePlotScreen::setUpOpponentResultLabel()
{
	_opponentScoreLabel->setObjectName("opponentScoreLabel");
	_opponentScoreLabel->setFont(setUpFont(OTHER_COMPONENTS_FONT));
	_resultInfoLayout->addWidget(_opponentScoreLabel, 0, Qt::AlignHCenter);
}

void Ui_gamePlotScreen::changeOurScoreLabel(int score)
{
	_ourScoreLabel->setText(QString::number(score));
}

void Ui_gamePlotScreen::chaneOpponentScoreLabel(int score)
{
	_opponentScoreLabel->setText(QString::number(score));
}

void Ui_gamePlotScreen::handleDrawSeries(double idx, double fitness)
{
	_plot->drawSeriesOurResult(idx, fitness);
}

void Ui_gamePlotScreen::handleOpponentDrawSeries(double idx, double fitness)
{
	_plot->drawSeriesOpponentResult(idx, fitness);
}

void Ui_gamePlotScreen::handleResetPlots()
{
	_plot->clearOpponentPlot();
	_plot->clearOurPlot();
}
