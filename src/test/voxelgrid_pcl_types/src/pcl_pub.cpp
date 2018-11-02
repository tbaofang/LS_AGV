/*************************************************************************
    > File Name: pcl_pub.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月30日 星期二 10时59分53秒
 ************************************************************************/

#include <iostream>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
//#include <pcl_conversions/pcl_conversions.h>

#include <pcl/point_cloud.h>

using namespace std;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "pcl_pub");
	ros::NodeHandle n;
	ros::Publisher pcl_pub = n.advertise<sensor_msgs::PointCloud2>("input", 1);

	sensor_msgs::PointCloud2 output;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

	for(float x = -0.5f; x <= 0.5f; x += 0.01f)
	{
		for(float y = -0.5f; y <= 0.5f; y += 0.01f)
		{
			pcl::PointXYZ point;
			point.x = x; point.y = y; point.z = 0;
			cloud->points.push_back(point);
		}
	}
	cloud->width = (int)cloud->points.size();
	cloud->height = 1;
	
	// cloud->width = 100;
	// cloud->height = 1;
	// cloud->points.resize(cloud->width * cloud->height);

	//convert the cloud to ROS message
	pcl::toROSMsg(*cloud, output);

	output.header.stamp = ros::Time::now();
	output.header.frame_id = "odom";

	ros::Rate loop_rate(10);
	while(ros::ok())
	{
		pcl_pub.publish(output);
		ros::spinOnce();
		loop_rate.sleep();
	}

	
	return 0;
}
