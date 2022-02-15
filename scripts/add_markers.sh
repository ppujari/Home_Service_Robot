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
# xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
# It takes a long time to add the marker visualization in rviz,
# and the robot will already have gone to the pickup location,
# so I added a config to automatically use the marker visualization.
# same as view_navigation.launch, but automatically has marker visualization.
xterm -e "roslaunch pick_objects marker_viz_rviz.launch" &
sleep 5

# ADD_MARKERS c++ node.  This will add a marker at the pickup zone.
# Delete the marker when the robot reaches the pickup zone,
# and add the marker at the drop-off zone when the robot arrives at the drop-off zone.
xterm -e "rosrun add_markers add_markers"