#include <iostream>

using namespace std;

class Engine {
    public:
        Engine() {
            cout << "default constructor" << endl;
            CC = 125; type=0; weight=100; 
        }
        
        Engine(int cc) { 
            cout << "Init CC only constructor" << endl;
            CC = cc; type=0; weight=100;
        }
        
        Engine(const Engine &obj) {
            cout << "copy constructor" << endl;
            CC = obj.CC; type = obj.type; weight = obj.weight;
        }
        
        Engine& operator=(Engine obj) {
            cout << "copy assignment operator" << endl;
            CC = obj.CC; type = obj.type; weight = obj.weight;
            return *this;
        }
        
        Engine ( Engine && obj) noexcept {
            cout << "move constructor" << endl;
            CC = move(obj.CC);
            type = move(obj.type);
            weight = move(obj.weight);
        }
        
        void printEngine() {
            cout << "CC=" << CC << endl;
            cout << "type=" << type << endl;
            cout << "weight=" << weight << endl;    
        }
   
    private:
        int CC, type, weight;
};

class Car {
    public:
        Car(Engine &e) 
           : my_engine(e) { 
          //  {
            cout << "Car constructor" << endl;
          //  my_engine = e;
        }
        
    friend void check_engine(Car& car);
    void check_my_engine();

    private:
        Engine my_engine;
        
};

void check_engine(Car& car)
{
    car.my_engine.printEngine();
}

void Car::check_my_engine()
{
    my_engine.printEngine();
}

class Police {
  public:
    static void check_car(Car&);
};

void Police::check_car(Car& car)
{
  //check_engine(car);        // version 1
  car.check_my_engine();      // version 2
}

int main(int argc, char const *argv[])
{
    Engine e(50);
    //e.printEngine();
    Car car(e);
    check_engine(car);
    
    /*
    Engine ee(100);
    ee.printEngine();
    
    Engine eee = ee;
    eee.printEngine();
    
    Engine eeee;
    eeee = eee;
    eeee.printEngine();
    
    Engine eeeee = std::move(e);
    eeeee.printEngine();
    */
    
    //Car car(e);
    //check_engine(car);
    //car.check_my_engine();
    
    //Police::check_car(car);
    
}
