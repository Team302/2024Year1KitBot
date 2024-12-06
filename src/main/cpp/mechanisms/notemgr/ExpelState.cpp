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
// This file was automatically generated by the Team 302 code generator version 1.2.3.6
// Generated on Sunday, February 18, 2024 12:51:47 PM

// C++ Includes
#include <string>

// FRC includes

// Team 302 includes
#include "mechanisms/notemgr/ExpelState.h"
#include "teleopcontrol/TeleopControl.h"
#include "teleopcontrol/TeleopControlFunctions.h"
#include "utils/logging/Logger.h"
using namespace LauncherConstants;
// Third Party Includes

using namespace std;

/// @class ExampleForwardState
/// @brief information about the control (open loop, closed loop position, closed loop velocity, etc.) for a mechanism state
ExpelState::ExpelState(std::string stateName,
					   int stateId,
					   CANLauncher *mech) : State(stateName, stateId), m_mechanism(mech), m_timer(new frc::Timer())
{
}

void ExpelState::Init()
{
	m_timer->Restart();
}

void ExpelState::Run()
{
	m_mechanism->SetLaunchWheel(kLauncherSpeed);
	auto speed = (m_timer->Get() > kLauncherDelay) ? kLaunchFeederSpeed : 0.0;
	m_mechanism->SetFeedWheel(speed);
}

void ExpelState::Exit()
{
}

bool ExpelState::AtTarget()
{
	return true;
}

bool ExpelState::IsTransitionCondition(bool considerGamepadTransitions)
{
	// To get the current state use m_mechanism->GetCurrentState()

	return (considerGamepadTransitions && TeleopControl::GetInstance()->IsButtonPressed(TeleopControlFunctions::EXPEL));
}
