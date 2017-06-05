#include <string>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class Square;
class Circle;

class visitor
{
  public:
    virtual double visit(Square *e) = 0;
    virtual double visit(Circle *e) = 0;
};

class Vistable_Item
{
  public:
    virtual double accept(class visitor* v) = 0;
};

class Square: public Vistable_Item
{
  private:
    int _value;
    
  public:
     virtual double accept(visitor* v) 
     { 
       return v->visit(this);
     }
     
    Square(int v)
      : _value(v) 
    { }
     
};

class Circle: public Vistable_Item
{
  private:
    int _value;
    
  public:
     virtual double accept(visitor* v)
     { 
       return v->visit(this);
     }
     
    Circle(int v)
      : _value(v) 
    { }
     
};



class get_area_vistor: public visitor
{
    virtual double visit(Square *e)
    {
        return 100;
    }

    virtual double visit(Circle *e)
    {
        return 78.5;
    }
};

class get_perimeter_vistor: public visitor
{
    virtual double visit(Square *e)
    {
        return 40;
    }

    virtual double visit(Circle *e)
    {
        return 31.4;
    }
};



TEST(testVisitor, UseCase1)
{
	std::vector<Vistable_Item*> items;
	items.push_back (new Square(10));
	items.push_back(new Circle(5));
	visitor* v = new get_area_vistor;
  EXPECT_EQ(items[0]->accept(v),100);
  EXPECT_EQ(items[1]->accept(v),78.5);

  delete items[0];
  delete items[1];
  delete v;
}

TEST(testVisitor, UseCase2)
{
	std::vector<Vistable_Item*> items;
	items.push_back (new Square(10));
	items.push_back(new Circle(5));
	visitor* v = new get_perimeter_vistor;
  EXPECT_EQ(items[0]->accept(v),40);
  EXPECT_EQ(items[1]->accept(v),31.4);

  delete items[0];
  delete items[1];
  delete v;
}


