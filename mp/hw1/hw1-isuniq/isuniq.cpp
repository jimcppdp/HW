#include <iostream>

using namespace std;

// instructor function template version
template<typename T, typename Q>
bool isuniq(T first, Q sec)
{
   if (first == sec) return false;
   return true;
}

template<typename T, typename Q, typename... Args>
bool isuniq(T first, Q sec, Args... args)
{
  return isuniq(first, sec) && isuniq(first, args...) && isuniq(sec, args...);
}

// This order is important for compiler, sum(T value) and then variadic sum is OK, but reverse is not. 
// my function template version
template<typename T, typename Q>
bool myisuniq(T first, Q sec)
{
   if (first == sec) return false;
   return true;
}

template<typename T, typename Q, typename... Args>
bool myisuniq(T first, Q sec, Args... args)
{
  if (!myisuniq(first, sec)) return false;
  if (!myisuniq(first, args...)) return false;
  if (!myisuniq(sec, args...)) return false;
  return true;
}


// my class template version

// base template needs to be declared first 
template<int...>
struct Isuniq;

// below three Specialization can change the order 
template<>
struct Isuniq<>
{
  static const bool value = false;
};

template<int first, int second>
struct Isuniq<first, second>
{
  static const bool value = first != second;
};

template<int first, int second, int ...Rest>
struct Isuniq<first, second, Rest...>
{
  static const bool value = Isuniq<first, second>::value && 
                            Isuniq<first, Rest...>::value && 
                            Isuniq<second, Rest...>::value;
};


// my another class template version, complicated but efficient
template<int...> 
struct ISuniq;

template<int Head, int... Tail > 
struct ISuniq< Head, Head, Tail... >
{
  static const bool value = false;
};

template <int T, int Head, int... Tail>
struct ISuniq < T, Head, Tail... >
  : ISuniq< T, Tail... >
{ };

template <int T>
struct ISuniq < T >
{
  static const bool value = true;
};

int main()
{
  //static char karray[isuniq(3, 4, 1, 2, 5, 6)]; // error
  static char array[Isuniq<3, 4, 1, 2, 5, 6>::value];

  cout << "instructor function template version" << endl;
  cout << "isuniq(3, 4, 1, 2, 5, 6)=" << isuniq(3, 4, 1, 2, 5, 6) << endl;
  cout << "isuniq(3, 4, 1, 2, 5, 3)=" << isuniq(3, 4, 1, 2, 5, 3) << endl;
  cout << "isuniq(3, 4, 1, 2, 3)=" << isuniq(3, 4, 1, 2, 3) << endl;

  cout << "my function template version" << endl;
  cout << "myisuniq(3, 4, 1, 2, 5, 6)=" << myisuniq(3, 4, 1, 2, 5, 6) << endl;
  cout << "myisuniq(3, 4, 1, 2, 5, 3)=" << myisuniq(3, 4, 1, 2, 5, 3) << endl;
  cout << "myisuniq(3, 4, 1, 2, 3)=" << myisuniq(3, 4, 1, 2, 3) << endl;

  cout << "my class template version" << endl;
  cout << "Isuniq<1, 1>=" << Isuniq<1, 1>::value << endl;
  cout << "Isuniq<1, 2>=" << Isuniq<1, 2>::value << endl;
  cout << "Isuniq<3, 3, 1, 1, 3, 3>=" << Isuniq<3, 3, 1, 1, 3, 3>::value << endl;
  cout << "Isuniq<3, 3, 1, 1, 3, 4>=" << Isuniq<3, 3, 1, 1, 3, 4>::value << endl;
  cout << "Isuniq<3, 4, 1, 2, 5, 6>=" << Isuniq<3, 4, 1, 2, 5, 6>::value << endl;
  cout << "Isuniq<3, 4, 1, 2, 5, 3>=" << Isuniq<3, 4, 1, 2, 5, 3>::value << endl;
    
  cout << "my another class template version" << endl;
  cout << "ISuniq<1, 1>=" << ISuniq<1, 1>::value << endl;
  cout << "ISuniq<1, 2>=" << ISuniq<1, 2>::value << endl;
  cout << "ISuniq<1, 2, 3>=" << ISuniq<1, 2, 3>::value << endl;

  return 0;
}


