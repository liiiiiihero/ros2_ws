//#include"iostream"
#include"rclcpp/rclcpp.hpp"
int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<rclcpp::Node>("cpp_node");
    RCLCPP_INFO(node->get_logger(),"hello cpp node!");
    rclcpp::spin(node);
    rclcpp::shutdown();

    //std::cout<<"number  ="<<argc<<std::endl;
    //std::cout<<"name  ="<<argv[0]<<std::endl;
    //std::string arg1 = argv[1]; 
    //if(arg1 =="--help")
    //{
    //    std::cout<<"right"<<std::endl;
    //}

    return 0;
}