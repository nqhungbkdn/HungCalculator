import QtQuick 2.11
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
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
        mainResultValue: _calculator.mainResult.toString()
        historyExpressionValue: _calculator.historyExpression.toString()
        hexResultValue: _calculator.hexResult.toString()
        decResultValue: _calculator.decResult.toString()
        octResultValue: _calculator.octResult.toString()
        binResultValue: _calculator.binResult.toString()
    }

    FunctionButton{
        id: fullKeypadFunctionButton
        width: (parent.width-175)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        Image{
            id: fullKeypadFunctionButtonImage
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/fullKeypadIcon_blue.png"
        }
        Rectangle{
            id: fullKeypadFunctionButtonHighlight
            width: parent.width
            height: 5;
            color: "#0178D7";
            anchors.bottom: parent.bottom
        }
        onFunctionButtonClicked:
        {
            fullKeypadFunctionButtonHighlight.visible = true
            fullKeypadFunctionButtonImage.source = "icon/fullKeypadIcon_blue.png"
            bitTogglingKeypadFunctionButtonHighlight.visible = false
            bitTogglingKeypadFunctionButtonImage.source = "icon/bitToggleIcon.png"
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
        Rectangle{
            id: bitTogglingKeypadFunctionButtonHighlight
            width: parent.width
            height: 5;
            color: "#0178D7";
            anchors.bottom: parent.bottom
            visible: false
        }
        onFunctionButtonClicked:
        {
            fullKeypadFunctionButtonHighlight.visible = false
            fullKeypadFunctionButtonImage.source = "icon/fullKeypadIcon.png"
            bitTogglingKeypadFunctionButtonHighlight.visible = true
            bitTogglingKeypadFunctionButtonImage.source = "icon/bitToggleIcon_blue.png"
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
        onFunctionButtonClicked: _calculator.onChangeSizeOfDataFunctionButtonClicked();
        Text{
            id: txtChangeSizeOfDataButton
            anchors.centerIn: parent
            font.pixelSize: 20
            text: _calculator.sizeOfData
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
            _memoryModel.onMemoryStoreFunctionButtonClicked(_calculator.mainResult.toString())
        }
    }

    FunctionButton{
        id: memoryListFunctionButton
        width: (parent.width-170)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: memoryStoreFunctionButton.right
        anchors.right: parent.right
        enabled: true //(listView.count != 0)? true : false
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "M▾"
            color: "white"
            opacity: (listView.count == 0)? 0.3 : 1
        }
        onFunctionButtonClicked:
        {
            if(memoryListWindowsPopup.opened)
            memoryListWindowsPopup.close()
            else memoryListWindowsPopup.open()
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
        property bool isShiftClicked: false

        Repeater{
            id: digits
            model: ["Lsh", "Rsh", "Or", "Xor", "Not", "And", "↑", "Mod", "CE", "Clear", "⌫", "÷", "A", "B", "7", "8", "9", "×", "C", "D", "4", "5", "6", "-", "E", "F", "1", "2", "3", "+", "(", ")", "±", "0", ".", "="]
            KeypadButton {
                x: (index % 6) * width
                y: Math.floor(index / 6) * height
                width: parent.width / 6
                height: parent.height / 6
                color:{
                    if(modelData == "." || (modelData>="0" && modelData <= "9") || modelData == "A" || modelData == "B" || modelData == "C" || modelData == "D" || modelData == "E" || modelData == "F")
                    {
                        if(containMouse)
                        {
                            if(pressed)
                                return "#d6d6d6"
                            return "#737373"
                        }
                        else
                        {
                            return "#111111"
                        }
                    }
                    else if(modelData == "+" || modelData == "-" || modelData == "×" || modelData == "." || modelData == "÷" || modelData == "=")
                    {
                        if(containMouse)
                        {
                            if(pressed)
                                return "#98cffc"
                            return "#3e98e1"
                        }
                        else
                        {
                            return "#262626"
                        }
                    }
                    else
                    {
                        if(containMouse)
                        {
                            if(pressed)
                                return "#d6d6d6"
                            return "#737373"
                        }
                        else
                        {
                            return "#262626"
                        }
                    }
                }

                border.color: (modelData==".")?("#1B1B1B") : containMouse?"#afafaf":"#1B1B1B"
                text: (modelData == "Clear")? "C" : (modelData == "Lsh" && fullKeypadWindows.isShiftClicked)? "RoL" :(modelData == "Rsh" && fullKeypadWindows.isShiftClicked)? "RoR" : modelData
                textcolor:{
                    if(resultScreen.currentInputType=="HEX"&&modelData==".")
                        return "#505050"
                    if(resultScreen.currentInputType=="DEC"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F"))
                        return "#505050"
                    if(resultScreen.currentInputType=="OCT"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F" || modelData=="8" || modelData=="9"))
                        return "#505050"
                    if(resultScreen.currentInputType=="BIN"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F" || (modelData>="2" && modelData<="9")))
                        return "#505050"
                    return "white"
                }
                enabled: (resultScreen.currentInputType=="HEX"&&modelData==".")? false : (resultScreen.currentInputType=="DEC"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F"))? false : (resultScreen.currentInputType=="OCT"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F" || modelData=="8" || modelData=="9"))? false : (resultScreen.currentInputType=="BIN"&&(modelData=="."||modelData=="A"|| modelData=="B"|| modelData=="C" || modelData=="D" || modelData=="E" || modelData=="F" || (modelData>="2" && modelData<="9")))? false : true
                onClicked: {
                    if(modelData<='9'&& modelData>= '0')
                        _calculator.onDigitKeypadButtonCliked(modelData)
                    else if(modelData =='+' || modelData == '-' || modelData == '×' || modelData == '÷' ||modelData == 'Mod' || modelData == '=' || modelData == '(' ||  modelData == ')' || text == 'Lsh' || text == 'Rsh' || modelData == 'And' || modelData == 'Or' || modelData == 'Xor' || modelData == 'Not')
                        _calculator.onOperatorKeypadButtonClicked(modelData)
                    else if(modelData == 'Clear' || modelData == 'CE' || modelData == '⌫')
                        _calculator.onDeleteButtonClicked(modelData)
                    else if(modelData == '↑')
                        fullKeypadWindows.isShiftClicked = !fullKeypadWindows.isShiftClicked
                }
            }
        }
    }

    Popup{
        id: memoryListWindowsPopup
        y: mainWindow.height/2 - 5
        width: mainWindow.width
        height: mainWindow.height/2 + 5
        contentItem:  Rectangle{
            id: memoryListWindows
            height: mainWindow.height/2 + 5
            color: "#222222"
            anchors.fill: parent
            visible: true

            Component {
                id: memoryComponent
                Rectangle {
                    width: memoryListWindows.width ; height: 100
                    color: (memoryComponentMouse.containsMouse || memoryClearButtonMouse.containsMouse || memoryAddButtonMouse.containsMouse || memorySubtractButtonMouse.containsMouse )? "#373737" : "#222222"
                    Text
                    {
                        x: parent.width - 50
                        y: parent.height/5
                        text: model.name;
                        font.pixelSize: 20
                        color: "white"
                    }

                    MouseArea{
                        id: memoryComponentMouse
                        anchors.fill: parent
                        hoverEnabled: true
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
                            onClicked: _memoryModel.onMemoryClearButtonClicked(model.index)
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
                            onClicked: _memoryModel.onMemoryAddButtonClicked(model.index,_calculator.mainResult)
                        }
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
                            onClicked: _memoryModel.onMemorySubtractButtonClicked(model.index, _calculator.mainResult)
                        }
                    }
                }
            }

            ListView {
                id: listView
                anchors.top: parent.top
                anchors.bottom: clearAllMemoryBar.top
                anchors.left: parent.left
                anchors.right: parent.right
                model: _memoryModel
                delegate: memoryComponent
                clip: true
                spacing: 20
            }

            Rectangle{
                id: clearAllMemoryBar
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                color: parent.color
                Rectangle{
                    id: clearAllMemoryButton
                    height: 40
                    width: 40
                    color: clearAllMemoryButtonMouse.containsMouse? "#4d4d4d" :parent.color
                    border.width: 2
                    border.color: "white"
                    anchors.right: parent.right
                    Image{
                        anchors.fill: parent
                        source: "icon/ClearAllMemoryListIcon.png"
                    }
                    MouseArea{
                        id: clearAllMemoryButtonMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: _memoryModel.onClearAllMemoryButtonClicked()
                    }
                }
            }
            Text{
                text: "There's nothing saved in memory"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 30
                anchors.leftMargin: 10
                color: "white"
                font.pixelSize: 16
                font.bold: true
                visible: (listView.count == 0) ? true : false
            }
        }
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
            color: "yellow"
            font.bold: true
        }
    }
    function closeAllWindows()
    {
        fullKeypadWindows.visible = false;
        bitTogglingKeypadWindows.visible = false;
    }
}
