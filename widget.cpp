#include "widget.h"
#include "./ui_widget.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QGridLayout>

NFLMiddle::NFLMiddle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // ----------------------
    // Create all the objects
    // ----------------------
    gameLabel = new QLabel("NFL Middle");
    gameLabel->setAlignment(Qt::AlignCenter);

    QFont font = gameLabel->font();
    font.setPointSize(font.pointSize() + 10);
    gameLabel->setFont(font);

    amountLabel = new QLabel("Total Stake (£)");
    amountLabel->setAlignment(Qt::AlignCenter);
    amountStake = new QLineEdit("40");
    amountStake->setAlignment(Qt::AlignCenter);

    connect(amountStake, SIGNAL(textEdited(QString)), this, SLOT(calculateStakes()));

    seasonLabel = new QLabel("Season");
    seasonLabel->setAlignment(Qt::AlignCenter);
    qleSeason = new QLineEdit("2021");
    qleSeason->setAlignment(Qt::AlignCenter);

    weekLabel = new QLabel("Week");
    weekLabel->setAlignment(Qt::AlignCenter);
    qleWeek = new QLineEdit("1");
    qleWeek->setAlignment(Qt::AlignCenter);

    homeLabel = new QLabel("Home");
    homeLabel->setAlignment(Qt::AlignCenter);
    favHome = new QRadioButton();
    favHome->setChecked(true);
    underdogHome = new QRadioButton();

    spreadLabel = new QLabel("Spread");
    spreadLabel->setAlignment(Qt::AlignCenter);

    spread = new QLineEdit("3");
    spread->setAlignment(Qt::AlignCenter);
    spread->setMaxLength(5);

    connect(spread, SIGNAL(textEdited(QString)), this, SLOT(spreadChanged()));

    favLabel = new QLabel("Favourite");
    underdogLabel = new QLabel("Underdog");

    favTeam = new QLineEdit("Atl");
    favTeam->setAlignment(Qt::AlignCenter);
    favTeam->setMaxLength(3);

    connect(favTeam, SIGNAL(textEdited(QString)), this, SLOT(favTeamChanged()));

    underdogTeam = new QLineEdit("Car");
    underdogTeam->setAlignment(Qt::AlignCenter);
    underdogTeam->setMaxLength(3);

    connect(underdogTeam, SIGNAL(textEdited(QString)), this, SLOT(underdogTeamChanged()));

    oddsLabel = new QLabel("Odds");
    oddsLabel->setAlignment(Qt::AlignCenter);
    commLabel = new QLabel("Comm. (%)");
    commLabel->setAlignment(Qt::AlignCenter);
    stakeLabel = new QLabel("Stake (£)");
    stakeLabel->setAlignment(Qt::AlignCenter);

    QPalette bluePalette;
    bluePalette.setColor(QPalette::Base,QColor(0x66, 0x99, 0xff));
    bluePalette.setColor(QPalette::Text,Qt::black);

    favOdds = new QLineEdit("1.66");
    favOdds->setAlignment(Qt::AlignCenter);
    //favOdds->setPalette(bluePalette);

    connect(favOdds, SIGNAL(textEdited(QString)), this, SLOT(calculateStakes()));

    underdogOdds = new QLineEdit("1.75");
    underdogOdds->setAlignment(Qt::AlignCenter);
    //underdogOdds->setPalette(bluePalette);

    connect(underdogOdds, SIGNAL(textEdited(QString)), this, SLOT(calculateStakes()));

    favComm = new QComboBox();
    favComm->addItem("2");
    favComm->addItem("0");
    favComm->addItem("5");

    connect(favComm, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateStakes()));

    underdogComm = new QComboBox();
    underdogComm->addItem("2");
    underdogComm->addItem("0");
    underdogComm->addItem("5");

    connect(underdogComm, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateStakes()));

    favStake = new QLineEdit("");
    favStake->setReadOnly(true);
    favStake->setAlignment(Qt::AlignCenter);

    underdogStake = new QLineEdit("");
    underdogStake->setReadOnly(true);
    underdogStake->setAlignment(Qt::AlignCenter);

    gameCountLabel = new QLabel("Game Count: ");
    gameCountLabel->setAlignment(Qt::AlignCenter);
    profitLabel = new QLabel("Profit (£)");
    profitLabel->setAlignment(Qt::AlignCenter);
    probabilityLabel = new QLabel("Probability");
    probabilityLabel->setAlignment(Qt::AlignCenter);

    favWinsLabel = new QLabel();
    QString favWinsStr = favTeam->displayText() + " wins by " + spread->displayText() + " or more";
    favWinsLabel->setText(favWinsStr);
    favWinsLabel->setAlignment(Qt::AlignCenter);

    pushLabel = new QLabel();
    QString pushStr = favTeam->displayText() + " wins by exactly " + spread->displayText();
    pushLabel->setText(pushStr);
    pushLabel->setAlignment(Qt::AlignCenter);

    middleLabel = new QLabel();
    QString middleStr = favTeam->displayText() + " wins by less than " + spread->displayText();
    middleLabel->setText(middleStr);
    middleLabel->setAlignment(Qt::AlignCenter);

    underdogWinsLabel = new QLabel();
    QString underdogStr = underdogTeam->displayText() + " wins";
    underdogWinsLabel->setText(underdogStr);
    underdogWinsLabel->setAlignment(Qt::AlignCenter);

    favWinsProfit = new QLineEdit();
    favWinsProfit->setAlignment(Qt::AlignCenter);
    favWinsProfit->setReadOnly(true);

    favWinsProb = new QLineEdit();
    favWinsProb->setAlignment(Qt::AlignCenter);
    favWinsProb->setReadOnly(true);

    pushProfit = new QLineEdit();
    pushProfit->setAlignment(Qt::AlignCenter);
    pushProfit->setReadOnly(true);

    pushProb = new QLineEdit();
    pushProb->setAlignment(Qt::AlignCenter);
    pushProb->setReadOnly(true);

    middleProfit = new QLineEdit();
    middleProfit->setAlignment(Qt::AlignCenter);
    middleProfit->setReadOnly(true);

    middleProb = new QLineEdit();
    middleProb->setAlignment(Qt::AlignCenter);
    middleProb->setReadOnly(true);

    underdogWinsProfit = new QLineEdit();
    underdogWinsProfit->setAlignment(Qt::AlignCenter);
    underdogWinsProfit->setReadOnly(true);

    underdogWinsProb = new QLineEdit();
    underdogWinsProb->setAlignment(Qt::AlignCenter);
    underdogWinsProb->setReadOnly(true);

    expectedProfitlabel = new QLabel("Expected profit (£)");
    expectedProfitlabel->setAlignment(Qt::AlignCenter);

    profitAmount = new QLineEdit();
    profitAmount->setAlignment(Qt::AlignCenter);
    profitAmount->setReadOnly(true);

    profitPercent = new QLineEdit();
    profitPercent->setAlignment(Qt::AlignCenter);
    profitPercent->setReadOnly(true);

    winPercentLabel = new QLabel("Total Win %");
    winPercentLabel->setAlignment(Qt::AlignCenter);

    winPercent = new QLineEdit();
    winPercent->setAlignment(Qt::AlignCenter);
    winPercent->setReadOnly(true);

    saveButton = new QPushButton("Save game");
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));

    // -----------------
    // Create the layout
    // -----------------
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(gameLabel, 0, 0, 2, 2);

    mainLayout->addWidget(amountLabel, 0, 2);
    mainLayout->addWidget(amountStake, 0, 3);

    mainLayout->addWidget(seasonLabel, 0, 4);
    mainLayout->addWidget(qleSeason, 0, 5);

    mainLayout->addWidget(weekLabel, 1, 4);
    mainLayout->addWidget(qleWeek, 1, 5);

    mainLayout->addWidget(homeLabel, 2, 0);
    mainLayout->addWidget(spreadLabel, 2, 1);
    mainLayout->addWidget(spread, 2, 2);
    mainLayout->addWidget(oddsLabel, 2, 3);
    mainLayout->addWidget(commLabel, 2, 4);
    mainLayout->addWidget(stakeLabel, 2, 5);

    mainLayout->addWidget(favHome, 3, 0, Qt::AlignCenter);
    mainLayout->addWidget(favLabel, 3, 1);
    mainLayout->addWidget(favTeam, 3, 2);
    mainLayout->addWidget(favOdds, 3, 3);
    mainLayout->addWidget(favComm, 3, 4);
    mainLayout->addWidget(favStake, 3, 5);

    mainLayout->addWidget(underdogHome, 4, 0, Qt::AlignCenter);
    mainLayout->addWidget(underdogLabel, 4, 1);
    mainLayout->addWidget(underdogTeam, 4, 2);
    mainLayout->addWidget(underdogOdds, 4, 3);
    mainLayout->addWidget(underdogComm, 4, 4);
    mainLayout->addWidget(underdogStake, 4, 5);

    mainLayout->setColumnMinimumWidth(6, 50);

    mainLayout->addWidget(gameCountLabel, 0, 7);
    mainLayout->addWidget(profitLabel, 0, 8);
    mainLayout->addWidget(probabilityLabel, 0, 9);

    mainLayout->addWidget(favWinsLabel, 1, 7);
    mainLayout->addWidget(favWinsProfit, 1, 8);
    mainLayout->addWidget(favWinsProb, 1, 9);

    mainLayout->addWidget(pushLabel, 2, 7);
    mainLayout->addWidget(pushProfit, 2, 8);
    mainLayout->addWidget(pushProb, 2, 9);

    mainLayout->addWidget(middleLabel, 3, 7);
    mainLayout->addWidget(middleProfit, 3, 8);
    mainLayout->addWidget(middleProb, 3, 9);

    mainLayout->addWidget(underdogWinsLabel, 4, 7);
    mainLayout->addWidget(underdogWinsProfit, 4, 8);
    mainLayout->addWidget(underdogWinsProb, 4, 9);

    mainLayout->setColumnMinimumWidth(10, 50);

    mainLayout->addWidget(expectedProfitlabel, 0, 11, 1, 2);
    mainLayout->addWidget(profitAmount, 1, 11);
    mainLayout->addWidget(profitPercent, 1, 12);

    mainLayout->addWidget(winPercentLabel, 3, 11);
    mainLayout->addWidget(winPercent, 3, 12);

    mainLayout->addWidget(saveButton, 5, 11, 1, 2);

    setLayout(mainLayout);
    setWindowTitle("NFL Middles");

    calculateStakes();
}

