// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/RobotController.h>
#include <Robot.h>

#include <string>

#include "chassis/CANDrivetrain.h"
#include "mechanisms/notemgr/CANLauncher.h"

// #include "auton/AutonPreviewer.h"
// #include "auton/CyclePrimitives.h"
// #include "chassis/configs/ChassisConfig.h"
// #include "chassis/configs/ChassisConfigMgr.h"
#include "configs/RobotConfig.h"
#include "configs/RobotConfigMgr.h"
// #include "driveteamfeedback/DriverFeedback.h"
#include "PeriodicLooper.h"
#include "Robot.h"
#include "robotstate/RobotState.h"
#include "teleopcontrol/TeleopControl.h"
// #include "utils/DragonField.h"
#include "utils/logging/DragonDataLoggerMgr.h"
#include "utils/logging/LoggableItemMgr.h"
#include "utils/logging/Logger.h"
#include "utils/logging/LoggerData.h"
#include "utils/logging/LoggerEnums.h"
#include "utils/logging/DataTrace.h"

using std::string;

void Robot::RobotInit()
{
    isFMSAttached = frc::DriverStation::IsFMSAttached();

    Logger::GetLogger()->PutLoggingSelectionsOnDashboard();
    if (!isFMSAttached)
    {
        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("RobotInit"), string("arrived"));
        InitializeDataTracing();
    }

    m_controller = nullptr;

    InitializeRobot();
    InitializeAutonOptions();
    InitializeDriveteamFeedback();

    m_datalogger = DragonDataLoggerMgr::GetInstance();

    if (!isFMSAttached)
    {
        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("RobotInit"), string("end"));
    }
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
    isFMSAttached = isFMSAttached ? true : frc::DriverStation::IsFMSAttached();
    if (!isFMSAttached)
    {
        LoggableItemMgr::GetInstance()->LogData();
        Logger::GetLogger()->PeriodicLog();
    }

    if (m_datalogger != nullptr && !frc::DriverStation::IsDisabled())
    {
        m_datalogger->PeriodicDataLog();
    }

    if (m_robotState != nullptr)
    {
        m_robotState->Run();
    }

    UpdateDriveTeamFeedback();
    LogDiagnosticData();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic()
{
    /**
    if (!isFMSAttached)
    {
        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("AutonomousPeriodic"), string("arrived"));
    }

    if (m_cyclePrims != nullptr)
    {
        m_cyclePrims->Run();
    }
    PeriodicLooper::GetInstance()->AutonRunCurrentState();
    if (!isFMSAttached)
    {
        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("AutonomousPeriodic"), string("end"));
    }
    **/
}

void Robot::TeleopInit()
{
    m_drive->Periodic();
    m_launcher->SetCurrentState(1, false);
    m_launcher->RunCurrentState();

    // PeriodicLooper::GetInstance()->TeleopRunCurrentState();
}

void Robot::TeleopPeriodic()
{
    m_drive->Periodic();
    m_launcher->RunCurrentState();

    // PeriodicLooper::GetInstance()->TeleopRunCurrentState();
}

void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic()
{
}
void Robot::TestInit()
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TestInit"), string("arrived"));
}

void Robot::TestPeriodic()
{
}

void Robot::LogDiagnosticData()
{
}

void Robot::LogSensorData()
{
}

void Robot::LogMotorData()
{
}

void Robot::LogCameraData()
{
}

void Robot::SimulationInit()
{
    PeriodicLooper::GetInstance()->SimulationRunCurrentState();
}

void Robot::SimulationPeriodic()
{
    PeriodicLooper::GetInstance()->SimulationRunCurrentState();
}

void Robot::InitializeRobot()
{
    int32_t teamNumber = frc::RobotController::GetTeamNumber();
    RobotConfigMgr::GetInstance()->InitRobot((RobotConfigMgr::RobotIdentifier)teamNumber);

    m_drive = new Drive(new CANDrivetrain(), TeleopControl::GetInstance());
    m_launcher = new CANLauncher();

    m_robotState = RobotState::GetInstance();
    m_robotState->Init();
}

void Robot::InitializeAutonOptions()
{
    // m_cyclePrims = new CyclePrimitives(); // intialize auton selections
    // m_previewer = new AutonPreviewer(m_cyclePrims);
}
void Robot::InitializeDriveteamFeedback()
{
    // m_field = DragonField::GetInstance(); // TODO: move to drive team feedback
}

void Robot::UpdateDriveTeamFeedback()
{
    /**
    if (m_previewer != nullptr)
    {
        m_previewer->CheckCurrentAuton();
    }
    if (m_field != nullptr && m_chassis != nullptr)
    {
        m_field->UpdateRobotPosition(m_chassis->GetPose()); // ToDo:: Move to DriveTeamFeedback (also don't assume m_field isn't a nullptr)
    }
    auto feedback = DriverFeedback::GetInstance();
    if (feedback != nullptr)
    {
        feedback->UpdateFeedback();
    }
    **/
}

void Robot::InitializeDataTracing()
{
    DataTrace::GetInstance()->Connect();
}
#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
