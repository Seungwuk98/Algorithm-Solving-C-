#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
using Key = string;
using Value = string;
using KeyValue = pair<string, string>;

class Bucket
{
private:
    vector<KeyValue> _items;

public:
    Value &get(const Key &key)
    {
        for (KeyValue &keyValue : _items)
        {
            if (keyValue.first == key)
            {
                return keyValue.second;
            }
        }
        _items.push_back(std::make_pair(key, Value()));
        return _items.back().second;
    }
};

class HashTable
{
private:
    vector<Bucket> _buckets;

    int hash(const Key &key) const
    {
        int h = 0;
        for (char ch : key)
        {
            h += ch;
        }
        return h;
    }

public:
    HashTable(int size = 100) : _buckets(vector<Bucket>(size)){};

    Value &operator[](Key key)
    {
        int bucketIndex = hash(key) % _buckets.size();
        Bucket &bucket = _buckets[bucketIndex];
        return bucket.get(key);
    }
};

int main()
{
    HashTable hash;
    hash["abc"] = "def";

    cout << hash["abc"] << endl;

    hash["abc"] = "123";
    cout << hash["abc"] << endl;

    hash["cba"] = "456";
    cout << hash["abc"] << endl;
    cout << hash["cba"] << endl; 
} // namespace std;
