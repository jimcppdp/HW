// C++ program to implement Custom Linked List and
// iterator pattern.
#include <iostream>
#include <memory>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator_adaptors.hpp>
#include "gtest/gtest.h"


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


using namespace std;
 
// Custom class to handle Linked List operations
// Operations like push_back, push_front, pop_back,
// pop_front, erase, size can be added here
template <typename T>
class LinkedList
{
    // Forward declaration
    class Node;
 
public:
    LinkedList<T>() noexcept
    {
        // caution: static members can't be
        // initialized by initializer list
        m_spRoot = nullptr;
    }
 
    // Forward declaration must be done
    // in the same access scope
    class Iterator;
 
    // Root of LinkedList wrapped in Iterator type
    Iterator begin()
    {
        return Iterator(m_spRoot);
    }
 
    // End of LInkedList wrapped in Iterator type
    Iterator end()
    {
        return Iterator(nullptr);
    }
 
    // Adds data to the end of list
    void push_back(T data);
 
    void Traverse();
 
    // Iterator class can be used to
    // sequentially access nodes of linked list
    class Iterator
    {
    public:
    Iterator() noexcept :
        m_pCurrentNode (m_spRoot) { }
 
    Iterator(const Node* pNode) noexcept :
        m_pCurrentNode (pNode) { }
 
        Iterator& operator=(Node* pNode)
        {
            this->m_pCurrentNode = pNode;
            return *this;
        }
 
        // Prefix ++ overload
        Iterator& operator++()
        {
            if (m_pCurrentNode)
                m_pCurrentNode = m_pCurrentNode->pNext;
            return *this;
        }
 
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
 
        bool operator!=(const Iterator& iterator)
        {
            return m_pCurrentNode != iterator.m_pCurrentNode;
        }
 
        int operator*()
        {
            return m_pCurrentNode->data;
        }
 
    private:
        const Node* m_pCurrentNode;
    };
 
private:
 
    class Node
    {
        T data;
        Node* pNext;
 
        // LinkedList class methods need
        // to access Node information
        friend class LinkedList;
    };
 
    // Create a new Node
    Node* GetNode(T data)
    {
        Node* pNewNode = new Node;
        pNewNode->data = data;
        pNewNode->pNext = nullptr;
 
        return pNewNode;
    }
 
    // Return by reference so that it can be used in
    // left hand side of the assignment expression
    Node*& GetRootNode()
    {
        return m_spRoot;
    }
 
    static Node* m_spRoot;
};
 
template <typename T>
/*static*/ typename LinkedList<T>::Node* LinkedList<T>::m_spRoot = nullptr;
 
template <typename T>
void LinkedList<T>::push_back(T data)
{
    Node* pTemp = GetNode(data);
    if (!GetRootNode())
    {
        GetRootNode() = pTemp;
    }
    else
    {
        Node* pCrawler = GetRootNode();
        while (pCrawler->pNext)
        {
            pCrawler = pCrawler->pNext;
        }
 
        pCrawler->pNext = pTemp;
    }
}
 
template <typename T>
void LinkedList<T>::Traverse()
{
    Node* pCrawler = GetRootNode();
 
    while (pCrawler)
    {
        cout << pCrawler->data << " ";
        pCrawler = pCrawler->pNext;
    }
 
    cout << endl;
}



struct node_base
{
    node_base() : m_next(0) {}

    // Each node manages all of its tail nodes
    virtual ~node_base() { delete m_next; }

    // Access the rest of the list
    node_base* next() const { return m_next; }

    // print to the stream
    virtual void print(std::ostream& s) const = 0;

    // double the value
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



inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}



class node_iterator
  : public boost::iterator_facade<
        node_iterator
      , node_base
      , boost::forward_traversal_tag
    >
{
 public:
    node_iterator()
      : m_node(0) {}

    explicit node_iterator(node_base* p)
      : m_node(p) {}

 private:
    friend class boost::iterator_core_access;

    void increment() { m_node = m_node->next(); }

    bool equal(node_iterator const& other) const
    {
        return this->m_node == other.m_node;
    }

    node_base& dereference() const { return *m_node; }

    node_base* m_node;
};

//------------------------------------------------------








 
//Driver program
/*
int main()
{
    LinkedList<int> list;
 
    // Add few items to the end of LinkedList
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
 
    cout << "Traversing LinkedList through method" << endl;
    list.Traverse();
 
    cout << "Traversing LinkedList through Iterator" << endl;
    for ( LinkedList<int>::Iterator iterator = list.begin();
            iterator != list.end(); iterator++)
    {
        cout << *iterator << " ";
    }
 
    cout << endl;
    
    LinkedList<int>::Iterator iterator = list.begin();
    iterator++;
    cout<< "" << *iterator << "\n";

    
    
    std::auto_ptr<node<int> > nodes(new node<int>(42));
    nodes->append(new node<std::string>(" is greater than "));
    nodes->append(new node<int>(13));

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, " ")
    );
    std::cout << std::endl;
    
   // std::for_each(
   //     node_iterator(nodes.get()), node_iterator()
   //   , std::mem_fun_ref(&node_base::double_me)
   // );

    //std::copy(
    //    node_iterator(nodes.get()), node_iterator()
    //  , std::ostream_iterator<node_base>(std::cout, "/")
    //);
    //std::cout << std::endl;    
 
    return 0;
}
*/

TEST(testIterator, UseCase1)
{
  std::ostream result;

  std::auto_ptr<node<int> > nodes(new node<int>(42));
  nodes->append(new node<std::string>(" is greater than "));
  nodes->append(new node<int>(13));

  std::copy(
      node_iterator(nodes.get()), node_iterator()
    , std::ostream_iterator<node_base>(std::cout, " ")
  );
  std::cout << std::endl;

  //EXPECT_EQ(*iterator, 2);
}
