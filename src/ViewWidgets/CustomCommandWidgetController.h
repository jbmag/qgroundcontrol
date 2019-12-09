/****************************************************************************
 *
 *   (c) 2009-2018 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#pragma once

#include <QObject>

#include "AutoPilotPlugin.h"
#include "FactPanelController.h"

#include "VehicleExtensionTopo.h"

class CustomCommandWidgetController : public FactPanelController
{
	Q_OBJECT
	
public:
	CustomCommandWidgetController(void);
    
    Q_PROPERTY(QString customQmlFile MEMBER _customQmlFile NOTIFY customQmlFileChanged)


	
    Q_INVOKABLE void sendCommand    (int commandId, QVariant componentId, QVariant confirm, QVariant param1, QVariant param2, QVariant param3, QVariant param4, QVariant param5, QVariant param6, QVariant param7);

    Q_INVOKABLE void sendNamedValueFloatMsg   (QString name, int value);
    Q_INVOKABLE QString getCurrentGiinavStatus (void);
    Q_INVOKABLE QString getCurrentRFStatus (void);

    Q_INVOKABLE void selectQmlFile  (void);
    Q_INVOKABLE void clearQmlFile   (void);
    Q_INVOKABLE void toggleGiinav   (void);
    Q_INVOKABLE void toggleRF   (void);
    
signals:
    void customQmlFileChanged   (const QString& customQmlFile);
    void newGiinavStatus (void);
    void newRFStatus (void);
    void giinavStart(void);
    void rfStart(void);

public slots:
    void updateGiinavStatus(void);
    void giinavReceivedFirstTime(void);
    void updateRFStatus(void);
    void rfReceivedFirstTime(void);



private:
    Vehicle*            _vehicle;
    std::shared_ptr<VehicleExtensionTopo> _vehicleExt;
    QString             _customQmlFile;
    static const char*  _settingsKey;
    QString _currGiinavStatus;
    QString _currRFStatus;
};

