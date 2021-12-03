#include "main.h"
#include <math.h>
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
double analogToVoltage(double analog, double maxVoltage = VOLTAGE_LIMIT){
    double voltage = 0;
    voltage = analog * maxVoltage;
    return voltage;
}

void opcontrol() {
    pros::lcd::set_text(1, "Manual Control")
    ControllerButton runAutoButton(ControllerDigital::X);
    leftWheels.setCurrentLimit(4000);
    rightWheels.setCurrentLimit(4000);
    rightWheels.setVoltageLimit(VOLTAGE_LIMIT);
    rightWheels.setVoltageLimit(VOLTAGE_LIMIT);
    int power, turn, left, right;
    while (true) {
        power = controller.getAnalog(ControllerAnalog::leftY);
        turn = controller.getAnalog(ControllerAnalog::rightX);
        left = power + turn;
        right = power - turn;
        leftWheels.moveVoltage(analogToVoltage(left));
        rightWheels.moveVoltage(analogToVoltage(right));
        pros::delay(2);
    }
}
