import QtQuick 2.15

Item {
    width: parent ? parent.width : 1024
        height: parent ? parent.height : 600

        Rectangle {
            color: "#171717"
            width: parent.width
            height: parent.height
        }

        Image {
            id: background_img
            anchors {
                left: parent.horizontalCenter
                top: parent.verticalCenter
                topMargin: - (parent.height / 2)
                leftMargin: - (parent.width / 2)
            }
            width: parent.width
            height: parent.height
            opacity: 0.3
            source: "qrc:/back.png"
            z: 1
        }

}
