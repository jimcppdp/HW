#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &a);
void recursiveBubbleSort(vector<int> &arr, int first, int last);

void printVector(vector<int> a);

int main(int argc, char const *argv[])
{
    vector<int> a{3,2,6,1};
    printVector(a);

    //bubbleSort(a);
    recursiveBubbleSort(a, 0, 3);
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

void recursiveBubbleSort(vector<int> &arr, int first, int last){

    if(first < last && last > 0){
        if(arr[first] > arr[first+1]){
            int temp = arr[first];
            arr[first] = arr[first+1];
            arr[first+1] = temp;
        }
        recursiveBubbleSort(arr, first+1, last);
        recursiveBubbleSort(arr, first, last-1);
    }
    else
        return;
}

void printVector(vector<int> a)
{
    for (int i=0;  i <a.size();  i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
