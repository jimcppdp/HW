#include <iostream>

using namespace std;

class Engine {
    public:
        ~Engine() {
            cout << "destructor" << endl;
        }
    
        Engine() {
            cout << "default constructor" << endl;
            CC = 125; type=0; weight=100; 
        }
        
        Engine(int cc) { 
            cout << "constructor" << endl;
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

int main(int argc, char const *argv[])
{
    Engine e;
    e.printEngine();
    
    //Engine ee(100);
    //ee.printEngine();
    
    //Engine eee = ee;
    //eee.printEngine();
    
    //Engine eeee;
    //eeee = eee;
    //eeee.printEngine();
    
    //original version  
    //Engine eeeee = std::move(e);
    //Reference static_cast<typename> remove_reference<T>::type&&>(t);
    // New Version
    Engine eeeee = (Engine &&)e;

    eeeee.printEngine();
    
}

