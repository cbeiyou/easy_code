/*************************************************************************
	> File Name: testallocator.cpp
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月15日 星期三 20时42分51秒
 ************************************************************************/

#include<iostream>
#include"testAlloc.h"
#include<vector>
using namespace std;

int main()
{
    int a[5] = {0,1,2,3,4};
    YOU::test_allocator<int> test1;
    YOU::test_allocator<int> test2;

    vector<int ,YOU::test_allocator<int>>iv(a,a+5);
    for(auto it = iv.begin();it!=iv.end();it++)
        cout<<*it<<" ";
    cout<<endl;
    return 0;
}

