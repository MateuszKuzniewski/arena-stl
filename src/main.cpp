#include <print>
//--------------------
#include "types.h"
#include "arena.h"

size_t to_mb(size_t val)
{
    return val / 1024 / 1024;
}

int main()
{
    const i32 MB = 1024 * 1024 * 3; 
    my::arena arena(MB);
    
    std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());
    i32* x = arena.allocate<i32>(1);

    std::print("Value: {0}\n", *x);
    std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());

    std::print("RESET\n");

    arena.reset();

    std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());
    return 0;
};
