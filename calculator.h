#ifndef CALCULATORCLASS_H
#define CALCULATORCLASS_H

#include<QObject>
#include<QStack>
#include<QChar>
#include<QDebug>
#include<QStringRef>

class calculator: public QObject
{
public:
    calculator();
    int checkPriority(QChar c);
    bool isNumber(QChar c);
    QString convertInfixToPostFix(QString expression);
    int calculate(QString expression);
private:
    QString m_mainResultValue;
};

#endif // CALCULATORCLASS_H
