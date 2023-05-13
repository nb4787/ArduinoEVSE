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
#include <MainsMeter.h>

#include <Arduino.h>

void MainsMeter::setup()
{
    auto now = millis();
    // Pretend it was 'infinitely' long ago
    _updated = now - UINT64_MAX;
}

void MainsMeter::updateValues(ThreePhases importCurrent, ThreePhases exportCurrent)
{
    _importCurrent = importCurrent;
    _exportCurrent = exportCurrent;
    _updated = millis();
}