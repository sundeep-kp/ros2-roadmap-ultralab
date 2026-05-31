#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/u_int8.hpp"

using namespace std::placeholders;
class MyNode: public rclcpp::Node{
    public:
        MyNode(): Node("publisher")
        {
            subscriber_ = create_subscription<sensor_msgs::msg::Image>(
                "/image", //remember /image is a just a placeholder for now. later when running we define /image topic using --ros-args -r /image:=/topic-name
                rclcpp::SensorDataQoS(),
                std::bind(&MyNode::image_callback, this, _1) //_1 is a placeholder for the argument of image_callback function. which will later be the image variable which is nothing but a class with an array called data which is [R1,G1,B1,  R2,B2,G2  ,R3,G3,B3...] i.e RGB values of each pixel of the image
                ); //initialise subscriber node
            
            publisher_ = create_publisher<std_msgs::msg::UInt8>("/brightness", rclcpp::SensorDataQoS()); //initialise publisher node
            
            RCLCPP_INFO(get_logger(),"Node Started!");
        }

    private:
        void image_callback(const sensor_msgs::msg::Image::SharedPtr image){
            long long sum =0;
            for(uint8_t value : image->data){
                sum += value;
            }
            int avg = sum/image->data.size();

            std_msgs::msg::UInt8 brightness_msg;//define brightness_msg object using std_msgs::msg::UInt8 class
            brightness_msg.data = avg;

            publisher_->publish(brightness_msg); //call publish function

            RCLCPP_INFO(get_logger(),"debug: image received ");

        }  
        
       rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
       rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr publisher_;
    };

int main(int argc, char **argv){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
}