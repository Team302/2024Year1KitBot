// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "chassis/CANDrivetrain.h"

using namespace DrivetrainConstants;

CANDrivetrain::CANDrivetrain()
    : m_left1{kLeftFrontID, rev::CANSparkMax::MotorType::kBrushed},
      m_left2{kLeftRearID, rev::CANSparkMax::MotorType::kBrushed},
      m_right1{kRightFrontID, rev::CANSparkMax::MotorType::kBrushed},
      m_right2{kRightRearID, rev::CANSparkMax::MotorType::kBrushed}
{
  // Invert left side motors so both sides drive forward with positive output
  // values
  m_leftMotors.SetInverted(true);
  m_rightMotors.SetInverted(false);

  // Set current limits for all motors
  m_left1.SetSmartCurrentLimit(kCurrentLimit);
  m_left2.SetSmartCurrentLimit(kCurrentLimit);
  m_right1.SetSmartCurrentLimit(kCurrentLimit);
  m_right2.SetSmartCurrentLimit(kCurrentLimit);
}

void CANDrivetrain::ArcadeDrive(double speed, double rotation)
{
  m_drive.ArcadeDrive(speed, rotation);
}