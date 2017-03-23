#include "ros/ros.h"
#include <test1/eStopStart.h>
#include <std_msgs/String.h>
#include <cstdlib>
#include <iostream>

bool estsp(test1::eStopStart::Request  &req,
            test1::eStopStart::Response &res) 
			{
			ROS_INFO("request:Estop=%d, Estart=%d ", req.estopt, req.estartt);

			ros::param::set("estart",(bool)req.estartt);
     		ros::param::set("estop",(bool)req.estopt);
    		ROS_INFO("sending back response: [%ld]", (long int)res.donet);
     		return true;

			}

int main(int argc, char **argv)
   {
     ros::init(argc, argv, "estart_estop_server");
     ros::NodeHandle n;
    
     ros::ServiceServer service = n.advertiseService("estart_estop", estsp);
     ROS_INFO("Ready take the commands.");
    // ROS_INFO("dist%2f velo%2f dir%c ", dist,velo,dir);
     ros::spin();
   
     return 0;
   }