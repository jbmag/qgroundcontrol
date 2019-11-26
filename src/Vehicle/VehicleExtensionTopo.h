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

    // get current giinav status
    QString getCurrGiinavStatus(void);
    QGeoCoordinate getGiinavCoordinates(void);
    //toggle boolean that determine if Giinav coordinates should be displayed on Map
    void toggleDisplayGiinav(void);

    //handle functions used in Vehicle.cc when a new MAVLink message is received
    void handleReceivedGiinavStatus(uint16_t msg_value);
    void handleReceivedGiinavCoordinates(float latitude, float longitude, float altitude, uint64_t timestamp);

    //static array for status giinav message

    uint32_t currGiinavCoordTimestamp;





private:

    //coordinates from Giinav
    QGeoCoordinate _giinavCoordinate;
    bool _displayGiinav;
    uint64_t _timestampCurrGiinavCoord;

    QString _currGiinavStatus;

    static const int _nbOfGiinavStatus;
    //static array for status giinav message
    static const char* const  _giinavStatus [];

signals:

    //signal emitted when giinav status changed
    void giinavStatusChanged();
    // signal emitted when new giinav coordinate
    void giinavCoordinateChanged();
    // signal emitted when giinav coordinates are received for the first time
    void giinavStartable();
    // signal emitted when switch button is toggled in qml widget
    void toggleGiinavOnMap();

};

#endif // VEHICLEEXTENSIONTOPO_H
