#include "randomnumbergenerator.h"

RandomNumberGenerator::RandomNumberGenerator(QObject *parent)
    : QObject{parent}
{

}

RandomNumberGenerator::generateRandomNumber(int min, int max){
    int randomNumber = QRandomGenerator::global()->bounded(min, max+1);
    emit randomNumberGenerated(randomNumber);
    return randomNumber;
}
