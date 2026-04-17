#include <print>
#include <cstring>
//--------------------
#include "types.h"
#include "arena.h"
#include "string.h"
#include "vector.h"

struct vector_data
{
    i32 x;
    i32 y;
    i32 z;
};

size_t to_mb(const size_t val)
{
    return val / 1024 / 1024;
}

int main() 
{
    const i32 MB = 1024 * 1024 * 3; 
    my::arena arena(MB);

    //////////////// STRING //////////////////////////
    std::print("\nSTRING\n");
    my::string s(arena, "Hello World");

    std::print("word: {0} | size: {1} | 2nd char: {2}\n", s.c_str(), s.size(), s[1]);
 

    //////////////// VECTOR //////////////////////////
    std::print("\nVECTOR - primitive type\n");
    my::vector<int> v(arena, 5);

    for (int i = 0; i <= 4; i++)
    {
        v.push_back(i);
    }
    
    for (auto i : v)
    {
        std::print("item: {0}\n", i);
    }

    std::print("\nVECTOR - non-trivial type\n");
    my::vector<vector_data> vd(arena, 2);

    vector_data vds
    {
        .x = 1,
        .y = 2,
        .z = 3
    };

    vd.push_back(vds);
    vd.emplace_back(5,6,7);

    for (auto item : vd)
    {
        std::print("x: {0}, y: {1}, z: {2}\n", item.x, item.y, item.z);
    }


    std::print("arena size: {0}\n", arena.used());

    arena.reset();

    std::print("arena size: {0}\n", arena.used());

    return 0;
};
