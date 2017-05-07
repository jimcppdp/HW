// pimpl.cpp
// below can be run on Linux/MacOS to detect c/c++ memory leak
// valgrind --leak-check=full ./pimpl

#include "driver.h"
#include <memory>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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

//IDriver::IDriver(const std::string& name) : pImpl(new IDriver::Impl())
IDriver::IDriver(const std::string& name) : pImpl(std::make_unique<IDriver::Impl>())
{
  std::cout << "IDriver constructor called\n";
  pImpl->mName = name;
}

IDriver::~IDriver()
{
  std::cout << "IDriver destructor called\n";
  //delete pImpl;
}

std::string IDriver::getName()
{
  return   pImpl->mName;
}


public Mouse: public IDriver
{
}

public Unknown: public IDriver
{
}

Class DriverFactorySimpleVersion
{
  Public:
    Static IDriver* create(std::string choice)
    {
      If (choice == “mouse”) 
        return new Mouse;
      Esle
        Return new Unknown;
     }
}


class Global
{
  int m_value;
  static Global* s_instance;
  Global() {};
  
public:
  int getValue() { return m_value; };
  void setValue(int value) { m_value = value; };
  
  static Global *instance()
  {
      if (!s_instance)
        s_instance = new Global;
      return s_instance;
  }
};
Global *Global::s_instance = 0;



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
            cout << "m_instance is NULL" << endl;
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


class DriverFactory: public CSingleton<DriverFactory> 
{
  Public:
    std::map<std::string, std::functor<IDriver*()> > callbackmap;
    IDriver* register(std::string, std::functor);

  static DriverFactory *instance()
  {
      if (!s_instance)
        s_instance = new Global;
      return s_instance;
  }	

  Static IDriverIDriver* create(std::string choice)
  {
    return callbackmap[choice]();
  }
};



TEST_Driver_Factory (DriverFactoryTest, Creation)
{
	
  IDriver *pdriver = NULL;

  std::string driver_name (“mouse”);

  DriverFactory::register(driver_name , &mouse::create);

  pdriver = DriverFactory::get()->create(driver_name);
  if( pdriver )
  {
      EXPECT_EQ(pdriver->status_check(), true);
  }
  else
  {
      cout << “creation failed” << endl;
  }

}


