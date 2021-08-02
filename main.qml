import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: mainWindow
    visible: true
    width: 322*1.5
    height: 681
    title: qsTr("Hung's Calculator")
    color: "#525353"

    ResultScreen{
        id: resultScreen
        anchors.top: parent.top
        anchors.bottom: fullKeypadFunctionButton.top
        mainResultValue: calculator.mainResult.toString()
        historyExpressionValue: calculator.historyExpression.toString()
        hexResultValue: calculator.hexResult.toString()
        decResultValue: calculator.decResult.toString()
        octResultValue: calculator.octResult.toString()
        binResultValue: calculator.binResult.toString()
    }

    FunctionButton{
        id: fullKeypadFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: parent.left
        Image{
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/fullKeypadIcon.png"
        }
    }

    FunctionButton{
        id: bitTogglingKeypadFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: fullKeypadFunctionButton.right
        Image{
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/bitToggleIcon.png"
        }
    }

    FunctionButton{
        id: changeSizeOfDataFunctionButton
        width: 150
        anchors.bottom: fullKeypadWindows.top
        anchors.left: bitTogglingKeypadFunctionButton.right
        onFunctionButtonClicked: calculator.onChangeSizeOfDataFunctionButtonClicked();
        Text{
            id: txtChangeSizeOfDataButton
            anchors.centerIn: parent
            font.pixelSize: 20
            text: calculator.sizeOfData
            color: "white"
        }
    }

    FunctionButton{
        id: msFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: changeSizeOfDataFunctionButton.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "MS"
            color: "white"
        }
    }

    FunctionButton{
        id: mListFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: msFunctionButton.right
        anchors.right: parent.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "M▾"
            color: "white"
        }
    }

    Rectangle{
        id: fullKeypadWindows
        width: mainWindow.width
        height: mainWindow.height/2
        color: "#494949"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.bottomMargin: 5


        Repeater{
            id: digits
            model: ["Lsh", "Rsh", "Or", "Xor", "Not", "And", "↑", "Mod", "CE", "Clear", "⌫", "÷", "A", "B", "7", "8", "9", "×", "C", "D", "4", "5", "6", "-", "E", "F", "1", "2", "3", "+", "(", ")", "±", "0", ".", "="]
            KeypadButton {
                x: (index % 6) * width
                y: Math.floor(index / 6) * height
                width: parent.width / 6
                height: parent.height / 6
                color: (modelData=="=")?( containMouse?(pressed ? "#0178D7" : "#036FC4"): "#104066" ):(modelData==".")?("#111111") : (containMouse?(pressed ? "#d6d6d6" : "#737373") : (pressed ? "#d6d6d6" : "#111111"))
                border.color: (modelData==".")?("#1B1B1B") : containMouse?"white":"#1B1B1B"
                text: (modelData == "Clear")? "C" : modelData
                textcolor: (modelData=="." || modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F")? "#505050": "white"
                enabled: ((modelData<='9'&& modelData>= '0') || modelData == '+' || modelData == '-' || modelData == '×' || modelData == '÷' || modelData == 'Mod' || modelData == '⌫' || modelData == 'Clear' || modelData == 'CE'|| modelData == '(' || modelData == ')' || modelData == '=' || modelData == 'Lsh' || modelData == 'Rsh' || modelData == 'And' || modelData == 'Or' || modelData == 'Xor')? true : false
                onClicked: {
                    if(modelData<='9'&& modelData>= '0')
                        calculator.onDigitKeypadButtonCliked(modelData)
                    else if(modelData =='+' || modelData == '-' || modelData == '×' || modelData == '÷' ||modelData == 'Mod' || modelData == '=' || modelData == '(' ||  modelData == ')' || modelData == 'Lsh' || modelData == 'Rsh' || modelData == 'And' || modelData == 'Or' || modelData == 'Xor' || modelData == 'Not' || modelData == 'Clear' || modelData == 'CE' || modelData == '⌫')
                        calculator.onOperatorKeypadButtonClicked(modelData)
                }
            }
        }
    }

//        Rectangle{
//            id: bitTogglingKeypadWindows
//            width: mainWindow.width
//            height: mainWindow.height/2
//            color: "blue"
//            anchors.bottom: parent.bottom
//            visible: false
//        }
}
