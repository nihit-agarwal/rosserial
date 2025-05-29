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
Servo pump(p21);
Servo valve(p22);
#elif defined(TARGET_KL25Z) || defined(TARGET_NUCLEO_F401RE)
Servo pump(D8);
Servo valve(D9);
#else
#error "You need to specify a pin for the Servo"
#endif
DigitalOut valve_led(LED2);
DigitalOut pump_led(LED1);

void pump_cb( const std_msgs::UInt16& cmd_msg) {
    pump.position(cmd_msg.data); //set servo angle, should be from 0-180
    pump_led = !pump_led;  //toggle led
}

void valve_cb( const std_msgs::UInt16& cmd_msg) {
    valve.position(cmd_msg.data); //set servo angle, should be from 0-180
    valve_led = !valve_led;  //toggle led
}

ros::Subscriber<std_msgs::UInt16> pump_sub("pump", pump_cb);
ros::Subscriber<std_msgs::UInt16> valve_sub("valve", valve_cb);

int main() {

    nh.initNode();
    nh.subscribe(pump_sub);
    nh.subscribe(valve_sub);

    while (1) {
        nh.spinOnce();
        wait_ms(1);
    }
}

