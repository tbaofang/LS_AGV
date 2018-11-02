/*************************************************************************
    > File Name: src/voxelgrid_pcl_types.cpp
    > Author: tangbf
    > Mail: 
    > Created Time: 2018年10月30日 星期二 09时09分16秒
 ************************************************************************/

#include <iostream>

#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>


#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/segmentation/sac_segmentation.h>

using namespace std;

ros::Publisher pub;

// void cloud_cb(const pcl::PCLPointCloud2ConstPtr& cloud)
// {
// 	pcl::PCLPointCloud2 cloud_filtered;

// 	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
// 	sor.setInputCloud(cloud);
// 	sor.setLeafSize(0.1, 0.1, 0.1);
// 	sor.filter(cloud_filtered);

// 	// Convert to ROS data type
//     sensor_msgs::PointCloud2 output;
//     pcl_conversions::fromPCL(cloud_filtered, output);


// 	output.header.frame_id = "odom";

// 	// cout << output.header.frame_id  << endl;

// 	pub.publish(output);
// }

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  // Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::fromROSMsg (*input, cloud);

  pcl::ModelCoefficients coefficients;
  pcl::PointIndices inliers;
  // Create the segmentation object
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // Optional
  seg.setOptimizeCoefficients (true);
  // Mandatory
  seg.setModelType (pcl::SACMODEL_PLANE);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.01);

  seg.setInputCloud (cloud.makeShared ());
  seg.segment (inliers, coefficients);

  cout << "coefficients: " << coefficients.values[0] << " " << coefficients.values[1] << " "  << coefficients.values[2] << " "  << coefficients.values[3] << " "  << endl;

  // Publish the model coefficients
  pcl_msgs::ModelCoefficients ros_coefficients;
  pcl_conversions::fromPCL(coefficients, ros_coefficients);
//   pub.publish (ros_coefficients);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "voxel_grid");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("input", 1, cloud_cb);

	pub = n.advertise<pcl::PCLPointCloud2>("output", 1);

	ros::spin();
}
