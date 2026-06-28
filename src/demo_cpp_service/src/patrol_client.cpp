#include "rclcpp/rclcpp.hpp"
#include "srv_pkg/srv/patrol.hpp"
#include "rcl_interfaces/msg/parameter.hpp"
#include "rcl_interfaces/msg/parameter_value.hpp"
#include "rcl_interfaces/msg/parameter_type.hpp"
#include "rcl_interfaces/srv/set_parameters.hpp"
#include <chrono>
#include <ctime>


using namespace std::chrono_literals; // 可以使用直接表达时间
using Patrol =  srv_pkg::srv::Patrol;
using set_param = rcl_interfaces::srv::SetParameters;

class Patrol_client: public rclcpp::Node
{
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<Patrol>::SharedPtr Patrol_client_;

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
            //异步发送请求  获取反馈
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
    /** 
     * 创建客户端 发送请求 返回结果
     * 
     */
    set_param::Response::SharedPtr call_get_set_paramter(const rcl_interfaces::msg::Parameter &param)
    {
        auto param_client = this->create_client<set_param>("/cmd_node/set_parameters");
        while(!param_client->wait_for_service(1s))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(),"服务上线失败");
                return nullptr;
            }
            RCLCPP_INFO(this->get_logger(),"服务上线成功");
        }
        //创建请求对象
        auto request_ = std::make_shared<set_param::Request>();
        request_ ->parameters.push_back(param);
        //发送请求 获取反馈
        auto future = param_client->async_send_request(request_);
        rclcpp::spin_until_future_complete(this->get_node_base_interface(),future);
        auto response = future.get();
        return response;
    }
    //更新k函数
    void refresh_paramter(double k)
    {

        //创建参数对象
        auto param = rcl_interfaces::msg::Parameter();
        param.name = "k";
        //创建参数值
        auto param_value =rcl_interfaces::msg::ParameterValue();
        param_value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
        param_value.double_value = k;
        param.value = param_value;
        //请求更新参数
        auto response = this->call_get_set_paramter(param);
        if(response == NULL)
        {
            RCLCPP_INFO(this->get_logger(),"参数更新失败");
            return ; 
        }
        for(auto result:response->results)
        {
            if(result.successful == false)
            {
                RCLCPP_INFO(this->get_logger(),"参数更新失败,原因：%s",result.reason.c_str());
                return ; 
            }
            RCLCPP_INFO(this->get_logger(),"参数更新成功");
        }



    }




};


int main(int argc,char*argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<Patrol_client>("patrol_node");
    node->refresh_paramter(5.0);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;


}



