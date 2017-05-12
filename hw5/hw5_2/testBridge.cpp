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

  protected:
    DrawApi* mDrawApi;
};

class Triangle: public Shape
{
  public:
    Triangle(DrawApi* dapi): Shape(dapi) {}

    std::string draw() { return mDrawApi->draw(); }
};

class Circle: public Shape
{
  public:
    Circle(DrawApi* dapi): Shape(dapi) {}

    std::string draw() { return mDrawApi->draw(); }
};

    

TEST(testBridge, BridgeShapeDraw)
{
  Shape* triangle = new Triangle( new OpenGL_api );
  Shape* circle = new Circle( new DirectX_api );
  EXPECT_EQ(triangle->draw(), "using OpenGL to draw");
  EXPECT_EQ(circle->draw(), "using DirectX to draw");
  delete triangle;
  delete circle;
}



