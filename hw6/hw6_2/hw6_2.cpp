// https://wandbox.org/permlink/V06lq5hdCzcA7Bz9

// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
# include <boost/iterator/iterator_facade.hpp>

// Polymorphic list node base class

struct node_base
{
    node_base() : m_next(0) {}

    virtual ~node_base()
    {
        delete m_next;
    }

    node_base* next() const
    {
        return m_next;
    }

    virtual void print(std::ostream& s) const = 0;
    virtual void double_me() = 0;
        
    void append(node_base* p)
    {
        if (m_next)
            m_next->append(p);
        else
            m_next = p;
    }
    
 private:
    node_base* m_next;
};

inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}

template <class T>
struct node : node_base
{
    node(T x)
      : m_value(x)
    {}

    void print(std::ostream& s) const { s << this->m_value; }
    void double_me() { m_value += m_value; }
    
 private:
    T m_value;
};
    


class node_iterator
  : public boost::iterator_facade<
        node_iterator
      , node_base
      , boost::forward_traversal_tag
    >
{
 public:
    node_iterator()
      : m_node(0)
    {}

    explicit node_iterator(node_base* p)
      : m_node(p)
    {}

 private:
    friend class boost::iterator_core_access;

    void increment()
    { m_node = m_node->next(); }
    
    bool equal(node_iterator const& other) const
    { return this->m_node == other.m_node; }
    
    node_base& dereference() const
    { return *m_node; }

    node_base* m_node;
};

int main()
{
    std::auto_ptr<node<int> > nodes(new node<int>(42));
    nodes->append(new node<std::string>(" is greater than "));
    nodes->append(new node<int>(13));

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, " ")
    );
    std::cout << std::endl;
    
    std::for_each(
        node_iterator(nodes.get()), node_iterator()
      , std::mem_fun_ref(&node_base::double_me)
    );

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, "/")
    );
    std::cout << std::endl;
}

