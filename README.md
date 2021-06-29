# Localised Robot
A simple robot modelled using URDF and programmed using ROS that can localise itself (identify it's true world position) using the Adaptive Monte Carlo Localisation (AMCL) library and reach a set goal

The ROS project consists of 2 packages, **my_robot** and **localise_robot**. The *my_robot* package contains the robot and world models which can be visualised in the Gazebo simulator when the package is run using the *roslaunch* command. The *localise_robot* package is responsible for running the nodes map_server, amcl and move_base to perform the localisation of the robot

## Nodes
* map_server 
* amcl
* move_base

## Demo
![Localisation Demo](Localisation%20Demo.gif)

## ROS and Ubuntu version used
ROS Kinetic in Ubuntu 16.04
