#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

#include <iomanip>
#include <ctime>

using namespace std;
using namespace std::chrono;

#define YEAR1900 70+24*17
//#define YEAR2000 31+24*7

#define YEAR2000 70+24*20

#define TEST 1
#if TEST
  #define ITEM_COUNT 10  // for test only
#else
  #define ITEM_COUNT 100000
#endif


class TRADE_DATE {
  public:
    int ID;
    tuple <int, int, int> begin_date;
    tuple <int, int, int> end_date;
    int duration;
    system_clock::time_point tp_begin_date;
    system_clock::time_point tp_end_date;
    
    bool operator < (TRADE_DATE b) {
      return (this->begin_date < b.begin_date);
    }
    
    bool operator > (TRADE_DATE b) {
      return (this->begin_date > b.begin_date);
    }    

    bool operator == (TRADE_DATE b) {
      return (this->ID == b.ID);
    }     
};


void print_tds(std::vector<TRADE_DATE> tds)
{
  for (auto td : tds) {
      std::cout << td.ID << " : " << td.duration << " : " << 
        std::get<0>(td.begin_date) << " : " << 
        std::get<1>(td.begin_date) << " : " << 
        std::get<2>(td.begin_date) << " : " <<
        std::get<0>(td.end_date) << " : " << 
        std::get<1>(td.end_date) << " : " << 
        std::get<2>(td.end_date) << '\n';
  }
  cout << '\n';
}

void print_tds_diff_days(TRADE_DATE ttd, std::vector<TRADE_DATE> tds)
{
  for (auto td : tds) {
    std::time_t tt = system_clock::to_time_t(ttd.tp_begin_date);
    
    std::cout << "TRADE_DATA ID: " << ttd.ID << " overlaps with TRADE_DATE ID: " << td.ID << " by " <<
      std::chrono::duration_cast<std::chrono::hours>
        (std::max(ttd.tp_begin_date, td.tp_end_date) - 
        std::min(ttd.tp_begin_date, td.tp_begin_date)).count()/24 <<
        " days" << '\n';
  }
  cout << '\n';
}
        


template <class T>
class uniform_time_distribution{
public:
  uniform_time_distribution(T start, T end)
    : m_start(start), m_end(end),
    m_seconds(std::chrono::duration_cast<std::chrono::seconds>(end - start))
  {}

  template <class Generator>
  T operator()(Generator && g){
    std::uniform_int_distribution<std::chrono::seconds::rep> d(0, m_seconds.count());

    return m_start + std::chrono::seconds(d(g));
  }

private:
  T m_start;
  T m_end;
  std::chrono::seconds m_seconds;
};

template <class T>
T randomTime(T start, T end){
  static std::random_device rd;
  static std::mt19937 gen(rd());

  uniform_time_distribution<T> t(start, end);

  return t(gen);
}

void randomGenerator(std::vector<TRADE_DATE>& tds)
{
  
  time_point <system_clock,duration<int>> tp_seconds (duration<int>(0));
  system_clock::time_point tp (tp_seconds);
  system_clock::time_point rand_begin = tp + hours(24 * 365 * YEAR1900);
  system_clock::time_point rand_end = tp + hours(24 * 365 * YEAR2000);

  std::random_device rd;
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> dis1(1, 10);

  for (int n = 0; n < ITEM_COUNT; ++n) {
    TRADE_DATE td;
    auto time = randomTime(rand_begin, rand_end);
    td.tp_begin_date = time;
    auto ttime = system_clock::to_time_t(time);
    tm utc_tm = *gmtime(&ttime); 

    td.duration = dis1(gen);
    td.ID = n;
    int begin_year = utc_tm.tm_year + 1900;
    int begin_month = utc_tm.tm_mon + 1;
    int begin_day = utc_tm.tm_mday;
    auto end_time = time + hours(24*td.duration);
    td.tp_end_date = end_time;
    auto tend_time = system_clock::to_time_t(end_time);
    utc_tm = *gmtime(&tend_time);     
    int end_year = utc_tm.tm_year + 1900;
    int end_month = utc_tm.tm_mon + 1;
    int end_day = utc_tm.tm_mday;
    td.begin_date = make_tuple(begin_year, begin_month, begin_day);
    td.end_date = make_tuple(end_year, end_month, end_day);
    tds.push_back(td); 
  }
  
}


bool myfunction (TRADE_DATE a,TRADE_DATE b)
{ 
  return a.begin_date < b.begin_date;
}


class intersection_finder {
  
  public:

    void operator_sort(std::vector<TRADE_DATE> &tds) {
      std::sort(tds.begin(), tds.end());
    }

    void functor_sort(std::vector<TRADE_DATE> &tds) {
      // sort using a custom function object
      
      struct {
        bool operator()(TRADE_DATE a, TRADE_DATE b)
        {   
            return a.begin_date < b.begin_date;
        }   
      } customLess;
      
      std::sort(tds.begin(), tds.end(), customLess);
    }
    
    void lambda_sort(std::vector<TRADE_DATE> &tds) {
      // sort using a lambda expression
      std::sort(tds.begin(), tds.end(), [](TRADE_DATE a, TRADE_DATE b) {
          return ((a.begin_date < b.begin_date) ||
           ((a.begin_date == b.begin_date) && (a.end_date < b.end_date)));

      });
    }
    
    void run(std::vector<TRADE_DATE> &tds) {
      lambda_sort(tds);
      
      for (auto td : tds) {
        std::vector<TRADE_DATE> to_tds;
        auto lower = std::lower_bound(tds.begin(), tds.end(), td, myfunction);
        auto upper = std::upper_bound(tds.begin(), tds.end(), td, myfunction);
        
        std::copy(lower, upper, std::back_inserter(to_tds)); 

        auto it = std::find(to_tds.begin(), to_tds.end(), td);
        to_tds.erase(it);
        
        print_tds_diff_days(td, to_tds);

        std::cout << '\n';
      }
    }

};


  
int main(int argc, char const *argv[])
{
  std::vector<TRADE_DATE> tds;
  
  randomGenerator(tds);
  print_tds(tds);
  
  //std::sort (tds.begin(), tds.end(), myfunction);
  
  intersection_finder ifinder;
  //ifinder.functor_sort(tds);
  //ifinder.operator_sort(tds);
  //ifinder.lambda_sort(tds);
  
  ifinder.run(tds);
  
  print_tds(tds);
}