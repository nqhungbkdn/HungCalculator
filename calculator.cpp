#include "calculator.h"


Calculator::Calculator()
{
    m_lastOperator ="+";
    m_historyExpression = "";
    m_mainResult = "0";
    m_sizeOfData = "QWORD";
    m_expressionForCalculate = "";
    m_expressionForDisplay = "";
    m_decResult = "0";
    m_octResult = "0";
    m_hexResult = "0";
    m_binResult = "0";
    m_isCalculated = false;
    m_isEquaButtonlPressed = false;
}

Calculator::~Calculator()
{

}

int Calculator::checkPriority(QChar _element)
{
    if(_element == '|' || _element == '^')
        return 1;
    if(_element == '&')
        return 2;
    if(_element == '+' || _element == '-')
        return 3;
    if(_element == '*' || _element == '/' || _element == '%' || _element == '<' || _element == '>')
        return 4;
    if(_element == "~")
        return 5;
    return 0;
}

bool Calculator::isNumber(QChar _element)
{
    return ((_element >= '0' && _element <= '9'));
}

bool Calculator::isOperator(QChar _element)
{
    return(_element=="+" || _element=="-" || _element=="*" || _element=="/" || _element=="&" || _element=="|" || _element=="^" || _element=="<" || _element==">");
}

QString Calculator::convertInfixToPostFix(QString _expression)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Infix: " << _expression;
    QString result ="";
    QStack<QChar> convertStack;
    for (int index = 0; index < _expression.length(); index++)
    {
        if (_expression[index] == '+' || _expression[index] == '-' || _expression[index] == '/' || _expression[index] == '*' || _expression[index] == '%' || _expression[index] == '<' || _expression[index] == '>' || _expression[index] == '&' || _expression[index] == '|' || _expression[index] == '^' || _expression[index] == '~')
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
    if(_symbolCharacter == "Lsh")
        return "<";
    if(_symbolCharacter == "Rsh")
        return ">";
    if(_symbolCharacter == "And")
        return "&";
    if(_symbolCharacter == "Or")
        return "|";
    if(_symbolCharacter == "Xor")
        return "^";
    if(_symbolCharacter == "Not")
        return "~";

    return _symbolCharacter;
}

QString Calculator::calculate(QString _expression)
{
    qDebug() << Q_FUNC_INFO;
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
            if(operand1 == 0)
            {
                return "Cannot divide by zero";
            }
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
        else if(PostfixExpression[index]=='<')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 << operand1);
        }
        else if(PostfixExpression[index]=='>')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 >> operand1);
        }
        else if(PostfixExpression[index]=='&')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 & operand1);
        }
        else if(PostfixExpression[index]=='|')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 | operand1);
        }
        else if(PostfixExpression[index]=='^')
        {
            operand1 = calculateStack.pop();
            operand2 = calculateStack.pop();
            calculateStack.push(operand2 ^ operand1);
        }
        else if(PostfixExpression[index] == '~')
        {
            operand1 = calculateStack.pop();
            calculateStack.push(~operand1);
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
    return QString::number(calculateStack.top());
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
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Digit button clicked:" << _element;
    if(m_mainResult=="0" && _element == "0")
        return;
    if(m_isEquaButtonlPressed)
    {
        m_expressionForCalculate = "";
        m_expressionForDisplay = "";
    }
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
    m_isCalculated = false;
    m_isEquaButtonlPressed = false;
}

