#include <actionlib/client/simple_action_client.h>
#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <ros/ros.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState &state,
            const ardrone_as::ArdroneResultConstPtr &result) {
  ROS_INFO("[State Result]: %s", state.toString().c_str());
  ROS_INFO("The Action has been completed");
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb() { ROS_INFO("Goal just went active"); }

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr &feedback) {
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ardrone_action_client_nowait");
  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client(
      "ardrone_action_server", true);
  client.waitForServer();

  ardrone_as::ArdroneGoal goal;
  goal.nseconds = 10;

  client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
  // client.waitForResult();

  ros::Rate loop_rate(2);
  actionlib::SimpleClientGoalState state_result = client.getState();
  ROS_INFO("[State Result]: %s", state_result.toString().c_str());

  while (state_result == actionlib::SimpleClientGoalState::ACTIVE ||
         state_result == actionlib::SimpleClientGoalState::PENDING) {
    ROS_INFO("Doing Stuff while waiting for the Server to give a result...");
    loop_rate.sleep();
    state_result = client.getState();
    ROS_INFO("[State Result]: %s", state_result.toString().c_str());
  }

  return 0;
}