#include <print>
#include <cstring>
//--------------------
#include "types.h"
#include "arena.h"
#include "string.h"

size_t to_mb(const size_t val)
{
    return val / 1024 / 1024;
}


int main()
{
    const i32 MB = 1024 * 1024 * 3; 
    my::arena arena(MB);

    my::string s(arena, "Hello World");
    const char* cstr = s.c_str();
    size_t size = s.size();
    char c = s[1];

    std::print("{0} | size: {1} | 2nd character: {2}\n", cstr, size, c);
    std::print("arena size: {0}\n", arena.used());
    
    arena.reset();

    std::print("arena size: {0}\n", arena.used());

    // std::vector<int> a;
    // std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());
    // i32* x = arena.allocate<i32>(1);
    //
    // std::print("Value: {0}\n", *x);
    // std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());
    //
    // std::print("RESET\n");
    //
    // arena.reset();
    //
    // std::print("capacity: {0} MB\n offset: {1}\n", to_mb(arena.capacity()), arena.used());
    //
    return 0;
};
