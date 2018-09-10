#include "cartevip.h"

CarteVIP::CarteVIP(QWidget *parent) : QWidget(parent)
{
    //The first interface of the search
    m_pWidgetSearchVIPCard = new QWidget();
    m_pLabel = new QLabel();
    m_pLineEditCardID = new QLineEdit();
    m_pPushButtonSearchVIPCard = new QPushButton();
    m_pPushButtonSearchVIPCard->setText("Search");
    m_pTableViewVIPCard = new QTableView();
    m_pSqlQueryModelVIPCard = new QSqlQueryModel(m_pTableViewVIPCard);
    m_pPushButtonConfirmedVIPCard = new QPushButton();
    m_pPushButtonConfirmedVIPCard->setText("Confirm");

    //The layout of the search
    QGridLayout *pGridLayoutSearchVIPCard = new QGridLayout();
    m_pLabel->setText("Please insert the client code: ");
    pGridLayoutSearchVIPCard->addWidget(m_pLabel,0,0);
    pGridLayoutSearchVIPCard->addWidget(m_pLineEditCardID,1,0);
    pGridLayoutSearchVIPCard->addWidget(m_pPushButtonSearchVIPCard,1,1);
    pGridLayoutSearchVIPCard->addWidget(m_pTableViewVIPCard,2,0);
    pGridLayoutSearchVIPCard->addWidget(m_pPushButtonConfirmedVIPCard,3,0);
    pGridLayoutSearchVIPCard->setHorizontalSpacing(10);
    pGridLayoutSearchVIPCard->setVerticalSpacing(10);
    m_pWidgetSearchVIPCard->setLayout(pGridLayoutSearchVIPCard);

    //The page to show the VIP Card
    m_pWidgetShowVIPCard = new QWidget();
    m_pLabelShowVIPCard = new QLabel();
    m_pLabelShowVIPCard->setText("Balance");
    QGridLayout *pGridLayoutShowVIPCard = new QGridLayout();
    pGridLayoutShowVIPCard->addWidget(m_pLabelShowVIPCard,0,0);
    m_pWidgetShowVIPCard->setLayout(pGridLayoutShowVIPCard);

    //The global interface
    m_pStackedWidget = new QStackedWidget(this);
    m_pStackedWidget->addWidget(m_pWidgetSearchVIPCard);
    m_pStackedWidget->addWidget(m_pWidgetShowVIPCard);
    m_pStackedWidget->adjustSize();

//    QDesktopWidget* desktop = QApplication::desktop();
//    int screenWidth = desktop->screenGeometry().width();
//    int screenHeight = desktop->screenGeometry().height();

//    this->resize(0.5*screenWidth,0.5*screenHeight);

    connect(m_pPushButtonConfirmedVIPCard,SIGNAL(clicked(bool)),this,SLOT(switchPageSlot()));
    connect(m_pPushButtonSearchVIPCard,SIGNAL(clicked(bool)),this,SLOT(searchButtonClickedSlot()));
}

//Change the widget
void CarteVIP::switchPageSlot()
{
    int nIndex = m_pStackedWidget->currentIndex();
    nIndex++;
    m_pStackedWidget->setCurrentIndex(nIndex);

}

//Connect the 2 databases
bool CarteVIP::initConnectDatabase()
{
    bool flag = false;

    //Connect the database erp and ventap
    QString databaseERPFilePath = "/home/echo/Database/arcerp.fdb";
    QString databaseVentapFilePath = "/home/echo/Database/ventap.fdb";
    QFile dbERPFile(databaseERPFilePath);
    QFile dbVentapFile(databaseVentapFilePath);
    if (dbERPFile.exists() && dbVentapFile.exists()) {
        m_DatabaseERP = QSqlDatabase::addDatabase("QIBASE","ERP");
        m_DatabaseERP.setDatabaseName(dbERPFile.fileName());
        m_DatabaseERP.setUserName("SYSDBA");
        m_DatabaseERP.setPassword("masterkey");

        m_DatabaseVentap = QSqlDatabase::addDatabase("QIBASE","Ventap");
        m_DatabaseVentap.setDatabaseName(dbVentapFile.fileName());
        m_DatabaseVentap.setUserName("SYSDBA");
        m_DatabaseVentap.setPassword("masterkey");

        if (m_DatabaseERP.open() && m_DatabaseVentap.open()) {
            flag = true;
        } else {
            QMessageBox::about(NULL,"Info","Database file cannot be opened!");
        }
    } else {
        QMessageBox::about(NULL,"Info","Database file does not exist!");
    }
    return flag;
}

//Search the customer
void CarteVIP::searchButtonClickedSlot()
{

    QString str = m_pLineEditCardID->text();
    QString sql = "SELECT CARD.CARD_ID,CUSTOMER.CUSTOMER_NAME_1,CUSTOMER.CUSTOMER_REFERENCE,CUSTOMER.CUSTOMER_TEL_1 "
                  "FROM CUSTOMER "
                  "INNER JOIN CARD ON CARD.CUSTOMER_ID =CUSTOMER.CUSTOMER_ID ";
    sql = sql + "WHERE CUSTOMER.CUSTOMER_NAME_1 LIKE '%" + str + "%' "
                      "OR CUSTOMER.CUSTOMER_TEL_1 LIKE '%" + str + "%' "
                      "OR CUSTOMER.CUSTOMER_REFERENCE LIKE '%" + str + "%' "
                      "OR CARD.CARD_ID LIKE '%" + str + "%'";
    m_pSqlQueryModelVIPCard->setQuery(sql,m_DatabaseERP);
    m_pTableViewVIPCard->setModel(m_pSqlQueryModelVIPCard);
}
