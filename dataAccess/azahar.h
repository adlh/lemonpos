/***************************************************************************
 *   Copyright (C) 2008-2009 by Miguel Chavez Gamboa                  *
 *   miguel.chavez.gamboa@gmail.com                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *

 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef AZAHAR_H
#define AZAHAR_H

#include <QtSql>
#include <QObject>
#include <QHash>
#include "../src/structs.h"
#include "../src/enums.h"


class QString;

/**
 * This class makes all database access.
 *
 * @short Database access class
 * @author Miguel Chavez Gamboa <miguel.chavez.gamboa@gmail.com>
 * @version 0.9
 */

class Azahar : public QObject
{
  Q_OBJECT  
  private:
    QSqlDatabase db;
    QString errorStr;
    void setError(QString err);
    QString m_mainClient;
  public:
    Azahar();
    ~ Azahar();
    bool isConnected();
    QString lastError();
    void initDatabase(QString user, QString server, QString password, QString dbname);
    void setDatabase(const QSqlDatabase& database);

    // PRODUCTS
    // Si se introduce el alphacode, entonces tambien para buscar el producto por alphacode...
    ProductInfo  getProductInfo(QString code);
    qulonglong   getProductOfferCode(qulonglong code);
    qulonglong   getProductCode(QString text);
    QList<qulonglong> getProductsCode(QString regExpName);
    QStringList  getProductsList();
    bool         insertProduct(ProductInfo info);
    bool         updateProduct(ProductInfo info, qulonglong oldcode);
    bool         decrementProductStock(qulonglong code, double qty, QDate date);
    bool         incrementProductStock(qulonglong code, double qty);
    double       getProductDiscount(qulonglong code);
    QList<pieProdInfo>  getTop5SoldProducts();
    QList<pieProdInfo>  getAlmostSoldOutProducts(int min, int max);

    //CATEGORIES
    QHash<QString, int> getCategoriesHash();
    QStringList getCategoriesList();
    qulonglong  getCategoryId(QString texto);
    QString     getCategoryStr(qulonglong id);
    bool        insertCategory(QString text);

    //MEASURES
    QStringList getMeasuresList();
    qulonglong  getMeasureId(QString texto);
    QString     getMeasureStr(qulonglong id);
    bool        insertMeasure(QString text);

    //OFFERS
    bool         createOffer(OfferInfo info);
    bool         deleteOffer(qlonglong id);
    QString      getOffersFilterWithText(QString text); //get all products with desc=text as a regexp that has discounts.
    bool         moveOffer(qulonglong oldp, qulonglong newp);

    //USERS
    bool         updateUser(UserInfo info);
    QString      getUserName(QString username); //gets the user name from username
    unsigned int getUserId(QString uname);
    QHash<QString,UserInfo> getUsersHash();
    bool         insertUser(UserInfo info);

    //CLIENTS
    bool         insertClient(ClientInfo info);
    bool         updateClient(ClientInfo info);
    bool         incrementClientPoints(qulonglong id, qulonglong points);
    bool         decrementClientPoints(qulonglong id, qulonglong points);
    ClientInfo   getClientInfo(qulonglong clientId);
    QHash<QString, ClientInfo> getClientsHash();
    QString      getMainClient();
    unsigned int getClientId(QString uname);

    //TRANSACTIONS
    TransactionInfo getTransactionInfo(qulonglong id);
    qulonglong  insertTransaction(TransactionInfo info);
    QList<TransactionInfo> getDayTransactions(int terminal);
    AmountAndProfitInfo    getDaySalesAndProfit(int terminal);
    QList<TransactionInfo> getMonthTransactions();
    ProfitRange getMonthProfitRange();
    ProfitRange getMonthSalesRange();
    bool        updateTransaction(TransactionInfo info);
    bool        cancelTransaction(qulonglong id, bool inProgress);
    bool        deleteTransaction(qulonglong id);
    bool        deleteEmptyTransactions();
    QList<TransactionInfo> getLastTransactions(int pageNumber=1,int numItems=20,QDate beforeDate=QDate::currentDate ());
    QList<TransactionInfo> getTransactionsPerDay(int pageNumber=1,int numItems=20,QDate beforeDate=QDate::currentDate ());
    
    // TRANSACTIONITEMS
    bool        insertTransactionItem(TransactionItemInfo info);
    bool        deleteAllTransactionItem(qulonglong id);
    QList<TransactionItemInfo> getTransactionItems(qulonglong id);

    
    //BALANCES
    qulonglong  insertBalance(BalanceInfo info);

    //CASHOUTS
    qulonglong insertCashFlow(CashFlowInfo info);

    //PayTypes
    QString     getPayTypeStr(qulonglong type);
    qulonglong  getPayTypeId(QString type);

    //TAX MODELS
    double      getTotalTaxPercent(const QString& elementsid);

};

#endif
