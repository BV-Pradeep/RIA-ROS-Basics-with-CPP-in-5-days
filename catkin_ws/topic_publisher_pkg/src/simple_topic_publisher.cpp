#include <ros/ros.h>
#include <std_msgs/Int32.h>
// Here we are including all the headers necessary to use the most common public
// pieces of the ROS system. Always we create a new C++ file, we will need to
// add this include.

int main(int argc, char** argv) {// We start the main C++ program

    ros::init(argc, argv, "topic_publisher");// We initiate a ROS node called topic_publisher
    ros::NodeHandle nh;// We create a handler for the node. This handler will actually do the initialization of the node.

    ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000); //We create a publisher called counter which uses std_msgs of Int32 type to publish 1000
    ros::Rate loop_rate(2);// We create a Rate object of 2Hz

    std_msgs::Int32 count;//We initializing count variable.
    count.data = 0;// we are setting Count data to zero

    while (ros::ok())//Endless loop to publish the count variable
    {
        pub.publish(count);// Publish the message within the 'count' variable
        ros::spinOnce();
        loop_rate.sleep();// Make sure the publish rate maintains at 2 Hz
        ++count.data;// Increment 'count' variable
    }

    return 0;
}