#include "main.h"

// Other motors
Motor ringIntake = Motor(RING_INTAKE_PORT);
Motor backWrist = Motor(BACK_WRIST_PORT);

// Left & right motor groups.
MotorGroup leftWheels = MotorGroup({LEFT_WHEEL_1_PORT, LEFT_WHEEL_2_PORT, LEFT_WHEEL_2_PORT});
MotorGroup rightWheels = MotorGroup({RIGHT_WHEEL_1_PORT, RIGHT_WHEEL_2_PORT, RIGHT_WHEEL_2_PORT});
// Chassis Controller - drive the robot around with open- or closed-loop control
std::shared_ptr <ChassisController> drive =
        ChassisControllerBuilder()
                .withMotors(leftWheels, rightWheels)
                        // Green gear-set, 4 in wheel diam, 11.5 in wheel track
                .withDimensions(AbstractMotor::gearset::green, {{WHEEL_DIAMETER, WHEEL_TRACK}, imev5GreenTPR})
                .withMaxVoltage(VOLTAGE_LIMIT)
                        /*.withGains(
                                {KP, KI, KD}, // Distance controller gains
                                {0, 0, 0}, // Turn controller gains
                                {0, 0, 0}  // Angle controller gains (helps drive straight)
                        )*/
                .withOdometry()
                .buildOdometry();

// Controller
Controller controller;

// Vision
pros::Vision vision(VISION_PORT);

// Pneumatics
pros::ADIDigitalOut frontHand = pros::ADIDigitalOut(FRONT_HAND_PORT, false);
pros::ADIDigitalOut frontWrist = pros::ADIDigitalOut(FRONT_WRIST_PORT, false);
pros::ADIDigitalOut backHand = pros::ADIDigitalOut(BACK_HAND_PORT, false);
pros::ADIDigitalOut backArm = pros::ADIDigitalOut(BACK_ARM_PORT, false);
pros::ADIDigitalOut gearChange = pros::ADIDigitalOut(GEAR_CHANGE_PORT, false);

