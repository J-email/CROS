#include "main.h"
#include <math.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
double analogToVoltage(double analog, double maxVoltage = VOLTAGE_LIMIT) {
    return analog * maxVoltage;
}

void opcontrol() {
    bool gearChangeExtended = true;
    bool frontHandClosed = false;
    bool backHandClosed = false;
    bool backArmLifted = false;
    double power, turn, left, right;
    pros::lcd::set_text(1, "Manual Control");
    controller.setText(1, 0, "");

    ControllerButton brakeButton(ControllerDigital::right);
    ControllerButton gearChangeButton(ControllerDigital::Y);
    ControllerButton ringIntakeButton(ControllerDigital::down);

    ControllerButton frontHandButton(ControllerDigital::up);
    ControllerButton frontWristUpButton(ControllerDigital::R1);
    ControllerButton frontWristDownButton(ControllerDigital::R2);

    ControllerButton backHandButton(ControllerDigital::X);
    ControllerButton backWristUpButton(ControllerDigital::L1);
    ControllerButton backWristDownButton(ControllerDigital::L2);
    ControllerButton backArmButton(ControllerDigital::left);

    leftWheels.setCurrentLimit(CURRENT_LIMIT);
    rightWheels.setCurrentLimit(CURRENT_LIMIT);
    leftWheels.setVoltageLimit(VOLTAGE_LIMIT);
    rightWheels.setVoltageLimit(VOLTAGE_LIMIT);
    while (true) {
        power = controller.getAnalog(ControllerAnalog::leftY);
        turn = controller.getAnalog(ControllerAnalog::rightX);
        left = power + 0.5 * turn;
        right = power - 0.5 * turn;

        if (brakeButton.isPressed()) {
            leftWheels.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
            rightWheels.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
        } else {
            leftWheels.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
            rightWheels.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        }

        if (ringIntakeButton.changedToPressed()) {
            if (ringIntake.isStopped()) ringIntake.moveVoltage(VOLTAGE_LIMIT);
            else ringIntake.moveVelocity(0);
        }

        if (gearChangeButton.changedToPressed()) {
            gearChangeExtended = !gearChangeExtended;
            gearChange.set_value(gearChangeExtended);
        }

        if (frontHandButton.changedToPressed()) {
            frontHandClosed = !frontHandClosed;
            frontHand.set_value(frontHandClosed);
        }

        if (frontWristUpButton.isPressed()) frontWrist.set_value(true);
        else if (frontWristDownButton.isPressed()) frontWrist.set_value(false);

        if (backHandButton.changedToPressed()) {
            backHandClosed = !backHandClosed;
            backHand.set_value(backHandClosed);
        }

        if (backWristUpButton.isPressed()) backWrist.moveVoltage(VOLTAGE_LIMIT);
        else if (backWristDownButton.isPressed()) backWrist.moveVoltage(-1 * VOLTAGE_LIMIT);

        if (backArmButton.changedToPressed()){
            backArmLifted = !backArmLifted;
            backArm.set_value(backArmLifted);
        }

        leftWheels.moveVoltage(analogToVoltage(left));
        rightWheels.moveVoltage(analogToVoltage(right));
        pros::delay(2);
    }
}

#pragma clang diagnostic pop