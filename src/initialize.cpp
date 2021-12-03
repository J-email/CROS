#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
    pros::lcd::set_text(4, "80 International"); //print "80 INT" in the 3rd line
    pros::lcd::set_text(1, "Initialization")
    drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);//set the brake mode to coast
	controller.rumble(".");//rumble to indicate end of initialization
}
