#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

/**
 * @brief Abstract class representing a servo motor.
 *
 * The ServoMotor class defines an interface for controlling servo motors.
 */
class ServoMotor
{
public:
    /**
     * @brief Turns on the servo motor.
     */
    virtual void on() = 0;

    /**
     * @brief Sets the angle of the servo motor.
     *
     * @param angle The desired angle for the servo motor.
     */
    virtual void setAngle(short angle) = 0;

    /**
     * @brief Turns off the servo motor.
     */
    virtual void off() = 0;
};

#endif
