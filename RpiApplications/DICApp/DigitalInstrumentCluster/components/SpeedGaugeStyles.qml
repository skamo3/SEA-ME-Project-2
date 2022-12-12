import QtQuick 2.15
import QtQuick.Controls.Styles 1.4

CircularGaugeStyle {
    labelStepSize: 3000
    minimumValueAngle: -130
    maximumValueAngle: 110

    foreground: Item {
        Rectangle {
            width: outerRadius * 0.15
            height: width
            radius: width / 2
            color: "#e5e5e5"
            anchors.centerIn: parent
        }
    }

    tickmarkLabel:  Text {
        font.pixelSize: Math.max(3, outerRadius * 0.1)
        text: styleData.value
        color: styleData.value >= rpmGauge.maximumValue * 0.8 ? "#9C0412" : "#e5e5e5"
        antialiasing: true
    }

    tickmark: Rectangle {
        visible: styleData.value % 500 == 0
        implicitWidth: outerRadius * 0.02
        antialiasing: true
        implicitHeight: outerRadius * 0.07
        color: styleData.value >= rpmGauge.maximumValue * 0.8 ? "#9C0412" : "#e5e5e5"
    }

    minorTickmark: Rectangle {
        visible: styleData.value < rpmGauge.maximumValue * 0.8
        implicitWidth: outerRadius * 0.01
        antialiasing: true
        implicitHeight: outerRadius * 0.03
        color: "#61D3F7"
    }

    function degreesToRadians(degrees) {
        return degrees * (Math.PI / 180);
    }

    background: Canvas {
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            ctx.beginPath();
            ctx.strokeStyle = "#FC0412";
            ctx.lineWidth = outerRadius * 0.02;

            ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                degreesToRadians(valueToAngle(rpmGauge.minimumValue) + 100), degreesToRadians(valueToAngle(rpmGauge.minimumValue) + 150));
            ctx.stroke();
        }
    }
}
