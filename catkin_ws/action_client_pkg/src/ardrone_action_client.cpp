#include <actionlib/client/simple_action_client.h>
#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <ros/ros.h>

int nImage = 0; // Initialization of a global variable

// Definition of the done calback. It is called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState &state,
            const ardrone_as::ArdroneResultConstPtr &result) {
  ROS_INFO("The Action has been completed");
  ros::shutdown();
}

// Definition of the active callback. It is called once when the goal becomes
// active
void activeCb() { ROS_INFO("Goal just went active"); }

// Definition of the feedback callback. This will be called when feedback is
// received from the action server. It just // prints a message indicating a new
// message has been received
void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr &feedback) {
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}

int main(int argc, char **argv) {
  ros::init(argc, argv,
            "drone_action_client"); // Initializes the action client node
  // Create the connection to the action server
  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client(
      "ardrone_action_server", true);
  client.waitForServer(); // Waits until the action server is up and running

  ardrone_as::ArdroneGoal goal; // Creates a goal to send to the action server
  goal.nseconds =
      10; // Fills the goal. Indicates, take pictures along 10 seconds
  client.sendGoal(
      goal, &doneCb, &activeCb,
      &feedbackCb); // sends the goal to the action server, specifying which //
                    // functions to call when the goal completes, when the //
                    // goal becames active, and when feedback is received

  client.waitForResult();
  return 0;
}