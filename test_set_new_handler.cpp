/*************************************************************************
	> File Name: test_set_new_handler.cpp
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月15日 星期三 19时14分33秒
 ************************************************************************/

#include<iostream>
#include<new>

void handler()
{
    std::cout << "Memory allocation failed,terminating\n";
    std::set_new_handler(nullptr);
}

int main()
{
    std::set_new_handler(handler);
    try{
        while(true){
            new int[1000000ul];
        }
    }catch (const std::bad_alloc& e){
        std::cout<< e.what() <<std::endl;
    }
    return 0;
}

