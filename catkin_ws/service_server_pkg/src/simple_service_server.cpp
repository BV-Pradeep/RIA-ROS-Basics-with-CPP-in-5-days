#include "ros/ros.h"
#include "std_srvs/Empty.h"
// Import the service message header file generated from the Empty.srv message

// We define the callback function of the service
bool my_callback(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("My_callback has been called"); // We print an string whenever the
                                           // Service gets called
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  ros::ServiceServer my_service = nh.advertiseService(
      "/my_service", my_callback); // create the Service called // my_service
                                   // with the defined // callback
  ros::spin(); // mantain the service open.

  return 0;
}