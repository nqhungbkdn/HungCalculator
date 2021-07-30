#include "calculator.h"


Calculator::Calculator()
{
    m_lastOperator ="+";
    m_historyExpression = "";
    m_mainResult = "0";
    m_typeOfData = "QWORD";
    m_expressionForCalculate = "";
    m_expressionForDisplay = "";
    m_decResult = "0";
    m_octResult = "0";
    m_hexResult = "0";
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
    qDebug() << "Infix: " << _expression;
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
    qDebug() << "Postfix: " << result;
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
    qDebug() << "result of Calculate: " << calculateStack.top();
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

void Calculator::onDigitKeypadButtonCliked(QString _element)
{
    m_expressionForCalculate += _element;
    m_expressionForDisplay+=_element;
    int startIndexOfNumber = m_expressionForDisplay.length()-1;
    while(m_expressionForDisplay[startIndexOfNumber].isNumber())
    {
        startIndexOfNumber--;
        if(startIndexOfNumber <0)
            break;
    }
    QStringRef temp(&m_expressionForDisplay, startIndexOfNumber+1,m_expressionForDisplay.length()-startIndexOfNumber-1);
    setMainResult(temp.toString());
    setSubResult(m_mainResult);
}

void Calculator::onOperatorKeypadButtonClicked(QString _element)
{
    if(_element=="C")
    {
        m_expressionForCalculate = "";
        m_expressionForDisplay = "";
        setMainResult("0");
        setHistoryExpression("");
        return;
    }

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

    if(_element == "⌫")
    {
        if(m_mainResult.length()==1 && m_mainResult[0] == "0")
            return;
        m_expressionForCalculate.chop(1);
        m_expressionForDisplay.chop(1);
    }

    QString elementAfterConvert = convertSymbolCharacterToOperator(_element);


    if(elementAfterConvert == "=") // "=" button clicked
    {
        int resultOfCalculate = calculate(m_expressionForCalculate);
        setMainResult(QString::number(resultOfCalculate));
        setSubResult(m_mainResult);
        setHistoryExpression("");
        if(resultOfCalculate < 0)
        {
            m_expressionForCalculate = "0" + QString::number(resultOfCalculate);
            m_expressionForDisplay = QString::number(resultOfCalculate);
        }
        else
        {
            m_expressionForDisplay = QString::number(resultOfCalculate);
            m_expressionForCalculate = QString::number(resultOfCalculate);
        }
    }
    else
    {

        if(m_expressionForCalculate.back()=="+" || m_expressionForCalculate.back()=="-" || m_expressionForCalculate.back()=="*" || m_expressionForCalculate.back()=="/")
        {
            if(m_expressionForCalculate.isEmpty())
                m_expressionForCalculate.append("0");
            if(elementAfterConvert==m_expressionForCalculate.back())
            {
                return;
            }
            m_expressionForCalculate.chop(1);
            m_expressionForDisplay.chop(1);
        }
        m_expressionForCalculate += elementAfterConvert;
        m_expressionForDisplay+=_element;
        setHistoryExpression(m_expressionForDisplay);
        if(checkPriority(elementAfterConvert[0]) <= checkPriority(m_lastOperator[0]))
        {
            QStringRef temp(&m_expressionForCalculate, 0, m_expressionForCalculate.length()-1);
            setMainResult(QString::number(calculate(temp.toString())));
            //setBinResult(convertDecimalToBinary(m_mainResult));
        }
        m_lastOperator = elementAfterConvert;
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
    // Need to handle negative number!
    QString PositiveBinaryString;
    bool isNegative = false;
    int decimal = _decimalString.toInt();
    if(decimal<0)
    {
        isNegative = true;
        decimal = - decimal;
    }
    qDebug() << "decimal: " <<decimal ;
    while(decimal > 0)
    {
        PositiveBinaryString.prepend(QString::number(decimal%2));
        decimal = decimal / 2;
    }
    while((PositiveBinaryString.length()%4)!=0)
    {
        PositiveBinaryString.prepend("0");
    }

    for(int index = PositiveBinaryString.length()-1; index>0; index --)
    {
        if(index%4==0)
            PositiveBinaryString.insert(index," ");
    }

    if(isNegative == false)
    {
        qDebug() << "Positive binary: " << PositiveBinaryString;
        return PositiveBinaryString;
    }
    else
    {
        QString makeUpBinaryString = "";
        QString negativeBinaryString = "";
        QString carry = "0";
        for(int index = 0; index < PositiveBinaryString.length(); index++)
        {
            if(PositiveBinaryString[index]=='0')
                PositiveBinaryString[index] ='1';
            else if(PositiveBinaryString[index] == '1')
                PositiveBinaryString[index] = '0';
            else {
                PositiveBinaryString[index] = ' ';
            }
        }
        qDebug() << "Ngich dao: " << PositiveBinaryString;
        for(int index = 0; index < PositiveBinaryString.length() -1; index++)
        {
            if(PositiveBinaryString[index] == ' ')
                makeUpBinaryString.append(' ');
            else
                makeUpBinaryString.append('0');
        }
        makeUpBinaryString.append('1');

        qDebug() << "makeUpBinaryString: " << makeUpBinaryString;
        for(int i = PositiveBinaryString.length()-1; i>=0; i--)
        {
            if(PositiveBinaryString[i] == makeUpBinaryString[i])
            {
                if(PositiveBinaryString[i]=='0' && carry == '0')
                {
                    negativeBinaryString.prepend('0');
                }
                else if(PositiveBinaryString[i]=='1' && carry == '0')
                {
                    negativeBinaryString.prepend('0');
                    carry = '1';
                }
                else if(PositiveBinaryString[i] == '0' && carry == '1')
                {
                    negativeBinaryString.prepend('1');
                    carry = '0';
                }
                else if(PositiveBinaryString[i] == '1' && carry == '1')
                {
                    negativeBinaryString.prepend('1');
                    carry = '1';
                }
                else
                {
                    negativeBinaryString.prepend(' ');
                }
            }
            else
            {
                if(carry == '0')
                {
                    negativeBinaryString.prepend('1');
                    carry ='0';
                }
                else
                {
                    negativeBinaryString.prepend('1');
                    carry = '1';
                }
            }
            qDebug() << "result*: " << negativeBinaryString;
        }
        qDebug() << "result: " << negativeBinaryString;
        return negativeBinaryString;
    }
}

QString Calculator::convertBinaryToHex(QString _binaryString)
{
    QString hexString;
    QString binaryString = _binaryString;
    qDebug() << "binaryString: " << binaryString;
    binaryString.remove(' ');

    for(int index = 0; index < binaryString.length()-1; index+=4)
    {
        qDebug() << "binaryString.mid(index,4): " << binaryString.mid(index,4);
        if(binaryString.mid(index,4) == "0000")
            hexString.append('0');
        else if(binaryString.mid(index,4) == "0001")
            hexString.append('1');
        else if(binaryString.mid(index,4) == "0010")
            hexString.append('2');
        else if(binaryString.mid(index,4) == "0011")
            hexString.append('3');
        else if(binaryString.mid(index,4) == "0100")
            hexString.append('4');
        else if(binaryString.mid(index,4) == "0101")
            hexString.append('5');
        else if(binaryString.mid(index,4) == "0110")
            hexString.append('6');
        else if(binaryString.mid(index,4) == "0111")
            hexString.append('7');
        else if(binaryString.mid(index,4) == "1000")
            hexString.append('8');
        else if(binaryString.mid(index,4) == "1001")
            hexString.append('9');
        else if(binaryString.mid(index,4) == "1010")
            hexString.append('A');
        else if(binaryString.mid(index,4) == "1011")
            hexString.append('B');
        else if(binaryString.mid(index,4) == "1100")
            hexString.append('C');
        else if(binaryString.mid(index,4) == "1101")
            hexString.append('D');
        else if(binaryString.mid(index,4) == "1110")
            hexString.append('E');
        else
            hexString.append('F');
    }

    for(int index = hexString.length() - 4; index>0; index-=4)
    {
            hexString.insert(index," ");
    }
    qDebug() << "hexString: " << hexString;
    return hexString;
}

QString Calculator::convertBinaryToOctal(QString _binaryString)
{
    QString octalString;
    QString binaryString = _binaryString;
    qDebug() << "binaryString: " << binaryString;
    binaryString.remove(' ');

    while(binaryString.front()=='0')
        binaryString.remove(0, 1);

    while((binaryString.length()%3) != 0)
    {
        binaryString.prepend('0');
    }
    for(int index = 0; index < binaryString.length()-1; index+=3)
    {
        if(binaryString.mid(index,3) == "000")
            octalString.append('0');
        else if(binaryString.mid(index,3) == "001")
            octalString.append('1');
        else if(binaryString.mid(index,3) == "010")
            octalString.append('2');
        else if(binaryString.mid(index,3) == "011")
            octalString.append('3');
        else if(binaryString.mid(index,3) == "100")
            octalString.append('4');
        else if(binaryString.mid(index,3) == "101")
            octalString.append('5');
        else if(binaryString.mid(index,3) == "110")
            octalString.append('6');
        else
            octalString.append('7');
    }
    for(int index = octalString.length() - 3; index>0; index-=3)
    {
            octalString.insert(index," ");
    }
    qDebug() << "octalString: " << octalString;
    return octalString;
}

QString Calculator::hexResult()
{
    return m_hexResult;
}

void Calculator::setHexResult(QString _hexResult)
{
    if(m_hexResult == _hexResult)
        return;
    m_hexResult = _hexResult;
    emit hexResultChanged(m_hexResult);
}

QString Calculator::decResult()
{
    return m_decResult;
}

void Calculator::setDecResult(QString _decResult)
{
    if(m_decResult == _decResult)
        return;
    m_decResult = _decResult;
    emit decResultChanged(m_decResult);
}

QString Calculator::octResult()
{
    return m_octResult;
}

void Calculator::setOctResult(QString _octResult)
{
    if(m_octResult == _octResult)
        return;
    m_octResult = _octResult;
    emit octResultChanged(m_octResult);
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

void Calculator::setSubResult(QString _decimalString)
{
    setDecResult(_decimalString);
    setBinResult(convertDecimalToBinary(_decimalString));
    setHexResult(convertBinaryToHex(convertDecimalToBinary(_decimalString)));
    setOctResult(convertBinaryToOctal(convertDecimalToBinary(_decimalString)));
}
