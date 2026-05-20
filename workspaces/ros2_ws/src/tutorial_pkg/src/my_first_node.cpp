#include "rclcpp/rclcpp.hpp" //.hpp is the extnsion for header files in cpp

class MyNode : public rclcpp::Node
{

    public:
        MyNode(): Node("my_node")// you don't have to add semicolon for some reason
         {
            RCLCPP_INFO(get_logger(),"Node started!");
        }


};

int main(int argc, char **argv){
    rclcpp::init(argc,argv); //to initialise the ROS2 communication layer
    auto node = std::make_shared<MyNode>(); //create an object called node from MyNode class
    rclcpp::spin(node); //start the node, This call will block the main thread and continuously loop until the node is shut down.
    rclcpp::shutdown(); 
}