/*************************************************************************
	> File Name: List.h
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月17日 星期五 15时49分22秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#include<iostream>
#include<cassert>
#include<cstdlib>
using std::cout;
using std::endl;

template<class T>
class List
{
public:
    enum{begin = 0,end = -1};
    typedef struct ListNode
    {
        ListNode * pNext;
        T data;
    }uList,*pList;

    explicit List(const T s[],const int n );//将数组转换为一个链表，否认隐式转换
    explicit List();//否认隐式转换，构造函数
    List<T>& operator=(const List<T>& rhs);//重载赋值运算符
    bool operator==(const List<T>& rhs);//重载==
    //friend bool operator==(const List<T>& lhs,const List<T>& rhs);//比较两个list
    ~List();//list的析构
protected:
    uList* CreatedList(const T s[],const int& count) const //将数组s[]初始化一个链表，返回该链表的头指针
    {
        cout<<"creat list use s[]\n";
        if(count < 0)
        {
            cout << "count < 0 error!";
            exit(0);
        }
        pList p1 = new uList;
        p1->data = s[0];
        pList temp=p1;
        for (int i= 1;i<count-1;i++)
        {
            pList p2 = new uList;
            p2->data  = s[i];
            temp->pNext = p2;
            temp = p2;
        }
        pList p3 = new uList;
        p3->data = s[count-1];
        temp->pNext = p3;
        p3->pNext = nullptr;
        return p1;
    }

    uList* GetAddress (const int& index = 1)//获取index处元素的地址
    {
        //if(index == 1 ) return pHeader->pNext;
        if(index < -1  && index >e_length)
        {
            cout<< "index error !";
            exit(0);
        }
        pList p = pHeader;
        for (int i=0;i<index;++i) p = p->pNext;
        return p;
    }
    
    inline void Swap(uList* lhs,uList* rhs) const;//交换俩个node
    int Partition(int low,int high);//快排
    void Qsort(int low,int high);
    void QuickSort();
private:
    pList pHeader;//list的头指针
    int e_length;//list的长度


public:
    void show() const;//打印list
    int GetLength() const;//list长度
    T GetAt(const int& index) const;//取第index元素
    T operator[](int index) const;//使用[]操作符获取index元素
    void Insert (const T& lhs,const int& index = end);//在第index个元素前插入lhs，缺省为end
    void Insert (const T s[],const int count,const int& index = end);//在list中第index前插入数组s[]中的前count个元素
    void Delete (const int& index);//删除第index个元素
    void Delete (const int& index,const int& n);//删除从index开始的n个元素
    void DeleteBetween(const int& index1,const int& index2);//删除index1和index2之间的元素
    void DeleteAll();
    void GetAllData(T s[]) const;//获取list的元素，存入数组
    T GetMaxData() const ;
    T GetMinData() const;
    void SortList();//排序
    void ReverseList();//翻转list
    bool IsEmpty() const ;
    void Replace(const T& rhs,const int& index);//将list中第index位替换为rhs
    void Replace(const T s[],const int& count,const int& index);
    int Find(const T& temp,const int pos = begin);
    int FindLastof(const T& temp,const int pos = end);
    inline int GetMax(const int& a,const int& b)const 
    {
        return a>b?a:b;
    }
    inline int GetMin(const int& a,const int& b)const 
    {
        return a<b?a:b;
    }
    void Release();
    void Release(const int& index);
    void Release(const int& index1,const int& index2);
};

template<class T>
List<T>::List():pHeader(nullptr),e_length(0)
{
    cout<<"constructor list \n";
    pHeader = new uList;
    pHeader -> pNext = nullptr;
    pHeader -> data = (T)0;
}
template<class T>
List<T>::List(const T s[],const int n):pHeader(nullptr),e_length(n)
{
    cout<<"construct list use s[]\n";
    pHeader = new uList;
    pHeader -> data = (T)0;
    pHeader -> pNext = CreatedList(s,n);
}
template<class T>
void List<T>::Release()
{
    cout<<"release all \n";
    pList p = pHeader;
    while (p)
    {
        pList temp = p->pNext;
        delete p;
        p = temp;
    }
    pHeader = nullptr;
    e_length = 0;
}
template<class T>
List<T>::~List()
{
    cout<<"~list()\n";
    Release();
}
template<class T>
void List<T>::show()const
{
    cout<<"e_length : "<<e_length<<endl;
    if(e_length==0) cout<<"null\n";
    pList p = pHeader->pNext;
    while (p!=nullptr)
    {
        cout<<p->data;
        p = p->pNext;
        if (p!=nullptr) cout<<"--->";
    }
    cout<<endl;
    //cout<<p->data<<endl<<endl;
}
template<class T>
int List<T>::GetLength()const
{
    return e_length;
}
template<class T>
T List<T>::GetAt(const int& index) const 
{
    if(index < 0 && index >=e_length)
    {
        cout<<"index error!";
        exit(0);
    }
    pList p =pHeader;
    for (int i=1;i<=index;++i)
    {
        p=p->pNext;
    }
    return p->data;
}
template <class T>
T List<T>::operator [](int index) const
{
    return GetAt(index);
}
template<class T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
    //先释放该list，然后创建一个新的list将rhs拷贝过去
    if (*this == rhs) return *this;
    Release();
    pHeader = new uList;
    pHeader->data = rhs[0];
    e_length = rhs.e_length;
    pList lp = pHeader;
    for(int i=1;i<=e_length-1;++i)
    {
        pList temp = new uList;
        temp -> data = rhs[i];
        cout<<i<<":"<<rhs[i]<<endl;
        lp->pNext = temp;
        lp = temp;
    }
    pList tail = new uList;
    tail->data = rhs[e_length];
    tail->pNext = nullptr;
    lp->pNext = tail;
    return *this;
}
template<class T>
bool List<T>::operator ==(const List<T>& rhs)
{
    if(e_length != rhs.e_length) return false;
    else 
    {
        for(int i=0;i<e_length;++i)
        {
            pList p1 = pHeader;
            pList p2 = rhs.pHeader;
            if(p1->data != p2->data) return false;
        }
    }
    return true;
}
template <class T>
void List<T>::Insert(const T& lhs,const int& index)
{
    if(index < 0 && index >e_length+2)
    {
        cout<<"index error!";
        exit(0);
    }
    pList p = new uList;
    p->data = lhs;
    if(index==e_length+1 || index==-1) 
    {
        pList ptemp = GetAddress(e_length);
        ptemp->pNext = p;
        p->pNext = nullptr;
    }
    else 
    {
        pList ptemp;
        if(index == 0) ptemp = GetAddress();
        else ptemp = GetAddress(index -1);
        p->pNext = ptemp ->pNext;
        ptemp ->pNext = p;
    }
    e_length ++;
}

template<class T>
void List<T>::Insert(const T s[],const int count,const int& index)
{
    assert(count>1);
    assert(index>=-1 && index<e_length);
    pList p = CreatedList(s,count);
    pList ptemp;
    if(index ==-1) 
    {
        ptemp = GetAddress(e_length);
        ptemp ->pNext = p;
    }
    else 
    {
        if(index == 0) ptemp = GetAddress();
        else ptemp = GetAddress(index-1);
        pList tail = p->pNext;
        while (tail->pNext) tail = tail->pNext;
        tail->pNext = ptemp->pNext;
        ptemp->pNext = p;
    }
    e_length +=count;
}

template<class T>
void List<T>::Delete(const int& index)
{
    assert(index>0 && index<=e_length);
    cout<<"delete: "<<index<<endl;
    if(index==1) 
    {
        pList ptemp = pHeader -> pNext;
        pHeader->pNext = ptemp->pNext;
        delete ptemp;
    }
    else if(index == e_length)
    {
        pList ptemp = GetAddress(e_length -1);
        pList pl = ptemp->pNext;
        ptemp->pNext = nullptr;
        delete pl;
    }
    else 
    {
        pList ptemp = GetAddress(index -1);
        pList pl = ptemp ->pNext;
        ptemp ->pNext = pl ->pNext;
        delete pl;
    }
    e_length --;
}
template<class T>
void List<T>::Delete(const int&index,const int& n)
{
    assert(index >0 && index <=e_length);
    assert(n>0);
    if(e_length - index <n) Release(index);
    else Release(index,n+index-1);
}
template <class T>
void List<T>::DeleteBetween(const int& index1,const int& index2)
{
    assert(index1>=0&&index1<=e_length);
    assert(index2>=0&&index2<=e_length);
    Release(index1,index2);
}
template<class T>
void List<T>::DeleteAll()
{
    Release();
    pHeader = new uList;
    pHeader->pNext = nullptr;
    pHeader->data = (T)0;
}

template<class T>
void List<T>::GetAllData(T s[]) const
{
    pList ptemp = pHeader->pNext;
    int i=0;
    while(ptemp)
    {
        s[i++]=ptemp->data ;
        ptemp = ptemp->pNext;
    }
}

template<class T>
void List<T>::Release(const int& index)
{
    pList ptemp = GetAddress(index-1);
    pList phs = ptemp ->pNext;
    ptemp->pNext= nullptr;
    while (phs)
    {
        pList pls = phs->pNext;
        delete phs;
        phs = pls;
    }
    e_length = index -1;
}

template<class T>
void List<T>::Release(const int& index1,const int& index2)
{
    int maxt,mint;
    if (index1 == index2 )
    {
        pList ptemp = GetAddress(index1-1);
        pList pnode = ptemp ->pNext;
        ptemp ->pNext = pnode->pNext;
        delete pnode;
    }
    else 
    {
        maxt=GetMax(index1,index2);
        mint=GetMin(index1,index2);
        if (maxt ==e_length)
        {
            Release(mint);
            return ;
        }
        pList p1 = GetAddress(mint-1);
        pList p2 = GetAddress(maxt+1);
        pList p3 = p1->pNext;
        p1->pNext = p2;
        while (p3!=p2)
        {
            pList ptemp = p3->pNext;
            delete p3;
            p3 = ptemp;
        }
    }
    e_length = e_length-maxt+mint-1;
}

template<class T>
T List<T>::GetMaxData()const
{
    pList ptemp = pHeader->pNext;
    T temp = ptemp->data;
    while (ptemp)
    {
        if(ptemp->data>temp) temp = ptemp->data;
        ptemp = ptemp->pNext;
    }
    return temp;
}

template<class T>
T List<T>::GetMinData()const 
{
    pList ptemp = pHeader->pNext;
    T temp = ptemp->data;
    while (ptemp)
    {
        if(ptemp->data<temp) temp = ptemp->data;
        ptemp = ptemp->pNext;
    }
    return temp;
}

template <class T>
void List<T>::SortList()
{
    if(e_length <2) return ;
    QuickSort();
}

template <class T>
inline void List<T>::Swap(uList* lhs,uList*rhs)const
{
    T temp=lhs->data;
    lhs->data = rhs->data;
    rhs->data = temp;
}
template<class T>
void List<T>::ReverseList()
{
    if(e_length<2) return ;
    int ls=1,rs=e_length;
    while (ls<rs)
    {
        Swap(GetAddress(ls),GetAddress(rs));
        ls++;
        rs--;
    }
}

template<class T>
int List<T>::Partition(int low,int high)
{
    T key = GetAddress(low)->data;
    cout<<"key :"<<key<<endl;
    while (low<high)
    {
        while (low<high && GetAddress(high)->data>= key) --high;
        GetAddress(low)->data = GetAddress(high)->data;
        while (low<high && GetAddress(low)->data<=key) ++low;
        GetAddress(high)->data = GetAddress(low)->data;
    }
    GetAddress(low)->data = key;
    return low;
}
template <class T>
void List<T>::Qsort(int low,int high)
{
    if(low<high)
    {
        int temp = Partition(low,high);
	cout<<"temp:"<<temp<<endl;
        Qsort(low,temp-1);
        Qsort(temp+1,high);
    }
}
template<class T>
void List<T>::QuickSort()
{
    Qsort(1,e_length);
}

template<class T>
bool List<T>::IsEmpty()const
{
    if(pHeader==nullptr) return true;
    else return false;
}
template<class T>
void List<T>::Replace(const T& rhs,const int& index)
{
    assert(index>=0 && index<e_length);
    pList ptemp = GetAddress(index);
    ptemp->data = rhs;
}
template<class T>
void List<T>::Replace(const T s[],const int& count,const int& index)
{
    assert(count>=0);
    assert(index>=0&& index<=e_length);
    if(count==0) return ;
    if(e_length-index+1>count)
    {
        for(int i=0;i<count;++i) GetAddress(index+i)->data = s[i];
    }
    else 
    {
        for(int i=0;i<e_length-index+1;++i) GetAddress(index+i)->data = s[i];
    }
}

template<class T>
int List<T>::Find(const T& temp,const int pos)
{
    assert(pos>=0&& pos<=e_length);
    int index = pos;
    pList ptemp = GetAddress(pos);
    while (1)
    {
        if(ptemp->data == temp) return index;
        if(ptemp->pNext == nullptr) return -1;
        ptemp = ptemp->pNext;
        ++index;
    }
}

template<class T>
int List<T>::FindLastof(const T& temp,const int pos)
{
    //assert(pos>=0 && pos<=e_length);
    int index = pos ;
    pList ptemp;
    if(pos == end)
    {
        ptemp = GetAddress(e_length-1);
        index = e_length -1;
    }
    else ptemp = GetAddress(pos);
    while (1)
    {
        if(ptemp->data == temp) return index;
        if(index==0) return -1;
        --index;
        ptemp = GetAddress(index);
    }
}

#endif
