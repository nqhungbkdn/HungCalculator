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
    Q_PROPERTY(QString mainResult READ mainResult WRITE setMainResult NOTIFY mainResultChanged)
    Q_PROPERTY(QString historyExpression READ historyExpression WRITE setHistoryExpression NOTIFY historyExpressionChanged)
    Q_PROPERTY(QString typeOfData READ typeOfData WRITE setTypeOfData NOTIFY typeOfDataChanged)
    Q_PROPERTY(QString binResult READ binResult WRITE setBinResult NOTIFY binResultChanged)

signals:
    void mainResultChanged(QString mainResult);
    void historyExpressionChanged(QString mainResult);
    void typeOfDataChanged(QString typeOfData);
    void binResultChanged(QString binResult);
public:
    int checkPriority(QChar _element);
    bool isNumber(QChar _element);
    QString convertInfixToPostFix(QString _expression);
    QString convertSymbolCharacterToOperator(QString _symbolCharacter);
    int calculate(QString _expression);
    static Calculator* getInstance();
    Q_INVOKABLE void onKeypadButtonClicked(QString _element);

    QString mainResult() const;
    void setMainResult(const QString &_mainResult);
    QString historyExpression() const;
    void setHistoryExpression(const QString &_historyExpression);
    QString typeOfData() const;
    void setTypeOfData(const QString &_typeOfData);

    Q_INVOKABLE void onChangeTypeFunctionButtonClicked();

    QString convertDecimalToBinary(QString _decimalString);

    QString binResult();
    void setBinResult(QString _binResult);

    void connectSignalsToSlots();



private:
    Calculator();
    ~Calculator();
private:
    QString m_expressionForDisplay;
    QString m_expressionForCalculate;
    QString m_mainResult;
    QString m_historyExpression;
    QString m_lastOperator;
    QString m_typeOfData;
    QString m_binResult;
    QString m_hexResult;
    QString m_octResult;
    QString m_decResult;
};

#endif // CALCULATORCLASS_H
