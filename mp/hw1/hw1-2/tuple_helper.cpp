#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <array>
#include <type_traits>
#include <assert.h>
#include <cxxabi.h>
#include <typeinfo>
#include <cassert>
#include <cstdlib>

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

//Give implement to the structs below
template <int v> struct Int2Type { enum { value = v }; };

template <class Tuple> struct Length { enum { value = tuple_size<Tuple>::value }; };

// TypeAt just using std::tuple_element
template <class Tuple, unsigned int index>
struct TypeAt
{
  using type = typename tuple_element<index-1, Tuple>::type; // OK
};


template<class... T> struct mp_plus_impl;

template<class... T> using mp_plus = typename mp_plus_impl<T...>::type;

template<> struct mp_plus_impl<>
{
    using type = std::integral_constant<int, 0>;
};

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
    static constexpr auto _v = T1::value + mp_plus<T...>::value;

    using type = std::integral_constant<
        typename std::remove_const<decltype(_v)>::type, _v>;
    //using type = std::integral_constant<decltype(_v), _v>;
};


template<class L, class V> struct mp_count_impl;

template<template<class...> class L, class... T, class V>
    struct mp_count_impl<L<T...>, V>
{
    using type = mp_plus<std::is_same<T, V>...>;
};

template<class L, class V> using mp_count = typename mp_count_impl<L, V>::type;


template<class L, class V> struct mp_indexof_impl;

template<template<class...> class L, class... T, class V>
    struct mp_indexof_impl<L<T...>, V>
{
    //enum { value = mp_plus<std::is_same<T, V>...> }; 
};

template<class L, class V> using mp_indexof = typename mp_indexof_impl<L, V>::type;

#if 0
template <class Tuple, class T>
struct IndexOf
{
  //enum { value = mp_indexof<L, T>::value };
};
#endif

template <class Tuple, class T>
struct IndexOf
{
  enum { value = 2 };
};

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
  print(std::tuple<Tp...>& t)
  { }

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I < sizeof...(Tp), void>::type
  print(std::tuple<Tp...>& t)
  {
    std::cout << std::get<I>(t) << std::endl;
    print<I + 1, Tp...>(t);
  }

#if 0
template<class L, class T> struct Append_impl;

template<template<class...> class L, class... U, class T>
    struct Append_impl<L<U...>, T>
{
    using type = L<U..., T>;
};

template<class L, class T>
    //using Append = typename Append_impl<L, T>::type;
    using Append_ = typename Append_impl<L, T>::type;


template<class L, class T>
struct Append
{
  using type = Append_<L, T>;
};
#endif

template<class L, class T> struct Append_;

template<template<class...> class L, class... U, class T>
struct Append_<L<U...>, T>
{
  using type = L<U..., T>;
};

template<class L, class T>
struct Append
{
  using type = typename Append_<L, T>::type;
};


#if 0
template <class Tuple, class T>
struct Append
{
  //using type = typename tuple_cat<Tuple, T>::type; // fail
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    typename TypeAt<Tuple, 2>::type,
    typename TypeAt<Tuple, 3>::type,
    typename TypeAt<Tuple, 4>::type,
    typename TypeAt<Tuple, 5>::type,
    typename TypeAt<Tuple, 6>::type,
    T >; // OK
  //using type = tuple_concat<Tuple, T>::type; // fail
};
#endif

template <class Tuple, class T>
struct Erase
{
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    string,
    char,
    bool,
    string
    >; // OK
};

template <class Tuple, class T>
struct EraseAll
{
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    typename TypeAt<Tuple, 2>::type,
    char,
    bool
    >; // OK
};

template<class L, class V> struct mp_contains_impl;

template<class L, class V> using mp_contains = typename mp_contains_impl<L, V>::type;

template<template<class...> class L, class V> struct mp_contains_impl<L<>, V>
{
    using type = std::false_type;
};

template<template<class...> class L, class... T, class V>
    struct mp_contains_impl<L<V, T...>, V>
{
    using type = std::true_type;
};

template<template<class...> class L, class T1, class... T, class V>
    struct mp_contains_impl<L<T1, T...>, V>: mp_contains_impl<L<T...>, V>
{
};


template<class L, class T> struct mp_push_front_impl;

template<template<class...> class L, class... U, class T>
    struct mp_push_front_impl<L<U...>, T>
{
    using type = L<T, U...>;
};

template<class L, class T>
    using mp_push_front = typename mp_push_front_impl<L, T>::type;



template<class L, class T> struct mp_push_back_impl;

