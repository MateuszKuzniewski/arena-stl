#pragma once
#include <cstddef>
#include <assert.h>
//-----------------
#include "arena.h"


namespace my
{
    template<typename T>
    class vector
    {
    public:

        vector(arena& arena, size_t capacity) : m_arena(arena), m_size(0), m_capacity(capacity) 
        {
            m_data = static_cast<T*>(arena.alloc_bytes(sizeof(T) * m_capacity, alignof(T)));
        }

        ~vector()
        {
            for (int i = 0; i < m_size; i++)
            {
                m_data[i].~T();
            }
        }

        vector(const vector&) = delete;
        vector(vector&&) = delete;
        vector& operator=(const vector&) = delete;
        vector& operator=(vector&&) = delete;

        void push_back(const T& item)
        {
            assert(m_size < m_capacity && "Arena memory overflow");
            new (m_data + m_size) T(item);
            m_size++;
        }

        void push_back(T&& item)
        {
            assert(m_size < m_capacity && "Arena memory overflow");
            new (m_data + m_size) T(std::move(item));
            m_size++;
        }

        template<typename... Args>
        T& emplace_back(Args&&... args)
        {
            assert(m_size < m_capacity && "Arena memory overflow");
            T* ptr = new (m_data + m_size) T(std::forward<Args>(args)...);
            m_size++;
            return *ptr;
        }

        T& operator[](size_t i)                         { return assert(i < m_size); m_data[i]; }
        const T& operator[](size_t i) const             { return assert(i < m_size); m_data[i]; }

        [[nodiscard]] size_t size() const noexcept      { return m_size; }
        [[nodiscard]] size_t capacity() const noexcept  { return m_capacity; }

        [[nodiscard]] T* begin()                        { return m_data; }
        [[nodiscard]] const T* begin() const            { return m_data; }
        [[nodiscard]] T* end()                          { return m_data + m_size; }
        [[nodiscard]] const T* end() const              { return m_data + m_size; }

    private:

        arena& m_arena;
        T* m_data;
        size_t m_size;
        size_t m_capacity;
    };
}
