#include "HashTable.h"

template <typename K, typename V>
HashTable<K, V>::HashTable(int cap, const IHashProvider<K> &hp)
    : capacity(cap), hashProvider(hp), itemsCount(0)
{
    table.resize(capacity);
}

template <typename K, typename V>
void HashTable<K, V>::insert(K key, V value)
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

template <typename K, typename V>
bool HashTable<K, V>::get(K key, V &outValue) const
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

template <typename K, typename V>
bool HashTable<K, V>::remove(K key)
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

template <typename K, typename V>
void HashTable<K, V>::printExtended() const
{
    for (int i = 0; i < capacity; ++i)
    {
        std::cout << "[" << i << "]: ";
        for (const auto &entry : table[i])
        {
            std::cout << "{" << entry.key << ":" << entry.value << "} -> ";
        }
        std::cout << "null\n";
    }
}