/*************************************************************************
    > File Name: src/quaternion_to_eular.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月29日 星期一 17时44分51秒
 ************************************************************************/

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>

using namespace std;

ros::Publisher rpy_publisher;
ros::Subscriber quat_subscriber;

void MsgCallback(const geometry_msgs::Quaternion msg)
{
	//the incoming geometry_msgs::Quaternion is transform to a tf::Quaterion
	tf::Quaternion quat;
	tf::quaternionMsgToTF(msg, quat);

	double roll, pitch, yaw;
	tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
	
	geometry_msgs::Vector3 rpy;
	rpy.x = roll;
	rpy.y = pitch;
	rpy.z = yaw;

	rpy_publisher.publish(rpy);
	ROS_INFO("published rpy angles: roll=%f pitch=%f yaw=%f", rpy.x, rpy.y, rpy.z);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "talker");	
	ros::NodeHandle n;
	rpy_publisher = n.advertise<geometry_msgs::Vector3>("ryp_angles", 1000);
	quat_subscriber = n.subscribe("rotation_quaternion", 1000, MsgCallback);

	ROS_INFO("waiting for quaternion");
	ros::spin();
	return 0;
}
