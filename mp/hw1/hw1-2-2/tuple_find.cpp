// Reference: https://stackoverflow.com/questions/25958259/how-do-i-find-out-if-a-tuple-contains-a-type

#include <iostream>
#include <tuple>
#include <assert.h>
#include <cxxabi.h>

const std::string demangle(const char* const mangledTypeName) {
   int resultStatus = -4;
   const char* const result = abi::__cxa_demangle( mangledTypeName, 0, 0, &resultStatus );
   std::string demangledTypeName;
   const bool noError = (0 == resultStatus);
   const bool demangledSuccess = (noError && result != 0);
   assert(demangledSuccess);
   demangledTypeName = (demangledSuccess ? result : "Unknown type.");
   free(const_cast<char*>(result));
   return demangledTypeName;
}
 
const std::string demangle(const std::string& mangledTypeName) {
   return demangle(mangledTypeName.c_str());
}
 
const std::string demangledNameOfType(const std::type_info& type_id) {
   return demangle(type_id.name());
}
 
#define DEMANGLED_NAME_OF_TYPE(TypeOrValue) (demangledNameOfType(typeid(TypeOrValue)))
#define PRINT_NAME_OF_TYPE(TypeOrValue) {std::cout<<DEMANGLED_NAME_OF_TYPE(TypeOrValue)<<std::endl;}


using namespace std;

// tuple_element
template<class T, std::size_t I> 
struct my_tuple_element;

template<class Head, class... Tail, std::size_t I>
struct my_tuple_element<std::tuple<Head, Tail...>, I>
  : my_tuple_element<std::tuple<Tail...>, I-1>
{ };

template <class Head, class... Tail>
struct my_tuple_element<std::tuple<Head, Tail...>, 0>
{
  typedef Head type;
};

// tuple find
#if 1
template<class Tuple, class T> 
struct tuple_find;

template<class... Tail, class T> 
struct tuple_find< tuple <T, Tail...>, T >
{
  static const bool value = true;
};

template <class Head, class... Tail, class T>
struct tuple_find < tuple<Head, Tail...>, T>
  : tuple_find< tuple<Tail...>, T>
{ };

template <class T>
struct tuple_find < tuple<>, T>
{
  static const bool value = false;
};
#endif

// reference tuple has_type
template <typename T, typename Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

int main()
{
  using MyTuple1 = tuple<int, double, string, char, bool, string>;

  std::cout << "my_tuple_element = ";
  using mytype_my_tuple_element = my_tuple_element<MyTuple1, 1>::type;
  PRINT_NAME_OF_TYPE(mytype_my_tuple_element);

  std::cout << "has_type = ";
  using tuple_contains_type = has_type<int, MyTuple1>::type;
  PRINT_NAME_OF_TYPE(tuple_contains_type);

  std::cout << "tuple_find = " << tuple_find<MyTuple1, int>::value << endl;
  std::cout << "tuple_find = " << tuple_find<MyTuple1, long>::value << endl;
 

  return 0;
}


