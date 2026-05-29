#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/uint8_t.hpp"

class MyNode{
    public:
        MyNode(): Node("publisher"){
            subscriber_ = create_subscription<std_msgs::msg::uint8_t>(

            )
        }

    private:
};

int main(argc, char **argv){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
}