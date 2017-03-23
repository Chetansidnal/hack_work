#include "ros/ros.h"
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>




int main(int argc, char **argv)
{
	geometry_msgs::Twist vel_msg;
	vel_msg.linear.x = 0.0;
	vel_msg.linear.y = 0.0;
	vel_msg.angular.z = 0.0;
	//Twist twist = new Twist();
	//twist.linear.x=0;
	//twist.linear.y=0.2;
	//twist.linear.z=0;
	ros::init(argc, argv, "testpub");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
	ros::Rate loop_rate(10);	
	ROS_INFO("Ready take the commands.");
  //   ros::spin();
   
   int count = 0;
  while (ros::ok())
  {

    chatter_pub.publish(vel_msg);
     ros::spinOnce();
      loop_rate.sleep();
     ++count;
  }  
     return 0;

}    