#include "calculator.h"


Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}

int Calculator::checkPriority(QChar c)
{
    if(c == '+' || c == '-')
        return 1;
    if(c == '*' || c == '/' || c == '%')
        return 2;
    return 0;
}

bool Calculator::isNumber(QChar c)
{
    return ((c >= '0' && c <= '9'));
}

QString Calculator::convertInfixToPostFix(QString expression)
{
    QString result ="";
    QStack<QChar> convertStack;
    for (int index = 0; index < expression.length(); index++)
    {
        if (expression[index] == '+' || expression[index] == '-' || expression[index] == '/' || expression[index] == '*' || expression[index] == '%')
        {
            if(!convertStack.empty())
            {
                if (checkPriority(convertStack.top()) >= checkPriority(expression[index]))
                {
                    result += convertStack.pop();
                }
            }
            convertStack.push(expression[index]);
        }

        if (expression[index] >= '0' && expression[index] <= '9')
        {
            int pos = index;
            while (isNumber(expression[index]))
            {
                index++;
                if (index == expression.length())
                    break;
            }
            QStringRef subString(&expression, pos, index - pos);
            result += subString + '#';
            index--;
        }

        if (expression[index] == '(')
        {
            convertStack.push('(');
        }

        if (expression[index] == ')')
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

QString Calculator::convertSymbolCharacterToOperator(QString symbolCharacter)
{
    if(symbolCharacter == "X")
        return "*";
    if(symbolCharacter == "÷")
        return "/";
    if(symbolCharacter == "Mod")
        return "%";

    return symbolCharacter;
}

int Calculator::calculate(QString expression)
{
    QString PostfixExpression = convertInfixToPostFix(expression);
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
            calculateStack.push(operand1 / operand2);
        }
        else if(PostfixExpression[index]=='%')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand1 % operand2);
        }
        else if(PostfixExpression[index]=='-')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand1 - operand2);
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

void Calculator::addElementToExpression(QString _element)
{
    if(_element == "⌫")
    {
        if(m_expressionForCalculate.isEmpty())
            return;
        m_expressionForCalculate.chop(1);
        m_expressionForDisplay.chop(1);
        setmainResult(m_expressionForDisplay);
        return;
    }

    QString elementAfterConvert = convertSymbolCharacterToOperator(_element);
    if(elementAfterConvert == "=" && !m_expressionForCalculate.isEmpty())
    {
        setmainResult(QString::number(calculate(m_expressionForCalculate)));
        qDebug() << m_expressionForCalculate;
    }
    else if(elementAfterConvert != "=")
    {
        m_expressionForCalculate += elementAfterConvert;
        m_expressionForDisplay+=_element;
        setmainResult(m_expressionForDisplay);
        qDebug() << m_mainResult;
    }
}

QString Calculator::mainResult() const
{
    return m_mainResult;
}

void Calculator::setmainResult(const QString &_mainResult)
{
    if(_mainResult==m_mainResult)
        return;
    m_mainResult = _mainResult;
    emit mainResultChanged(m_mainResult);
}
