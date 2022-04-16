#include <iostream>
#include <array>
using namespace std;
int main()
{
    array<int, 5> arr{1,2,3,4,5};
    array<int, 5> arr1{5,4,3,2,1};

    array<char, 6> arr0{"abcde"};
    

    if (arr == arr1)
        cout << "Equal" << endl;

    if (arr > arr1)
        cout << ">" << endl;
    
    if (arr < arr1)
        cout << "<" << endl;
    for (int i =0; i<arr.size(); i++)
        cout << arr[i];
    cout << endl;

    for (int i=0; i<arr1.size(); i++)
        cout << arr1[i];
    cout << endl;


} // namespace std;
