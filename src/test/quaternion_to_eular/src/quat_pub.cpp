/*************************************************************************
    > File Name: src/quat_pub.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月29日 星期一 18时11分41秒
 ************************************************************************/

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>

using namespace std;

ros::Publisher quat_pub;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "guat_pub");
	ros::NodeHandle n;
	quat_pub = n.advertise<geometry_msgs::Quaternion>("rotation_quaternion", 1000);

	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		geometry_msgs::Quaternion quat;
		quat.x = 1.0;
		quat.y = 1.2;
		quat.z = 1.1;
		quat.w = 1.3;

		quat_pub.publish(quat);
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
