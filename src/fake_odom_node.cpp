#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "fake_odom");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("fake_odom_topic", 50);
  tf::TransformBroadcaster odom_broadcaster;

  double x = 5.0;
  double y = -4.0;
  double th = 0.0;

  double vx = 0.1;
  double vy = -0.1;
  double vth = 0.1;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(1.0);
  while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);


    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry fake_odom_topic;
    fake_odom_topic.header.stamp = current_time;
    fake_odom_topic.header.frame_id = "odom";

    //set the position
    fake_odom_topic.pose.pose.position.x = x;
    fake_odom_topic.pose.pose.position.y = y;
    fake_odom_topic.pose.pose.position.z = 0.0;
    fake_odom_topic.pose.pose.orientation = odom_quat;

    //set the velocity
    fake_odom_topic.child_frame_id = "base_link";
    fake_odom_topic.twist.twist.linear.x = vx;
    fake_odom_topic.twist.twist.linear.y = vy;
    fake_odom_topic.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(fake_odom_topic);

    last_time = current_time;
    r.sleep();
  }
}
