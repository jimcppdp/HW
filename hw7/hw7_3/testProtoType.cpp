// Non GoogleTest Version https://repl.it/IR7X/2
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class prototype
{
  public:
    virtual prototype* clone() = 0;
};

class Image
{
  public:
    virtual Image* clone() = 0;
    virtual std::string info() = 0;
};

class DogImage : public Image
{
  private:
    std::string _name;
  
  public:
    DogImage(std::string name) 
      : _name(name)
    { }
    
    virtual Image* clone()
    {
      return new DogImage(*this);
    }
    
    virtual std::string info()
    {
      return "dog image: " + _name;
    }

};

class CatImage : public Image
{
  private:
    std::string _name;
  
  public:
    CatImage(std::string name) 
      : _name(name)
    { }
    
    virtual Image* clone()
    {
      return new CatImage(*this);
    }
    
    virtual std::string info()
    {
      return "cat image: " + _name;
    }

};



TEST(testComposite, UseCase1)
{
  std::vector<Image*> all_images;
  all_images.push_back ( new DogImage("big") );
  all_images.push_back ( new CatImage("small") );
  all_images.push_back ( new DogImage("huge") );
  Image* my_image = all_images[1]->clone();
  EXPECT_EQ( "cat image: small", my_image->info() );
  my_image = all_images[2]->clone();
  EXPECT_EQ( "dog image: huge", my_image->info() );  
}


