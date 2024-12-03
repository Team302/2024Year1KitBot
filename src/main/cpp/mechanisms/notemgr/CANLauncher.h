// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <map>
#include <string>

#include "rev/CANSparkMax.h"

#include "Constants.h"

#include "mechanisms/base/StateMgr.h"

class CANLauncher : public StateMgr
{
public:
  enum STATE_NAMES
  {
    STATE_READY,
    STATE_INTAKE,
    STATE_EXPEL
  };

  static std::map<std::string, STATE_NAMES> StringToSTATE_NAMESEnumMap;

  CANLauncher();

  // An accessor method to set the speed (technically the output percentage) of the launch wheel
  void SetLaunchWheel(double speed);

  // An accessor method to set the speed (technically the output percentage) of the feed wheel
  void SetFeedWheel(double speed);

  // A helper method to stop both wheels. You could skip having a method like this and call the
  // individual accessors with speed = 0 instead
  void Stop();

  void CreateAndRegisterStates();

  void SetCurrentState(int state, bool run) override;

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax m_launchWheel;
  rev::CANSparkMax m_feedWheel;
};
