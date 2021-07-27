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
    }

    FunctionButton{
        id: changeTypeFunctionButton
        width: 150
        anchors.bottom: fullKeypadWindows.top
        anchors.left: bitTogglingKeypadFunctionButton.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "QWORD"
            color: "white"
        }
    }

    FunctionButton{
        id: msFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: changeTypeFunctionButton.right
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

        //        Rectangle{
        //            id: bitWise
        //            border.width: 1
        //            border.color: "white"
        //            height: parent.height/7
        //            width: parent.width/3
        //            color: "#494949"
        //            Text {
        //                anchors.left: parent.left
        //                anchors.right: parent.right
        //                anchors.top: parent.top
        //                anchors.bottom: parent.bottom
        //                height: parent.height - 2
        //                horizontalAlignment: Text.AlignHCenter
        //                verticalAlignment: Text.AlignVCenter
        //                font.pixelSize: height * 0.3
        //                color: "white"
        //                font.family: "Open Sans Regular"
        //                text: "Bitwise"
        //            }
        //        }

        //        Rectangle{
        //            id: bitShift
        //            border.width: 1
        //            border.color: "white"
        //            height: parent.height/7
        //            width: parent.width/3
        //            anchors.left: bitWise.right
        //            color: "#494949"
        //            Text {
        //                anchors.left: parent.left
        //                anchors.right: parent.right
        //                anchors.top: parent.top
        //                anchors.bottom: parent.bottom
        //                height: parent.height - 2
        //                horizontalAlignment: Text.AlignHCenter
        //                verticalAlignment: Text.AlignVCenter
        //                font.pixelSize: height * 0.3
        //                color: "white"
        //                font.family: "Open Sans Regular"
        //                text: "Bit Shift"
        //            }
        //        }

        Repeater{
            id: digits
            model: ["Lsh", "Rsh", "Or", "Xor", "Not", "And", "↑", "Mod", "CE", "C", "⌫", "÷", "A", "B", "7", "8", "9", "X", "C", "D", "4", "5", "6", "-", "E", "F", "1", "2", "3", "+", "(", ")", "+/-", "0", ".", "="]
            KeypadButton {
                x: (index % 6) * width
                y: Math.floor(index / 6) * height
                width: parent.width / 6
                height: parent.height / 6
                color: (modelData=="=")?( containMouse?(pressed ? "#0178D7" : "#036FC4"): "#104066" ): containMouse?(pressed ? "#d6d6d6" : "#737373") : (pressed ? "#d6d6d6" : "#111111")
                text: modelData
                onClicked: resultScreen.mainResultValue = eventName
                property string eventName: {
                    switch (text) {
                    case ".": return "POINT"
                    case "C": return "C"
                    default: return text
                    }
                }
            }
        }
    }

    //    Rectangle{
    //        id: bitTogglingKeypadWindows
    //        width: mainWindow.width
    //        height: mainWindow.height/2
    //        color: "blue"
    //        anchors.bottom: parent.bottom
    //        visible: false
    //    }
}
