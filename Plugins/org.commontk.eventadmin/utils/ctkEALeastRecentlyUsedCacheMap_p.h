#ifndef CTKEALEASTRECENTLYUSEDCACHEMAP_P_H
#define CTKEALEASTRECENTLYUSEDCACHEMAP_P_H

#include <QHash>
#include <QList>
#include <QMutex>

#include "ctkEACacheMap_p.h"

template <typename K, typename V>
class ctkEALeastRecentlyUsedCacheMap : public ctkEACacheMap<K, V, ctkEALeastRecentlyUsedCacheMap<K, V>>
{
private:
    mutable QMutex mutex;

    const int maxSize;

    QHash<K, V> cache;

    mutable QList<K> history;

public:
    typedef K KeyType;
    typedef V ValueType;

    ctkEALeastRecentlyUsedCacheMap(int maxSize);

    const V value(const K &key) const;

    const V value(const K &key, const V &defaultValue) const;

    void insert(const K &key, const V &value);

    const V remove(const K &key);

    int ssize() const;

    void clear();
};
#include "ctkEALeastRecentlyUsedCacheMap.tpp"
#endif // CTKEALEASTRECENTLYUSEDCACHEMAP_P_H