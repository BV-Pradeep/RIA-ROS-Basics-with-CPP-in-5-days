#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <actionlib/client/simple_action_client.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState& state,
            const ardrone_as::ArdroneResultConstPtr& result)
{
  ROS_INFO("The Action has been completed");
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr& feedback)
{
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ardrone_action_client_wait");
  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client("ardrone_action_server", true);
  client.waitForServer();

  ardrone_as::ArdroneGoal goal;
  goal.nseconds = 10;

  client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
  //client.waitForResult();

  ros::Rate loop_rate(2);

  while (client.waitForResult() != true)
  {
    ROS_INFO("Doing Stuff while waiting for the Server to give a result...");
    loop_rate.sleep();
  }

  return 0;
}