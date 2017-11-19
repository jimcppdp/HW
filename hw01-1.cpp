#include <iostream>
#include <tuple>

using namespace std;

struct F
{
  template <typename T>
  void operator()(T&& t) { std::cout << "unexpected type: " << typeid(std::forward<T&&>(t)).name() << std::endl; }
  void operator()(int i) { std::cout << "void F::operator()(int): " << i << std::endl; }
  void operator()(double d) { std::cout << "void F::operator()(double): " << d << std::endl; }
  void operator()(const std::string& s) { std::cout << "void F::operator()(const std::string&): " << s << std::endl; }
};

template<typename FuncType, typename Tuple, std::size_t N>
struct VisitF {
  static void visit(const Tuple& t)
  {
    FuncType ft;
    VisitF<FuncType, Tuple, N-1>::visit(t);
    ft(std::get<N-1>(t));
  }
};

template<typename FuncType, typename Tuple>
struct VisitF<FuncType, Tuple, 1> {
  static void visit(const Tuple& t)
  {
    FuncType ft;
    ft(std::get<0>(t));
  }
};

template<typename FuncType, typename... Args>
void tuple_visitor(FuncType, const std::tuple<Args...>& t)
{
  VisitF<FuncType, decltype(t), sizeof...(Args)>::visit(t);
}

int main()
{
  auto t = std::make_tuple(10, std::string("Test"), 3.14, "Test");

  F f;
  
  tuple_visitor(f, t); //please implement this tuple_visitor
  
  return 0;
}
