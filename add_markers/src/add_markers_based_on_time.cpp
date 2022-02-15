#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  float pickUpPose[] = { -6, 1.5, 0.911, 0.412 };
  float dropOffPose[] = { 3, -3, 0.707, -0.707 };

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE
    marker.type = visualization_msgs::Marker::CUBE;

    // Set the marker action.  Options are ADD, DELETE
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickUpPose[0];
    marker.pose.position.y = pickUpPose[1];
    marker.pose.orientation.w = pickUpPose[2];
    marker.pose.orientation.z = pickUpPose[3];

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Wait for subscription
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      r.sleep();
    }
    //Publish Marker to the pick up zone
    marker_pub.publish(marker);
    ROS_INFO("Marker at pick up zone");
    
    // Wait for robot arrival at pick up zone
    sleep(5.0);
   
    //Hide the marker	
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Robot arrived. Marker deleted");
    
    // Wait for robot arrival at drop off zone
    sleep(5.0);
   
    //Publish the marker to the drop off zone
    marker.pose.position.x = dropOffPose[0]-0.5;
    marker.pose.position.y = dropOffPose[1];
    marker.pose.orientation.w = dropOffPose[2];
    marker.pose.orientation.z = dropOffPose[3];
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Marker is now at the drop off zone");

    ros::spin();    
}
