#pragma once
#include <cstddef>
#include <cstring>
//-----------------------
#include "arena.h"


namespace my
{
    class string
    {
    public:

        string(arena& arena, const char* str) : m_arena(arena)
        {
            m_size = std::strlen(str);
            m_data = static_cast<char*>(m_arena.alloc_bytes(m_size + 1));
            memcpy(m_data, str, m_size + 1);
        };

        string(const string&) = delete;
        string(string&&) = delete;
        string& operator=(const string&) = delete;
        string& operator=(string&&) = delete;

        const char* c_str() const { return m_data; }
        size_t size() const { return m_size; }
        char operator[](size_t i) const { return m_data[i]; }

    private:

        arena& m_arena;
        char* m_data;
        size_t m_size;
    };
};
