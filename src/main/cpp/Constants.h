// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/time.h>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace OperatorConstants
{
    // Port numbers for driver and operator gamepads. These correspond with the numbers on the USB tab of the DriverStation
    constexpr int kDriverControllerPort = 0;
    constexpr int kOperatorControllerPort = 1;
} // namespace OperatorConstants

namespace DrivetrainConstants
{
    // PWM ports/CAN IDs for motor controllers
    constexpr int kLeftRearID = 14;
    constexpr int kLeftFrontID = 1;
    constexpr int kRightRearID = 3;
    constexpr int kRightFrontID = 2;

    // Current limit for drivetrain motors
    constexpr int kCurrentLimit = 60;
} // namespace DrivetrainConstants

namespace LauncherConstants
{
    // PWM ports/CAN IDs for motor controllers
    constexpr int kFeederID = 13;
    constexpr int kLauncherID = 12;

    // Current limit for launcher and feed wheels
    constexpr int kLauncherCurrentLimit = 80;
    constexpr int kFeedCurrentLimit = 80;

    // Speeds for wheels when intaking and launching. Intake speeds are negative to run the wheels in reverse
    constexpr double kLauncherSpeed = 1;
    constexpr double kLaunchFeederSpeed = 1;
    constexpr double kIntakeLauncherSpeed = -1;
    constexpr double kIntakeFeederSpeed = -.2;

    constexpr units::second_t kLauncherDelay = 1_s;
} // namespace LauncherConstants
