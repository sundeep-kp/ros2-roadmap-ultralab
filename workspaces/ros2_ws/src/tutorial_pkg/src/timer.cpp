#include <chrono>
#include "rclcpp/rclcpp.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

class MyNode : public rclcpp::Node{
    public:
        MyNode() : Node("my_node"){

            declare_parameter("timer_period_s", 5); //a function from rclcpp::Node class
            auto timer_period_s = std::chrono::seconds(get_paramater("timer_period_s").as_int)
            timer_ = create_wall_timer(5s, std::bind(&MyNode::timer_callback, this)); // its an rclcpp function, we use chrono only for the '5s' here
            
            RCLCPP_INFO(get_logger(), "Node Started!");
        }

    private:
        void timer_callback() {
            RCLCPP_INFO(get_logger(),"Timer Activate, counting five seconds");
        }
        rclcpp::TimerBase::SharedPtr timer_; //timer_base is a timer object type
    };


int main(int argc, char ** argv){

    rclcpp::init(argc,argv);

    auto node = std::make_shared<MyNode>(); //incase you forgot like I did, <template> like <Mynode> is used for making different functions for different datatypes, here MyNode class is kind of a user defined datatype
    rclcpp::spin(node);

    rclcpp::shutdown();
}

