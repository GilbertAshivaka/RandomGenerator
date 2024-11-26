#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

    Q_INVOKABLE void saveToFile(const QString &filename, const QList<int> &data);
    Q_INVOKABLE QString loadFromFile(const QString &filename);

signals:
    void fileError (const QString &message);
    void fileSaved (const QString &filename);
    void fileLoaded (const QString &data);

};

#endif // FILEHANDLER_H
