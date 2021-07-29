#include "calculator.h"


Calculator::Calculator()
{
    m_lastOperator ="+";
    m_historyExpression = "";
    m_mainResult = "0";
    m_typeOfData = "QWORD";
    m_expressionForCalculate = "";
    m_expressionForDisplay = "";
    m_binResult = "0";
}

Calculator::~Calculator()
{

}

int Calculator::checkPriority(QChar _element)
{
    if(_element == '+' || _element == '-')
        return 1;
    if(_element == '*' || _element == '/' || _element == '%')
        return 2;
    return 0;
}

bool Calculator::isNumber(QChar _element)
{
    return ((_element >= '0' && _element <= '9'));
}

QString Calculator::convertInfixToPostFix(QString _expression)
{
    QString result ="";
    QStack<QChar> convertStack;
    for (int index = 0; index < _expression.length(); index++)
    {
        if (_expression[index] == '+' || _expression[index] == '-' || _expression[index] == '/' || _expression[index] == '*' || _expression[index] == '%')
        {
            if(!convertStack.empty())
            {
                while(checkPriority(convertStack.top()) >= checkPriority(_expression[index]))
                {
                    result += convertStack.pop();
                    if(convertStack.empty())
                        break;
                }
            }
            convertStack.push(_expression[index]);
        }

        if (_expression[index] >= '0' && _expression[index] <= '9')
        {
            int pos = index;
            while (isNumber(_expression[index]))
            {
                index++;
                if (index == _expression.length())
                    break;
            }
            QStringRef subString(&_expression, pos, index - pos);
            result += subString + '#';
            index--;
        }

        if (_expression[index] == '(')
        {
            convertStack.push('(');
        }

        if (_expression[index] == ')')
        {
            QChar tmp = convertStack.pop();
            while (tmp != '(')
            {
                result += tmp;
                tmp = convertStack.pop();
            }
        }
    }

    while (!convertStack.empty())
    {
        result += convertStack.pop();
    }
    return result;
}

QString Calculator::convertSymbolCharacterToOperator(QString _symbolCharacter)
{
    if(_symbolCharacter == "×")
        return "*";
    if(_symbolCharacter == "÷")
        return "/";
    if(_symbolCharacter == "Mod")
        return "%";

    return _symbolCharacter;
}

int Calculator::calculate(QString _expression)
{
    //    qDebug() << _expression;
    QString PostfixExpression = convertInfixToPostFix(_expression);
    QStack<int> calculateStack;
    int operand1, operand2;

    for (int index = 0; index < PostfixExpression.length(); index++)
    {
        if(PostfixExpression[index]=='*')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand1 * operand2);
        }
        else if(PostfixExpression[index]=='/')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 / operand1);
        }
        else if(PostfixExpression[index]=='%')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 % operand1);
        }
        else if(PostfixExpression[index]=='-')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 - operand1);
        }
        else if(PostfixExpression[index]=='+')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand1 + operand2);
        }
        else{
            if(isNumber(PostfixExpression[index]))
            {
                int operandStartPosition = index;
                while(isNumber(PostfixExpression[index]))
                    index++;
                QStringRef subString(&PostfixExpression, operandStartPosition, index - operandStartPosition);
                calculateStack.push(subString.toInt());
            }
        }
    }
    return calculateStack.top();
}

Calculator *Calculator::getInstance()
{
    static Calculator* m_instance = nullptr;
    if (m_instance == nullptr) {
        m_instance = new Calculator();
    }
    return m_instance;
}

