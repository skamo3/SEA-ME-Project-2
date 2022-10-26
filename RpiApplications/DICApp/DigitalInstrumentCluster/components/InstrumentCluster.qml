import QtQuick 2.15
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import qml.data 1.0
import QtGraphicalEffects 1.0


Item {
    id: container
    width: parent ? parent.width : 1024
    height: parent ? parent.height : 600

    DataController {
        id: datacontroller
    }

    CircularGauge {
        id: rpmGauge
        width: height
        height: parent.height * 0.5

        x:(parent.x + parent.width) / 4 / 2
        anchors.verticalCenter: parent.verticalCenter

        value: datacontroller.rpm // 스피드 값 넣기
        minimumValue: 0
        maximumValue: 5000 // 최대값

        style: GaugeStyles {

        }

        Behavior on value {
            NumberAnimation {
                duration: 1000
            }
        }
    }

    CircularGauge {
        id: speedGauge
        width: height
        height: parent.height * 0.5
        x:(parent.x + parent.width) / 1.75
        anchors.verticalCenter: parent.verticalCenter

        value: datacontroller.rpm
        minimumValue: 0
        maximumValue: 300

        Behavior on value {
            NumberAnimation {
                duration: 1000
            }
        }
    }

    Item {
        width: height * 1.1
        height: parent.height * 0.15

        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: parent.width * 0.02
        }

        Rectangle {
            width: (batteryImg.width * 0.7) * datacontroller.battery % 100
            height: batteryImg.height * 0.4
            radius: width * 0.1
            color: "#00FF00"

            anchors {
                right: batteryImg.right
                top: batteryImg.top
                rightMargin: (batteryImg.x + batteryImg.width) * 0.125
                topMargin: (batteryImg.y + batteryImg.height) * 0.31
            }
        }

        Image {
            id: batteryImg
            width: parent.width
            height: parent.height
            source: "qrc:/battery.png"
        }

        ColorOverlay {
                anchors.fill: batteryImg
                source: batteryImg
                color: "#FFFFFF"  // make image like it lays under red glass
            }
    }

    Gauge {
        id: temperature
        minimumValue: 0
        maximumValue: 50
        value: datacontroller.temperature
        width: parent.width
        height: parent.height * 0.2
        x: ((parent.x + parent.width) / 2) - parent.width * 0.1
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height * 0.05
        }

        style: GaugeStyle {
            valueBar: Rectangle {
                implicitWidth: 8
                color: "#FF0000"
            }
        }

        Behavior on value {
            NumberAnimation {
                duration: 4000
            }
        }
    }

    Gauge {
        id: humidity
        minimumValue: 0
        maximumValue: 100
        value: datacontroller.humidity
        width: parent.width
        height: parent.height * 0.2
        x: ((parent.x + parent.width) / 2)
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height * 0.05
        }

        style: GaugeStyle {
            valueBar: Rectangle {
                implicitWidth: 8
                color: "#0000FF"
            }
        }

        Behavior on value {
            NumberAnimation {
                duration: 4000
            }
        }
    }

}


