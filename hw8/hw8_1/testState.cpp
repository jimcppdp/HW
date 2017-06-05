#include <iostream>
#include <map>
using namespace std;

double result;

class Machine
{
  class State *current;
  
  public:
    Machine();
    ~Machine();
    std::map <char, double> gen_prob_1;
    std::map <char, double> gen_prob_2;
    
    void setCurrent(State *s)
    {
        current = s;
    }
    void go0(char);
    void go1(char);
    void go2(char);
};

class State
{
  public:
    virtual void go0(Machine *m, char c)
    {
      cout << "1(initial) * ";
      result = 1;
      cout << m->gen_prob_1[c] << " (state1 emits " << c << ") ";
      result = result * m->gen_prob_1[c];
      //cout << "\ncurrent result = " << result << "\n";
    }
    virtual void go1(Machine *m, char c)
    {
      cout << "* 0.99 (state1->state1) * ";
      result = result * 0.99;
      cout << m->gen_prob_1[c] << " (state1 emits " << c << ") ";
      result = result * m->gen_prob_1[c];
      //cout << "\ncurrent result = " << result << "\n";
    }
    virtual void go2(Machine *m, char c)
    {
      cout << "* 0.9 (state2->state2) * ";
      result = result * 0.9;
      cout << m->gen_prob_2[c] << " (state2 emits " << c << ") ";
      result = result * m->gen_prob_2[c];
      //cout << "\ncurrent result = " << result << "\n";
    }
};

void Machine::go0(char c)
{
  current->go0(this, c);
}

void Machine::go1(char c)
{
  current->go1(this, c);
}

void Machine::go2(char c)
{
  current->go2(this, c);
}

class ST1: public State
{
  public:
    ST1()
    {
    };
    
    ~ST1()
    {
    };
    
    void go2(Machine *m, char c);
};

class ST2: public State
{
  public:
    ST2()
    {
    };
    
    ~ST2()
    {
    };
    
    void go1(Machine *m, char c)
    {
        cout << "* 0.1 (state2->state1) * ";
        result = result * 0.1;
        cout << m->gen_prob_1[c] << " (state1 emits " << c << ") ";
        result = result * m->gen_prob_1[c];
        //cout << "\ncurrent result = " << result << "\n";
        m->setCurrent(new ST1());
        delete this;
    }
};

void ST1::go2(Machine *m, char c)
{
  cout << "* 0.01 (state1->state2) * ";
  result = result * 0.01;
  cout << m->gen_prob_2[c] << " (state2 emits " << c << ") ";
  result = result * m->gen_prob_2[c];
  //cout << "\ncurrent result = " << result << "\n";
  m->setCurrent(new ST2());
  delete this;
}

Machine::Machine()
{
  current = new ST1();
  cout << '\n';
}

Machine::~Machine()
{ 
  delete current;
}

int main()
{
  Machine fsm;
  
  fsm.gen_prob_1['A'] = 0.4;
  fsm.gen_prob_1['C'] = 0.1;
  fsm.gen_prob_1['G'] = 0.1;
  fsm.gen_prob_1['T'] = 0.4;
  
  fsm.gen_prob_2['A'] = 0.05;
  fsm.gen_prob_2['C'] = 0.4;
  fsm.gen_prob_2['G'] = 0.5;
  fsm.gen_prob_2['T'] = 0.05;
  
	string state  = "01221121";   // first 1 change to 0 for initial state
  string symbol = "ATCGTACG";

	for (int i=0; i<state.size(); i++)
	{
	  switch (state[i])
	  {
	    case '0':
	      fsm.go0(symbol[i]);
	      break;
	    case '1':
	      fsm.go1(symbol[i]);
	      break;
	    case '2':
	      fsm.go2(symbol[i]);
	      break;
	  }
	}
	
	cout << "\n\nresult = " << result << "\n";

}

