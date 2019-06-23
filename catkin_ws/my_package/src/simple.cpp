#include <ros/ros.h>
// Here we are including all the headers necessary to use the most common public
// pieces of the ROS system. Always we create a new C++ file, we will need to
// add this include.

int main(int argc, char **argv) { // We start the main C++ program

  ros::init(argc, argv, "ObiWan"); // We initiate a ROS node called ObiWan
  ros::NodeHandle nh;     // We create a handler for the node. This handler will
                          // actually do the initialization of the // node
  ros::Rate loop_rate(2); // We create a Rate object of 2Hz
  while (ros::ok())       // Endless loop_rate
  {
    ROS_INFO(
        "Help me Obi-Wan Kenobi, you're my only hope"); // This is the same as a
                                                        // print in ROS
    ros::spinOnce(); // Calling ros::spinOnce() here is not necessary for this
                     // simple program, because we are not // receiving any
                     // callbacks. However, if you were to add a subscription
                     // into this application, and                      // did
                     // not have ros::spinOnce() here, your callbacks would
                     // never get called. So, add it for good measure.
    loop_rate.sleep(); // We sleep for the needed time
  }

  return 0; // We end our program
}