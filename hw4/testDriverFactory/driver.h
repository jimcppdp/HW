// driver.h

#include <string>
#include <iostream>
#include <memory>

class IDriver
{
  public:
    explicit IDriver(const std::string& name);
    ~IDriver();
    std::string getName();

  private:
    class Impl;
    //Impl *pImpl;
    //std::shared_ptr<Impl> pImpl;
    std::unique_ptr<Impl> pImpl;
};

std::ostream& operator<<(std::ostream& os, IDriver& idriver);

