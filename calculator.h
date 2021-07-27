#ifndef CALCULATORCLASS_H
#define CALCULATORCLASS_H

#include<QObject>
#include<QStack>
#include<QChar>
#include<QDebug>
#include<QStringRef>

class Calculator: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainResult READ mainResult WRITE setmainResult NOTIFY mainResultChanged)

signals:
    void mainResultChanged(QString mainResult);
public:
    int checkPriority(QChar c);
    bool isNumber(QChar c);
    QString convertInfixToPostFix(QString expression);
    QString convertSymbolCharacterToOperator(QString symbolCharacter);
    int calculate(QString expression);
    static Calculator* getInstance();
    Q_INVOKABLE void addElementToExpression(QString element);

    QString mainResult() const;
    void setmainResult(const QString &_mainResult);
private:
    Calculator();
    ~Calculator();
private:
    QString m_expressionForDisplay;
    QString m_expressionForCalculate;
    QString m_mainResult;
};

#endif // CALCULATORCLASS_H
