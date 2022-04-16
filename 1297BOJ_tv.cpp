#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int d, h, w;
    scanf("%d%d%d", &d, &h, &w);
    float x = float(d) / sqrt(float(h * h + w * w));
    int a, b;
    a = int(h * x);
    b = int(w * x);
    printf("%d %d", a, b);

} // namespace std;
