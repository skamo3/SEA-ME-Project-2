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
        maximumValue: 15000 // 최대값

        style: RpmGaugeStyles {

        }

        Behavior on value {
            NumberAnimation {
                duration: 3000
            }
        }
    }

    CircularGauge {
        id: speedGauge
        width: height
        height: parent.height * 0.5
        x:(parent.x + parent.width) / 1.75
        anchors.verticalCenter: parent.verticalCenter

        value: datacontroller.speed
        minimumValue: 0
        maximumValue: 36

        Behavior on value {
            NumberAnimation {
                duration: 1000
            }
        }

        style: SpeedGaugeStyles {

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
            width: (batteryImg.width * 0.7) * datacontroller.battery / 100
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

    Rectangle {
        id: tempBox
        width: height
        height: parent.height*0.08
        x: (parent.x + parent.width) / 2.5
        y: (parent.y + parent.height)/1.35

        Image {
            id: temp
            width: height
            source: "qrc:/temperature.jpg"
                    }
        Text {
            id :temptextbox
            width: parent.width/2
            height: parent.height
            x: (temp.x + temp.width) + (temp.x + temp.width) / 4
            y: (temp.y + temp.height) / 4
            text:datacontroller.temperature + "℃"
            font.pointSize: 12
            color: "#F17758"
        }
    }

    Rectangle {
        id: humBox
        height: parent.height*0.08
        x: (parent.x + parent.width) / 1.8
        y: (parent.y + parent.height)/1.35

        Image {
            id: hum
            width: height
            source: "qrc:/humidity.jpg"
                    }
        Text {
            id :humtextbox
            width: parent.width/2
            height: parent.height
            x: (hum.x + hum.width) + (hum.x + hum.width) / 4
            y: (hum.y + hum.height) / 4
            text:+datacontroller.humidity + "%"
            font.pointSize: 12

            color: "#F17758"
        }
    }





}


