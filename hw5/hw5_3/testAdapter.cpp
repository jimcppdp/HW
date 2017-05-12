#include <string>
#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class DrawApi
{
  public:
    virtual std::string draw() = 0;
};

class OpenGL_api: public DrawApi
{
  public:
    std::string draw() { return "using OpenGL to draw"; }
};
    
class DirectX_api: public DrawApi
{
  public:
    std::string draw() { return "using DirectX to draw"; }
};

class Shape
{
  public:
    Shape(DrawApi* dapi) { mDrawApi = dapi; }
    virtual std::string draw() = 0;
    friend class AdapterTriangle;

  protected:
    DrawApi* mDrawApi;
};

class Triangle: public Shape
{
  public:
    Triangle(DrawApi* dapi): Shape(dapi)
    {
    }

    std::string draw() { return mDrawApi->draw(); }
};

class Circle: public Shape
{
  public:
    Circle(DrawApi* dapi): Shape(dapi) {}

    std::string draw() { return mDrawApi->draw(); }
};


class NewShape
{
  public:
    virtual std::string newdraw() = 0;

};

class AdapterTriangle: public NewShape, private Triangle
{
  public:

    AdapterTriangle(Triangle* tri): Triangle(tri->mDrawApi), mTriangle(tri) 
    { 
    }

    std::string newdraw()
    {
       return mTriangle->draw();
    }

  private:
    Triangle* mTriangle;
};

TEST(testAdapter, AdapterNewDraw)
{
  NewShape* newtriangle = new AdapterTriangle( new Triangle ( new OpenGL_api) );
  EXPECT_EQ(newtriangle->newdraw(), "using OpenGL to draw");
  delete newtriangle;
}

