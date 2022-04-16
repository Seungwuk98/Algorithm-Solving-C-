#include <iostream>
using namespace std;
enum TextAttribute
{
    Bold = 1,
    Underline = 2,
    Italic = 4,
    Strikethrough = 8
};

enum struct CircleAttribute{
    Bold = 1
};

int main()
{
    TextAttribute::Bold;

} // namespace std;
