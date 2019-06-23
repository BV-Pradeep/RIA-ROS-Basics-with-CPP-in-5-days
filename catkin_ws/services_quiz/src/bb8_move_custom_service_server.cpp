#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <services_quiz/BB8CustomServiceMessage.h>

class MoveBB8 {
  // Other variables
  bool running_;
  int state_;
  int rate_hz_;
  float duration_;
  int times_;
  float radius_;
  int repetitions_;

  // ROS Objects
  ros::NodeHandle nh_;
  ros::Rate *rate_;

  // ROS Services
  ros::ServiceServer srv_perform_square_;

  // ROS Publishers
  ros::Publisher pub_cmd_vel_;

public:
  MoveBB8() {
    // Other variables
    running_ = false;
    state_ = 0;
    rate_hz_ = 20;
    duration_ = 0;
    times_ = 0;
    radius_ = 0;
    repetitions_ = 0;

    // ROS Objects
    rate_ = new ros::Rate(rate_hz_);

    // ROS Services
    srv_perform_square_ = nh_.advertiseService("/move_bb8_in_square_custom",
                                               &MoveBB8::my_callback, this);

    // ROS Publishers
    pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  }

  ~MoveBB8(void) {}

  void rateSleep(void) { rate_->sleep(); }

  geometry_msgs::Twist getStateVelocity() {
    geometry_msgs::Twist vel;
    switch (state_) {
    case 0:
      // go ahead
      vel.linear.x = 0.2;
      vel.angular.z = 0;
      break;
    case 1:
      // stop
      vel.linear.x = 0;
      vel.angular.z = 0;
      break;
    case 2:
      // turn right
      vel.linear.x = 0;
      vel.angular.z = 0.2;
      break;
    case 3:
      // stop
      vel.linear.x = 0;
      vel.angular.z = 0;
      break;
    }
    return vel;
  }

  void runTimeStateMachine(void) {
    geometry_msgs::Twist vel;

    if (!running_) {
      vel.linear.x = 0;
      vel.angular.z = 0;
      pub_cmd_vel_.publish(vel);
      return;
    }

    vel = this->getStateVelocity();

    pub_cmd_vel_.publish(vel);

    duration_ -= 1 / (float)rate_hz_;

    ROS_INFO("State [%d], Vel[%.2f, %.2f], Duration [%.2f]", state_,
             vel.linear.x, vel.angular.z, duration_);

    if (duration_ <= 0) {
      float state_duration[4] = {radius_, 3.8, 4.0, 0.1};
      int next_state = state_ + 1;
      if (state_ == 3) {
        next_state = 0;
        times_ -= 1;
      }
      int next_state_duration = state_duration[next_state];
      this->changeState(next_state, next_state_duration);
    }

    if (times_ == 0) {
      running_ = false;
      vel.linear.x = 0;
      vel.angular.z = 0;
      pub_cmd_vel_.publish(vel);
    }
  }

  void changeState(int state, float duration) {
    state_ = state;
    duration_ = duration;
    ROS_INFO("Change to state [%d]", state_);
  }

  bool my_callback(services_quiz::BB8CustomServiceMessage::Request &req,
                   services_quiz::BB8CustomServiceMessage::Response &res) {
    running_ = !running_;
    radius_ = req.radius;
    repetitions_ = req.repetitions;
    times_ = 4 * repetitions_;
    return running_;
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "MoveBB8Server");

  MoveBB8 moveBB8;

  while (ros::ok()) {
    moveBB8.runTimeStateMachine();

    moveBB8.rateSleep();

    ros::spinOnce();
  }

  ros::spin();

  return 0;
}