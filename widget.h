#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QLabel *gameLabel;

    QLabel *amountLabel;
    QLineEdit *amountStake;

    QLabel *homeLabel;
    QRadioButton *favHome, *underdogHome;

    QLabel *spreadLabel;
    QLineEdit *spread;

    QLabel *favLabel, *underdogLabel;
    QLineEdit *favTeam, *underdogTeam;

    QLabel *oddsLabel, *commLabel, *stakeLabel;
    QLineEdit *favOdds, *favStake;
    QComboBox *favComm;
    QLineEdit *underdogOdds, *underdogStake;
    QComboBox *underdogComm;

    QLabel *gameCountLabel, *profitLabel, *probabilityLabel;
    QLabel *favWinsLabel, *pushLabel, *middleLabel, *underdogWinsLabel;
    QLineEdit *favWinsProfit, *favWinsProb;
    QLineEdit *pushProfit, *pushProb;
    QLineEdit *middleProfit, *middleProb;
    QLineEdit *underdogWinsProfit, *underdogWinsProb;

    QLabel *expectedProfitlabel;
    QLineEdit *profitAmount, *profitPercent;

    QLabel *winPercentLabel;
    QLineEdit *winPercent;

private slots:
    void calculateStakes();
    void favTeamChanged();
    void underdogTeamChanged();
};
#endif // WIDGET_H
