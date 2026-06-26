#include "iostream"
#include "functional"



//成员函数

class File_save
{
private:
    /* data */
public:
    File_save(/* args */)=default;
    ~File_save()=default;


    void save_with_member_fun( const std::string & file_name)
    {
      std::cout<<"成员函数:"<<file_name<<std::endl;
    };

};

//自由函数xiaoliiiii

void save_with_free_fun( const std::string & file_name)
{
    std::cout<<"自由函数:"<<file_name<<std::endl;
}

int main()
{
    File_save file_save;

    //lambda
    auto save_with_lambda_fun = [](const std::string &file_name)->void
    {
        std::cout<<"lambda函数:"<<file_name<<std::endl;


    };
    //调用
    //save_with_free_fun("xiaoliii");
    //file_save.save_with_member_fun("xiaoliii");
    //save_with_lambda_fun("xiaoliii");

    //包装器
    std::function<void(const std:: string&)>save1=save_with_free_fun;
    std::function<void(const std:: string&)>save2=save_with_lambda_fun;
    //成员函数放入包装器,不能直接扶植，最后为占位符，因一个成员函数故为1
    std::function<void(const std:: string&)>save3=std::bind(&File_save::save_with_member_fun,&file_save,std::placeholders::_1);
    //包装后统一调用
    save1("hahahah1");
    save2("hahahah2");
    save3("hahahah3");



    return 0;
}