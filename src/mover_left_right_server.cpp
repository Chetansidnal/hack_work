#include "ros/ros.h"
#include <test1/MoverLeftRight.h>
#include <std_msgs/String.h>
#include <cstdlib>
#include <iostream>
using namespace std;
 float dist, velo;  
int dir;
bool move(test1::MoverLeftRight::Request  &req,
            test1::MoverLeftRight::Response &res)      // this is for subscribing cammands
{
     res.done = true;
    // char *check = (char*)malloc(sizeof(char) *100);
// strcpy(check, req.direction.c_str());
  //  string s="hello";
    //  strcpy(s,st*);
     //strcpy(direction,req.c_str());
     ROS_INFO("request: distance=%2f, velocity=%2f, direction=%c", req.distance, 
              req.velocity, req.direction);
     //ROS_INFO(s.c_str());
     dist=(float)req.distance;
     velo=(float)req.velocity;
     dir=req.direction;
     ros::param::set("distance",dist);
     ros::param::set("velocity",velo);
     ros::param::set("dirnum",dir);
     
     ROS_INFO("dist%2f velo%2f dir%d ", dist,velo,dir);
     ROS_INFO("sending back response: [%d]", (bool)res.done);
     return true;
}
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "mover_left_right_server");
     ros::NodeHandle n;
    
     ros::ServiceServer service = n.advertiseService("mover_left_right", move);
     ROS_INFO("Ready take the commands.");
     ROS_INFO("dist%2f velo%2f dir%c ", dist,velo,dir);
     ros::spin();
   
     return 0;
   }