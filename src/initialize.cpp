#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	controller.rumble("- - -");//rumble 3 times to indicate start of initialization
	drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);//set the brake mode to coast
	pros::lcd::initialize();
	pros::lcd::set_text(3, "80 International"); //print "80 INT" in the 3rd line
	controller.rumble(". . .");//rumble 3 times to indicate end of initialization
}