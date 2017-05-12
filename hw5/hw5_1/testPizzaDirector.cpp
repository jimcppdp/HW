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


class Dough {
  public:
    std::string brand() { return mBrand; }
    Dough(std::string brand) { mBrand = brand; }

  private:
    std::string mBrand;
};

class Topping {
  public:
    std::string name() { return mName; }
    Topping(std::string name) { mName = name; }

  private:
    std::string mName;
};


class Sauce {
  public:
    std::string type() { return mType; }
    Sauce(std::string type) { mType = type; }

  private:
    std::string mType;
};

class Pizza
{
  public:
    explicit Pizza(std::string dough, std::string topping, std::string sauce)
    : mDough(dough), mTopping(topping), mSauce(sauce)
    {}

    ~Pizza();
    Dough* get_dough() {return new Dough(mDough); }
    Topping* get_topping() {return new Topping(mTopping); };
    Sauce* get_sauce() {return new Sauce(mSauce); };

  private:
    std::string mDough;
    std::string mTopping;
    std::string mSauce;
};


class IPizzaBuilder
{
  public:
    virtual Pizza* getPizza() = 0;
};


class HawaiianPizzaBuilder: IPizzaBuilder
{
  public:
    HawaiianPizzaBuilder()
    {
      mPizza = new Pizza("", "", "");
    }

    Pizza* getPizza()
    {
      return mPizza;
    }

    static IPizzaBuilder* create() {
      return new HawaiianPizzaBuilder();
    }

  private:
    Pizza* mPizza;
};

class HawaiiPizzaBuilder: IPizzaBuilder
{
  public:
    HawaiiPizzaBuilder()
    {
      mPizza = new Pizza("CrisspyFlower", "Pineapple", "mayo");
    }

    Pizza* getPizza()
    {
      return mPizza;
    }

    static IPizzaBuilder* create() {
      return new HawaiiPizzaBuilder();
    }

  private:
    Pizza* mPizza;

};

class SpiceCrazPizzaBuilder: IPizzaBuilder
{
  public:
    SpiceCrazPizzaBuilder()
    {
      mPizza = new Pizza("ToughFlower", "chili pepper", "sour sauce");
    }

    Pizza* getPizza()
    {
      return mPizza;
    }

    static IPizzaBuilder* create() {
      return new SpiceCrazPizzaBuilder();
    }

  private:
    Pizza* mPizza;
};

class pizza_director: CSingleton<pizza_director> 
{
    typedef IPizzaBuilder* (*CreateCallback)();

  private:
    typedef std::map<std::string, CreateCallback> CallbackMap;
    static CallbackMap mCallbackMap;

    IPizzaBuilder* pb;

  public:

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

    Pizza* getPizza(std::string choice)
    {
      //return mCallbackMap[choice](choice);
      if (choice == "Hawaii") {
          pb = (IPizzaBuilder*)new HawaiiPizzaBuilder();
      }
      else if (choice == "SpicyCraz") {
          pb = (IPizzaBuilder*)new SpiceCrazPizzaBuilder();
      }
      else {
          pb = nullptr;
      }

      return pb->getPizza();
      
    }

};
pizza_director::CallbackMap pizza_director::mCallbackMap;


TEST(testPizzaDirector, CreationHawaiiPizza)
{

  // &HawaiianPizzaBuilder::create doesn't make sense
  //pizza_director::register_pizza_builder( “Hawaii” , &HawaiianPizzaBuilder::create);

  // original version, HawaiianPizzaBuilder::create works but doesn't make sense
  pizza_director::register_pizza_builder( "Hawaii" , HawaiianPizzaBuilder::create);

  // modify version, although HawaiiPizzaBuilder::create is not used at all
  // it can be extended in future version
  //pizza_director::register_pizza_builder( "Hawaii" , HawaiiPizzaBuilder::create);

  Pizza* pizza = pizza_director::get_instance()->getPizza("Hawaii");
  Dough* my_dough = pizza->get_dough();
  Topping* my_topping = pizza->get_topping();
  Sauce* my_sauce = pizza->get_sauce();
  EXPECT_EQ(my_dough->brand(), "CrisspyFlower");
  EXPECT_EQ(my_topping->name(), "Pineapple");
  EXPECT_EQ(my_sauce->type(), "mayo");
}

TEST(testPizzaDirector, CreationSpicyCrazPizza)
{
  // &HawaiianPizzaBuilder::create doesn't make sense
  //pizza_director::register_pizza_builder( “SpicyCraz” , &HawaiianPizzaBuilder::create );

  // original version, HawaiianPizzaBuilder::create works but doesn't make sense
  pizza_director::register_pizza_builder( "Hawaii" , HawaiianPizzaBuilder::create);

  // modify version, although SpiceCrazPizzaBuilder::create is not used at all
  // it can be extended in future version
  //pizza_director::register_pizza_builder( "SpicyCraz" , SpiceCrazPizzaBuilder::create);

  Pizza* pizza = pizza_director::get_instance()->getPizza("SpicyCraz");
  Dough* my_dough = pizza->get_dough();
  Topping* my_topping = pizza->get_topping();
  Sauce* my_sauce = pizza->get_sauce();
  EXPECT_EQ(my_dough->brand(), "ToughFlower");
  EXPECT_EQ(my_topping->name(), "chili pepper");
  EXPECT_EQ(my_sauce->type(), "sour sauce");
}



