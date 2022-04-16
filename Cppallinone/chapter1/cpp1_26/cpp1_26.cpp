#include <iostream>
#include <array>

using namespace std;

struct Person
{
    float weight;
    float height;
};


int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    array<int, 5> arr1{1,2,3,4,5};
    for (int num : arr)
        cout << num << endl;
    for (int i : arr1)
        cout << i << endl;

    Person person[] = {
        Person{70.0f, 181.1f},
        Person{56.2f, 167.3f}
    };
    for (Person p : person)
        cout << p.height << " " << p.weight << endl;
        
} // namespace std;
