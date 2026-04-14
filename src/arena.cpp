#include <cstddef>
#include <assert.h>
#include <print>
//------------------
#include "arena.h"


my::arena::arena(size_t capacity) : m_capacity(capacity), m_offset(0)
{
    m_storage = new std::byte[capacity];
};

my::arena::~arena() noexcept
{
    delete[] m_storage;
};

[[nodiscard]] void* my::arena::alloc_bytes(size_t size)
{
    size_t align = alignof(max_align_t);
    size_t alignment = (m_offset + align - 1) & ~(align- 1); 
    
    assert(alignment + size <= m_capacity && "Arena out of memory");

    void* ptr = m_storage + alignment;
    m_offset = alignment + size;
    return ptr;
};

void my::arena::reset()
{
    std::print("Arena Reset\n");
    m_offset = 0;
};

size_t my::arena::used() const
{
    return m_offset;
};

size_t my::arena::capacity() const
{
    return m_capacity;
};

size_t my::arena::remaining() const
{
    return m_capacity - m_offset;
};

