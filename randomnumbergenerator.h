#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <QObject>
#include <QRandomGenerator>

class RandomNumberGenerator : public QObject
{
    Q_OBJECT
public:
    explicit RandomNumberGenerator(QObject *parent = nullptr);

    Q_INVOKABLE int generateRandomNumber(int min, int max);

signals:
    void randomNumberGenerated(int randomNumber);

};

#endif // RANDOMNUMBERGENERATOR_H
