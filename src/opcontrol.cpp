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
    pros::lcd::set_text(1, "Manual Control");
    pros::lcd::clear_line(2);
    controller.setText(1, 0, "");

    ControllerButton brakeButton(ControllerDigital::L1);
    ControllerButton gearChangeButton(ControllerDigital::L1);
    ControllerButton ringIntakeButton(ControllerDigital::X);

    ControllerButton frontHandButton(ControllerDigital::L1);
    ControllerButton frontWristUpButton(ControllerDigital::L1);
    ControllerButton frontWristDownButton(ControllerDigital::L1);

    ControllerButton backHandButton(ControllerDigital::L1);
    ControllerButton backWristUpButton(ControllerDigital::L1);
    ControllerButton backWristDownButton(ControllerDigital::L1);
    ControllerButton backArmButton(ControllerDigital::L1);

    leftWheels.setCurrentLimit(CURRENT_LIMIT);
    rightWheels.setCurrentLimit(CURRENT_LIMIT);
    leftWheels.setVoltageLimit(VOLTAGE_LIMIT);
    rightWheels.setVoltageLimit(VOLTAGE_LIMIT);
    double power, turn, left, right;
    while (true) {
        power = controller.getAnalog(ControllerAnalog::leftY);
        turn = controller.getAnalog(ControllerAnalog::rightX);
        left = power + 0.5 * turn;
        right = power - 0.5 * turn;

        if (brakeButton.isPressed()) {
            leftWheels.setBrakeMode(brake);
            rightWheels.setBrakeMode(brake);
        } else {
            leftWheels.setBrakeMode(coast);
            rightWheels.setBrakeMode(coast);
        }

        if (ringIntakeButton.changedToPressed()){
        }
        leftWheels.moveVoltage(analogToVoltage(left));
        rightWheels.moveVoltage(analogToVoltage(right));
        pros::delay(2);
    }
}

#pragma clang diagnostic pop