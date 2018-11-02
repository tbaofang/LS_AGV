/*************************************************************************
    > File Name: src/pointcloud_pub.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月30日 星期二 09时28分54秒
 ************************************************************************/

#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>

using namespace std;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "pointcloud_pub");
	ros::NodeHandle n;

	ros::Publisher pointcloud_pub = n.advertise<pcl::PCLPointCloud2>("input", 1);

	ros::Rate loop_rate(10);
	while(ros::ok())
	{
		pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2());

		pcl::PCDReader reader;
		reader.read("table_scene_lms400.pcd", *cloud);

		pointcloud_pub.publish(cloud);

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;


}
