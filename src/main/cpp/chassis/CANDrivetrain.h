// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "rev/CANSparkMax.h"

#include "Constants.h"

class CANDrivetrain
{
public:
  CANDrivetrain();

  void ArcadeDrive(double speed, double rotation);

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  // The motor controllers
  rev::CANSparkMax m_left1;
  rev::CANSparkMax m_left2;
  rev::CANSparkMax m_right1;
  rev::CANSparkMax m_right2;

  // The motors on the left side of the drive
  frc::MotorControllerGroup m_leftMotors{m_left1, m_left2};

  // The motors on the right side of the drive
  frc::MotorControllerGroup m_rightMotors{m_right1, m_right2};

  // The robot's drive
  frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};
};
