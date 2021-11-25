#include "main.h"
//Various definitions of autonomous modes.
void blue_left_auto(){
// Move 1 meter to the first goal
    drive->moveDistance(1_m);
// Turn 90 degrees to face second goal
    drive->turnAngle(90_deg);
// Move 1 meter to the first goal
    drive->moveDistance(1_m);
// Turn 90 degrees to face second goal
    drive->turnAngle(90_deg);
    // Move 1 meter to the first goal
    drive->moveDistance(1_m);
// Turn 90 degrees to face second goal
    drive->turnAngle(90_deg);
// Move 1 meter to the first goal
    drive->moveDistance(1_m);
// Turn 90 degrees to face second goal
    drive->turnAngle(90_deg);
}
void blue_right_auto(){

}
void red_left_auto(){

}
void red_right_auto(){

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
  switch(AUTONOMOUS_MODE){
    case 0:
      pros::lcd::set_text(1, "BLUE LEFT");
      blue_left_auto();
      break;
    case 1:
      pros::lcd::set_text(1, "BLUE RIGHT");
      blue_right_auto();
      break;
    case 2:
      pros::lcd::set_text(1, "RED LEFT");
      red_left_auto();
      break;
    case 3:
      pros::lcd::set_text(1, "RED RIGHT");
      red_right_auto();
      break;
    default:
      pros::lcd::set_text(1, "UNKNOWN AUTONOMOUS MODE");
      break;
  }
}
