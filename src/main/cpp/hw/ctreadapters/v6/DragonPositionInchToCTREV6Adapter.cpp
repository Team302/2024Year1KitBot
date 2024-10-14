//====================================================================================================================================================
// Copyright 2024 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <numbers>
#include <string>

// FRC includes

// Team 302 includes
#include "hw/DistanceAngleCalcStruc.h"
#include "hw/ctreadapters/v6/DragonControlToCTREV6Adapter.h"
#include "hw/ctreadapters/v6/DragonPositionInchToCTREV6Adapter.h"
#include "mechanisms/controllers/ControlData.h"
#include "mechanisms/controllers/ControlModes.h"
#include "utils/ConversionUtils.h"

// Third Party Includes
#include "units/length.h"
#include "ctre/phoenix6/controls/PositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/PositionTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/PositionVoltage.hpp"

using ctre::phoenix6::controls::PositionDutyCycle;
using ctre::phoenix6::controls::PositionTorqueCurrentFOC;
using ctre::phoenix6::controls::PositionVoltage;
using ctre::phoenix6::hardware::TalonFX;
using std::string;

DragonPositionInchToCTREV6Adapter::DragonPositionInchToCTREV6Adapter(string networkTableName,
                                                                     int controllerSlot,
                                                                     const ControlData &controlInfo,
                                                                     const DistanceAngleCalcStruc &calcStruc,
                                                                     ctre::phoenix6::hardware::TalonFX &controller) : DragonControlToCTREV6Adapter(networkTableName, controllerSlot, controlInfo, calcStruc, controller)
{
}

void DragonPositionInchToCTREV6Adapter::Set(double value)
{
    units::angle::degree_t target = (m_calcStruc.countsPerInch > DistanceAngleCalcStruc::countsPerTolerance) ? units::angle::turn_t(value / m_calcStruc.countsPerInch) : units::angle::turn_t(value / (m_calcStruc.diameter * std::numbers::pi));
    units::angular_velocity::turns_per_second_t angVel = 0.0_tps; // TODO:  get this passed in
    bool overrideBrakeMode = false;                               // TODO: get this passed in
    bool forwardLimitSw = false;                                  // TODO: get this passed in
    bool reverseLimitSw = false;                                  // TODO: get this passed in

    if (m_isVoltage)
    {
        PositionVoltage out{target, angVel, m_enableFOC, m_voltageFeedForward, m_controllerSlot, overrideBrakeMode, forwardLimitSw, reverseLimitSw};
        m_controller.SetControl(out);
    }
    else if (m_isTorque)
    {
        PositionTorqueCurrentFOC out{target, angVel, m_torqueCurrentFeedForward, m_controllerSlot, overrideBrakeMode, forwardLimitSw, reverseLimitSw};
        m_controller.SetControl(out);
    }
    else
    {
        PositionTorqueCurrentFOC out{target, angVel, m_torqueCurrentFeedForward, m_controllerSlot, overrideBrakeMode, forwardLimitSw, reverseLimitSw};
        m_controller.SetControl(out);
    }
}

void DragonPositionInchToCTREV6Adapter::SetControlConstants(int controlSlot,
                                                            const ControlData &controlInfo)
{
    SetPeakAndNominalValues(m_networkTableName, controlInfo);
    SetPIDConstants(m_networkTableName, m_controllerSlot, controlInfo);
}
