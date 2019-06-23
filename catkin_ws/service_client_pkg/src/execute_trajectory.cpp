#include "ros/ros.h"
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include <ros/package.h>
// Import rospackage

int main(int argc, char **argv)
{
  ros::init(argc, argv, "execute_trajectory_node");
  ros::NodeHandle nh;

  // Create the connection to the service /execute_trajectory
  ros::ServiceClient exec_traj_service = nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>("/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj trajectory; // Create an object of type ExecTraj

  // This ros::package::getPath works in the same way as $(find name_of_package) in the launch files.
  trajectory.request.file = ros::package::getPath("service_client_pkg") + "/config/get_food.txt";
  // Fill the variable file of this object with the desired value

  if (exec_traj_service.call(trajectory))
  {
    ROS_INFO("%s", "Service successfully called. Executing trajectory.");
  }
  else
  {
    ROS_ERROR("Failed to call service delete_model");
    return 1;
  }

  return 0;
}