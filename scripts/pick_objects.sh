#!/bin/sh

# TURTLEBOT GAZEBO WORLD: launches gazebo with a world file.
# package turtlebot_gazebo, launch file: turtlebot_world.launch
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/map/c_shape.world" &
sleep 10

# TURTLEBOT GAZEBO AMCL DEMO
# package turtlebot_gazebo, launch file: amcl_demo.launch
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/map/map.yaml" &
sleep 10

# TURTLEBOT_RVIZ_LAUNCHERS launches rviz and automatically loads the robot model, trajectories, and map.
# package:  turtlebot_rviz_launchers , launch file: view_navigation.launch
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

# PICK_OBJECTS c++ node.  This will direct the robot to the pickup location,
# wait 5 seconds, and direct the robot to the drop-off location.
xterm -e "rosrun pick_objects pick_objects"