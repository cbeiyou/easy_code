/*************************************************************************
	> File Name: vector.h
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月26日 星期日 00时41分52秒
 ************************************************************************/
//试着实现一个vector
//包括vector的内存增长机制。。。

#ifndef _VECTOR_H
#define _VECTOR_H

#include<iostream>
#include<algorithm>
#include<memory>

template<typename T>
void destroy(T* p)
{
    p->~T();
}

template<typename ForwardIterator>
void destroy(ForwardIterator first,ForwardIterator last)
{
    for(ForwardIterator it = first;it!=last;++it)
    {
        destroy(&(*it));
    }
}

template<typename T>
class youVector
{
public:
    typedef T         value_type;
    typedef T*        iterator;
    typedef const T*  const_iterator;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef size_t    size_type;
    
    //construct
    youVector();
    youVector(size_type n,T value = T());
    youVector(iterator begin,iterator end);
    ~youVector();

    //copy construct
    youVector(const youVector&);
    youVector& operator=(const youVector&);

    bool empty() const 
    {
        return begin()==end();
    }
    size_type size() const 
    {
        return (size_type)(finish-start);
    }
    size_type capacity()const 
    {
        return (size_type)(end_of_storage - start);
    }

    iterator begin() { return start; }
    const_iterator begin() const { return start; }
    iterator end() { return finish; }
    const_iterator end()const  { return finish; }

    reference operator[](size_type i) { return *(start+i); } 
    const_reference operator[](size_type i) const { return *(start + i); }

    void insert(iterator position,size_type n,const T& value);
    void push_back(const T& value);
    void pop_back();
    void erase(iterator first,iterator last);
    void clear();
protected:
    iterator start;//空间头
    iterator finish;//空间尾
    iterator end_of_storage;//分配空间尾
private:
    static std::allocator<T> alloc;//创建一个allocator对象来实现空间的申请
};

template<typename T>
std::allocator<T> youVector<T>::alloc;

template<typename T>
youVector<T>::youVector():start(nullptr),finish(nullptr),end_of_storage(nullptr) {}
//在ｎ这样大小的空间，初始化尾value
template<typename T>
youVector<T>::youVector(size_type n,T value)
{
    start = alloc.allocate(n);
    end_of_storage = finish = start + n;
    for(iterator i = start ;i!= finish;++i) alloc.construct(i,value);
}
template<typename T>
youVector<T>::youVector(iterator begin,iterator end)
{
    const size_type  n = begin - end;
    start = alloc.allocate(n);
    end_of_storage = finish = start + n;
    std::uninitialized_copy(begin,end,start);//？
}
template<typename T>
youVector<T>::~youVector()
{
    ::destroy(start,finish);
    alloc.deallocate(start,end_of_storage - start);
}

template<typename T>
youVector<T>::youVector(const youVector& rhs)
{
    start = alloc.allocate(rhs.capacity());
    std::uninitialized_copy(rhs.start,rhs.finish,start);
    finish  = start + (rhs.finish - rhs.start);
    end_of_storage = start+ (rhs.end_of_storage - rhs.start);
}
template<typename T>
youVector<T>& youVector<T>::operator=(const youVector& rhs)
{
    start = alloc.allocate(rhs.capacity());
    std::uninitialized_copy(rhs.start,rhs.finish,start);
    finish  = start + (rhs.finish - rhs.start);
    end_of_storage = start+ (rhs.end_of_storage - rhs.start);

    return *this;
}

template<typename T>
void youVector<T>::insert(iterator position,size_type n,const T& value)
{
    if(n<=size_type(end_of_storage - finish))
    {  
//备用空间大于新增元素个数
        
        T x_copy = value;
        const size_type elems_after = finish - position;
        iterator old_finish  = finish;
        if(elems_after > n)//插入点之后的现有元素个数大于新增元素个数
        {
            /*首先如果在position位置插入n个value，也就是我们需要在finish后开辟一个n大小的空间保存finish前面n空间内的数据，并且先把finish前n空间的数据先拷贝到finish后面的空间中去，然后在将position位置到finish-n位置内的数据以此使用copy_backward方法一一拷贝，如此就在position位置后面留出了一个n大小的空间用来存放value！！！！！！！！！*/
            std::uninitialized_copy(finish - n,finish,finish);
            finish += n;
            std::copy_backward(position,old_finish - n,old_finish);
            std::fill(position,position+n,x_copy);
        }
        else 
        {
            std::uninitialized_fill_n(finish,n-elems_after,x_copy);
            finish+= n-elems_after;
            std::uninitialized_copy(position,old_finish,finish);
            finish += elems_after;
            std::fill(position,old_finish,x_copy);
        }
    }
    else 
    {
        //备用空间小于新增元素个数，那么就需要开辟新的空间来保存vector
        //首先决定新长度:为旧长度的两倍，或者尾旧长度+新增元素的个数
        const size_type old_size  =size();
        const size_type len = old_size + std::max(old_size,n);
        //使用allocator配置新的内存
        iterator new_start  = alloc.allocate(len);
        iterator new_finish = new_start;

        new_finish = std::uninitialized_copy(start,position,new_start);
        std::uninitialized_fill_n(new_finish,n,value);
        new_finish += n;
        new_finish = std::uninitialized_copy(position,finish,new_finish);

        alloc.deallocate(start,(size_type)(finish-start));
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start+len;
    }
}

template<typename T>
void youVector<T>::push_back(const T &value)
{
    insert(end(),1,value);
}

template<typename T>
void youVector<T>::pop_back()
{
    ::destroy(--finish);
}

template<typename T>
void youVector<T>::erase(iterator first,iterator last)
{
    iterator old_finish = finish;
    finish = std::copy(last,finish,first);
    ::destroy(finish,old_finish);
    //alloc.deallocate(finish,(size_type)(old_finish-finish));
}

template<typename T>
void youVector<T>::clear()
{
    erase(start,finish);
}

#endif
