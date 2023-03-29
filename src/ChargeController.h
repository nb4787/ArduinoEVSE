/* 
 * This file is part of the ArduinoEVSE (https://github.com/tomwetjens/ArduinoEVSE).
 * Copyright (c) 2023 Tom Wetjens.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARGECONTROLLER_H_  _
#define CHARGECONTROLLER_H_  _

#include "Pilot.h"

enum State
{
    Ready,
    Charging,
    Error
};

using EventHandler = void (*)();

struct LoadBalancingSettings {
  // Safe fallback (A) current when no current limit is set within timeout (for load balancing)
  // If set to <6A, fallback will mean that charging will stop temporarily
  float fallbackCurrent = 0;

  // Timeout (milliseconds) after which charging will fall back to safe current, when current limit has not been received (for load balancing)
  // If set to 0, no fallback will be performed
  unsigned long currentLimitTimeout = 20000;
};

struct ChargingSettings
{
  // Max current (A) that installed cabling can handle and must never be exceeded
  float maxCurrent = 16.0;

  LoadBalancingSettings loadBalancing;
};

class ChargeController
{
private:
    ChargingSettings settings;
    State state;
    Pilot pilot;
    VehicleState vehicleState;
    float currentLimit;
    unsigned long currentLimitLastUpdated;
    unsigned long started;
    EventHandler vehicleStateChange;
    EventHandler stateChange;
    void updateVehicleState();
    void fallbackCurrentIfNeeded();
    void applyCurrentLimit();
    void closeRelay();
    void openRelay();

public:
    void setup(ChargingSettings settings);
    void loop();
    
    void startCharging();
    void stopCharging();

    State getState();
    VehicleState getVehicleState();
    unsigned long getElapsedTime();
    float getCurrentLimit();
    void setCurrentLimit(float amps);
    Pilot* getPilot();

    // Event handlers
    void onVehicleStateChange(EventHandler handler);
    void onStateChange(EventHandler handler);
};

#endif // CHARGECONTROLLER_H_