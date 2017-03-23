#include "ros/ros.h"
#include <math.h>
#include <std_msgs/String.h>
#include <string.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

bool tempestart=false, tempestop=false;
float cposx , cposy, posx,posy, tdistance,tvelocity, reach;
float tdirection=0;

void odoCallback(const nav_msgs::Odometry::ConstPtr& msg){


	//ROS_INFO("Seq: [%d]", msg->header.seq);
	//ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y,msg->pose.pose.position.z);
	///ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	//ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);

	
	 	posx= msg->pose.pose.position.x;
	 	posy= msg->pose.pose.position.y;
	 //float	posx= pose.pose.position.z;

}



int main(int argc, char **argv){
	
	bool current_xy =true;
	ros::init(argc, argv, "event1");
	ros::NodeHandle n;//create a handle node
	n.setParam("estart", false);
	n.setParam("estop",false);
	n.setParam("distance",0.0);
	n.setParam("velocity",0.2);
	//n.setparam("dirnum",0.0);
	ros::param::set("dirnum",0.0);
	//n.setParam("direction","nodir".c_str());
	geometry_msgs::Twist vel_msg;
	ros::Subscriber sub = n.subscribe("/odom",1000, odoCallback);
        //subscriber lister the msgs of given topic
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
	ros::Rate loop_rate(10);	
	ROS_INFO("Ready take the commands.");
  //   ros::spin();
   
   int count = 0;
  while (ros::ok())
  {
  	//std::string global_name, relative_name, default_param;
  ros::param::get("/estart", tempestart);
  
  if (tempestart ){
  	ROS_INFO("estart is true");
  		if (current_xy){
  			cposx=	posx;
  			cposy=posy;
  			current_xy=false;
  		}
  	ros::param::get("/velocity", tvelocity);
  	ros::param::get("/estop",tempestop);
  	//ros::param::get("/direction",tdirection.c_str());
  	ros::param::get("/distance", tdistance);
  	ros::param::get("/dirnum", tdirection);
  		if (tempestop){
  		vel_msg.linear.x = 0.0;
		vel_msg.linear.y = 0.0;
		vel_msg.angular.z = 0.0;
		ROS_INFO("recived Estop command!!!");
		chatter_pub.publish(vel_msg);
  		}
  		else {
  			ROS_INFO("step2 ok ");
  			reach= sqrt(pow((cposx-posx),2)+(pow((cposy-posy),2)));
  			ROS_INFO("reach =%2f",reach);
  			ROS_INFO("posx =%2f posy =%2f cposx =%2f cposy =%2f",posx ,posy,cposx,cposy );
  			ROS_INFO("distancec =%2f",tdistance);
  			ROS_INFO("velocity= %2f",tvelocity);

  			if (reach<=(tdistance/10)){
  				//if (strcmp(tdirection, "left")){ 
  				 if (tdirection==1){
  					vel_msg.linear.x = 0.0; vel_msg.linear.y = tvelocity*0.1; vel_msg.angular.z = 0.0;
  					ROS_INFO("moving Left %f",reach);
  					chatter_pub.publish(vel_msg);
  					}
  				//else if(strcmp(tdirection, "right"))
  				else if(tdirection==2)	{vel_msg.linear.x = 0.0; vel_msg.linear.y = -(tvelocity*0.1); vel_msg.angular.z = 0.0;
  														ROS_INFO("moving right %f",reach);
  														chatter_pub.publish(vel_msg); }
  			}

  			else {
  				vel_msg.linear.x = 0.0;
				vel_msg.linear.y = 0.0;
				vel_msg.angular.z = 0.0;
        current_xy=true;
        ros::param::set("velocity", 0.0);
				ROS_INFO("success!!!! its reached ");
  			}
  	
  }
  chatter_pub.publish(vel_msg);
  
  }
  else if(tempestart!=true){ROS_INFO("Waiting for estart");}
     ros::spinOnce();
      loop_rate.sleep();
     ++count;
  }  
    
return 0;
}