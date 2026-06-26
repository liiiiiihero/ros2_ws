#include "iostream"
#include "memory"

int main()
{
    auto p3 =0;
    auto p1 = std::make_shared<std::string>("this is a str."); //<数据类型/类>（参数）
    std::cout<<"p1的引用计数:"<<p1.use_count()<<",指向内存地址："<<p1.get()<<std::endl;//1

    auto p2 = p1;
    std::cout<<"p1的引用计数:"<<p1.use_count()<<",指向内存地址："<<p1.get()<<std::endl;//2
    std::cout<<"p2的引用计数:"<<p2.use_count()<<",指向内存地址："<<p2.get()<<std::endl;//2

    p1.reset();//释放
    std::cout<<"p1的引用计数:"<<p1.use_count()<<",指向内存地址："<<p1.get()<<std::endl;//0
    std::cout<<"p2的引用计数:"<<p2.use_count()<<",指向内存地址："<<p2.get()<<std::endl;//2-1 = 1

    std::cout<<",指向内存地址的数据："<<p2->c_str() << std::endl;//调用成员方法

    return 0;
}