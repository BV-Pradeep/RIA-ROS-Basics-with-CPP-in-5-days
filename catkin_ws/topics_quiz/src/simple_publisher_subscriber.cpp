#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
// Here we are including all the headers necessary to use the most common public
// pieces of the ROS system. Always we create a new C++ file, we will need to
// add this include.

float linX, angZ; // Starting global variables linear x and Angular z

void counterCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {
  ROS_INFO("%f", msg->ranges[360]); // We print the distance to an obstacle in
                                    // front of the robot

  // If the distance to an obstacle in front of the robot is bigger than 1
  // meter, the robot will move forward
  if (msg->ranges[360] > 1) {
    linX = 0.1;
    angZ = 0.0;
  }
  // If the distance to an obstacle in front of the robot is smaller than 1
  // meter, the robot will turn left
  if (msg->ranges[360] < 1) {
    linX = 0.0;
    angZ = 0.4;
  }
  // If the distance to an obstacle at the left side of the robot is smaller
  // than 0.3 meters, the robot will turn right
  if (msg->ranges[719] < 0.3) {
    linX = 0.0;
    angZ = -0.4;
  }
  // If the distance to an obstacle at the right side of the robot is smaller
  // than 0.3 meters, the robot will turn left
  if (msg->ranges[0] < 0.3) {
    linX = 0.0;
    angZ = 0.4;
  }
}

int main(int argc, char **argv) { // We start the main C++ program

  ros::init(
      argc, argv,
      "topics_quiz_node"); // We initiate a ROS node called topic_publisher
  ros::NodeHandle nh; // We create a handler for the node. This handler will
                      // actually do the initialization of the node.

  ros::Subscriber sub =
      nh.subscribe("/kobuki/laser/scan", 1000,
                   counterCallback); // Create a Subscriber object that will
                                     // call the 'callback' function each time
                                     // message is received on Topic 'counter'
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1000); // Create a publisher object
  geometry_msgs::Twist move;

  ros::Rate rate(2); // Create a rate object of 2Hz frequency

  while (ros::ok()) {

    move.linear.x = linX;
    move.angular.z = angZ;
    pub.publish(move); // Publishes the cmd_vel based what is being updated in
                       // the callback function

    rate.sleep();
    ros::spinOnce();
  }

  return 0;
}