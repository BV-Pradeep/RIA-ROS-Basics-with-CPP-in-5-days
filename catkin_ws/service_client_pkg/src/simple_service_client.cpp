#include "gazebo_msgs/DeleteModel.h"
#include "ros/ros.h"
// Import the service message used by the service /gazebo/delete_model

int main(int argc, char **argv) {
  ros::init(
      argc, argv,
      "service_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  // Create the connection to the service /gazebo/delete_model
  ros::ServiceClient delete_model_service =
      nh.serviceClient<gazebo_msgs::DeleteModel>("/gazebo/delete_model");
  gazebo_msgs::DeleteModel srv;      // Create an object of type DeleteModel
  srv.request.model_name = "bowl_1"; // Fill the variable model_name of this
                                     // object with the desired value

  if (delete_model_service
          .call(srv)) // Send through the connection the name of the object to
                      // be deleted by the // service
  {
    ROS_INFO("%s",
             srv.response.status_message
                 .c_str()); // Print the result given by the service called
  } else {
    ROS_ERROR("Failed to call service delete_model");
    return 1;
  }

  return 0;
}