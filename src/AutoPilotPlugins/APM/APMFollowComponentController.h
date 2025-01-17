/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "FactPanelController.h"

class APMFollowComponentController : public FactPanelController
{
    Q_OBJECT
    
public:
    APMFollowComponentController(void);

    Q_PROPERTY(Fact* angle      READ angleFact      CONSTANT)
    Q_PROPERTY(Fact* distance   READ distanceFact   CONSTANT)
    Q_PROPERTY(Fact* height     READ heightFact     CONSTANT)

    Fact* angleFact     (void) { return &_angleFact; }
    Fact* distanceFact  (void) { return &_distanceFact; }
    Fact* heightFact    (void) { return &_heightFact; }

    static const char* settingsGroup;
    static const char* angleName;
    static const char* distanceName;
    static const char* heightName;

private:
    QMap<QString, FactMetaData*> _metaDataMap;

    SettingsFact _angleFact;
    SettingsFact _distanceFact;
    SettingsFact _heightFact;
};
