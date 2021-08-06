import QtQuick 2.0

Rectangle{
    width: parent.width
    property int subResultHeight: 38
    property int subResultTextSize: 18
    property string hexResultValue : "0"
    property string decResultValue : "0"
    property string octResultValue : "0"
    property string binResultValue : "0"
    property string mainResultValue: "0"
    property string historyExpressionValue: ""
    property string currentInputType: "DEC"

    id: resultScreen
    color:"#525353"

    Rectangle{
        id: historyExpression
        width: parent.width
        height: 40
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: mainResult.top
        anchors.bottomMargin: 5
        opacity: 0.5
        Text{
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            text: "" + historyExpressionValue
            color: "white"
        }
    }

    Rectangle{
        id: mainResult
        width: parent.width
        height: 40
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: hexResult.top
        anchors.bottomMargin: 15
        Text{
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
            text: "" + mainResultValue
            color: "white"
        }
    }

    Rectangle{
        id: hexResult
        width: parent.width
        height: subResultHeight
        color: hexMouse.containsMouse?"#737373" : parent.color
        anchors.left: parent.left
        anchors.bottom: decResult.top
        Text{
            id: hexText
            font.pixelSize: resultScreen.subResultTextSize
            text: "HEX"
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.verticalCenter: parent.verticalCenter
        }
        Text{
            anchors.left: hexText.right
            anchors.leftMargin: 25
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: resultScreen.subResultTextSize
            text: hexResultValue
            color: "white"
        }
        MouseArea {
            id: hexMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                hightLight.anchors.verticalCenter = hexResult.verticalCenter
                currentInputType = "HEX";
            }
        }
    }

    Rectangle{
        id: decResult
        width: parent.width
        height: subResultHeight
        color: decMouse.containsMouse?"#737373" : parent.color
        anchors.left: parent.left
        anchors.bottom: octResult.top

        Text{
            id: decText
            font.pixelSize: resultScreen.subResultTextSize
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.verticalCenter: parent.verticalCenter
            text: "DEC"
            color: "white"
        }
        Text{
            anchors.left: decText.right
            anchors.leftMargin: 25
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: resultScreen.subResultTextSize
            text: decResultValue
            color: "white"
        }
        MouseArea {
            id: decMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                hightLight.anchors.verticalCenter = decResult.verticalCenter
                currentInputType = "DEC"
            }
        }
    }

    Rectangle{
        id: octResult
        width: parent.width
        height: subResultHeight
        color: octMouse.containsMouse?"#737373" : parent.color
        anchors.left: parent.left
        anchors.bottom: binResult.top
        Text{
            id: octText
            font.pixelSize: resultScreen.subResultTextSize
            text: "OCT"
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.verticalCenter: parent.verticalCenter
        }
        Text{
            anchors.left: octText.right
            anchors.leftMargin: 23
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: resultScreen.subResultTextSize
            text: octResultValue
            color: "white"
        }
        MouseArea {
            id: octMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                hightLight.anchors.verticalCenter = octResult.verticalCenter
                currentInputType = "OCT";
            }
        }
    }

    Rectangle{
        id: binResult
        width: parent.width
        height: subResultHeight
        color: binMouse.containsMouse?"#737373" : parent.color
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Text{
            id: binText
            font.pixelSize: resultScreen.subResultTextSize
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            text: "BIN"
            color: "white"
        }
        Text{
            anchors.left: binText.right
            anchors.leftMargin: 28
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: resultScreen.subResultTextSize
            text: binResultValue
            color: "white"
            wrapMode: Text.WordWrap
        }
        MouseArea {
            id: binMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                hightLight.anchors.verticalCenter = binResult.verticalCenter
                currentInputType = "BIN";
            }
        }
    }

    Rectangle{
        id: hightLight
        anchors.verticalCenter: decResult.verticalCenter
        width: 5
        height: 20
        color: "#0178D7"
        visible: true
    }
}
