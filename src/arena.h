#pragma once
#include <cstddef>
#include <utility>


namespace my 
{
    class arena
    {
    public:
        explicit arena(size_t capacity);
        ~arena() noexcept;

        arena(const arena& arena) = delete;
        arena& operator=(const arena&) = delete;

        
        template<typename T, typename... Args>
        T* allocate(Args&&... args)
        {
            void* ptr = alloc_bytes(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        };

        void reset();

        size_t used() const;
        size_t capacity() const;
        size_t remaining() const;

    private:
        [[nodiscard]] void* alloc_bytes(size_t size);
        
    private:
        std::byte* m_storage;
        size_t m_capacity;
        size_t m_offset;
    };
};
