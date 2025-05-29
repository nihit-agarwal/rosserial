/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 *
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_mbed_demos
 *
 */


#include "mbed.h"
#include "Servo.h"
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

#ifdef TARGET_LPC1768
Servo servo(p21);
#elif defined(TARGET_KL25Z) || defined(TARGET_NUCLEO_F401RE)
Servo servo(D8);
#else
#error "You need to specify a pin for the Servo"
#endif
DigitalOut myled(LED2);

void servo_cb( const std_msgs::UInt16& cmd_msg) {
    servo.position(cmd_msg.data); //set servo angle, should be from 0-180
    myled = !myled;  //toggle led
}


ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

int main() {

    nh.initNode();
    nh.subscribe(sub);

    while (1) {
        nh.spinOnce();
        wait_ms(1);
    }
}



/*
#include "mbed.h"

#ifdef TARGET_LPC1768
PwmOut servo(p21);
#elif defined(TARGET_KL25Z) || defined(TARGET_NUCLEO_F401RE)
PwmOut servo(D8);
#else
#error "You need to specify a pin for the Servo"
#endif



const float minPulse = 0.0003f;  // 0 ms
const float maxPulse = 0.0023f;  // 2 ms
const float period = 0.020f;     // 20 ms (50 Hz)
const float stepSize = 0.00005f; // 50 µs step size
const int delayTime = 30;      // 1 second delay at each step

int main() {
    servo.period(period); // Set PWM period to 20 ms

    while (true) {
        for (float pulseWidth = minPulse; pulseWidth <= maxPulse; pulseWidth += stepSize) {
            servo.pulsewidth(pulseWidth); // Set PWM pulse width
            if (pulseWidth == 0.0013f) {
                break;
            }
            wait_ms(delayTime); // Wait at each step
        }


        wait_ms(200); // Pause before restarting
    }
}
*/