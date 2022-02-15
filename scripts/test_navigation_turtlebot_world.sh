#!/bin/sh

# TURTLEBOT GAZEBO WORLD: launches gazebo with a world file.
# package turtlebot_gazebo, launch file: turtlebot_world.launch
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10

# TURTLEBOT GAZEBO AMCL DEMO
# package turtlebot_gazebo, launch file: amcl_demo.launch
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 10

# TURTLEBOT_RVIZ_LAUNCHERS launches rviz and automatically loads the robot model, trajectories, and map.
# package:  turtlebot_rviz_launchers , launch file: view_navigation.launch
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
