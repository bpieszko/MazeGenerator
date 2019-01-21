#include "FindAndUnion.hpp"

using namespace Kruskal;

FindAndUnion::FindAndUnion(const size_t a_nodes)
    : m_parent(a_nodes), m_size(a_nodes, 0) 
{
    for (size_t i = 0; i < a_nodes; ++i)
        m_parent.at(i) = i;
}

void FindAndUnion::Union(size_t a, size_t b)
{
    a = Find(a);
    b = Find(b);

    if (m_size.at(a) >= m_size.at(b))
    {
        m_parent.at(b) = a;
        m_size.at(a) += m_size.at(b);
        m_size.at(b) = 0;
    }
    else
    {
        m_parent.at(a) = b;
        m_size.at(b) += m_size.at(a);
        m_size.at(a) = 0;
    }
}

size_t FindAndUnion::Find(const size_t a)
{
    if (m_parent.at(a) != a)
        m_parent.at(a) = Find(m_parent.at(a));
    return m_parent.at(a);
}