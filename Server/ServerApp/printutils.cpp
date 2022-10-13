#include <iostream>
#include <QDebug>
#include "printutils.h"

PrintUtils* PrintUtils::instance;

PrintUtils::PrintUtils()
{

}

int PrintUtils::PrintErrorText(const QString &errorText, int errorNo)
{
    qDebug() << COLOR_RED << errorText << COLOR_RESET;
    return errorNo;
}

int PrintUtils::PrintErrorText(const QString &errorText, int errorNo, int value)
{
    qDebug() << COLOR_RED << errorText << " : " << value << COLOR_RESET;
    return errorNo;
}

void PrintUtils::PrintSuccessText(const QString &Text)
{
    qDebug() << COLOR_RED << Text << COLOR_RESET;
}

PrintUtils *PrintUtils::getInstance()
{
    if (instance == NULL)
        instance = new PrintUtils();
    return instance;
}