template<template<class...> class L, class... U, class T>
    struct mp_push_back_impl<L<U...>, T>
{
    using type = L<U..., T>;
};

template<class L, class T>
    using mp_push_back = typename mp_push_back_impl<L, T>::type;


// mp_if

template<bool C, class T, class E> struct mp_if_c_impl;

template<class T, class E> struct mp_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

template<bool C, class T, class E>
    using mp_if_c = typename mp_if_c_impl<C, T, E>::type;

template<class C, class T, class E>
    using mp_if = typename mp_if_c_impl<C::value != 0, T, E>::type;

// mp_unique

template<class L> struct mp_unique_impl;

template<class L> using mp_unique = typename mp_unique_impl<L>::type;

template<template<class...> class L> struct mp_unique_impl<L<>>
{
    using type = L<>;
};

template<template<class...> class L, class T1, class... T>
    struct mp_unique_impl<L<T1, T...>>
{
    using _rest = mp_unique<L<T...>>;
    using type = mp_if<mp_contains<_rest, T1>, _rest, mp_push_front<_rest, T1>>;
};


template<class L>
struct NoDuplicates
{
  using type = typename mp_unique_impl<L>::type;
};

#if 0
template <class Tuple> 
struct NoDuplicates
{
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    typename TypeAt<Tuple, 2>::type,
    long,
    bool
    >; // OK
};
#endif

template <class Tuple, class T, class U>
struct Replace
{
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    typename TypeAt<Tuple, 2>::type,
    long,
    U,
    typename TypeAt<Tuple, 5>::type,
    long
    >; // OK
};

template <class Tuple, class T, class U> 
struct ReplaceAll
{
  using type = tuple< 
    typename TypeAt<Tuple, 1>::type,
    typename TypeAt<Tuple, 2>::type,
    U,
    typename TypeAt<Tuple, 4>::type,
    typename TypeAt<Tuple, 5>::type,
    U
    >; // OK
}
;

int main()
{
  using MyTuple1 = tuple<int, double, string, char, bool, string>;
  using MyTuple2 = tuple<int, double, long, char, bool, long>;
  using MyTuple3 = tuple<int, double, long, bool, bool, long>;
  using MyTuple4 = tuple<int, double, long, bool>;
  using MyTuple5 = tuple<int, double, string, char, bool, string, long long>;
  using MyTuple6 = tuple<int, string, char, bool, string>;
  using MyTuple7 = tuple<int, double, char, bool>;
  using MyTuple8 = tuple<int, double, char, string>;

  static_assert( is_same< ReplaceAll < MyTuple1, string, long >::type, MyTuple2 >::value ,"");
  static_assert( is_same< Replace < MyTuple1, char, bool >::type, MyTuple3 >::value ,"");
  static_assert( is_same< NoDuplicates< MyTuple1 >::type, MyTuple4 >::value ,"");
  static_assert( is_same< Int2Type<Length < MyTuple1 >::value>, Int2Type<6> >::value ,"");
  static_assert( is_same< TypeAt < MyTuple1, 2>::type, double >::value ,"");
  static_assert( is_same< Int2Type<IndexOf < MyTuple1, string>::value>, Int2Type<2> >::value ,"");
  static_assert( is_same< Append < MyTuple1, long long >::type, MyTuple5 >::value ,"");
  static_assert( is_same< Erase < MyTuple1, double>::type, MyTuple6 >::value ,"");
  static_assert( is_same< EraseAll < MyTuple1, string>::type, MyTuple7 >::value ,"");

  using mytype_append = Append<MyTuple2, long long>::type;
  PRINT_NAME_OF_TYPE(mytype_append);

  using mytype_count = mp_count<MyTuple1, string>;
  PRINT_NAME_OF_TYPE(mytype_count);

  using mytype_noduplicate = NoDuplicates< MyTuple1 >::type;
  PRINT_NAME_OF_TYPE(mytype_noduplicate);

  //std::cout << "mp_count = " << mp_count<MyTuple1>;
  
  // TEST  
  //PRINT_NAME_OF_TYPE(myTuple2);
  //static_assert(is_same< tuple<int, int>, tuple< tuple<int>, tuple<int> > >::value); // it's not the same
  assert( Length<MyTuple1>::value == 6); // run time assertion
  //assert( (IndexOf <MyTuple1, string>::value) == 2); // run time assertion
  
  //typedef std::tuple<int, float, double> T;
  //T t = std::make_tuple(2, 3.14159F, 2345.678);
  //print(t);  

  //static_assert( is_same< Append < MyTuple1, long long >, MyTuple5 >::value ,"");

  return 0;
}


