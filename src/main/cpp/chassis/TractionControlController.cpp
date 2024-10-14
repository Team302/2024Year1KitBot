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
// This file was automatically generated by the Team 302 code generator version 1.3.0.8
// Generated on Wednesday, February 21, 2024 8:17:08 PM

// C++ Includes
#include "algorithm"
#include <cmath>

// FRC Includes

// Team 302 Includes
#include "chassis/TractionControlController.h"
#include "utils/logging/Logger.h"

/**
 * @brief      Construct a TractionControlController object
 * @param [in] staticCoF       - static coefficient of friction
 * @param [in] dynamicCoF      - dynamic coefficient of friction
 * @param [in] optimalSlipRatio- optimal slip ratio
 * @param [in] mass            - mass of the robot (lbs)
 * @param [in] maxLinearSpeed  - maximum linear speed (m/s)
 *
 * The TractionControlController object takes in the static and dynamic coefficients of friction, the optimal slip ratio, the mass of the robot, and the maximum linear speed of the robot to generate a control output to prevent slipping.
 */
TractionControlController::TractionControlController(double staticCoF,
                                                     double dynamicCoF,
                                                     double optimalSlipRatio,
                                                     double mass,
                                                     units::velocity::meters_per_second_t maxLinearSpeed) : m_staticCoF(staticCoF),
                                                                                                            m_dynamicCoF(dynamicCoF),
                                                                                                            m_optimalSlipRatio(optimalSlipRatio),
                                                                                                            m_mass(mass / 4.0),
                                                                                                            m_maxLinearSpeed(maxLinearSpeed),
                                                                                                            m_maxPredictedSlipRatio((maxLinearSpeed * m_robotLoopRate_Hz) / (staticCoF * m_mass * 9.81)),
                                                                                                            m_isSlipping(false),
                                                                                                            m_slippingDebouncer(MIN_SLIPPING_TIME, frc::Debouncer::DebounceType::kRising)
{
    if (dynamicCoF > staticCoF)
    {
        Logger::GetLogger()->LogData(LOGGER_LEVEL::ERROR, "TractionControlController", "Coefficent of Friction Error", "Static CoF must be higher than dynamic CoF!");
    }
    m_optimalSlipRatio = std::clamp(optimalSlipRatio, MIN_SLIP_RATIO, MAX_SLIP_RATIO);
}

units::velocity::meters_per_second_t TractionControlController::calculate(units::velocity::meters_per_second_t velocityRequest, units::velocity::meters_per_second_t inertialVelocity, units::velocity::meters_per_second_t wheelSpeed)
{
    units::velocity::meters_per_second_t velocityOutput = velocityRequest;

    inertialVelocity = units::velocity::meters_per_second_t(std::abs(inertialVelocity.value()));

    double currentSlipRatio = std::abs(inertialVelocity <= INERTIAL_VELOCITY_THRESHOLD ? wheelSpeed.value() / m_maxLinearSpeed.value()
                                                                                       : (std::abs(wheelSpeed.value()) - inertialVelocity.value()) / inertialVelocity.value());

    m_isSlipping = m_slippingDebouncer.Calculate(currentSlipRatio > m_optimalSlipRatio && std::abs(wheelSpeed.value()) > m_maxLinearSpeed.value() * m_optimalSlipRatio);

    double desiredAcceleration = (velocityRequest.value() - inertialVelocity.value()) / m_robotLoopRate_Hz;

    double sigmoid = 1 / (1 + std::exp(-SIGMOID_K * std::clamp(2 * (currentSlipRatio - m_optimalSlipRatio) - 1, -1.0, 1.0)));

    double effectiveCoF = m_isSlipping ? m_staticCoF * (1 - sigmoid) + m_dynamicCoF * sigmoid : m_staticCoF;

    double predictedSlipRatio = std::abs(desiredAcceleration / (inertialVelocity.value() * 9.81 + effectiveCoF * m_mass * 9.81)) / m_maxPredictedSlipRatio;

    double velocityCorrection = (m_optimalSlipRatio - predictedSlipRatio) * VELOCITY_CORRECTION_SCALAR;

    return units::velocity::meters_per_second_t(std::clamp(velocityOutput.value() + velocityCorrection, -m_maxLinearSpeed.value(), m_maxLinearSpeed.value()));
}

bool TractionControlController::isSlipping() const
{
    return m_isSlipping;
}
