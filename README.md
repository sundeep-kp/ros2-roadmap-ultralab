# **walkthrough**


- after following through the initial setup, all i had to do was source ros (default /opt/ros/humble/setup.bash)and source install/setup.bash of my current workspace (which was the rosbot_ws). and then I ran ROSBOT_SIM command which opened up a gazebo + rviz simulation window.

**writing my first packages**
- i created a new workspace called practice_ws. then a created a launch file example.launch.py to launch a listerner and talker node at the same time
- now i asked gpt to explain me the code and now attempted to write the code launch the demo talker and listener in a launch file myself using 1. python , 2. xml (in practicality you can use either one) 3. yaml
    - **python**

        DeclareLaunchArgument as the name suggests is used to declare a argument i.e parameter for the launch file and set its default value

        the Node function calls a node with the parameters -- package , executable, a custom name that you get to decide and optionally a condition to call the node (e.g the launch argument like run_listener_arg) 

        LaunchConfigurationEquals basically allows you to check condition. e.g condition=LaunchConfigurationEquals("run_listener","true")\
        
        at the end we return LaunchDescription([run_listener_arg, talker_node, listener_node])
        which kind of makes sense that LaunchDescription is probably a function receives the output from talker_node and listerner_node, and accepts the launch argument run_listener_arg as paramater. But i haven't quite digested it yet

    - **xml**

        its simple. its made of argument tag and node tags(option if condition, pkg, exec, name) enclosed inside of <launch> and </launch>
        imp stuff -
        no commas, separation using space only

    - **yaml** 

        it takes more lines of code than xml but def looks pretty. similar abbreviations as xml thingy

    **examining**
        learnt about ros2 node/topic list/info, rqt_graph (use the refresh button if nodes don't appear )


**ROSBOT_SIM**
    - encountered a issue where camera node and topic did not exist (therefore /camera doesn't show in rviz2 aswell)however the rest of the simulation worked . did ```sudo apt install ros-humble-gazebo-ros-pkgs ros-humble-gazebo-plugins ``` to eliminate the possibility of missing packages (suggested by gpt). eventually I put out a issue on https://community.husarion.com/t/rosbot-xl-simulation-camera-issue/2199 , apparently the naming convention on the document was outdated. its under /oak not camera, however as adviced by husarion team, i had to use the argument configuration:=autonomy which the alias ROBOT_SIM did not include by default. fixed that by editing ~/.bashrc alias line to 
```alias ROSBOT_SIM='ros2 launch rosbot_gazebo simulation.launch.py robot_model:=rosbot_xl configuration:=autonomy' ```
in nano and resourcing ~/.bashrc

    then the doc told to set the reliability policy to best effort (send message without receiving guarantee) instead of reliable (send message until receiving) for better latency i suppose

 
---

 **how to send information between nodes using messages**