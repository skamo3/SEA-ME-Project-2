import QtQuick 2.15

Item {
    width: parent ? parent.width : 1024
    height: parent ? parent.height : 600

    Image {
        id: background_neon
        anchors {
            left: parent.horizontalCenter
            top: parent.verticalCenter
            topMargin: - (parent.height / 2 * 1.1)
            leftMargin: - (parent.width / 2)
        }
        width: parent.width
        height: parent.height * 1.1
        opacity: 1
        source: "qrc:/images/neonback.png"
        z: 0
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
        opacity: 0.6
        source: "qrc:/images/back.png"
        z: 1
    }

    Image {
        id: background_ghost
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        opacity: 0.9
        source: "qrc:/images/halloween.png"
        fillMode: Image.PreserveAspectFit
        z: 2
    }

}