NFLMiddle::~NFLMiddle()
{
    delete ui;
}

// Update the labels when the favourite team changes
void NFLMiddle::favTeamChanged()
{
    QString favWinsStr = favTeam->displayText() + " wins by " + spread->displayText() + " or more";
    favWinsLabel->setText(favWinsStr);

    QString pushStr = favTeam->displayText() + " wins by exactly " + spread->displayText();
    pushLabel->setText(pushStr);

    QString middleStr = favTeam->displayText() + " wins by less than " + spread->displayText();
    middleLabel->setText(middleStr);
}

// Update the label when the underdog team changes
void NFLMiddle::underdogTeamChanged()
{
    QString underdogStr = underdogTeam->displayText() + " wins";
    underdogWinsLabel->setText(underdogStr);
}

void NFLMiddle::spreadChanged()
{
    favTeamChanged();
    calculateStakes();
}

#include <QDir>

void NFLMiddle::saveGame()
{
    QString qsSeason = qleSeason->displayText();
    QString qsWeek = qleWeek->displayText();

    QString qsGame;
    if(favHome->isChecked())
    {
        qsGame = underdogTeam->displayText() + " @ " + favTeam->displayText();
    }
    else
    {
        qsGame = favTeam->displayText() + " @ " + underdogTeam->displayText();
    }

    QString qsSpread = spread->displayText();
    QString qsStake = amountStake->displayText();
    QString qsEP = profitAmount->displayText();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Database\\NFLSpreadStats.db");
    bool db_ok = db.open();

    if(db_ok)
    {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO BetHistory (Season, Week, Game, Spread, Stake, EP) VALUES (:season, :week, :game, :spread, :stake, :ep)");
        insertQuery.bindValue(":season", qsSeason);
        insertQuery.bindValue(":week", qsWeek);
        insertQuery.bindValue(":game", qsGame);
        insertQuery.bindValue(":spread", qsSpread);
        insertQuery.bindValue(":stake", qsStake);
        insertQuery.bindValue(":ep", qsEP);
        insertQuery.exec();

        qInfo() << insertQuery.lastError();
    }

    db.close();
}

