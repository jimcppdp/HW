// insertion sort
#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &a);
void insertionSort(vector<int> &data, int n); 

void printVector(vector<int> a);

int main(int argc, char const *argv[])
{
    vector<int> a{3,2,6,1};
    printVector(a);

    //bubbleSort(a);
    insertionSort(a, 4);
    printVector(a);
}

void bubbleSort(vector<int> &a)
{
    bool swapp = true;
    while(swapp)
    {
        swapp = false;
        for (int i = 0; i < a.size()-1; i++)
        {
            if (a[i]>a[i+1] )
            {
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}

void insertionSort (vector<int> &data, int n) 
{
int i, j, tmp;

 for (i=1; i<n; i++)
 {
     j=i;
     tmp=data[i];
     while (j>0 && tmp<data[j-1])
     {
           data[j]=data[j-1];
           j--;
     }
     data[j]=tmp;
 }
}

void printVector(vector<int> a)
{
    for (int i=0;  i <a.size();  i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

