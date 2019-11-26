/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "CustomCommandWidgetController.h"
#include "MultiVehicleManager.h"
#include "QGCMAVLink.h"
#include "QGCQFileDialog.h"
#include "UAS.h"
#include "QGCApplication.h"



#include <QSettings>
#include <QUrl>

const char* CustomCommandWidgetController::_settingsKey = "CustomCommand.QmlFile";

CustomCommandWidgetController::CustomCommandWidgetController(void) :
    _vehicle(NULL)
{
    if(qgcApp()->toolbox()->multiVehicleManager()->activeVehicle()) {
        _vehicle = qgcApp()->toolbox()->multiVehicleManager()->activeVehicle();
        _vehicleExt = _vehicle->vehicleExtensionTopo;
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::giinavStatusChanged, this, &CustomCommandWidgetController::updateGiinavStatus);
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::giinavStartable, this, &CustomCommandWidgetController::giinavReceivedFirstTime);
    }
    QSettings settings;
    _customQmlFile = settings.value(_settingsKey).toString();
    //TOPO mod

}

void CustomCommandWidgetController::sendCommand(int commandId, QVariant componentId, QVariant confirm, QVariant param1, QVariant param2, QVariant param3, QVariant param4, QVariant param5, QVariant param6, QVariant param7)
{
    Q_UNUSED(confirm);

    if(_vehicle) {
        _vehicle->sendMavCommand(componentId.toInt(),
                                 (MAV_CMD)commandId,
                                 true,  // show error if fails
                                 param1.toFloat(), param2.toFloat(), param3.toFloat(), param4.toFloat(), param5.toFloat(), param6.toFloat(), param7.toFloat());
    }
}

//sends a NamedValueFloat MAVLink message using the Vehicle class
void CustomCommandWidgetController::sendNamedValueFloatMsg(QString name, int value)
{
    char nameC[10];
    memcpy(nameC, name.toStdString().c_str(), static_cast<size_t>(name.size()));
    nameC[name.size()] = 0;
    if(_vehicle) {
        _vehicle->sendMessageDebug(nameC, value);
    }
}

void CustomCommandWidgetController::updateGiinavStatus(void){
    _currGiinavStatus = _vehicleExt->getCurrGiinavStatus();
    emit statusChanged();
}

//called when giinavStartable signal is received
void CustomCommandWidgetController::giinavReceivedFirstTime(void){
    emit giinavStart();
}


QString CustomCommandWidgetController::getCurrentGiinavStatus(void){
    return _currGiinavStatus;
}

void CustomCommandWidgetController::toggleGiinav(void){
    _vehicleExt->toggleDisplayGiinav();
}

void CustomCommandWidgetController::selectQmlFile(void)
{
    QSettings settings;
    QString qmlFile = QGCQFileDialog::getOpenFileName(NULL, tr("Select custom Qml file"), QString(), tr("Qml files (*.qml)"));
    if (qmlFile.isEmpty()) {
        _customQmlFile.clear();
        settings.remove(_settingsKey);
    } else {
		QUrl url = QUrl::fromLocalFile(qmlFile);
		_customQmlFile = url.toString();
        settings.setValue(_settingsKey, _customQmlFile);
    }
    emit customQmlFileChanged(_customQmlFile);
}

void CustomCommandWidgetController::clearQmlFile(void)
{
    _customQmlFile.clear();
    QSettings settings;
    settings.remove(_settingsKey);
    emit customQmlFileChanged(_customQmlFile);
}
