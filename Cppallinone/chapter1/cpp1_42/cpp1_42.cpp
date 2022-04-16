#include <iostream>
#include <functional>

using namespace std;

enum struct RequestType
{
    Login,
    Register,
    Update,
    Delete
};

bool onLogin(string id, string password)
{
    cout << "onLogin" << endl;
    cout << id << endl;
    cout << password << endl;
    return true;
}

bool onRegister(string id, string password)
{
    cout << "onRegister" << endl;
    cout << id << endl;
    cout << password << endl;
    return true;
}

bool onUpdate(string id, string password)
{
    cout << "onUpdate" << endl;
    cout << id << endl;
    cout << password << endl;
    return true;
}

bool onDelete(string id, string password)
{
    cout << "onDelete" << endl;
    cout << id << endl;
    cout << password << endl;
    return true;
}

struct Caracter
{
    int health;
    void (*dieCallback)();
};

void damaged(Caracter &character)
{
    character.health -= 100;
    if (character.health <= 0)
    {
        cout << "died" << endl;
        if (character.dieCallback)
            character.dieCallback();
    }
}

void gameOver()
{
    cout << "gameOver" << endl;
}

using real32 = float;
using real64 = double;
using FuncType = void(*)();



int main()
{
    bool (*callbacks[])(string, string){
        onLogin, onRegister, onUpdate, onDelete};

    callbacks[(int)RequestType::Login]("davie", "1234");
    callbacks[(int)RequestType::Register]("davie", "1234");
    callbacks[(int)RequestType::Update]("davie", "1234");
    callbacks[(int)RequestType::Delete]("davie", "1234");

    Caracter character0{200, nullptr};
    Caracter character1{200, gameOver};

    damaged(character0);
    damaged(character0);

    damaged(character1);
    damaged(character1);

    auto f = gameOver;
    auto& r = gameOver;
    f();

    function<void()> x = gameOver;
    x();
    FuncType y = gameOver;
    y();


} // namespace stdl
