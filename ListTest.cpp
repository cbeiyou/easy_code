/*************************************************************************
	> File Name: ListTest.cpp
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月18日 星期六 16时47分33秒
 ************************************************************************/

#include<iostream>
#include"List.h"

using std::cout;
using std::endl;

int main()
{
    int a[10]={5,6,9,8,4,2,1,3,7,10};
    List<int> l1;
    List<int> l2(a,10);
    l1.show();
    l2.show();

    List<int> l3;
    l3=l2;
    l3.show();
/*
    if(l2==l3) cout<<"l2==l3\n";
    else cout<<"l2!=l3\n";

    int temp1 = l3.GetAt(4);
    int temp2 = l3.GetAt(10);
    cout<<temp1<<"   "<<temp2<<"   "<<l3[1]<<"   "<<l3[5]<<endl;
    l2.Insert(11,3);
    //l2.show();
    l2.Insert(12,10);
    //l2.show();
    l2.Insert(13);
    //l2.show();
    int b[5]={21,22,23,24,25};
    l2.Insert(b,4,4);
    //l2.show();
    l2.Insert(b,5);
    l2.show();

    l2.Delete(1);
    l2.show();
    l2.Delete(l2.GetLength());
    l2.show();
    l2.Delete(5);
    l2.show();

    l2.Delete(10,5);
    l2.show();

    l2.DeleteBetween(9,11);
    l2.show();
*/
    int *c = new int[10];
    l2.GetAllData(c);
    List<int> l4(c,10);
    l4.show();
    int maxdata = l4.GetMaxData();
    int mindata = l4.GetMinData();
    cout<<"l4.maxdata :"<<maxdata<<"   l4.mindata:"<<mindata<<endl;
    l4.SortList();
    l4.show();
    l4.ReverseList();
    l4.show();

    /*l4.Replace(100,5);
    l4.show();
    l4.Replace(a,5,2);
    l4.show();
    */

    int dir = l4.Find(5,1);
    cout<<"dir:"<<dir<<"  \n";
    cout<<"dir2:"<<l4.FindLastof(6,9)<<endl;
    return 0;
}

