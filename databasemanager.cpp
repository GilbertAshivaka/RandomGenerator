#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initializeDatabase(const QString &dbName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);

    if (!m_db.open()) {
        emit errorOccurred("Failed to open database: " + m_db.lastError().text());
        return false;
    }

    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS counter (id INTEGER PRIMARY KEY AUTOINCREMENT, value INTEGER)";
    if (!query.exec(createTableQuery)) {
        emit errorOccurred("Failed to create table: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DatabaseManager::insertCounterValue(int value)
{
    if (!m_db.isOpen()) {
//        emit errorOccurred("Database is not open.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO counter (value) VALUES (:value)");
    query.bindValue(":value", value);

    if (!query.exec()) {
        emit errorOccurred("Failed to insert value: " + query.lastError().text());
        return false;
    }

    return true;
}

QVariantList DatabaseManager::fetchAllCounterValues()
{
    QVariantList values;
    if (!m_db.isOpen()) {
        emit errorOccurred("Database is not open.");
        return values;
    }

    QSqlQuery query("SELECT value FROM counter");
    while (query.next()) {
        values.append(query.value(0).toInt());
    }

    return values;
}

bool DatabaseManager::updateCounterValue(int oldValue, int newValue)
{
    if (!m_db.isOpen()) {
        emit errorOccurred("Database is not open.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE counter SET value = :newValue WHERE value = :oldValue");
    query.bindValue(":newValue", newValue);
    query.bindValue(":oldValue", oldValue);

    if (!query.exec()) {
        emit errorOccurred("Failed to update value: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DatabaseManager::deleteCounterValue(int value)
{
    if (!m_db.isOpen()) {
        emit errorOccurred("Database is not open.");
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM counter WHERE value = :value");
    query.bindValue(":value", value);

    if (!query.exec()) {
        emit errorOccurred("Failed to delete value: " + query.lastError().text());
        return false;
    }

    return true;
}
