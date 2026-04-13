#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>

template <typename K>
class IHashProvider
{
public:
    virtual size_t getV(const K &key) const = 0;
    virtual size_t hash(const K &key, int capacity) const = 0;
    virtual ~IHashProvider() = default;
};

class MathHashProvider : public IHashProvider<std::string>
{
public:
    size_t getV(const std::string &key) const override
    {
        size_t v = 0;
        for (char ch : key)
            v += (unsigned char)ch;
        return v;
    }
    size_t hash(const std::string &key, int capacity) const override
    {
        return getV(key) % capacity;
    }
};

template <typename K, typename V>
class HashTable
{
private:
    struct Entry
    {
        K key;
        V value;
    };
    std::vector<std::list<Entry>> table;
    const IHashProvider<K> &hashProvider;
    int capacity;
    int itemsCount;

public:
    HashTable(int cap, const IHashProvider<K> &hp)
        : capacity(cap), hashProvider(hp), itemsCount(0)
    {
        table.resize(capacity);
    }

    void insert(K key, V value)
    {
        size_t idx = hashProvider.hash(key, capacity);
        for (auto &entry : table[idx])
        {
            if (entry.key == key)
            {
                entry.value = value;
                return;
            }
        }
        table[idx].push_back({key, value});
        itemsCount++;
    }

    bool get(K key, V &outValue) const
    {
        size_t idx = hashProvider.hash(key, capacity);
        for (const auto &entry : table[idx])
        {
            if (entry.key == key)
            {
                outValue = entry.value;
                return true;
            }
        }
        return false;
    }

    bool remove(K key)
    {
        size_t idx = hashProvider.hash(key, capacity);
        auto &bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->key == key)
            {
                bucket.erase(it);
                itemsCount--;
                return true;
            }
        }
        return false;
    }

    void printExtended() const
    {
        std::cout << std::left << std::setw(6) << "Idx" << " | "
                  << std::setw(12) << "Key (ID)" << " | "
                  << std::setw(6) << "V(K)" << " | "
                  << std::setw(6) << "h(V)" << " | " << "Data" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        for (int i = 0; i < capacity; ++i)
        {
            if (table[i].empty())
            {
                std::cout << std::setw(6) << i << " | " << std::setw(12) << "---" << " | " << "---" << " | " << "---" << " | " << "FREE" << std::endl;
            }
            else
            {
                for (const auto &e : table[i])
                {
                    std::cout << std::setw(6) << i << " | "
                              << std::setw(12) << e.key << " | "
                              << std::setw(6) << hashProvider.getV(e.key) << " | "
                              << std::setw(6) << hashProvider.hash(e.key, capacity) << " | " << e.value << std::endl;
                }
            }
        }
    }

    int size() const { return itemsCount; }
    double getLoadFactor() const { return (double)itemsCount / capacity; }
};

#endif