void Calculator::onOperatorKeypadButtonClicked(QString _element)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Operator button clicked:" << _element;
    if(_element=="Clear")
    {
        m_expressionForCalculate = "";
        m_expressionForDisplay = "";
        setMainResult("0");
        setSubResult("0");
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
                setSubResult("0");
                return;
            }
        }
        setMainResult("0");
        setSubResult("0");
        return;
    }

    if(_element == "⌫")
    {
        if((m_mainResult.length()==1 && m_mainResult[0] == "0") || !m_expressionForCalculate.back().isNumber() || m_isCalculated == true)
            return;
        m_expressionForCalculate.chop(1);
        m_expressionForDisplay.chop(1);
        if(m_mainResult.length()>1)
        {
            setMainResult(m_mainResult.left(m_mainResult.length()-1));
            setSubResult(m_mainResult);
        }
        else
        {
            setMainResult("0");
            setSubResult("0");
        }
    }

    QString elementAfterConvert = convertSymbolCharacterToOperator(_element);

    if(elementAfterConvert == "=") // "=" button clicked
    {
        if(m_expressionForCalculate.isEmpty())
            return;
        if(isOperator(m_expressionForCalculate.back()))
        {
            m_expressionForCalculate.append(m_mainResult);
            m_expressionForDisplay.append(m_mainResult);
        }
        QString resultOfCalculate = calculate(m_expressionForCalculate);
        setMainResult(resultOfCalculate);
        setSubResult(m_mainResult);
        setHistoryExpression("");
        if(resultOfCalculate.toInt() < 0)
        {
            m_expressionForCalculate = "0" + resultOfCalculate;
            m_expressionForDisplay = resultOfCalculate;
        }
        else
        {
            m_expressionForDisplay = resultOfCalculate;
            m_expressionForCalculate = resultOfCalculate;
        }
        m_isCalculated = true;
        m_isEquaButtonlPressed = true;
    }
    else if(elementAfterConvert == "+"||elementAfterConvert == "-"||elementAfterConvert == "*"||elementAfterConvert == "/" ||elementAfterConvert == "%" ||elementAfterConvert == "<" || elementAfterConvert == ">" || elementAfterConvert == "&" || elementAfterConvert == "|" || elementAfterConvert == "^")
    {
        m_isEquaButtonlPressed = false;
        if(m_expressionForCalculate.isEmpty()||m_expressionForCalculate.back()=='(')
        {
            m_expressionForCalculate.append("0");
            m_expressionForDisplay.append("0");
        }
        if(m_expressionForCalculate.back()=="+" || m_expressionForCalculate.back()=="-" || m_expressionForCalculate.back()=="*" || m_expressionForCalculate.back()=="/" || m_expressionForCalculate.back()=="%" || m_expressionForCalculate.back()=="<" || m_expressionForCalculate.back()==">" || m_expressionForCalculate.back()=="&" || m_expressionForCalculate.back()=="|" || m_expressionForCalculate.back()=="^")
        {
            if(elementAfterConvert == m_expressionForCalculate.back())
            {
                return;
            }
            m_expressionForCalculate.chop(1);
            m_expressionForDisplay.remove(m_expressionForDisplay.lastIndexOf(m_lastOperator),m_lastOperator.length());
        }
        m_expressionForCalculate += elementAfterConvert;
        m_expressionForDisplay += _element;
        setHistoryExpression(m_expressionForDisplay);
        if(checkPriority(elementAfterConvert[0]) <= checkPriority(convertSymbolCharacterToOperator(m_lastOperator)[0]))
        {
            QStringRef temp(&m_expressionForCalculate, 0, m_expressionForCalculate.length()-1);
            setMainResult(calculate(temp.toString()));
            setSubResult(m_mainResult);
            m_isCalculated = true;
        }
        m_lastOperator = _element;
    }
    else if(elementAfterConvert == '~') // Bitwise Not operator
    {
        QString lastNumber;
        if(!m_expressionForCalculate.isEmpty()) // Not empty
        {
            if(m_expressionForCalculate.back().isNumber())
            {
                while (m_expressionForCalculate.back().isNumber()) {
                    lastNumber.prepend(m_expressionForCalculate.back());
                    m_expressionForCalculate.chop(1);
                    m_expressionForDisplay.chop(1);
                    if(m_expressionForCalculate.isEmpty())
                        break;
                }
            }
            else if(isOperator(m_expressionForCalculate.back()))
            {
                lastNumber = m_mainResult;
            }
        }
        else
        {
            lastNumber = m_mainResult;
        }
        m_expressionForDisplay = m_expressionForDisplay + "Not(" + lastNumber + ")";
        m_expressionForCalculate = m_expressionForCalculate + elementAfterConvert + lastNumber;
        setHistoryExpression(m_expressionForDisplay);
        setMainResult(calculate(elementAfterConvert + lastNumber));
    }
    else if(elementAfterConvert == '(')
    {
        if(!m_expressionForCalculate.isEmpty()) // Not empty
        {
            if(m_expressionForCalculate.back().isNumber())
            {
                QString lastNumber;
                while (m_expressionForCalculate.back().isNumber()) {
                    lastNumber.prepend(m_expressionForCalculate.back());
                    m_expressionForCalculate.chop(1);
                    m_expressionForDisplay.chop(1);
                    if(m_expressionForCalculate.isEmpty())
                        break;
                }
                m_expressionForCalculate.append(elementAfterConvert);
                m_expressionForDisplay.append(_element);
                m_expressionForCalculate.append(lastNumber);
                m_expressionForDisplay.append(lastNumber);
                setHistoryExpression(m_expressionForDisplay);
                return;
            }
        }
        m_expressionForCalculate+=elementAfterConvert;
        m_expressionForDisplay+=elementAfterConvert;
        setHistoryExpression(m_expressionForDisplay);
    }
    else if(elementAfterConvert == ')')
    {
        if(m_expressionForCalculate.count('(')== m_expressionForCalculate.count(')'))
            return;
        if(m_expressionForCalculate.back()=='(')
        {
            m_expressionForCalculate.append("0");
            m_expressionForDisplay.append("0");
        }
        if(isOperator(m_expressionForCalculate.back()))
        {
            m_expressionForCalculate.append(m_mainResult);
            m_expressionForDisplay.append(m_mainResult);
        }
        m_expressionForCalculate.append(elementAfterConvert);
        m_expressionForDisplay.append(elementAfterConvert);
        setHistoryExpression(m_expressionForDisplay);
        setMainResult(calculate(m_expressionForCalculate));
        setSubResult(m_mainResult);
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

QString Calculator::sizeOfData() const
{
    return m_sizeOfData;
}

void Calculator::setSizeOfData(const QString &_sizeOfData)
{
    if(_sizeOfData==m_sizeOfData)
        return;
    m_sizeOfData = _sizeOfData;
    emit sizeOfDataChanged(m_sizeOfData);
}

void Calculator::onChangeSizeOfDataFunctionButtonClicked()
{
    if(m_sizeOfData=="BYTE")
        setSizeOfData("QWORD");
    else if(m_sizeOfData=="QWORD")
        setSizeOfData("DWORD");
    else if(m_sizeOfData=="DWORD")
        setSizeOfData("WORD");
    else if(m_sizeOfData=="WORD")
        setSizeOfData("BYTE");
}

QString Calculator::convertDecimalToBinary(QString _decimalString)
{
    qDebug() << Q_FUNC_INFO;
    QString PositiveBinaryString;
    bool isNegative = false;
    long long decimal = _decimalString.toLongLong();
    qDebug() << "decimal: " <<decimal ;
    if(decimal<0)
    {
        isNegative = true;
        decimal = - decimal;
    }
    while(decimal > 0)
    {
        PositiveBinaryString.prepend(QString::number(decimal%2));
        decimal = decimal / 2;
    }
    while((PositiveBinaryString.length()%4)!=0)
    {
        PositiveBinaryString.prepend("0");
    }

    if(isNegative == false)
    {
        for(int index = PositiveBinaryString.length()-1; index>0; index --)
        {
            if(index%4==0)
                PositiveBinaryString.insert(index," ");
        }
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
        }
        qDebug() << "Ngich dao: " << PositiveBinaryString;
        for(int index = 0; index < PositiveBinaryString.length() -1; index++)
        {
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
        }
        while(negativeBinaryString.length()<64)
            negativeBinaryString.prepend('1');
        for(int index = negativeBinaryString.length()-1; index>0; index--)
        {
            if(index%4==0)
                negativeBinaryString.insert(index," ");
        }
        qDebug() << "result: " << negativeBinaryString;
        return negativeBinaryString;
    }
}

QString Calculator::convertBinaryToHex(QString _binaryString)
{
    qDebug() << Q_FUNC_INFO;
    QString hexString;
    QString binaryString = _binaryString;
    qDebug() << "binaryString: " << binaryString;
    binaryString.remove(' ');

    for(int index = 0; index < binaryString.length()-1; index+=4)
    {
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
    qDebug() << Q_FUNC_INFO;
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
    qDebug() << Q_FUNC_INFO;
    qDebug() << "decimal: " << _decimalString;
    if(_decimalString == "Cannot divide by zero")
    {
        setHexResult("");
        setDecResult("");
        setOctResult("");
        setBinResult("");
        return;
    }
    if(_decimalString=="0")
    {
        setHexResult("0");
        setDecResult("0");
        setOctResult("0");
        setBinResult("0");
        return;
    }
    setDecResult(_decimalString);
    QString binaryString = convertDecimalToBinary(_decimalString);
    setBinResult(binaryString);
    setHexResult(convertBinaryToHex(binaryString));
    setOctResult(convertBinaryToOctal(binaryString));
}

void Calculator::connectSignalsToSlots()
{
    connect(this, SIGNAL(mainResultChanged(m_mainResult)), this, SLOT(setSubResult()));
}
