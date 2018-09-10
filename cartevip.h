#ifndef CARTEVIP_H
#define CARTEVIP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>

#include <QDebug>

class CarteVIP : public QWidget
{
    Q_OBJECT
public:
    explicit CarteVIP(QWidget *parent = nullptr);


signals:

public slots:
        void switchPageSlot();
        bool initConnectDatabase();
        void searchButtonClickedSlot();


private:
    //The widget of the search of the VIP card
    QWidget *m_pWidgetSearchVIPCard;
    QLineEdit *m_pLineEditCardID;
    QLabel *m_pLabel;
    QTableView *m_pTableViewVIPCard;
    QSqlQueryModel *m_pSqlQueryModelVIPCard;
    QPushButton *m_pPushButtonSearchVIPCard;
    QPushButton *m_pPushButtonConfirmedVIPCard;

    //The widget of showing the VIP card
    QWidget *m_pWidgetShowVIPCard;
    QLabel *m_pLabelShowVIPCard;

    //Layout
    QStackedWidget *m_pStackedWidget;

    //Database
    QSqlDatabase m_DatabaseERP;
    QSqlDatabase m_DatabaseVentap;

    //The infos of the VIP card
    QString m_sCardID;
    double m_dCardCreditAmount;


    QString m_sOrderID;
};

#endif // CARTEVIP_H
