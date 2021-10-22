#include "main.h"
// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
				.withMotors({LEFT_WHEEL_1_PORT, LEFT_WHEEL_2_PORT}, {RIGHT_WHEEL_1_PORT, RIGHT_WHEEL_2_PORT})
				// Green gearset, 4 in wheel diam, 11.5 in wheel track
				.withDimensions(AbstractMotor::gearset::green, {{WHEEL_DIAMETER, WHEEL_TRACK}, imev5GreenTPR})
				.withOdometry()
				.buildOdometry();

std::shared_ptr<AsyncMotionProfileController> path_gen =
		AsyncMotionProfileControllerBuilder()
				.withLimits({
				      1.0, // Maximum linear velocity of the Chassis in m/s
				      2.0, // Maximum linear acceleration of the Chassis in m/s/s
				      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
				    })
				.withOutput(drive)
				.buildMotionProfileController();

//controller
Controller controller;

//vision
pros::Vision vision(VISION_PORT);