// Calculate the stakes that should be used
// Calculate the probability of each event
// Calculate the expected profit
void NFLMiddle::calculateStakes()
{
    double dAmount = amountStake->displayText().toDouble();

    double dSpread = spread->displayText().toDouble();
    if(dSpread > 0)
    {
        dSpread *= -1;
    }

    double dFavOdds = favOdds->displayText().toDouble();
    double dUnderdogOdds = underdogOdds->displayText().toDouble();
    double dFavComm = favComm->currentText().toDouble() / 100;
    double dUnderdogComm = underdogComm->currentText().toDouble() / 100;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Database\\NFLSpreadStats.db");
    bool db_ok = db.open();

    qInfo() << db.lastError() << db.databaseName();

    if(db_ok)
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM NFLStats where spread = :spread");
        query.bindValue(":spread", dSpread);
        query.setForwardOnly(true);
        query.exec();
        query.first();

        // Get all the column references
        int nGameCountCol = query.record().indexOf("GameCount");
        int nPushPercentCol = query.record().indexOf("PushPercentC");
        int nMiddlePercentCol = query.record().indexOf("MiddlePercentC");
        int nCoverPercentCol = query.record().indexOf("CoverPercentC");

        // Get the values from the db
        double dbGameCount = query.value(nGameCountCol).toDouble();
        QString qsGameCount = "Game Count: " + QString::number(dbGameCount);
        gameCountLabel->setText(qsGameCount);

        double dFavCommOdds = 1 + ((1 - dFavComm) * (dFavOdds - 1));
        double dOneOverFavCommOdds = 1 / dFavCommOdds;

        double dUnderdogCommOdds = 1 + ((1 - dUnderdogComm) * (dUnderdogOdds - 1));
        double dOneOverUnderdogCommOdds = 1 / dUnderdogCommOdds;

        double dSumOneOverCommOdds = dOneOverFavCommOdds + dOneOverUnderdogCommOdds;
        double dFavPercentStake = dOneOverFavCommOdds / dSumOneOverCommOdds;
        double dUnderdogPercentStake = dOneOverUnderdogCommOdds / dSumOneOverCommOdds;

        double dFavStake = dFavPercentStake * dAmount;
        double dUnderdogStake = dUnderdogPercentStake * dAmount;

        QPalette yellowPalette;
        yellowPalette.setColor(QPalette::Base,QColor(0xff, 0xff, 0x66));
        yellowPalette.setColor(QPalette::Text,Qt::black);

        QString qsFavStake = QString::number(dFavStake, 'f', 2);
        favStake->setText(qsFavStake);
        favStake->setPalette(yellowPalette);

        QString qsUnderdogStake = QString::number(dUnderdogStake, 'f', 2);
        underdogStake->setText(qsUnderdogStake);
        underdogStake->setPalette(yellowPalette);

        double dbCoverPerc = query.value(nCoverPercentCol).toDouble();
        double dbPushPerc = query.value(nPushPercentCol).toDouble();
        double dbMiddlePerc = query.value(nMiddlePercentCol).toDouble();
        double dLosePercent = 100 - dbCoverPerc - dbPushPerc - dbMiddlePerc;

        QString qsCoverPerc = QString::number(dbCoverPerc, 'f', 2) + "%";
        favWinsProb->setText(qsCoverPerc);
        QString qsPushPerc = QString::number(dbPushPerc, 'f', 2) + "%";
        pushProb->setText(qsPushPerc);
        QString qsMiddlePerc = QString::number(dbMiddlePerc, 'f', 2) + "%";
        middleProb->setText(qsMiddlePerc);
        QString qsLosePerc = QString::number(dLosePercent, 'f', 2) + "%";
        underdogWinsProb->setText(qsLosePerc);

        double dWinProfit = (dFavStake * dFavOdds) - dAmount;
        double dPushProfit = (dFavStake * dFavOdds) - dAmount + dUnderdogStake;
        double dMiddleProfit = ((dFavStake * dFavOdds) + (dUnderdogStake * dUnderdogOdds)) - dAmount;
        double dLoseProfit = (dUnderdogStake * dUnderdogOdds) - dAmount;

        QPalette redPalette;
        redPalette.setColor(QPalette::Base,QColor(0xff, 0x50, 0x50));
        redPalette.setColor(QPalette::Text,Qt::black);

        QPalette greenPalette;
        greenPalette.setColor(QPalette::Base,QColor(0x99, 0xff, 0x66));
        greenPalette.setColor(QPalette::Text,Qt::black);

        QString qsFavWinsProfit = QString::number(dWinProfit, 'f', 2);
        favWinsProfit->setText(qsFavWinsProfit);
        if(dWinProfit > 0)
        {
            favWinsProfit->setPalette(greenPalette);
        }
        else
        {
            favWinsProfit->setPalette(redPalette);
        }

        QString qsPushProfit = QString::number(dPushProfit, 'f', 2);
        pushProfit->setText(qsPushProfit);
        if(dPushProfit > 0)
        {
            pushProfit->setPalette(greenPalette);
        }
        else
        {
            pushProfit->setPalette(redPalette);
        }

        QString qsMiddleProfit = QString::number(dMiddleProfit, 'f', 2);
        middleProfit->setText(qsMiddleProfit);
        if(dMiddleProfit > 0)
        {
            middleProfit->setPalette(greenPalette);
        }
        else
        {
            middleProfit->setPalette(redPalette);
        }

        QString qsLoseProfit = QString::number(dLoseProfit, 'f', 2);
        underdogWinsProfit->setText(qsLoseProfit);
        if(dLoseProfit > 0)
        {
            underdogWinsProfit->setPalette(greenPalette);
        }
        else
        {
            underdogWinsProfit->setPalette(redPalette);
        }

        double dWinEP = dWinProfit * (dbCoverPerc / 100);
        double dPushEP = dbPushPerc * (dPushProfit / 100);
        double dMiddleEP = dbMiddlePerc * (dMiddleProfit / 100);
        double dLoseEP = dLosePercent * (dLoseProfit / 100);        

        double dEP = dWinEP + dPushEP + dMiddleEP + dLoseEP;
        double dEPPercent = (dEP / dAmount) * 100;

        QPalette tealPalette;
        tealPalette.setColor(QPalette::Base,QColor(0x66, 0xff, 0xcc));
        tealPalette.setColor(QPalette::Text,Qt::black);

        QPalette lightBluePalette;
        lightBluePalette.setColor(QPalette::Base,QColor(0x66, 0xe6, 0xff));
        lightBluePalette.setColor(QPalette::Text,Qt::black);

        QString qsEP = QString::number(dEP, 'f', 2);
        profitAmount->setText(qsEP);

        QString qsEPPercent = QString::number(dEPPercent, 'f', 2) + "%";
        profitPercent->setText(qsEPPercent);

        qInfo() << dEPPercent;

        if(dEPPercent > 3)
        {
            profitPercent->setPalette(lightBluePalette);
        }
        else if(dEPPercent > 2)
        {
            profitPercent->setPalette(tealPalette);
        }
        else if(dEPPercent > 1)
        {
            profitPercent->setPalette(greenPalette);
        }
        else if(dEPPercent > 0)
        {
            profitPercent->setPalette(yellowPalette);
        }
        else
        {
            profitPercent->setPalette(redPalette);
        }

        double dWinPercent = dbPushPerc + dbMiddlePerc;
        QString qsWinPerc = QString::number(dWinPercent, 'f', 2) + "%";
        winPercent->setText(qsWinPerc);
    }

    db.close();
}

