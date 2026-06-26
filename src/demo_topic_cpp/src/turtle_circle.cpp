#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "chrono"


using namespace std::chrono_literals;


class turtle_circle_node: public rclcpp::Node
{
private:
    /* data */
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;//发布者智能指针

public:
    explicit turtle_circle_node(const std::string &node_name):Node(node_name)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
        timer_ = this->create_wall_timer(1000ms,std::bind(&turtle_circle_node::timer_callback,this));
    }
    void timer_callback()
    {
        auto msg =geometry_msgs::msg::Twist();
        msg.linear.x = -2.0;
        msg.linear.y = 0.0;
        msg.angular.x= 0.0;
        msg.angular.z= 5.0;
        publisher_->publish(msg);
    }

};


int main(int argc,char*argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<turtle_circle_node>("circle_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;


}



