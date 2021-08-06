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
    Q_PROPERTY(QString sizeOfData READ sizeOfData WRITE setSizeOfData NOTIFY sizeOfDataChanged)
    Q_PROPERTY(QString hexResult READ hexResult WRITE setHexResult NOTIFY hexResultChanged)
    Q_PROPERTY(QString decResult READ decResult WRITE setDecResult NOTIFY decResultChanged)
    Q_PROPERTY(QString octResult READ octResult WRITE setOctResult NOTIFY octResultChanged)
    Q_PROPERTY(QString binResult READ binResult WRITE setBinResult NOTIFY binResultChanged)


signals:
    void mainResultChanged(QString mainResult);
    void historyExpressionChanged(QString mainResult);
    void sizeOfDataChanged(QString sizeOfData);
    void hexResultChanged(QString hexResult);
    void decResultChanged(QString decResult);
    void octResultChanged(QString octResult);
    void binResultChanged(QString binResult);
public:
    int checkPriority(QChar _element);
    bool isNumber(QChar _element);
    bool isOperator(QChar _element);
    QString convertInfixToPostFix(QString _expression);
    QString convertSymbolCharacterToOperator(QString _symbolCharacter);
    QString calculate(QString _expression);
    static Calculator* getInstance();
    //Q_INVOKABLE void onKeypadButtonClicked(QString _element);
    Q_INVOKABLE void onDigitKeypadButtonCliked(QString _element);
    Q_INVOKABLE void onOperatorKeypadButtonClicked(QString _element);

    QString mainResult() const;
    void setMainResult(const QString &_mainResult);
    QString historyExpression() const;
    void setHistoryExpression(const QString &_historyExpression);
    QString sizeOfData() const;
    void setSizeOfData(const QString &_sizeOfData);

    Q_INVOKABLE void onChangeSizeOfDataFunctionButtonClicked();

    QString convertDecimalToBinary(QString _decimalString);
    QString convertBinaryToHex(QString _binaryString);
    QString convertBinaryToOctal(QString _binaryString);

    QString hexResult();
    void setHexResult(QString _hexResult);
    QString decResult();
    void setDecResult(QString _decResult);
    QString octResult();
    void setOctResult(QString _octResult);
    QString binResult();
    void setBinResult(QString _binResult);

    void setSubResult(QString _decimalString);

    Q_INVOKABLE void onDeleteButtonClicked(QString _element);
    void setResult(QString _decimalString);
private:
    Calculator();
    ~Calculator();
private:
    QString m_expressionForDisplay;
    QString m_expressionForCalculate;
    QString m_mainResult;
    QString m_historyExpression;
    QString m_lastOperator;
    QString m_sizeOfData;
    QString m_binResult;
    QString m_hexResult;
    QString m_octResult;
    QString m_decResult;
    bool m_isCalculated;
    bool m_isEquaButtonlPressed;
};

#endif // CALCULATORCLASS_H
