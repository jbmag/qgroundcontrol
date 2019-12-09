#ifndef VEHICLEEXTENSIONTOPO_H
#define VEHICLEEXTENSIONTOPO_H

#include <QObject>
#include <QGeoCoordinate>

class VehicleExtensionTopo : public QObject
{
    Q_OBJECT

public:

    VehicleExtensionTopo(void);

    // property text of giinav status
    Q_PROPERTY(QString giinavStatus MEMBER _currGiinavStatus NOTIFY giinavStatusChanged)
    // property for giinav_coordinate
    Q_PROPERTY(QGeoCoordinate giinavCoordinate MEMBER _giinavCoordinate NOTIFY giinavCoordinateChanged)
    // property text of RoamFree VDM status
    Q_PROPERTY(QString rfStatus MEMBER _currRFStatus NOTIFY rfStatusChanged)
    // property for RoamFree VDM coordinate
    Q_PROPERTY(QGeoCoordinate rfCoordinate MEMBER _rfCoordinate NOTIFY rfCoordinateChanged)

    // get current giinav status
    QString getCurrGiinavStatus(void);
    QGeoCoordinate getGiinavCoordinates(void);
    //toggle boolean that determine if Giinav coordinates should be displayed on Map
    void toggleDisplayGiinav(void);

    // get current RoamFree VDM status
    QString getCurrRFStatus(void);
    QGeoCoordinate getRFCoordinates(void);
    //toggle boolean that determine if RoamFree VDM coordinates should be displayed on Map
    void toggleDisplayRF(void);

    //handle functions used in Vehicle.cc when a new MAVLink message is received
    void handleReceivedGiinavStatus(uint16_t msg_value);
    void handleReceivedGiinavCoordinates(float latitude, float longitude, float altitude, uint64_t timestamp);
    void handleReceivedRFStatus(uint16_t msg_value);
    void handleReceivedRFCoordinates(float latitude, float longitude, float altitude, uint64_t timestamp);


    uint32_t currGiinavCoordTimestamp;
    uint32_t currRFCoordTimestamp;





private:

    //coordinates from Giinav
    QGeoCoordinate _giinavCoordinate;
    bool _displayGiinav;
    uint64_t _timestampCurrGiinavCoord;

    //coordinates from RoamFree VDM
    QGeoCoordinate _rfCoordinate;
    bool _displayRF;
    uint64_t _timestampCurrRFCoord;

    QString _currGiinavStatus;
    QString _currRFStatus;

    static const int _nbOfGiinavStatus;
    //static array for status giinav message
    static const char* const  _giinavStatus [];

    static const int _nbOfRFStatus;
    //static array for status RoamFree VDM message
    static const char* const  _rfStatus [];

signals:

    //signal emitted when giinav status changed
    void giinavStatusChanged();
    // signal emitted when new giinav coordinate
    void giinavCoordinateChanged();
    // signal emitted when giinav coordinates are received for the first time
    void giinavStartable();
    // signal emitted when switch button is toggled in qml widget
    void toggleGiinavOnMap();

    //signal emitted when RoamFree VDM status changed
    void rfStatusChanged();
    // signal emitted when new RoamFree VDM coordinate
    void rfCoordinateChanged();
    // signal emitted when RoamFree VDM coordinates are received for the first time
    void rfStartable();
    // signal emitted when switch button is toggled in qml widget
    void toggleRFOnMap();

};

#endif // VEHICLEEXTENSIONTOPO_H
