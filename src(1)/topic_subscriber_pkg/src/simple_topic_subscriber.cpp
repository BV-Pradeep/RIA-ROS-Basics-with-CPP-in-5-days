#include <ros/ros.h>
#include <std_msgs/Int32.h>
// Here we are including all the headers necessary to use the most common public
// pieces of the ROS system. Always we create a new C++ file, we will need to
// add this include.

void counterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  ROS_INFO("%d", msg->data);// we are using ROS_INFO to print message data to screen
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_subscriber");// We initiate a ROS node called topic_subscriber
    ros::NodeHandle nh;// We create a handler for the node. This handler will actually do the initialization of the node.

    ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback);// Create a Subscriber object that will call the 'callback' function each time message is received on Topic 'counter'

    ros::spin();// Create a loop that will keep the program in execution

    return 0;
}