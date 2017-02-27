/*************************************************************************
	> File Name: TestYouVector.cpp
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月26日 星期日 14时58分02秒
 ************************************************************************/

#include<iostream>
#include "vector.h"
using std::cout;
using std::endl;
int main()
{
    youVector<std::string> vec;
    vec.push_back("hello");
    std::string str1 = "wrold";
    std::string str2 = "you";
    vec.push_back(str1);
    vec.push_back(str2);
    
    int len = vec.size();
    for(int i=0;i<len;i++) cout<<vec[i]<<endl;
    cout<<"--------------\n";
    youVector<std::string>::iterator it;
    for(it=vec.begin();it!=vec.end();++it) cout<<*it<<endl;
    cout<<"--------------\n";
    //vec.pop_back();

    //for(it=vec.begin();it!=vec.end();++it) cout<<*it<<endl;

    youVector<int> vec2;
    vec2.push_back(5);
    vec2.push_back(4);
    vec2.push_back(1);
    vec2.push_back(8);
    vec2.erase(vec2.begin(),vec2.begin()+2);
    for(int i=0;i<vec2.size();i++) cout<<vec2[i]<<endl;
}

