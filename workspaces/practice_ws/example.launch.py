from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.conditions import LaunchConfigurationEquals
from launch import LaunchDescription


def generate_launch_description():
    run_listener_arg   = DeclareLaunchArgument("run_listener", default_value="true")

    talker_node = Node(
        package = "demo_nodes_cpp",
        executable = "talker",
        name="talker_node"

    )

    listener_node= Node(

        package = "demo_nodes_cpp",
        executable="listener",
        name = "listener_node",
        condition=LaunchConfigurationEquals("run_listener","true")\
        
    )

    return LaunchDescription([run_listener_arg, talker_node, listener_node])



