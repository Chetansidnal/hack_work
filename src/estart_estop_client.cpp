#include "ros/ros.h"
 #include <test1/eStopStart.h>
 #include <cstdlib>

int main(int argc, char **argv)
 {
   ros::init(argc, argv, "estart_estop_client");
   if (argc != 3)
   {
     ROS_INFO("usage: commands estop=1  estart=0 ");
     return 1;
   }

  ros::NodeHandle n;
   ros::ServiceClient client = n.serviceClient<test1::eStopStart>("estart_estop");
   test1::eStopStart srv1;
   srv1.request.estopt = atoll(argv[1]);
   srv1.request.estartt = atoll(argv[2]);
     if (client.call(srv1))
   {
     ROS_INFO("cammand status: %ld", (long int)srv1.response.donet);
   }
   else
   {
     ROS_ERROR("Failed to call estart_estop");
     return 1;
   }
 
   return 0;
 } 