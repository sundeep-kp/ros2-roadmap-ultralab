# **walkthrough**

>If you're too following this walkthrough, you may fork this branch, I'll add a link to your repository in the readme. I would love if you would **star this repo.**

>I have put the initial intro stuff here in the readme and the rest in notes folder --

>btw I made the notes myself , I have mentioned explicitly if I used ai in any particular line, the rest is handwritten based on whatever I understood with **no AI**  <img src="image.png" width="18">

>also I am learning formatting for markdown files and github in general simulataneouly through a course here : - https://www.udemy.com/course/git-and-github-master-class/learn/lecture/52518833#overview

<br/>
<br/>
<br/>

>This repository contains all the notes on everything i learnt using **Husarion docs** , all the problems i faced, all the fundamental concepts i had to learn *separately* including but not limited to *c++(libraries like **chrono**) and object oriented programming fundamentals;* ***basic parts of*** *os fundamentals (especially threads, clocks and scheduling/**interrupts and callbacks**), image processing*

**How to use this repository**--

Follow the instructions in Husarion docs(use dark mode like a normal person-- top right corner) and further the resources in the projects sections and use the walkthroughs as reference when you get stuck. Do read the topic in the doc after you briefly complete it in husarion docs/ project resource , you might get some additional info about the topic. Try to write all code by hand, seeing the code briefly and writing everything that you remember. Also question EVERYTHING. 
# [ROS 2 Introduction](https://husarion.com/tutorials/ros2-tutorials/1-ros2-introduction/)

*ROS 2 is a middleware based on a strongly-typed, anonymous publish/subscribe mechanism that allows for message passing between different processes* ~ros2 humble docs


- after following through the initial setup, all i had to do was source ros (default /opt/ros/humble/setup.bash)and source install/setup.bash of my current workspace (which was the rosbot_ws). and then I ran ROSBOT_SIM command which opened up a gazebo + rviz simulation window.

## **writing my first packages**

>https://husarion.com/tutorials/ros2-tutorials/1-ros2-introduction/ 

>[practice_ws](/ros2-roadmap-ultralab/workspaces/practice_ws/) -- visit this for the actual code and details. the following is my brief understanding of the code and the problems i encountered 

### Launch files

*to launch multiple nodes i.e programs at once*
- i created a new workspace called practice_ws. then a created a launch file example.launch.py to launch a listerner and talker node at the same time
- now i asked gpt to explain me the code and now attempted to write the code launch the demo talker and listener in a launch file myself using 1. python , 2. xml,  3. yaml (in practicality you can use either one)
    - **python**

        **DeclareLaunchArgument** as the name suggests is used to declare a argument i.e parameter for the launch file and set its default value

        the **Node function** calls a node with the parameters -- package , executable, a custom name that you get to decide and optionally a *condition* to call the node (e.g the launch argument like run_listener_arg) 

        **LaunchConfigurationEquals** basically allows you to check condition. e.g
        ```
        condition=LaunchConfigurationEquals("run_listener","true")
        ```
        at the end we return
        ```
         LaunchDescription([run_listener_arg, talker_node, listener_node])
        ```
        which kind of makes sense that 
        
        LaunchDescription is probably a function receives the output from talker_node and listerner_node, and accepts the launch argument run_listener_arg as paramater. 
        
        But i haven't quite digested it yet

    - **xml**

        its simple. its made of argument tag and node tags(option if condition, pkg, exec, name) enclosed inside of <launch> and </launch>
        imp stuff -
        no commas, separation using space only

    - **yaml** 

        it takes more lines of code than xml but def looks pretty. similar abbreviations as xml thingy

    **examining**

        Here I learnt about ros2 node/topic list/info, rqt_graph (use the refresh button if nodes don't appear )
    

**ROSBOT_SIM**

 - encountered a issue where camera node and topic did not exist (therefore /camera doesn't show in rviz2 aswell)however the rest of the simulation worked .
    
    I did 

```
    sudo apt install ros-humble-gazebo-ros-pkgs ros-humble-gazebo-plugins
```

to eliminate the possibility of missing packages (suggested by gpt). eventually I put out a issue on https://community.husarion.com/t/rosbot-xl-simulation-camera-issue/2199 , 

apparently the naming convention on the document was outdated.

 its under /oak not camera, however as adviced by husarion team, i had to use the argument **configuration:=autonomy** which the alias ROBOT_SIM did not include by default. 
 
 fixed that by editing ~/.bashrc alias line to 

```
alias ROSBOT_SIM='ros2 launch rosbot_gazebo simulation.launch.py robot_model:=rosbot_xl configuration:=autonomy' 
```

in nano and re-sourcing ~/.bashrc

then the doc told to set the reliability policy to **best effort** (send message without receiving guarantee) instead of reliable (send message until receiving) for better latency i suppose

 
---

 ### **creating packages**

 In ROS 2, nodes are organized into packages, so in order to create a node, you need to create a package using ros2 pkg create command inside of src follder of workspace (I'm using workspaces;ros2_ws/src) .

 ```
 ros2 pkg create package_name --build-type ament_cmake --dependencies <dependencies>
 ``` 
 
 (syntax; ament_cmake: default build type in ros2, all arguments like buildtype and dependencies are optional)

 now i'll create an example package: 

 ```
ros2 pkg create tutorial_pkg --build-type ament_cmake --dependencies rclcpp
 ```

this created 

```
ros2_ws/
   └── src/
      └── tutorial_pkg/
        ├── CMakeLists.txt
        ├── include/
        │   └── tutorial_pkg
        ├── package.xml
        └── src/

```

- now CMakeLists is used for build instructions,

    include dir is for header files(declarations of functions, classes, or other code elements that are used in your source code but are defined in other source files)

- package.xml (optional, mainly to deal with legal shit) is used for metadata

src toh pata hi hai (*translation: I know what src is for*) , its for the main source code to be later built


>TO recap : now we have a workspace called ros2_ws(literally just a folder named ros2_ws that we manually created),

> which has the source code of the packages(collection of executables: "files that be run individually") inside a folder called src .
 
 >Now we created the package called tutorial_pkg inside of src. the package is a folder (called tutorial_pkg ) which has another folder called src for the actual source code of the node(s).

I guess the reason we do this is to make separate collection of nodes(packages) to be used separately as needed. all these related packages are stored inside a workspace. like workspace car/ can contain packages --

*car_control_pkg* 
(which contains nodes like teleop_node
wheel_controller_node
brake_node
steering_node),  

*sensors_pkg*
(
lidar_node
gps_node
imu_node
),

*car_navigation_pkg*
(
path_planner_node
obstacle_avoidance_node
localization_node
)

*simulation_pkg*
(
gazebo_interface_node
world_manager_node
vehicle_model_node
)

---
Further-- 

[Unit 2:](https://husarion.com/tutorials/ros2-tutorials/2-creating-nodes-messages/){

[1.Making a node](notes/1.Making%20a%20node.md)

[2.Creating a subscriber](notes/2.Creating%20a%20subscriber.md)

[3.Creating a publisher](notes/3.Creating%20a%20publisher.md)
}

[Unit 3](https://husarion.com/tutorials/ros2-tutorials/3-creating-nodes-services/)

{

[1. Topics-Services-Actions](notes/4.%20Topics-Services-Actions.md)

[2. Calling a Service](notes/5.Calling%20a%20service.md)

[3. Creating a timer](notes/6.Creating%20a%20timer.md)

[4. Timer + save](notes/7.%20Timer%20+%20save.md)
    
}




