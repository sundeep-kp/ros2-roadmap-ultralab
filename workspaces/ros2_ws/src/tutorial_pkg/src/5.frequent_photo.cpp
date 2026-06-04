#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/uint_8.hpp"
#include "std_srvs/srv/empty.hpp" //empty service message type

using namespace std::placeholders;
using namespace std::chrono_literals;

class MyNode : public rclcpp::Node{

    public:
        MyNode() : Node("my_node")
        {
            declare_parameter("timer_period_s",5);
            auto timer_period_s = std::chrono::seconds(get_parameter(timer_period_s).as_int());

            timer_ = create_wall_timer(timer_period_s,std::bind(&MyNode::timer_callback, this));
            client_ = create_client<std_srvs::srv::empty>("/save");

            RCLCPP_INFO(get_logger(),"Node started!");

        }

    private: 
        timer_callback(){
            RCLCPP_INFO(get_logger(),"Timer Activate!")
        }
};