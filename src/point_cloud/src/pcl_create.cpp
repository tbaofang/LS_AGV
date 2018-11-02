/*************************************************************************
    > File Name: pcl_create.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月26日 星期五 17时14分51秒
 ************************************************************************/

#include <iostream>

#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>

#include <pcl/point_cloud.h>

using namespace std;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "pcl_create");
	ros::NodeHandle nh;
	ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);

	sensor_msgs::PointCloud2 output;

	pcl::PointCloud<pcl::PointXYZ> cloud;
	for(float x = -0.5f; x <= 0.5f; x += 0.01f)
	{
		for(float y = -0.1f; y <= 0.1f; y += 0.01f)
		{
			pcl::PointXYZ point; point.x = x; point.y = y; point.z = 0;
			cloud.points.push_back(point);
		}
	}
	cloud.width = (int)cloud.points.size();
	cloud.height = 1;


	//Convert the cloud to ROS message
	pcl::toROSMsg (cloud, output);
	output.header.frame_id = "odom";

	ros::Rate loop_rate(1);
	while (ros::ok ())
	{
		pcl_pub.publish (output);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

	cout << "succeed!" << endl;
}
