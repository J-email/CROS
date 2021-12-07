#include "main.h"

// Various definitions of autonomous modes.
void blue_left_auto() {
    // turn 45 degrees and drive approximately 1.4 ft
    drive->driveToPoint({0_ft, 6_ft});
    // turn approximately 45 degrees to end up at 90 degrees
    drive->turnToAngle(90_deg);
    // turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
    drive->turnToPoint({5_ft, 0_ft});
}

void blue_right_auto() {

}

void red_left_auto() {

}

void red_right_auto() {
    // Move forward to the goal
    drive->driveToPoint({0_ft, 6_ft});
    // Grab
    frontHand.set_value(true);
    // Go back
    backArm.set_value(true);
    drive->driveToPoint({0_ft, 3_ft}, true);
    // Turn & drop the goal
    drive->turnToPoint({-6_ft, 0_ft});
    frontHand.set_value(false);
    // Turn back
    drive->turnToPoint({-6_ft, 6_ft});
    // Grab the red one
    backArm.set_value(true);
    // Spit rings
    ringIntake.moveVoltage(VOLTAGE_LIMIT);
    // while doing that, go forward, grab middle goal
    drive->driveToPoint({-6_ft, 6_ft});
    // Grab
    frontHand.set_value(true);
    // place down all of them
    drive->driveToPoint({2_ft, 2_ft}, true);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    drive->setState({0_in, 0_in, 0_deg});
    pros::lcd::set_text(1, "Autonomous");
    switch (AUTONOMOUS_MODE) {
        case 0:
            pros::lcd::set_text(2, "BLUE LEFT");
            blue_left_auto();
            break;
        case 1:
            pros::lcd::set_text(2, "BLUE RIGHT");
            blue_right_auto();
            break;
        case 2:
            pros::lcd::set_text(2, "RED LEFT");
            red_left_auto();
            break;
        case 3:
            pros::lcd::set_text(2, "RED RIGHT");
            red_right_auto();
            break;
        default:
            pros::lcd::set_text(2, "UNKNOWN AUTONOMOUS MODE");
            break;
    }
    pros::lcd::clear_line(2);
}
