#include "rclcpp/rclcpp.hpp"
#include "srv_pkg/srv/patrol.hpp"
#include <chrono>
#include <ctime>

using namespace std::chrono_literals; // 可以使用直接表达时间
using Patrol =  srv_pkg::srv::Patrol;

class Patrol_client: public rclcpp::Node
{
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<Patrol>::SharedPtr Patrol_client_;

//     /* data */
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;//发布者智能指针
//     rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;//订阅者智能指针
//     rclcpp::Service<Patrol>::SharedPtr servicer_;
//     double target_x_{1.0};
//     double target_y_{1.0};
//     double k{1.0};
//     double max_speed{2.0};

public:
    explicit Patrol_client(const std::string &node_name):Node(node_name)
    {    
        srand(time(NULL));
        Patrol_client_ = this ->create_client<Patrol>("patrol");
        timer_ = this->create_wall_timer(10s,[&]()->void
        {
            while (!this->Patrol_client_ ->wait_for_service(1s))
            {
                if(!rclcpp::ok())
                {
                    RCLCPP_ERROR(this->get_logger(),"服务上线失败...");
                    return;
                }
                RCLCPP_INFO(this->get_logger(),"服务上线中");
               
            }
            //构造请求的对象
            auto request_ = std::make_shared<Patrol::Request>();
            request_->target_x = rand()%12;
            request_->target_y = rand()%12;
            RCLCPP_INFO(this->get_logger(),"目标点已准备就绪，%f,%f",request_->target_x,request_->target_y);
            //发送请求
            this->Patrol_client_->async_send_request(request_,[&](rclcpp::Client<Patrol>::SharedFuture result_future)->void
            {
                auto response_ = result_future.get();
                if(response_->result == Patrol::Response::FAIL)
                {
                    RCLCPP_INFO(this->get_logger(),"请求目标点失败");
                }
                RCLCPP_INFO(this->get_logger(),"请求目标点成功");
            });
        });
    
        
    }
};


int main(int argc,char*argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<Patrol_client>("patrol_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;


}



