#include <ros/ros.h>
#include <topic_subscriber_pkg/Age.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "publish_age_node");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<topic_subscriber_pkg::Age>("age_info", 1000);
    ros::Rate loop_rate(2);

    topic_subscriber_pkg::Age age;
    age.years = 5;
    age.months = 10;
    age.days = 21;

    while (ros::ok())
    {
        pub.publish(age);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}