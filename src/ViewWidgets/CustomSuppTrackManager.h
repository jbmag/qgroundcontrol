#ifndef CUSTOMSUPPTRACKMANAGER_H
#define CUSTOMSUPPTRACKMANAGER_H

#include <QObject>

#include "AutoPilotPlugin.h"

class CustomSuppTrackManager : public QObject
{
    Q_OBJECT


public:
    CustomSuppTrackManager(void);
    Q_PROPERTY(QGeoCoordinate giinavCoordinates MEMBER _giinavCoordinates NOTIFY giinavCoordinatesChanged)
    Q_INVOKABLE void _initialize  (void);

signals:
//    void newGiinavCoordinates(void);
    void displayGiinavMapItem(void);
    void giinavCoordinatesChanged(void);


public slots:
    void updateGiinavCoordinates(void);
    void toggleGiinavOnMap(void);

private:
    Vehicle*            _vehicle;
    std::shared_ptr<VehicleExtensionTopo> _vehicleExt;
    QGeoCoordinate      _giinavCoordinates;
    float _giinavLong;
    float _giinavLat;

};

#endif // CUSTOMSUPPTRACKMANAGER_H
