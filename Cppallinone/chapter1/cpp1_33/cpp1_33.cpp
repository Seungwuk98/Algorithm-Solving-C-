#include <iostream>
#include <array>
#include <vector>

using namespace std;
int main()
{
    vector<int> vec0{3, 2, 1};
    vector<int> vec1{3, 2, 1, 0};
    if (vec0 == vec1)
        cout << "==";
    else if (vec0 > vec1)
        cout << ">";
    else
        cout << "<";
} // namespace std;
