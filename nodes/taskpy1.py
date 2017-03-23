#!/usr/bin/env python
import rospy
from amr_msgs.msg import Ranges
#from sensor_msgs.msg import Range
from geometry_msgs.msg import Twist

def sonar_callback(msg):
    
    global velocity_publisher
        
    #left, right = msg.ranges[1].range, msg.ranges[6].range

    '''
        Data processing
    '''
    
    twist = Twist()

            
    twist.linear.x = 0.0
    twist.linear.y = 0.05
    twist.angular.z = 0.0
    
    velocity_publisher.publish(twist)
    

def main():
    twist = Twist()

            
    twist.linear.x = 0.0
    twist.linear.y = 0.05
    twist.angular.z = 0.0
    global velocity_publisher
    velocity_publisher = rospy.Publisher('/cmd_vel', twist)
    rospy.init_node('taskpy1', anonymous=true)    
    #rospy.Subscriber('/sonar_pioneer', Ranges, sonar_callback)
   
    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        #rospy.logwarn("Running the node, time {}".format(rospy.get_time()))
        rate.sleep()
    pass

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass    