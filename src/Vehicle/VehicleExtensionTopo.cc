#include "VehicleExtensionTopo.h"

const char* const VehicleExtensionTopo::_giinavStatus[] =  {"   First status Giinav","   Second status Giinav","   Third status Giinav"};
const int VehicleExtensionTopo::_nbOfGiinavStatus = 3;

const char* const VehicleExtensionTopo::_rfStatus[] =  {"   First status VDM RoamFree","   Second status VDM RoamFree","   Third status VDM RoamFree"};
const int VehicleExtensionTopo::_nbOfRFStatus = 3;

VehicleExtensionTopo::VehicleExtensionTopo(void)
{

}


QString VehicleExtensionTopo::getCurrGiinavStatus(void)
{
    return _currGiinavStatus;
}

QString VehicleExtensionTopo::getCurrRFStatus(void)
{
    return _currRFStatus;
}


QGeoCoordinate VehicleExtensionTopo::getGiinavCoordinates(void)
{
    return _giinavCoordinate;
}

QGeoCoordinate VehicleExtensionTopo::getRFCoordinates(void)
{
    return _rfCoordinate;
}

void VehicleExtensionTopo::toggleDisplayGiinav(void)
{
    _displayGiinav = !_displayGiinav;
    emit toggleGiinavOnMap();
}

void VehicleExtensionTopo::toggleDisplayRF(void)
{
    _displayRF = !_displayRF;
    emit toggleRFOnMap();
}

void VehicleExtensionTopo::handleReceivedGiinavStatus(uint16_t msg_value)
{
    if(msg_value < _nbOfGiinavStatus)
    {
        _currGiinavStatus = _giinavStatus[msg_value];
        emit giinavStatusChanged();
    }
}

void VehicleExtensionTopo::handleReceivedRFStatus(uint16_t msg_value)
{
    if(msg_value < _nbOfRFStatus)
    {
        _currRFStatus = _rfStatus[msg_value];
        emit rfStatusChanged();
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

void VehicleExtensionTopo::handleReceivedRFCoordinates(float latitude, float longitude, float altitude, uint64_t timestamp)
{
    _rfCoordinate.setLatitude(static_cast<double>(latitude));
    _rfCoordinate.setLongitude(static_cast<double>(longitude));
    _rfCoordinate.setAltitude(static_cast<double>(altitude));
    _timestampCurrRFCoord = timestamp;

    static bool rfInitialized = false;
    if (!rfInitialized){
        rfInitialized = true;
        _displayRF = false; //don't display on map by default

        emit rfStartable(); //emitted only when first received (PROBLEM?) allow the switch on widget to be clickable
    }
    if (_displayRF){
        emit rfCoordinateChanged();
    }

}
