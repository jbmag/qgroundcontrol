#include "VehicleExtensionTopo.h"

const char* const VehicleExtensionTopo::_giinavStatus[] =  {"first status","   Giinav Status","third status"};
const int VehicleExtensionTopo::_nbOfGiinavStatus = 3;

VehicleExtensionTopo::VehicleExtensionTopo(void)
{

}


QString VehicleExtensionTopo::getCurrGiinavStatus(void)
{
    return _currGiinavStatus;
}

QGeoCoordinate VehicleExtensionTopo::getGiinavCoordinates(void)
{
    return _giinavCoordinate;
}

void VehicleExtensionTopo::toggleDisplayGiinav(void)
{
    _displayGiinav = !_displayGiinav;
    emit toggleGiinavOnMap();
}

void VehicleExtensionTopo::handleReceivedGiinavStatus(uint16_t msg_value)
{
    if(msg_value < _nbOfGiinavStatus)
    {
        _currGiinavStatus = _giinavStatus[msg_value];
        emit giinavStatusChanged();
    }
}

void VehicleExtensionTopo::handleReceivedGiinavCoordinates(float latitude, float longitude, float altitude, uint64_t timestamp)
{
    _giinavCoordinate.setLatitude(static_cast<double>(latitude));
    _giinavCoordinate.setLongitude(static_cast<double>(longitude));
    _giinavCoordinate.setAltitude(static_cast<double>(altitude));
    _timestampCurrGiinavCoord = timestamp;

    static bool giinavInitialized = false;
    if (!giinavInitialized){
        giinavInitialized = true;
        _displayGiinav = false; //don't display on map by default

        emit giinavStartable(); //emitted only when first received (PROBLEM?) allow the switch on widget to be clickable
    }
    if (_displayGiinav){
        emit giinavCoordinateChanged();
    }

}
