#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QVariantList>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    Q_INVOKABLE bool initializeDatabase(const QString &dbName);
    Q_INVOKABLE bool insertCounterValue(int value);
    Q_INVOKABLE QVariantList fetchAllCounterValues();
    Q_INVOKABLE bool updateCounterValue(int oldValue, int newValue);
    Q_INVOKABLE bool deleteCounterValue(int value);

signals:
    void errorOccurred(const QString &error);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
