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
    Q_PROPERTY(QGeoCoordinate rfCoordinates MEMBER _rfCoordinates NOTIFY rfCoordinatesChanged)
    Q_INVOKABLE void _initialize  (void);

signals:
    void displayGiinavMapItem(void);
    void giinavCoordinatesChanged(void);
    void displayRFMapItem(void);
    void rfCoordinatesChanged(void);


public slots:
    void updateGiinavCoordinates(void);
    void toggleGiinavOnMap(void);
    void updateRFCoordinates(void);
    void toggleRFOnMap(void);

private:
    Vehicle*            _vehicle;
    std::shared_ptr<VehicleExtensionTopo> _vehicleExt;
    QGeoCoordinate      _giinavCoordinates;
    QGeoCoordinate      _rfCoordinates;


};

#endif // CUSTOMSUPPTRACKMANAGER_H
