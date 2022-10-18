import QtQuick 2.15
import QtQuick.Controls 2.15
import qml.data 1.0

Item {
    width: parent ? parent.width : 1024
    height: parent ? parent.height : 600

    DataController {
        id: datacontroller
    }

    Rectangle {
        id: data_area
        anchors {
            right: parent.horizontalCenter
            top: parent.verticalCenter
            rightMargin: 100
        }
        width: parent.width / 4.5
        height: parent.height / 3
        color: "#00ffffff"

        Text {
            id: data_text
            color: "#f9f9f9"
            text: datacontroller.printable
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Courier"
            font.bold: true
            font.pointSize: 150
        }
    }

    Rectangle {
        id: button_area
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        width: 210
        height: 70
        anchors.rightMargin: 30
        anchors.bottomMargin: 30

        Button {
            id: getData
            anchors {
                left: parent.left
                right: undefined
            }
            x: 0
            y: 0
            width: 100
            height: 70
            text: qsTr("Get Data")
            onClicked: datacontroller.getData()
        }

    }
}
