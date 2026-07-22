#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp" //empty service message type
#include "std_srvs/srv/trigger.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

class MyNode : public rclcpp::Node{

    public:
        MyNode() : Node("my_node")
        {
            declare_parameter("timer_period_s",5);
            auto timer_period_s = std::chrono::seconds(get_parameter("timer_period_s").as_int());

            timer_ = create_wall_timer(timer_period_s,std::bind(&MyNode::timer_callback, this));
            client_ = create_client<std_srvs::srv::Empty>("/save");
            server_ = create_service<std_srvs::srv::Trigger>("/image_counter", std::bind(&MyNode::counter_callback,this, _1,_2)); 
            
            RCLCPP_INFO(get_logger(),"Node started!");

        }

    private: 
        void timer_callback(){
            RCLCPP_INFO(get_logger(),"Timer Activate!");

            if(!client_->wait_for_service(1s)){ //if wait for service returns false after 1s then execute the following commands
                RCLCPP_ERROR(get_logger(),"unable to reach service!");
                return;
            }

            auto request = std::make_shared<std_srvs::srv::Empty::Request>(); //create the request
            auto future = client_->async_send_request(request); // push teh request

            saved_imgs_++;
        }

        void counter_callback(const std_srvs::srv::Trigger::Request::SharedPtr req, const std_srvs::srv::Trigger::Response::SharedPtr res){
            res->success = 1;
            res->message = "Saved images: " + std::to_string(saved_imgs_); //to_string is used to convert numerical to string
        }

        //all of the declarations -- 
        uint saved_imgs_ = 0;
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr server_;

};
int main(int argc , char ** argv){

    rclcpp::init(argc,argv);

    auto node = std::make_shared<MyNode>(); //just as a recap , std::make_shared means that find make_shared function inside of std namespace, also yes namespaces can be nested
    rclcpp::spin(node);

    rclcpp::shutdown();
}