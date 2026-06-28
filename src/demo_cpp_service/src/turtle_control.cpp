#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "chrono"
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include "srv_pkg/srv/patrol.hpp"
#include <algorithm>



using namespace std::chrono_literals;
using Patrol =  srv_pkg::srv::Patrol;
using SetParametersResult =  rcl_interfaces::msg::SetParametersResult;


class turtle_cmd_node: public rclcpp::Node
{
private:
    /* data */
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;//发布者智能指针
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;//订阅者智能指针
    rclcpp::Service<Patrol>::SharedPtr servicer_;
    OnSetParametersCallbackHandle::SharedPtr parameter_callback_handle_;

    double target_x_{1.0};
    double target_y_{1.0};
    double k{1.0};
    double max_speed{2.0};

public:
    explicit turtle_cmd_node(const std::string &node_name):Node(node_name)
    {
        this->declare_parameter("k", 1.0);
        this->get_parameter("k", k);
        parameter_callback_handle_ = this->add_on_set_parameters_callback([&](const std::vector<rclcpp::Parameter> &paramters)->rcl_interfaces::msg::SetParametersResult
            {
                rcl_interfaces::msg::SetParametersResult result;
                result.successful = true;
                for(const auto & paramter :paramters)
                {
                    RCLCPP_INFO(this->get_logger(),"更新的参数为 %s",paramter.get_name().c_str());
                   if(paramter.get_name ()=="k")
                   {
                     k = paramter.as_double();
                   }
                   
                }

                return result;
            }
        );
        

        servicer_   = this->create_service<Patrol>
        ("patrol",[&](const Patrol::Request::SharedPtr request,Patrol::Response::SharedPtr response)->void
            {
                if((request->target_x>0&&request->target_x<12.0f)&&(request->target_y>0&&request->target_y<12.0f))
                {
                    this->target_x_ = request->target_x;
                    this->target_y_ = request->target_y; 
                    response->result = Patrol::Response::SUCCESS;
                }
                else
                {
                    response->result = Patrol::Response::FAIL;
                }
            }
        );
        publisher_  = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose",
            10,
            std::bind(&turtle_cmd_node::subscriber_callback,
            this,
            std::placeholders::_1
        ));
        //timer_ = this->create_wall_timer(1000ms,std::bind(&turtle_cmd_node::timer_callback,this));

    }

    void subscriber_callback(const turtlesim::msg::Pose::SharedPtr pose)//参数是收到的数据共享指针
    {
        
        geometry_msgs::msg::Twist msg;
        auto current_x = pose->x;
        auto current_y = pose->y;
        RCLCPP_INFO(get_logger(),"当前x:%f,y:%f",current_x,current_y);
        auto distance = std::sqrt(
            (target_x_ - current_x)*(target_x_ - current_x)+
            (target_y_ - current_y)*(target_y_ - current_y)
        );
        auto angle = std::atan2((target_y_ - current_y),(target_x_ - current_x)) - pose->theta;
        if( distance >0.1)
        {
            if(fabs(angle)>0.2)
            {
                msg.angular.z = fabs(angle);
            }
            else
            {
                msg.linear.x = k*distance;
            }
        }
        
        if( msg.linear.x > max_speed)
        {
            msg.linear.x = max_speed;
        }

        publisher_->publish(msg);
    }

};


int main(int argc,char*argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<turtle_cmd_node>("cmd_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;


}



