#pragma once

#include <cstdlib>
#include <vector>

namespace Kruskal
{

class FindAndUnion
{
public:
    FindAndUnion(const size_t nodes);

    void Union(size_t a, size_t b);
    size_t Find(const size_t a);

private:
    std::vector<size_t> m_parent;
    std::vector<size_t> m_size;
};

}