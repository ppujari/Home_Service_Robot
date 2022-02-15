#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //Node handle to set ros parameters so other nodes know when the robot has reached a destination.
  ros::NodeHandle robotPosNodeHandle;
  robotPosNodeHandle.setParam("robot_is_at_pickup_loc", false);
  robotPosNodeHandle.setParam("robot_is_at_drop_off_loc", false);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal, drop_off_goal;

  // set up the frame id and stamp
  pickup_goal.target_pose.header.frame_id = "map";
  pickup_goal.target_pose.header.stamp = ros::Time::now();

  // Set pickup location at middle of the bottom hallway
  pickup_goal.target_pose.pose.position.x = 2.68486404419;
  pickup_goal.target_pose.pose.position.y = -2.00983738899;
  pickup_goal.target_pose.pose.position.z = 0.0;
  pickup_goal.target_pose.pose.orientation.w = 1.0;
  pickup_goal.target_pose.pose.orientation.z = 0.0; // point right

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(pickup_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot has reached the pickup goal");
    robotPosNodeHandle.setParam("robot_is_at_pickup_loc", true);
  } else {
    ROS_WARN_ONCE("The robot failed to reach the pickup goal");
  }

  ros::Duration(5).sleep(); // sleep for 5 seconds

  drop_off_goal.target_pose.header.frame_id = "map";
  drop_off_goal.target_pose.header.stamp = ros::Time::now();
  // Set drop-off location to be the top of the middle hallway (left of the top hallway)
  drop_off_goal.target_pose.pose.position.x = -0.133507564664;
  drop_off_goal.target_pose.pose.position.y = 4.03573846817;
  drop_off_goal.target_pose.pose.position.z = 0.0;
  drop_off_goal.target_pose.pose.orientation.w = 1.0;
  drop_off_goal.target_pose.pose.orientation.z = 1.57079; // point up

  ROS_INFO("Sending drop-off goal");
  ac.sendGoal(drop_off_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot has successfully reached the drop-off goal.");
    robotPosNodeHandle.setParam("robot_is_at_drop_off_loc", true);
  } else {
    ROS_WARN_ONCE("The robot has failed to reach the drop-off goal.");
  }

  return 0;
}