#include"rclcpp/rclcpp.hpp"

class PersonNode : public rclcpp::Node
{
private:
    std::string name_;
    int age_;
public:
    PersonNode(
        const std::string & node_name,
        const std::string & name,
        const int & age
    )
    :Node(node_name) //same as super()
    {
        this->name_ = name;
        this->age_  = age;

    }
    void love(const std::string &lover)
    {
        RCLCPP_INFO(this->get_logger(),"i am %s,%d years old, love %s ",
        this->name_.c_str(),
        this->age_,
        lover.c_str()
    );
    }

};

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<PersonNode>("person_node","xiaoli",18);
    RCLCPP_INFO(node->get_logger(),"hello cpp node!");
    node->love(" xiaodiii");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}

