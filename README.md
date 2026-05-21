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
    - encountered a issue where camera node and topic did not exist (therefore /camera doesn't show in rviz2 aswell)however the rest of the simulation worked . did 
    ```sudo apt install ros-humble-gazebo-ros-pkgs ros-humble-gazebo-plugins ``` 
    to eliminate the possibility of missing packages (suggested by gpt). eventually I put out a issue on https://community.husarion.com/t/rosbot-xl-simulation-camera-issue/2199 , apparently the naming convention on the document was outdated. its under /oak not camera, however as adviced by husarion team, i had to use the argument configuration:=autonomy which the alias ROBOT_SIM did not include by default. fixed that by editing ~/.bashrc alias line to 

```
alias ROSBOT_SIM='ros2 launch rosbot_gazebo simulation.launch.py robot_model:=rosbot_xl configuration:=autonomy' 
```

in nano and resourcing ~/.bashrc

then the doc told to set the reliability policy to best effort (send message without receiving guarantee) instead of reliable (send message until receiving) for better latency i suppose

 
---

 **how to send information between nodes using messages**

 In ROS 2, nodes are organized into packages, so in order to create a node, you need to create a package using ros2 pkg create command inside of src follder of workspace (I'm using workspaces;ros2_ws/src) .
 ```ros2 pkg create package_name --build-type ament_cmake --dependencies <dependencies>``` (syntax; ament_cmake: default build type in ros2, all arguments like buildtype and dependencies are optional)

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

now CMakeLists is used for build instructions,

include dir is for header files(declarations of functions, classes, or other code elements that are used in your source code but are defined in other source files)

package.xml (optional, mainly to deal with legal shit) is used for metadata

src toh pata hi hai , its for the main source code to be later built


TO recap : now we have a workspace called ros2_ws(literally just a folder named ros2_ws that we manually created), which has the source code of the packages(collection of nodes: "simplest program possible responsbile for controlling one particular thing usually") inside a folder called src . Now we created the package called tutorial_pkg inside of src. the package is a folder (called tutorial_pkg ) which has another folder called src for the actual source code of the node(s).

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

Now when i started writing a Node , I forgot the concept of inheritance in OOPS c++ in the second line itself

```
 Class Mynode: public rclcpp::Node
```

after I revised --

```

 C++ has 3 inheritance types : public, private and protected. 

let's say there's a class called Vegetables

class Vegetables{
public:
void aloo(
code code code 
)
private:
void gobi(
code code code 
)

protected: 
void tamatar(
code code code 
)

gobi( )  //usage allowed only inside of the same class

}

class GreenVeg : public Vegetables{
public:
void useTamatar(){
tamatar(); // child classes can access the function 
}
};

int main(){

Vegetables v;
v.aloo() //allowed anywhere
}


------------------


now when we write class MyNode : <form of inheritance> rclcpp::Node , e.g class MyNode : public rclcpp::Node

a sort of operation of conversion of  inheritance is just always applied on the public section of the parent class

in class MyNode : public rclcpp::Node
public of rclcpp::Node class stays public in MyNode class

for class MyNode : private rclcpp::Node
public of rclcpp::Node class goes to the private section in MyNode class

for class MyNode : protected rclcpp::Node
public of rclcpp::Node class goes to the protected section in MyNode class

```

now MyNode()  
is called a constructor, it has the exact same name as the this class its in i.e class MyNode. 
Constructor runs automatically any time an object of the class is created. Hence we define some basic stuff inside of it. 

```
MyNode() : Node("my_node") {
      RCLCPP_INFO(get_logger(), "Node started!");
   }
```


In a class constructor, a single colon : is used to start an initialization list. This allows you to initialize member variables before the body of the constructor executes, which is more efficient than assigning values inside the braces.Example: MyClass() : member1(value1), member2(value2) { ... }

----

then i noticed argc and argv are the arguments in the main function. upon some digging --
argc and argv are standard C/C++ mechanisms for command-line arguments.

argc = argument count → how many command-line arguments were passed
argv = argument vector → the actual arguments as text (strings)

Example:

./my_program hello 123

Then:

argc = 3

Why 3?

Because:

./my_program
hello
123

The program name itself counts as the first argument.

----

char ** argv is a c style character array 

in this example,
argv[0] = "./my_program"
argv[1] = "hello"
argv[2] = "123"

-----

encountered an error 

ros2-roadmap-ultralab/ros2-roadmap-ultralab/workspaces/ros2_ws/src/tutorial_pkg/src/my_first_node.cpp:16:41

error: template argument 1 is invalid
   16 |     auto node = std::make_shared<MyNode>();

corrected it. final code with breakdown of everything i understood -- [my_first_node.cpp](workspaces/ros2_ws/src/tutorial_pkg/src/my_first_node.cpp)

---

now colcon build --packages-select tutorial_pkg .
then source install/setup.bash

finally ros2 run tutorial_pkg my_first_node

ros2-roadmap-ultralab/ros2-roadmap-ultralab/workspaces/ros2_ws$ ros2 run tutorial_pkg my_first_node 
[INFO] [1779308731.962458249] [my_node]: Node started!

-----

now some interesting shit will happen

**We will use our camera to calculate the average brightness of the received image**

After shitting my panting at looking at the code for the first time, I decided to learn the c++ fundamentals that make up this piece of code --(using gpt)

1. Namespace = just grouping names

A namespace only organizes code and avoids name collisions.

```

namespace math
{
    int add(int a, int b)
    {
        return a + b;
    }
}

```

this can be called like math::add(2,3)


*difference between namespace and class*

```

class Dog
{
public:
    void bark()
    {
        std::cout << "Woof";
    }
};

```

This is not merely organization.

It defines:

behavior
data
objects

now

```

Dog d1;
Dog d2;

```

are two separate objects each with their own memory allocations done independlty

so practically namespace is kinda equivalent to using only one single class object (kinda, for most
 practical uses as far as i understand)


```

**using namespace std;**

```