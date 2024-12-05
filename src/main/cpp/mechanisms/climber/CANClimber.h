// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <map>
#include <string>

#include "rev/CANSparkMax.h"

#include "Constants.h"

#include "mechanisms/base/StateMgr.h"

class CANClimber : public StateMgr
{
public:
  enum STATE_NAMES
  {
    STATE_READY,
    STATE_CLIMB,
    STATE_RAISE
  };

  static std::map<std::string, STATE_NAMES> StringToSTATE_NAMESEnumMap;

  CANClimber();

  // An accessor method to set the speed (technically the output percentage) of the launch wheel
  void SetClimberMotor(double speed);

  // A helper method to stop both wheels. You could skip having a method like this and call the
  // individual accessors with speed = 0 instead
  void Stop();

  void CreateAndRegisterStates();

  void SetCurrentState(int state, bool run) override;

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax m_climbermotor;
};
