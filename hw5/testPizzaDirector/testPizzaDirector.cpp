#include <string>
#include <iostream>
#include <memory>
#include <map>
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
    typedef IDriver* (*CreateCallback)();
    DriverFactory() {}

    static DriverFactory* get() { return Instance(); } ;

    static void registerDriver(std::string choice, CreateCallback cb)
    {
      mCallbackMap[choice]=cb;
    }

    static void unregisterDriver(std::string choice)
    {
      mCallbackMap.erase(choice);
    }

    static IDriver* create(std::string choice)
    {
      return mCallbackMap[choice]();
    }

  private:
    typedef std::map<std::string, CreateCallback> CallbackMap;
    static CallbackMap mCallbackMap;

};

DriverFactory::CallbackMap DriverFactory::mCallbackMap;

TEST(DriverFactoryTest, Creation)
{
  IDriver *pdriver = NULL;

  std::string driver_name ("mouse");

  //DriverFactory::registerCallback(driver_name , &mouse::create);
  DriverFactory::registerDriver(driver_name , mouse::create);

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

class Pizza
{
  public:
    explicit Pizza(std::string dough, std::string topping, std::string sauce)
    : mDough(dough), mTopping(topping), mSauce(sause)
    {}

    ~Pizza();
    std::string get_dough() {return mDough; }
    std::string get_topping() {return mTopping; };
    std::string get_sauce() {return mSauce; };

  private:
    std::string mDough;
    std::string mTopping;
    std::string mSauce;
};

class pizza_director: CSingleton<pizza_director> 
{
  public:
    PizzaBuilder pb;

    typedef IDriver* (*CreateCallback)();
    pizza_director() {}

    static pizza_director* get_instance() { return Instance(); } ;

    static void register_pizza_builder(std::string choice, CreateCallback cb)
    {
      mCallbackMap[choice]=cb;
    }

    static void unregister_pizza_builder(std::string choice)
    {
      mCallbackMap.erase(choice);
    }

    static Pizza* getPizza(std::string choice)
    {
      return mCallbackMap[choice]();
    }

  private:
    typedef std::map<std::string, CreateCallback> CallbackMap;
    static CallbackMap mCallbackMap;

};
pizza_director::CallbackMap pizza_director::mCallbackMap;

class IPizzaBuilder
{
  public:
};

class HawaiianPizzaBuilder: IPizzaBuilder
{
  public:


    static Pizza* create(std::string choice) {
      return new mouse();
    };
};

class Dough {
  public:
    std::string brand() { return mBrand; }
    Dough(std::string brand) { mBrand = brand; }

  private:
    std::string mBrand;
};

TEST(testPizzaDirector, CreationHawaiiPizza)
{

  //pizza_director::register_pizza_builder( “Hawaii” , &HawaiianPizzaBuilder::create);
  pizza_director::register_pizza_builder( “Hawaii” , HawaiianPizzaBuilder::create);

  Pizza pizza = pizza_director::get_instance->getPizza(“Hawaii”);
  Dough my_dough = pizza.get_dough();
  Topping my_topping = pizza.get_topping();
  Sauce my_sauce = pizza.get_sauce();
  EXPECT_EQ(my_dough.brand(), “CrisspyFlower”);
  //EXPECT_EQ(my_topping.name(), “Pineapple”);
  //EXPECT_EQ(my_sauce.type(), “mayo”);
}

TEST(testPizzaDirector, CreationSpicyCrazPizza)
{
#if 0
  pizza_director::register_pizza_builder( “SpicyCraz” , &HawaiianPizzaBuilder::create );

  Pizza pizza = pizza_director::get_instance->getPizza(“SpicyCraz”);
  Dough my_dough = pizza.get_dough();
  Topping my_topping = pizza.get_topping();
  Sauce my_sauce = pizza.get_sauce();
  EXPECT_EQ(my_dough.brand(), “ToughFlower”);
  EXPECT_EQ(my_topping.name(), “chili pepper”);
  EXPECT_EQ(my_sauce.type(), “sour sauce”);
#endif
}



