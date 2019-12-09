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
        _vehicleExt = _vehicle->vehicleExtensionTopo;
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::giinavCoordinateChanged, this, &CustomSuppTrackManager::updateGiinavCoordinates);
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::toggleGiinavOnMap, this, &CustomSuppTrackManager::toggleGiinavOnMap);
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::rfCoordinateChanged, this, &CustomSuppTrackManager::updateRFCoordinates);
        QObject::connect(_vehicleExt.get(), &VehicleExtensionTopo::toggleRFOnMap, this, &CustomSuppTrackManager::toggleRFOnMap);
    }


}
void CustomSuppTrackManager::updateGiinavCoordinates(void)
{
    _giinavCoordinates = _vehicleExt->getGiinavCoordinates();


    emit giinavCoordinatesChanged();
}

void CustomSuppTrackManager::updateRFCoordinates(void)
{
    _rfCoordinates = _vehicleExt->getRFCoordinates();


    emit rfCoordinatesChanged();
}

void CustomSuppTrackManager::toggleGiinavOnMap(void)
{
           emit displayGiinavMapItem();
}

void CustomSuppTrackManager::toggleRFOnMap(void)
{
           emit displayRFMapItem();
}
