#include "CustomSuppTrackManager.h"
#include "MultiVehicleManager.h"
#include "QGCApplication.h"

#include "VehicleExtensionTopo.h"

#include <QSettings>

CustomSuppTrackManager::CustomSuppTrackManager(void) :
    _vehicle(NULL)
{
}

void CustomSuppTrackManager::_initialize(void)
{
    if(qgcApp()->toolbox()->multiVehicleManager()->activeVehicle()) {
        _vehicle = qgcApp()->toolbox()->multiVehicleManager()->activeVehicle();
    }

    QObject::connect(&_vehicle->vehicleExtensionTopo, &VehicleExtensionTopo::giinavCoordinateChanged, this, &CustomSuppTrackManager::updateGiinavCoordinates);
    QObject::connect(&_vehicle->vehicleExtensionTopo, &VehicleExtensionTopo::toggleGiinavOnMap, this, &CustomSuppTrackManager::toggleGiinavOnMap);
}
void CustomSuppTrackManager::updateGiinavCoordinates(void)
{
    _giinavCoordinates = _vehicle->vehicleExtensionTopo.getGiinavCoordinates();


    emit giinavCoordinatesChanged();
}

void CustomSuppTrackManager::toggleGiinavOnMap(void)
{
           emit displayGiinavMapItem();
}
