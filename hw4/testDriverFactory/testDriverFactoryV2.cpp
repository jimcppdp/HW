#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class IDriver
{
  public:
    explicit IDriver(const std::string& name);
    ~IDriver();
    std::string getName();
    bool status_check() {
      return true;
    }

  private:
    class Impl;
    //Impl *pImpl;                  // version 1 regular pointer
    //std::shared_ptr<Impl> pImpl;  // version 2 shared_ptr
    std::unique_ptr<Impl> pImpl;    // version 3 unique_ptr
};


class IDriver::Impl
{
  public:
    std::string mName;
};

std::ostream& operator<<(std::ostream& os, IDriver& idriver)
{
  return os
  << "Driver Name=" << idriver.getName();
}

//IDriver::IDriver(const std::string& name) : pImpl(new IDriver::Impl())  // version 1
IDriver::IDriver(const std::string& name) : pImpl(std::make_unique<IDriver::Impl>())
{
  pImpl->mName = name;
}

IDriver::~IDriver()
{
  //delete pImpl;  // version 1
}

std::string IDriver::getName()
{
  return  pImpl->mName;
}


// CSingleton is from internet somewhere
template <typename T> 
class CSingleton
{
public:
    
    //! Gets a reference to the instance of the singleton class.
    /*!
        \return A reference to the instance of the singleton class.
        If there is no instance of the class yet, one will be created.
    */
    static T* Instance()
    {
        if (m_instance == NULL) {
            m_instance = new T;
        }
        
        assert(m_instance != NULL);

        return m_instance;
    };

    //! Destroys the singleton class instance.
    /*!
        Be aware that all references to the single class instance will be
        invalid after this method has been executed!
    */
    static void DestroyInstance()
    {
        delete m_instance;
        m_instance = NULL;
    };

protected:

    // shield the constructor and destructor to prevent outside sources
    // from creating or destroying a CSingleton instance.

    //! Default constructor.
    CSingleton()
    {
    };


    //! Destructor.
    virtual ~CSingleton()
    {
    };

private:

    //! Copy constructor.
    CSingleton(const CSingleton& source)
    {
    };

    static T* m_instance; //!< singleton class instance
};

//! static class member initialisation.
template <typename T> T* CSingleton<T>::m_instance = NULL;


class mouse: public IDriver
{
  public:
    mouse(): IDriver("mouse") {}

    static IDriver* create() {
      return new mouse();
    };
};

class DriverFactory: CSingleton<DriverFactory> 
{
  public:
    //typedef IDriver* (*CreateCallback)();
    DriverFactory() {}

    static DriverFactory* get() { return Instance(); } ;

    static void registerDriver(std::string choice, std::function<IDriver*()> cb)
    {
      mCallbackMap[choice]=cb;
    }

    static void unregisterDriver(std::string choice)
    {
      mCallbackMap.erase(choice);
    }

    IDriver* create(std::string choice)
    {
      return mCallbackMap[choice]();
    }

  private:
    typedef std::map<std::string, std::function<IDriver*()>> CallbackMap;
    static CallbackMap mCallbackMap;

};

DriverFactory::CallbackMap DriverFactory::mCallbackMap;

TEST(DriverFactoryTest, Creation)
{
  IDriver *pdriver = NULL;

  std::string driver_name ("mouse");

  DriverFactory::registerDriver(driver_name, &mouse::create);
  //DriverFactory::registerDriver(driver_name , mouse::create);

  pdriver = DriverFactory::get()->create(driver_name);
  if( pdriver )
  {
      EXPECT_EQ(pdriver->status_check(), true);
  }
  else
  {
      std::cout << "creation failed" << std::endl;
      ASSERT_TRUE(false);
  }

}