void Calculator::onKeypadButtonClicked(QString _element)
{
    if(_element == ".")
        return;

    QString elementAfterConvert = convertSymbolCharacterToOperator(_element);
    if(_element=="CE")
    {
        if(m_mainResult == "0")
            return;

        while(isNumber(m_expressionForDisplay[m_expressionForDisplay.length()-1]))
        {
            m_expressionForCalculate.chop(1);
            m_expressionForDisplay.chop(1);
            if(m_expressionForDisplay.isEmpty())
            {
                setMainResult("0");
                return;
            }
        }
        setMainResult("0");
        return;
    }

    if(_element=="C")
    {
        m_expressionForCalculate = "";
        m_expressionForDisplay = "";
        setMainResult("0");
        setHistoryExpression("");
        return;
    }

    if(_element == "⌫")
    {
        if(m_expressionForCalculate.isEmpty())
            return;
        if(!m_expressionForCalculate.back().isNumber())
        {
            setMainResult("0");
            return;
        }
        m_expressionForCalculate.chop(1);
        m_expressionForDisplay.chop(1);

        int index = m_expressionForCalculate.length()-1;
        while(m_expressionForCalculate[index].isNumber())
        {
            index--;
        }
        if(index == m_expressionForCalculate.length()-1)
        {
            setMainResult("0");
            return;
        }
        else
        {
            setMainResult(m_expressionForCalculate.right(m_expressionForCalculate.length()-index-1));
            return;
        }
    }

    if(elementAfterConvert != "="){
        m_expressionForCalculate += elementAfterConvert;
        m_expressionForDisplay+=_element;
        if(elementAfterConvert == "+" || elementAfterConvert == "-" || elementAfterConvert == "*" || elementAfterConvert == "/" || elementAfterConvert == "(" || elementAfterConvert == ")")
        {
            setHistoryExpression(m_expressionForDisplay);

            if(checkPriority(elementAfterConvert[0]) <= checkPriority(m_lastOperator[0]))
            {
                //if(m_expressionForCalculate.length()>=3)
                {
                    QStringRef temp(&m_expressionForCalculate, 0, m_expressionForCalculate.length()-1);
                    setMainResult(QString::number(calculate(temp.toString())));
                    setBinResult(convertDecimalToBinary(m_mainResult));
                }
            }
            m_lastOperator = elementAfterConvert;
        }
        else if(elementAfterConvert>='0'&&elementAfterConvert<='9')
        {
            int startIndexOfNumber = m_expressionForDisplay.length()-1;
            while(m_expressionForDisplay[startIndexOfNumber].isNumber())
            {
                startIndexOfNumber--;
                if(startIndexOfNumber <0)
                    break;
            }
            QStringRef temp(&m_expressionForDisplay, startIndexOfNumber+1,m_expressionForDisplay.length()-startIndexOfNumber-1);
            setMainResult(temp.toString());
            setBinResult(convertDecimalToBinary(m_mainResult));
        }
    }
    else
    {
        setMainResult(QString::number(calculate(m_expressionForCalculate)));
        setHistoryExpression(m_expressionForDisplay + "=");
        if(calculate(m_expressionForCalculate)<0)
        {
            m_expressionForCalculate = "(0"+ QString::number(calculate(m_expressionForCalculate)) + ")";
        }
        else
        {
            m_expressionForDisplay = QString::number(calculate(m_expressionForCalculate));
            m_expressionForCalculate = QString::number(calculate(m_expressionForCalculate));
        }
        qDebug() << m_expressionForCalculate;
    }
}

QString Calculator::mainResult() const
{
    return m_mainResult;
}

void Calculator::setMainResult(const QString &_mainResult)
{
    if(_mainResult==m_mainResult)
        return;
    m_mainResult = _mainResult;
    emit mainResultChanged(m_mainResult);
}

QString Calculator::historyExpression() const
{
    return m_historyExpression;
}

void Calculator::setHistoryExpression(const QString &_historyExpression)
{
    if(_historyExpression==m_historyExpression)
        return;
    m_historyExpression = _historyExpression;
    emit historyExpressionChanged(m_historyExpression);
}

QString Calculator::typeOfData() const
{
    return m_typeOfData;
}

void Calculator::setTypeOfData(const QString &_typeOfData)
{
    if(_typeOfData==m_typeOfData)
        return;
    m_typeOfData = _typeOfData;
    emit typeOfDataChanged(m_typeOfData);
}

void Calculator::onChangeTypeFunctionButtonClicked()
{
    if(m_typeOfData=="BYTE")
        setTypeOfData("QWORD");
    else if(m_typeOfData=="QWORD")
        setTypeOfData("DWORD");
    else if(m_typeOfData=="DWORD")
        setTypeOfData("WORD");
    else if(m_typeOfData=="WORD")
        setTypeOfData("BYTE");
}

QString Calculator::convertDecimalToBinary(QString _decimalString)
{
    int decimalNumber = _decimalString.toInt();
    qDebug() << decimalNumber;
    QString result;
    for(int i =0; decimalNumber>0; i++)
    {
        result.append(QString::number(decimalNumber%2));
        decimalNumber=decimalNumber/2;
    }
    qDebug() << result;
    return result;
}

QString Calculator::binResult()
{
    return m_binResult;
}

void Calculator::setBinResult(QString _binResult)
{
    if(m_binResult == _binResult)
        return;
    m_binResult = _binResult;
    emit binResultChanged(m_binResult);
}
