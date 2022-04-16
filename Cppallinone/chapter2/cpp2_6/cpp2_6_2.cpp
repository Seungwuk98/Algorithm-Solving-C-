#include <iostream>

using namespace std;

struct Transaction
{
    const int txID;
    const int fromID;
    const int toID;
    const int value;

    class Builder
    {
    private:
        int _fromID;
        int _toID;
        int _value;

    public:
        Transaction build()
        {
            int txID = _fromID ^ _toID ^ _value;
            return Transaction{txID, _fromID, _toID, _value};
        }
        Builder &setFromID(int fromID)
        {
            _fromID = fromID;
            return *this;
        }
        Builder &settoID(int toID)
        {
            _toID = toID;
            return *this;
        }
        Builder &setvalue(int value)
        {
            _value = value;
            return *this;
        }
    };
};

int main()
{
    Transaction builder = Transaction::Builder().setFromID(1212).settoID(4321).setvalue(12232).build();

} // namespace std;
