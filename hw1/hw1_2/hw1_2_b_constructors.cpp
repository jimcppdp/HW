// default and non default constructor
#include <iostream>

using namespace std;

class Engine {
    public:
        Engine() {CC = 125; type=0; weight=100; }
        Engine(int cc) { CC = cc; type=0; weight=100;}
        void printEngine() {
            cout << "CC=" << CC << endl;
            cout << "type=" << type << endl;
            cout << "weight=" << weight << endl;    
        }
    private:
        int CC, type, weight;
};

int main(int argc, char const *argv[])
{
    Engine e;
    e.printEngine();
    
    Engine ee(100);
    ee.printEngine();
}

