#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
// Here we are including all the headers necessary to use the most common public
// pieces of the ROS system. Always we create a new C++ file, we will need to
// add this include.

int main(int argc, char** argv) {// We start the main C++ program

    ros::init(argc, argv, "move_forward");// We initiate a ROS node called topic_publisher
    ros::NodeHandle nh;// We create a handler for the node. This handler will actually do the initialization of the node.

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1); //We create a publisher called counter which uses std_msgs of Int32 type to publish 1000
    ros::Rate loop_rate(2);// We create a Rate object of 2Hz

    geometry_msgs::Twist move;//We initializing count variable.
    move.linear.x = 0.0;// we are setting Count data to zero
    move.angular.z = 0.0;
    while (ros::ok())//Endless loop to publish the count variable
    {
        pub.publish(move);// Publish the message within the 'count' variable
        ros::spinOnce();
        loop_rate.sleep();// Make sure the publish rate maintains at 2 Hz
    }

    return 0;
}