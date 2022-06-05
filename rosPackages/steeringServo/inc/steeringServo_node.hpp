#include <ros/ros.h>
#include "steeringServo/steeringServo.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "steeringServo");
    ros::NodeHandle nodehandle("~");

    steeringServo::SteeringServo steeringServo(nodehandle);
    ros::spin();

    return 0;
}
