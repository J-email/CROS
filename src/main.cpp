#include "main.h"
// Left & right motor groups.
MotorGroup leftWheels = MotorGroup({LEFT_WHEEL_1_PORT, LEFT_WHEEL_2_PORT, LEFT_WHEEL_2_PORT});
MotorGroup rightWheels = MotorGroup({RIGHT_WHEEL_1_PORT, RIGHT_WHEEL_2_PORT, RIGHT_WHEEL_2_PORT});
// Chassis Controller - drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
				.withMotors(leftWheels, rightWheels)
				// Green gear-set, 4 in wheel diam, 11.5 in wheel track
				.withDimensions(AbstractMotor::gearset::green, {{WHEEL_DIAMETER, WHEEL_TRACK}, imev5GreenTPR})
				.withMaxVoltage(VOLTAGE_LIMIT)
                .withOdometry()
				.buildOdometry();

// Controller
Controller controller;

// Vision
pros::Vision vision(VISION_PORT);

