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


int main()
{
  using MyTuple1 = tuple<int, double, string, char, bool, string>;

  std::cout << "mytype_my_tuple_element = ";
  using mytype_my_tuple_element = my_tuple_element<MyTuple1, 1>::type;
  PRINT_NAME_OF_TYPE(mytype_my_tuple_element);

  return 0;
}


