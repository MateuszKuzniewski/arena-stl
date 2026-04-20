#include <print>
#include <cstring>
//--------------------
#include "types.h"
#include "arena.h"
#include "string.h"
#include "array.h"
#include "list.h"

struct array_data
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

    //////////////// LIST //////////////////////////
    std::print("\nLIST\n");
    my::list<int> list(arena);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(5);
    list.push_front(6);
    list.push_front(7);

    std::print("list size: {0}\n", list.size());

    for (auto& item : list)
    {
        std::print("item: {0}\n", item);
    }

    my::list<array_data> secondList(arena);

    array_data ad {1, 2 ,3};
    secondList.push_back(ad);

    for (auto& item : secondList)
    {
        std::print("x: {0}, y: {1}, z: {2}\n", item.x, item.y, item.z);
    }
    //////////////// STRING //////////////////////////
    std::print("\nSTRING\n");
    my::string s(arena, "Hello World");
    
    auto sub = s.substr(3, 4);
    std::print("word: {0} | size: {1} | 2nd char: {2}\n", s.c_str(), s.size(), s[1]);
    std::print("{0}\n", sub->c_str());


    //////////////// ARRAY //////////////////////////
    std::print("\nARRAY- primitive type\n");
    my::array<int> v(arena, 5);

    for (int i = 0; i <= 4; i++)
    {
        v.push_back(i);
    }
    
    for (auto i : v)
    {
        std::print("item: {0}\n", i);
    }

    std::print("\nARRAY - non-trivial type\n");
    my::array<array_data> vd(arena, 2);

    array_data vds
    {
        .x = 1,
        .y = 2,
        .z = 3
    };

    vd.push_back(vds);
    vd.emplace_back(5,6,7);

    for (const auto& item : vd)
    {
        std::print("x: {0}, y: {1}, z: {2}\n", item.x, item.y, item.z);
    }


    std::print("arena size: {0}\n", arena.used());

    arena.reset();

    std::print("arena size: {0}\n", arena.used());

    return 0;
};
