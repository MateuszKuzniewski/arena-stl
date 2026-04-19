#pragma once
#include <cstddef>
#include <utility>
#include <functional> // silences clang error

namespace my 
{
    class arena
    {
    public:
        explicit arena(size_t capacity);
        ~arena() noexcept;
        
        arena() = delete;
        arena(const arena& arena) = delete;
        arena& operator=(const arena&) = delete;

        
        template<typename T, typename... Args>
        T* allocate(Args&&... args)
        {
            void* ptr = alloc_bytes(sizeof(T), alignof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        };

        [[nodiscard]] void* alloc_bytes(size_t size, size_t align = alignof(std::max_align_t));

        void reset();

        size_t used() const;
        size_t capacity() const;
        size_t remaining() const;

        
    private:
        std::byte* m_storage;
        size_t m_capacity;
        size_t m_offset;
    };
};
