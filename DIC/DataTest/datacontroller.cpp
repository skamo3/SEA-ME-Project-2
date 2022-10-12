#include "datacontroller.h"

DataController::DataController(QObject *parent)
    : QObject{parent}, Number("0")
{

}

void DataController::setNum(int num)
{
    Number.setNum(num);
    emit numchanged();
}

void DataController::increase()
{
    Number.setNum(Number.toInt() + 1);
    emit numchanged();
}

void DataController::decrease()
{
    Number.setNum(Number.toInt() - 1);
    emit numchanged();
}

QString DataController::getNum() const
{
    return Number;
}
