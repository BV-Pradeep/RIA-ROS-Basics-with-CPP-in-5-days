#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"
// Import the service message used by the service /move_bb8_in_square_custom

int main(int argc, char **argv) {
  ros::init(argc, argv,
            "service_move_bb8_in_square_client"); // Initialise a ROS node
  ros::NodeHandle nh;

  // Create the connection to the service /move_bb8_in_square_custom
  ros::ServiceClient perform_square_service_client =
      nh.serviceClient<services_quiz::BB8CustomServiceMessage>(
          "/move_bb8_in_square_custom");
  services_quiz::BB8CustomServiceMessage srv; // Create an object of type Empty
  srv.request.radius = 3.0;
  srv.request.repetitions = 2;

  if (perform_square_service_client.call(srv)) {
    ROS_INFO("Service successfully called. Moving BB8 in a square.");
  } else {
    ROS_ERROR("Failed to call service /move_bb8_in_square_custom");
    return 1;
  }

  return 0;
}