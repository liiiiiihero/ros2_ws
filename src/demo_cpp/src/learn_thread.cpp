#include "iostream"
#include "thread"
#include "chrono"
#include "functional"
#include "cpp.httplib/httplib.h"


class Download
{
private:
    /* data */
public:
    void download(const std::string &host,const std::string &path,const std::function<void(const std::string&,const std::string&)>&callbace_world_count)
    {
        std::cout<<"线程"<<std::this_thread::get_id()<<std::endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if

    };
    void start_download(const std::string &host,const std::string &path,const std::function<void(const std::string&,const std::string&)>&callbace_world_count)
    {

    };



};
int main()
{
    auto a = Download();
    auto world_count = [](const std::string&path,const std::string &result)->void{
        std::cout<<"下载完成"<<path<<":"<<result.length()<<"->"<<result.substr(0,5)<<std::endl
    };


    a.start_download("");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*10));
    return 0;

}