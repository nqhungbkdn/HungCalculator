import QtQuick 2.0

Rectangle{
    width: parent.width
    property int subResultHeight: 30
    property int subResultTextSize: 18
    property string hexResultValue : "0"
    property string decResultValue : "0"
    property string octResultValue : "0"
    property string binResultValue : "0"
    property string mainResultValue: "0"
    property string historyExpressionValue: ""

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
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: decResult.top
        anchors.leftMargin: 10
        Text{
            id: hexText
            font.pixelSize: resultScreen.subResultTextSize
            text: "HEX"
            color: "white"
        }
        Text{
            anchors.left: hexText.right
            anchors.leftMargin: 25
            font.pixelSize: resultScreen.subResultTextSize
            text: hexResultValue
            color: "white"
        }
    }

    Rectangle{
        id: decResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: octResult.top
        anchors.leftMargin: 10
        Text{
            id: decText
            font.pixelSize: resultScreen.subResultTextSize
            text: "DEC"
            color: "white"
        }
        Text{
            anchors.left: decText.right
            anchors.leftMargin: 25
            font.pixelSize: resultScreen.subResultTextSize
            text: decResultValue
            color: "white"
        }
    }

    Rectangle{
        id: octResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: binResult.top
        anchors.leftMargin: 10
        Text{
            id: octText
            font.pixelSize: resultScreen.subResultTextSize
            text: "OCT"
            color: "white"
        }
        Text{
            anchors.left: octText.right
            anchors.leftMargin: 23
            font.pixelSize: resultScreen.subResultTextSize
            text: octResultValue
            color: "white"
        }
    }

    Rectangle{
        id: binResult
        width: parent.width
        height: 40
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        Text{
            id: binText
            font.pixelSize: resultScreen.subResultTextSize
            text: "BIN"
            color: "white"
        }
        Text{
            anchors.left: binText.right
            anchors.leftMargin: 28
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.pixelSize: resultScreen.subResultTextSize
            text: binResultValue
            color: "white"
            wrapMode: Text.WordWrap
        }
    }
}
