// API.h

#include <string>
#include <iostream>

class Api
{
  public:
    explicit Api(const std::string& name);
    ~Api();
    std::string getName();

  private:
    class Impl;
    Impl *pImpl;
};

std::ostream& operator<<(std::ostream& os, Api& api);

