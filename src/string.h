#pragma once
#include <cstddef>
#include <cstring>
#include <assert.h>
//-----------------------
#include "arena.h"

namespace my
{
    class string
    {
    public:

        string(arena& arena) : m_arena(arena) {}

        string(arena& arena, const char* str) : m_arena(arena)
        {
            m_size = std::strlen(str);
            m_data = static_cast<char*>(m_arena.alloc_bytes(m_size + 1));
            std::memcpy(m_data, str, m_size + 1);
        };

        string(const string&) = delete;
        string(string&&) = delete;
        string& operator=(const string&) = delete;
        string& operator=(string&&) = delete;
        
        const string* substr(size_t pos, size_t length) const
        {
            assert(pos + length <= m_size && "substring position out of range");

            char* strptr = static_cast<char*>(m_arena.alloc_bytes(length + 1, alignof(char)));
            std::memcpy(strptr, m_data + pos, length);

            strptr[length] = '\0';

            string* copy = m_arena.allocate<string>(m_arena);
            copy->m_data = strptr;
            copy->m_size = length;
            return copy;
        }

        const char* c_str() const { return m_data; }
        size_t size() const { return m_size; }
        char operator[](size_t i) const { return m_data[i]; }

    private:

        arena& m_arena;
        char* m_data;
        size_t m_size;
    };
};
