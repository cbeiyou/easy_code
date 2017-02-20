/*************************************************************************
	> File Name: baseclass_to_derived.cpp
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月19日 星期日 23时08分37秒
 ************************************************************************/

#include<iostream>
//using namespace std;

class father1
{
private:
    int val;
public:
    father1(int i = 0 ):val(i) {}
    father1(const father1& fa)
    {
        val = fa.val;
        std::cout<<"调用father1 copy construct\n";
    }
    void getval()
    {
        std::cout<<"fatherval1:"<<val<<std::endl;
    }
};

class son1:public father1
{
private:
    int val;
public:
    son1(int i=0,int j=1):father1(i),val(j){}
    son1(const son1& so)
    {
        val = so.val;
        std::cout<<"调用son1 copy construct\n";
    }
    void getval()
    {
        std::cout<<"sonval1:"<<val<<std::endl;
    }
};

class father2
{
private:
    int val;
public:
    father2(int i=5):val(i){}
    virtual void getval()
    {
        std::cout<<"father2val:"<<val<<std::endl;
    }
};

class son2:public father2
{
private:
    int val;
public:
    son2(int i=2,int j=3):father2(i),val(j){}
    void getval()
    {
        std::cout<<"son2val:"<<val<<std::endl;
    }
};

void usefather1o(father1 o)
{
    o.getval();
}

void useson1o(son1 o)
{
    o.getval();
}
void usefather1p(father1* p)
{
    p->getval();
}
void useson1p(son1* p)
{
    p->getval();
}
void usefather2o(father2 o)
{
    o.getval();
}
void useson2o(son2 o)
{
    o.getval();
}
void usefather2p(father2* p)
{
    p->getval();
}
void useson2p(son2* p)
{
    p->getval();
}

int main()
{
    father1 fao;
    son1 soo;

    father1* fap=&fao;
    son1* sop=&soo;
    //按值传递,使用copy构造函数
    usefather1o(fao);//基类对象传递给基类对象
    usefather1o(soo);//派生类对象传递给基类对象，自动转换
    useson1o(soo);//派生类对象传递给派生类对象
    //useson1o(fao);基类对象无法自动转换为派生类对象 
    std::cout<<std::endl;

    //按指针传递参数
    usefather1p(fap);//基类指针指向基类指针
    usefather1p(sop);//派生类指针指向 基类指针 （允许这种派生类指针自动转换为base类指针）
    useson1p(sop);//派生类指针指向派生类
    //useson1p(fap);禁止将基类指针自动转换为派生类指针
    useson1p((son1*)fap);//将基类指针强制转换为派生类，但是该指针却调用了一个派生类的函数，该函数是派生类特有的，所以基类指针指向了一个不确定的位置，打印了一个随机值
    std::cout<<"\n";

    father1* fapp = new son1;//静态类型指向基类，动态类型指向派生类
    usefather1p(fapp);//基类指针 传递 基类指针 
    useson1p((son1*)fapp);//虽然是一个基类指针转换为派生类指针，但是在内存中，该基类指针指向的 是一个内存中一个确定的位置，所以调用类正确的函数。
    std::cout<<"\n";
//继承的方法使用virtual
    father2 fa2o;
    son2 so2o;

    usefather2o(fa2o);
    usefather2o(so2o);
    useson2o(so2o);
    //useson2o(fa2o);无法将基类对象自动转换为派生类对象
    std::cout<<"\n";

    father2* fa2p = &fa2o;
    son2* so2p = &so2o;
    usefather2p(fa2p);//调用虚函数表，对于fa2p 指针指向father2方法
    usefather2p(so2p);//对于so2p，虚函数表将so2p实际指向的位置是son2类的方法，所以虽然是将派生类指针传递给一个基类指针，但是虚函数表还是会自动识别该指针指向的实际的位置。
    useson2p(so2p);
    //useson2p(fa2p);
    useson2p((son2*)fa2p);//该行为同上，虽然传递的是一个派生类的指针，。但是实际上是一个基类的指针，所以调用的是基类的方法。

    std::cout<<"\n";
    //下面这种情况，由于是使用虚函数，所以指针指向了实际指针该指向的位置，那就是派生类方法，所以也就是调用的派生类方法。
    father2 * fa2pp = new son2;
    usefather2p(fa2pp);
    useson2p((son2*)fa2pp);///无法自动转化，必须强制转换
    return 0;
    
}
