#include <iostream>

using namespace std;

static int x; // 파일 스코프

int main()
{
    if (int num = 0)
    {
        cout << num << endl;
    }
    else
    {
        cout << num << endl;
    }

} // namespace std;
