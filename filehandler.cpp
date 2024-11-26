#include "filehandler.h"

FileHandler::FileHandler(QObject *parent)
    : QObject{parent}
{

}

void FileHandler::saveToFile(const QString &filename, const QList<int> &data){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        emit fileError("Could not open file for writing");
        return;
    }

    QTextStream out(&file);
    QStringList dataStrings;
    for (int value : data){
        dataStrings << QString::number(value);
    }
    out << dataStrings.join(",");
    file.close();
    emit fileSaved(filename);
}

QString FileHandler::loadFromFile(const QString &filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        emit fileError("Could not open file for reading.");
        return QString();
    }

    QTextStream in(&file);
    QString data = in.readAll();
    file.close();
    emit fileLoaded(data);
    return data;
}













