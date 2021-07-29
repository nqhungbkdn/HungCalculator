import QtQuick 2.0

Rectangle{
    width: parent.width
    property int subResultHeight: 30
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
            font.pixelSize: 20
            text: "HEX    " + hexResultValue
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
            font.pixelSize: 20
            text: "DEC    " + decResultValue
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
            font.pixelSize: 20
            text: "OCT    " + octResultValue
            color: "white"
        }
    }

    Rectangle{
        id: binResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        Text{
            font.pixelSize: 20
            text: "BIN     " + binResultValue
            color: "white"
        }
    }

}
