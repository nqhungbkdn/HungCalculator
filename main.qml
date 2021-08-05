import QtQuick 2.11
import QtQuick.Window 2.2
Window {
    id: mainWindow
    visible: true
    width: 322*1.5
    height: 681
    title: qsTr("Hung's Calculator")
    color: "#525353"
    opacity: 0.997
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
        width: (parent.width-175)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        //property alias fullKeypadFunctionButtonFooterVisible : footer.visible
        //anchors.right: bitTogglingKeypadFunctionButton.left
        //anchors.rightMargin: 5
        Image{
            id: fullKeypadFunctionButtonImage
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/fullKeypadIcon.png"
        }
        //        Rectangle{
        //            id: fullKeypadFunctionButtonFooter
        //            width: parent.width
        //            height: 5;
        //            color: "#0178D7";
        //            anchors.bottom: parent.bottom
        //        }
        onFunctionButtonClicked:
        {
            //            fullKeypadFunctionButtonFooter.visible = true
            //            fullKeypadFunctionButtonImage.source = "icon/fullKeypadIcon_blue.png"
            //            bitTogglingKeypadFunctionButtonFooter.visible = false
            //            bitTogglingKeypadFunctionButtonImage.source = "icon/bitToggleIcon.png"
            closeAllWindows()
            fullKeypadWindows.visible = true;
        }
    }

    FunctionButton{
        id: bitTogglingKeypadFunctionButton
        width: (parent.width-175)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: fullKeypadFunctionButton.right
        anchors.leftMargin: 5
        Image{
            id: bitTogglingKeypadFunctionButtonImage
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/bitToggleIcon.png"
        }
        //        Rectangle{
        //            id: bitTogglingKeypadFunctionButtonFooter
        //            width: parent.width
        //            height: 5;
        //            color: "#0178D7";
        //            anchors.bottom: parent.bottom
        //            visible: false
        //        }
        onFunctionButtonClicked:
        {
            //            fullKeypadFunctionButtonFooter.visible = false
            //            fullKeypadFunctionButtonImage.source = "icon/fullKeypadIcon.png"
            //            bitTogglingKeypadFunctionButtonFooter.visible = true
            //            bitTogglingKeypadFunctionButtonImage.source = "icon/bitToggleIcon_blue.png"
            closeAllWindows();
            bitTogglingKeypadWindows.visible = true;
        }
    }

    FunctionButton{
        id: changeSizeOfDataFunctionButton
        width: 150
        anchors.bottom: fullKeypadWindows.top
        anchors.left: bitTogglingKeypadFunctionButton.right
        anchors.leftMargin: 5
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
        id: memoryStoreFunctionButton
        width: (parent.width-170)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: changeSizeOfDataFunctionButton.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "MS"
            color: "white"
        }
        onFunctionButtonClicked:
        {
            _memoryModel.addNewData(calculator.mainResult.toString())
        }
    }

    FunctionButton{
        id: memoryListFunctionButton
        width: (parent.width-170)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: memoryStoreFunctionButton.right
        anchors.right: parent.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "M▾"
            color: "white"
        }
        onFunctionButtonClicked:
        {
            closeAllWindows()
            memoryListWindows.visible = true
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
                enabled: ((modelData<='9'&& modelData>= '0') || modelData == '+' || modelData == '-' || modelData == '×' || modelData == '÷' || modelData == 'Mod' || modelData == '⌫' || modelData == 'Clear' || modelData == 'CE'|| modelData == '(' || modelData == ')' || modelData == '=' || modelData == 'Lsh' || modelData == 'Rsh' || modelData == 'And' || modelData == 'Or' || modelData == 'Xor' || modelData == 'Not')? true : false
                onClicked: {
                    if(modelData<='9'&& modelData>= '0')
                        calculator.onDigitKeypadButtonCliked(modelData)
                    else if(modelData =='+' || modelData == '-' || modelData == '×' || modelData == '÷' ||modelData == 'Mod' || modelData == '=' || modelData == '(' ||  modelData == ')' || modelData == 'Lsh' || modelData == 'Rsh' || modelData == 'And' || modelData == 'Or' || modelData == 'Xor' || modelData == 'Not')
                        calculator.onOperatorKeypadButtonClicked(modelData)
                    else if(modelData == 'Clear' || modelData == 'CE' || modelData == '⌫')
                        calculator.onDeleteButtonClicked(modelData)
                }
            }
        }
    }

    Rectangle{
        id: memoryListWindows
        height: mainWindow.height/2 + 5
        color: "#222222"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        visible: true

        Component {
            id: memoryComponent
            Rectangle {
                width: memoryListWindows.width ; height: 100
                color: "#222222" //containMouse? "#373737" : "#222222"
                //property alias containMouse : memoryComponentMouse.containsMouse
                Text
                {
                    x: parent.width - 50
                    y: parent.height/5
                    text: model.name;
                    font.pixelSize: 20
                    color: "white"
                }

                    Rectangle{
                        id: memorySubtractButton
                        width: 48; height: 40
                        color: memorySubtractButtonMouse.containsMouse? "#4d4d4d" : parent.color
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.rightMargin: 15
                        border.width: 2
                        border.color: "white"
                        Text{
                            color: "white"
                            anchors.centerIn: parent
                            text: "M-"
                            font.pixelSize: 20
                        }
                        MouseArea{
                            id: memorySubtractButtonMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: _memoryModel.onMemorySubtractButtonClicked(model.index, calculator.mainResult)
                        }
                    }

                    Rectangle{
                        id: memoryAddButton
                        width: 48; height: 40
                        color: memoryAddButtonMouse.containsMouse? "#4d4d4d" : parent.color
                        anchors.verticalCenter: memorySubtractButton.verticalCenter
                        anchors.right: memorySubtractButton.left
                        anchors.rightMargin: 15
                        border.width: 2
                        border.color: "white"
                        Text{
                            color: "white"
                            anchors.centerIn: parent
                            text: "M+"
                            font.pixelSize: 20
                        }
                        MouseArea{
                            id: memoryAddButtonMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: _memoryModel.onMemoryAddButtonClicked(model.index,calculator.mainResult)
                        }
                    }

                    Rectangle{
                        id: memoryClearButton
                        width: 48; height: 40
                        color: memoryClearButtonMouse.containsMouse? "#4d4d4d" : parent.color
                        anchors.verticalCenter: memorySubtractButton.verticalCenter
                        anchors.right: memoryAddButton.left
                        anchors.rightMargin: 15
                        border.width: 2
                        border.color: "white"
                        Text{
                            color: "white"
                            anchors.centerIn: parent
                            text: "MC"
                            font.pixelSize: 20
                        }
                        MouseArea{
                            id: memoryClearButtonMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: _memoryModel.removeData(model.index)
                        }
                    }
//                MouseArea{
//                    id: memoryComponentMouse
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    onDoubleClicked: _memoryModel.removeData(model.index) // test
//                }
            }
        }

        ListView {
            anchors.fill: parent
            model: _memoryModel
            delegate: memoryComponent
            clip: true
            spacing: 20
        }

//        Rectangle{
//            height: 40
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//        }
    }

    Rectangle{
        id: bitTogglingKeypadWindows
        width: mainWindow.width
        height: mainWindow.height/2 + 5
        color: "blue"
        anchors.bottom: parent.bottom
        visible: false
        Text{
            text: "This feature is  currently under development"
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }
    function closeAllWindows()
    {
        fullKeypadWindows.visible = false;
        memoryListWindows.visible = false;
        bitTogglingKeypadWindows.visible = false;
    }
}
