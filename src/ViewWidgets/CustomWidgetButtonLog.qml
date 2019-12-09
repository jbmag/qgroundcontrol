import QtQuick 2.2
import QtQuick.Extras 1.4
import QtQuick.Controls 1.2


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

    //item handling signals to and from vehicle.cc
    CustomCommandWidgetController {
        id:         controller
        factPanel:  panel
        onNewGiinavStatus: {
            mtext.append(controller.getCurrentGiinavStatus()+"\n")
            mflick.flick(0,-1000)
        }
        onNewRFStatus: {
            mtext.append(controller.getCurrentRFStatus()+"\n")
            mflick.flick(0,-1000)
        }
        onGiinavStart: switchGiinav.enabled= true
        onRfStart: switchRF.enabled= true

    }

    function toggleGNSS() {
        if (switchGNSS.checked == true)
        {
            controller.sendNamedValueFloatMsg("onoffGNSS", 1)
        }
        else
        {
            controller.sendNamedValueFloatMsg("onoffGNSS", 0)
        }
    }


    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }

    Column {
        spacing: ScreenTools.defaultFontPixelHeight
        Row{
            spacing: 5
            QGCSwitch{
                id: switchGNSS
                enabled: true
                onCheckedChanged: toggleGNSS()
            }
            Text {
                text: "Toggle GNSS in Giinav and VDM Roamfree"
                color: "white"
            }
        }
        Row{
            spacing: 5
            QGCSwitch{
                id: switchGiinav
                enabled: false
                onCheckedChanged: controller.toggleGiinav()
            }
            Text {           
                text: "Display Giinav Solution on Map"
                color: "white"
            }
        }
        Row{
            spacing: 5
            QGCSwitch{
                id: switchRF
                enabled: false
                onCheckedChanged: controller.toggleRF()
            }
            Text {
                text: "Display VDM RoamFree Solution on Map"
                color: "white"
            }
        }
        Text {
            text: " \nOnboard Computer Status: "
            color: "white"
        }
        Flickable{
            id: mflick
            width: frame.width
            height: frame.height - 145
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
