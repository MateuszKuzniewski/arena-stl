#pragma once
#include <assert.h>
//---------------------
#include "arena.h"


namespace my
{
    template<typename T>
    class list
    {
    public:

        struct node 
        {
            T value;
            node* next;
        };
        
        struct iterator 
        {
            node* current;

            iterator(node* node) : current(node) {}

            T& operator*() { return current->value; }
            T* operator->() { return &current->value; }

            iterator& operator++()
            {
                current = current->next;
                return *this;
            }

            bool operator==(const iterator& other) const
            {
                return current == other.current;
            }
        };

    public:

        list(arena& arena) : m_arena(arena), m_head(nullptr), m_tail(nullptr), m_size(0) {}

        list(const list&) = delete;
        list(list&&) = delete;
        list& operator=(const list&) = delete;
        list& operator=(list&&) = delete;

        void push_back(const T& val)
        {
            node* n = m_arena.allocate<node>();
            n->value = val;
            n->next = nullptr;

            if (m_tail)
                m_tail->next = n;
            else
               m_head = n;

            m_tail = n;
            m_size++;
        }

        void push_front(const T& val)
        {
            node* n = m_arena.allocate<node>();
            n->value = val;
            n->next = m_head;
            m_head = n;

            if (m_tail == nullptr)
                m_tail = n;

            m_size++;
        }
        
        void pop_front() 
        {
            assert(m_head && "list is empty");

            m_head = m_head->next;

            if (m_head == nullptr)
                m_tail = nullptr;

            m_size--;
        }

        void pop_back() 
        {
            assert(m_head && "list is empty");
            
            if (m_head == m_tail)
            {
                m_head = nullptr;
                m_tail = nullptr;
                m_size--;
                return;
            }
            
            node* prev = m_head;
            while (prev->next != m_tail)
            {
                prev = prev->next;
            }

            prev->next = nullptr;
            m_tail = prev;
            m_size--;
        }

        [[nodiscard]] iterator begin() { assert(m_head); return iterator(m_head); }
        [[nodiscard]] iterator end() { return iterator(nullptr); }

        [[nodiscard]] size_t size() const { return m_size; }

        [[nodiscard]] T& front() { assert(m_head); return m_head->value; }
        [[nodiscard]] T& back() { assert(m_tail); return m_tail->value; }
    

    private:
        arena& m_arena;
        size_t m_size;
        node* m_tail;
        node* m_head;
    };
}
