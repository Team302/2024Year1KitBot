// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "mechanisms/climber/CANClimber.h"
#include "mechanisms/climber/RaiseState.h"
#include "mechanisms/climber/ClimbState.h"
#include "mechanisms/climber/ReadyState.h"

using namespace ClimberConstants;

std::map<std::string, CANClimber::STATE_NAMES> CANClimber::StringToSTATE_NAMESEnumMap{
    {"STATE_READY", CANClimber::STATE_NAMES::STATE_READY},
    {"STATE_CLIMB", CANClimber::STATE_NAMES::STATE_CLIMB},
    {"STATE_RAISE", CANClimber::STATE_NAMES::STATE_RAISE}};

CANClimber::CANClimber()
    : m_climbermotor{kClimberMotorID, rev::CANSparkMax::MotorType::kBrushed}
{
  m_climbermotor.SetSmartCurrentLimit(kClimberMotorSpeed);
  CreateAndRegisterStates();
}

// An accessor method to set the speed (technically the output percentage) of
// the launch wheel
void CANClimber::SetClimberMotor(double speed)
{
  m_climbermotor.Set(speed);
}

// A helper method to stop both wheels. You could skip having a method like this
// and call the individual accessors with speed = 0 instead
void CANClimber::Stop()
{
  m_climbermotor.Set(0);
}

void CANClimber::SetCurrentState(int state, bool run)
{
  StateMgr::SetCurrentState(state, run);
}

void CANClimber::CreateAndRegisterStates()
{
  auto ready = new ClimberReadyState("Ready", 0, this);
  auto climb = new ClimbState("Climb", 1, this);
  auto raise = new RaiseState("Raise", 2, this);

  AddToStateVector(ready);
  AddToStateVector(climb);
  AddToStateVector(raise);

  ready->RegisterTransitionState(climb);
  ready->RegisterTransitionState(raise);

  raise->RegisterTransitionState(ready);

  climb->RegisterTransitionState(ready);

  SetCurrentState(0, false);

  Init();
}
