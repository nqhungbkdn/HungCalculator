#include "calculator.h"

calculator::calculator()
{

}

int calculator::checkPriority(QChar c)
{
    if(c == '+' || c == '-')
        return 1;
    if(c == '*' || c == '/')
        return 2;
    return 0;
}

bool calculator::isNumber(QChar c)
{
    return ((c >= '0' && c <= '9'));
}

QString calculator::convertInfixToPostFix(QString expression)
{
    QString result ="";
    QStack<QChar> convertStack;
    for (int index = 0; index < expression.length(); index++)
    {
        if (expression[index] == '+' || expression[index] == '-' || expression[index] == '/' || expression[index] == '*')
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

int calculator::calculate(QString expression)
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
