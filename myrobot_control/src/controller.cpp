#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

float linx, angZ;

void filterVelocityCallback(const geometry_msgs::Twist& msg){
   //Using the callback function just for subscribing  
   //Subscribing the message and storing it in 'linx' and 'angZ'
   linx = msg.linear.x;      angZ = msg.angular.z;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "filter_velocity");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/my_diffbot/mobile_base_controller/cmd_vel",1000,&filterVelocityCallback);
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/my_diffbot/mobile_base_controller/pose", 1000);
  ros::Rate rate(2);

  while(ros::ok()){
     geometry_msgs::Twist msg;
     msg.linear.x = linx;     msg.angular.z = angZ;

     //It would be better to apply the conditions within the main function and use the 
     //Callback function just for subscribing
     if (angZ > 0){
        ROS_INFO_STREAM("Subscriber velocities:"<<" linear="<<linx<<" angular="<<angZ);
        //The above line doesn't publish. It's like printf (but not exactly)
        pub.publish(msg);   //This line is for publishing. It publishes to 'turtle1/pose'
     }  
     rate.sleep();
     ros::spinOnce();      //Notice this
  } 
}