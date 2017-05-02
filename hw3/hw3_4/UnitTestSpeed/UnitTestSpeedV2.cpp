#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>

#if 0
template<typename T, template<typename, typename> class Container>
class BackInserter
{
    Container<T, std::allocator<T>> container;

    void insert(T e)
    {
        container.push_back(e);
    }

};
#endif

template<typename T, template<typename, typename...> class ContainerType, typename... Args>
class BackInserter
{
    ContainerType<T, Args...> container;

    void insert(T e)
    {
        container.push_back(e);
    }

};


int main(int argc, char* argv[])
{
  BackInserter <int, std::vector> vector; //noted the use of a template template parameter
  BackInserter <int, std::list> list; //noted the use of a template template parameter
  BackInserter <int, std::deque> deque; //noted the use of a template template parameter
  BackInserter <int, std::queue> queue; //noted the use of a template template parameter
  BackInserter <int, std::set> set; //noted the use of a template template parameter
  
  std::cout << "Hello!\n";

}
