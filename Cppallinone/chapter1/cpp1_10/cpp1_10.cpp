#include <iostream>
#include <cstdio>

int main()
{
    printf("Hello %d\n", 10);
    printf("%d + %d = %i\n", 2, 3, 2 + 3);
    printf("%c%c\n", 'a', 'b');
    printf("%f - %f = %lf\n", 2.0, 3.0f, -1.0f);
    printf("%hhx\n", 256);

    printf("%-10da\n", 1);
    printf("%-10da\n", -1);
    printf("%-10.1fa\n", 1.1);
    printf("%-10.1fa\n", -1.1);
    printf("%%");

    freopen("output.txt", "w", stdout);
    printf("Hello World");
}