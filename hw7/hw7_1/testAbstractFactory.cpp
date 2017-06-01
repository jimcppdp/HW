// Non GoogleTest Version https://repl.it/IR7X/9 https://repl.it/IR7X/10
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

/*
Class abstract factory
{
  Virtual product* windowCreate() = 0;
  Virtual product* osxCreate() = 0;

}

Class concreteFactory
Class ButtonFactory
{
  Product windowCreate()
  {
    Return new winButton;
  }

  Product osxCreate()
  {
  }

}
*/


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
        
       // assert(m_instance != NULL);

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

class factory;
typedef std::function<factory*()> CreateCallback;
//typedef factory* (*CreateCallback)();

class CarPart
{
  private:
    std::string _name;
    
  public:
    CarPart(std::string p) : _name(p) { }
    
    std::string get_info() { return _name; }
};

class factory
{
  public:
    virtual std::string getName() = 0;
    virtual std::string create_wheel() = 0;
    virtual std::string create_frame() = 0;
};


class WoodenFactory : public factory, CSingleton<WoodenFactory> 
{
  private:
    std::string _name;
    
  public:
    
    WoodenFactory() : _name("wooden") { }
    std::string getName() { return _name; }
  
    static factory* get_instance() { return Instance(); }

    virtual std::string create_wheel() { return getName(); }
    virtual std::string create_frame() { return getName(); }
};

class SteelFactory : public factory, CSingleton<SteelFactory> 
{
  private:
    std::string _name;
    
  public:
  
    SteelFactory() : _name("steel") { }
    std::string getName() { return _name; }
  
    static factory* get_instance() { return Instance(); }
    
    virtual std::string create_wheel() { return getName(); }
    virtual std::string create_frame() { return getName(); }
};


class CarPartFactory : CSingleton<CarPartFactory> 
{
  public:
  
    static CarPartFactory* get_instance() { return Instance(); }


    static void register_factory(factory* instance)
    {
      mCallbackMap[instance->getName()] = instance;
    }
  
    virtual CarPart* create_wheel(std::string w) 
    { 
      return new CarPart("CarPart: " + mCallbackMap[w]->create_wheel() + " wheel");
    }
    
    virtual CarPart* create_frame(std::string f) 
    { 
      return new CarPart("CarPart: " + mCallbackMap[f]->create_frame() + " frame");
    }
    
  private:
    typedef std::map<std::string, factory*> CallbackMap;
    static CallbackMap mCallbackMap;
  
};
CarPartFactory::CallbackMap CarPartFactory::mCallbackMap;


TEST(testAbstractFactory, UseCase1)
{
  CarPartFactory::get_instance()->register_factory(WoodenFactory::get_instance());
  CarPartFactory::get_instance()->register_factory(SteelFactory::get_instance());
	
  CarPart* wooden_wheel = CarPartFactory::get_instance()->create_wheel("wooden");
  CarPart* steel_wheel  = CarPartFactory::get_instance()->create_wheel("steel");
  CarPart* wooden_frame = CarPartFactory::get_instance()->create_frame("wooden");
  CarPart* steel_frame  = CarPartFactory::get_instance()->create_frame("steel");

  EXPECT_EQ("CarPart: wooden wheel", wooden_wheel->get_info());
  EXPECT_EQ("CarPart: wooden frame", wooden_frame->get_info());
  EXPECT_EQ("CarPart: steel wheel", steel_wheel->get_info());
  EXPECT_EQ("CarPart: steel frame", steel_frame->get_info());

  delete wooden_wheel;
  delete steel_wheel;
  delete wooden_frame;
  delete steel_frame;
}


