/*************************************************************************
	> File Name: testAlloc.h
	> Author: bei 
	> Mail: 
	> Created Time: 2017年02月15日 星期三 19时07分06秒
 ************************************************************************/

#ifndef _TESTALLOC_H
#define _TESTALLOC_H

#include<new>
#include<cstddef>
#include<climits>
#include<iostream>

namespace YOU
{
    template<class T>
    inline T* _allocate(ptrdiff_t size,T*)
    {
        std::set_new_handler(nullptr);
        T* temp = (T*)(::operator new((size_t)(size*sizeof(T))));
        if (temp ==nullptr)
        {
            std::cout << "out of memory\n"<<std::endl;
            exit(1);
        }
        return temp;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        ::operator delete(buffer);
    }

    template<class T1,class T2>
    inline void _construct(T1* p,const T2& value)
    {
        new(p)T1(value);//在内存p位置初始化T1对象，并且调用T1的复制构造函数
    }

    template<class T>
    inline void _destroy(T* ptr)
    {
        ptr->~T();
    }

    template<class T>
    class test_allocator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        template<class U>
        struct rebind
        {
            typedef test_allocator<U> other;
        };

        pointer allocate(size_type n,const void* hint = 0 )
        {
            return _allocate((difference_type)n,(pointer)0);//分配对象
        }

        void deallocate(pointer p,size_type n)
        {
            _deallocate(p);//释放对象的内存
        }

        void construct(pointer p,const T& value)
        {
            _construct(p,value);
        }

        void destroy(pointer p)
        {
            _destroy(p);
        }

        pointer address(reference x)
        {
            return (pointer)&x;
        }

        const_pointer const_address(const_reference x)
        {
            return (const_pointer)&x;
        }

        size_type max_size() const
        {
            return size_type(UINT_MAX / sizeof(T));
        }
    };
}
#endif
