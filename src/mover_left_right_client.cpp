#include "ros/ros.h"
 #include <test1/MoverLeftRight.h>
 #include <cstdlib>
 
 int main(int argc, char **argv)
 {
   ros::init(argc, argv, "add_two_ints_client");
   if (argc != 4)
   {
     ROS_INFO("usage: commands distance velocity direction (left=1 right=2)");
     return 1;
   }
 
   ros::NodeHandle n;
   ros::ServiceClient client = n.serviceClient<test1::MoverLeftRight>("mover_left_right");
   test1::MoverLeftRight srv;
   srv.request.distance = atoll(argv[1]);
   srv.request.velocity = atoll(argv[2]);
   srv.request.direction = atoll(argv[3]);
   if (client.call(srv))
   {
     ROS_INFO("cammand status: %ld", (bool)srv.response.done);
   }
   else
   {
     ROS_ERROR("Failed to call service add_two_ints");
     return 1;
   }
 
   return 0;
 }