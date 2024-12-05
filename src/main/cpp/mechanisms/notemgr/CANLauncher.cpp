// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "mechanisms/notemgr/CANLauncher.h"
#include "mechanisms/notemgr/ExpelState.h"
#include "mechanisms/notemgr/IntakeState.h"
#include "mechanisms/notemgr/ReadyState.h"

using namespace LauncherConstants;

std::map<std::string, CANLauncher::STATE_NAMES> CANLauncher::StringToSTATE_NAMESEnumMap{
    {"STATE_READY", CANLauncher::STATE_NAMES::STATE_READY},
    {"STATE_INTAKE", CANLauncher::STATE_NAMES::STATE_INTAKE},
    {"STATE_EXPEL", CANLauncher::STATE_NAMES::STATE_EXPEL}};

CANLauncher::CANLauncher()
    : m_launchWheel{kLauncherID, rev::CANSparkMax::MotorType::kBrushed},
      m_feedWheel{kFeederID, rev::CANSparkMax::MotorType::kBrushed}
{
  m_launchWheel.SetSmartCurrentLimit(kLauncherCurrentLimit);
  m_feedWheel.SetSmartCurrentLimit(kFeedCurrentLimit);

  CreateAndRegisterStates();
}

// An accessor method to set the speed (technically the output percentage) of
// the launch wheel
void CANLauncher::SetLaunchWheel(double speed)
{
  m_launchWheel.Set(speed);
}

// An accessor method to set the speed (technically the output percentage) of
// the feed wheel
void CANLauncher::SetFeedWheel(double speed)
{
  m_feedWheel.Set(speed);
}

// A helper method to stop both wheels. You could skip having a method like this
// and call the individual accessors with speed = 0 instead
void CANLauncher::Stop()
{
  m_launchWheel.Set(0);
  m_feedWheel.Set(0);
}

void CANLauncher::SetCurrentState(int state, bool run)
{
  StateMgr::SetCurrentState(state, run);
}

void CANLauncher::CreateAndRegisterStates()
{
  auto ready = new ReadyState("Ready", 0, this);
  auto intake = new IntakeState("Intake", 1, this);
  auto launch = new ExpelState("Launch", 2, this);

  AddToStateVector(ready);
  AddToStateVector(intake);
  AddToStateVector(launch);

  ready->RegisterTransitionState(intake);
  ready->RegisterTransitionState(launch);

  launch->RegisterTransitionState(ready);

  intake->RegisterTransitionState(ready);

  SetCurrentState(0, false);

  Init();
}
