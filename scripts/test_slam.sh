#!/bin/sh

# TURTLEBOT GAZEBO WORLD: launches gazebo with a world file.
# package turtlebot_gazebo, launch file: turtlebot_world.launch
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/map/c_shape.world" &
sleep 10

# gmapping demo performs SLAM (Simultaneous localization and mapping).
# this launch file is inside of the `turtlebot_gazebo` project,
# not in the ros-perception/slam_gmapping as listed in the course.  (The course is wrong)
# package turtlebot_gazebo, launch file: gmapping_demo.launch
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 10

# TURTLEBOT_RVIZ_LAUNCHERS launches rviz and automatically loads the robot model, trajectories, and map.
# package:  turtlebot_rviz_launchers , launch file: view_navigation.launch
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

# KEYBOARD TELEOP: allows us to control the robot via the keyboard.
# package: turtlebot_teleop , launch file: keyboard_teleop.launch
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch"