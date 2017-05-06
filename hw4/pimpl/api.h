// API.h

#include <string>
#include <iostream>
#include <memory>

class Api
{
  public:
    explicit Api(const std::string& name);
    ~Api();
    std::string getName();

  private:
    class Impl;
    //Impl *pImpl;
    //std::shared_ptr<Impl> pImpl;
    std::unique_ptr<Impl> pImpl;
};

std::ostream& operator<<(std::ostream& os, Api& api);

