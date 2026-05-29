#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp" //used to process images received as image message type 

using namespace std::placeholders; // for placeholders like _1

class MyNode : public rclcpp::Node //put the stuff in public of rclcpp::Node class into the public of MyNode class,
                                    //  so we can directly use functions like Node()
{
    public:
        MyNode() : Node("avg_brightness") { //parent constructor, does registeration of this node with the ROS2 graph under the name "my_node" and other behind the scenes stuff
                    // any function put just after "constructor :" runs before the code inside constructor, we put things like initilisation of variables e.g x(10) or base constructors e.g Node() here
            subscriber_ = create_subscription<sensor_msgs::msg::Image>( //we are using the image template of the create_subscription image which creates a subscription object and returns a shared pointer to the variable subscriber_, we have declared it below in private
                "/image", //topic to subscribe to
                rclcpp::SensorDataQoS(), //QoS policy, here we are simply using a preset
                std::bind(&MyNode::image_callback, //bind is used for function callback, were provide the address of the function as argument , cause providing function() would cause it to run then and there  , also can't provide the name cause a variable might have the same name
                this, //the boject to make subscription object, "this" indicates the current object
                _1 //placeholder for an argument for the future 
                         )
                    
                 );
            
            RCLCPP_INFO(get_logger(),"Node Started!"); //like cout but more advanced, more convenient from ros2 perspective
            

        }

    private:
        void image_callback(const sensor_msgs::msg::Image::SharedPtr image)
        {
            long long sum =0;
            for(uint8_t value : image->data){
                sum += value;
            }

            int avg = sum/image->data.size();
            RCLCPP_INFO(get_logger(),"Brightness: %d", avg);
        }

        
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_; //We declare a private subscriber, which will be initialized inside the constructor. ~husarion docs
};


int main(int argc, char ** argv){ //argc = no. of arguments, argv = actual argument

    rclcpp::init(argc,argv); //start the underlying ros communication layer

    auto node = std::make_shared<MyNode>(); //make an object using MyNode class and return its shared_pointer to "node" variable
    rclcpp::spin(node); // keep the node running and process callbacks 
    //we can compress the above two lines into rclcpp::spin(std::make_shared<MyNode>());
    
    rclcpp::shutdown(); // stop ros communication layer

}

