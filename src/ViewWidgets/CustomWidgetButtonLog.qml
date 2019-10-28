import QtQuick 2.2


import QGroundControl.Controls      1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FactControls  1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Controllers   1.0


Rectangle {
    anchors.fill:   parent
    color:          qgcPal.window
    id: frame
    CustomCommandWidgetController {
        id:         controller
        factPanel:  panel
        onStatusChanged: {
            mtext.append(controller.getCurrentGiinavStatus()+"\n")
            mflick.flick(0,-1000)
        }

    }


    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }

    Column {
        spacing: ScreenTools.defaultFontPixelHeight

        QGCButton {
            text: "Send debug message"
            // Arguments to CustomCommandWidgetController::sendCommand (MAVLink COMMAND_LONG)
            //   command id
            //   component id
            //   confirmation
            //   param 1-7
            onClicked:  controller.sendDebugMsg(253, 1, 1)

        }
        Flickable{
            id: mflick
            width: frame.width
            height: frame.height - 70
            contentWidth: frame.width
            contentHeight: contentItem.childrenRect.height
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            Rectangle{
                width: frame.width
                height: mtext.height;
                color: "white"
                TextEdit{
                    id: mtext
                    width: frame.width
                    readOnly: true
                }
            }


        }






    }
}
