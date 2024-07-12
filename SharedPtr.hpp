#ifndef __SHAREDPTR__
#define __SHAREDPTR__

#include <iostream>

struct ControlBlock {
    int m_count = 0;
};

template <typename T>
class Shared_Ptr {

public:
    Shared_Ptr(T* ptr) {
        m_ptr = ptr;
        m_block = new ControlBlock;
        m_block -> m_count++;
    }
    
    Shared_Ptr() {
        m_block = new ControlBlock();
        m_ptr = nullptr;
    }

    Shared_Ptr(const Shared_Ptr<T>& other) {
        m_block = other.m_block;
        if (other.m_block->m_count == 0) {
            m_ptr = nullptr;
        }
        else {
            m_ptr = other.m_ptr;
            m_block->m_count++;
        }
    }

    Shared_Ptr& operator=(const Shared_Ptr<T>& other) {
        std::cout << "operator =" << std::endl;
        if (m_block != other.m_block) {
            if (m_block->m_count <= 1) {
                delete m_block;
            }
            else {
                m_block->m_count--;
            }
            m_block = other.m_block;
            if (other.m_block->m_count == 0) {
                m_ptr = nullptr;
            }
            else {
                m_ptr = other.m_ptr;
                m_block->m_count++;
            }
        }
        return *this;
    }

    ~Shared_Ptr() {
        std::cout << "dtor" << " count = " << m_block->m_count << std::endl;
        if (m_block->m_count <= 1) {
            delete m_block;
            m_block = nullptr;
            delete m_ptr;
            m_ptr = nullptr;
        }
        else {
            m_block->m_count--;
        }
        
    }

    T& operator*() {
        return *m_ptr;
    }

    T* operator->() {
        return m_ptr;
    }
private:
    T* m_ptr = nullptr;
    ControlBlock* m_block = nullptr;    
};

#endif // __SHAREDPTR__