template <typename K, typename V>
ctkEALeastRecentlyUsedCacheMap<K, V>::ctkEALeastRecentlyUsedCacheMap(int maxSize)
  : maxSize(maxSize)
{
    if(0>=maxSize)
    {
        throw ctkInvalidArgumentException("maxSize must be greater than 0");
    }
    cache.reserve(((maxSize+1)*4)/3);
}

template <typename K, typename V>
const V ctkEALeastRecentlyUsedCacheMap<K, V>::value(const K& key) const
{
    QMutexLocker locker(&mutex);
    if(cache.contains(key))
    {
        history.removeAll(key);
        history.push_back(key);
        return cache.value(key);
    }

    return V();
}

template <typename K, typename V>
const V   ctkEALeastRecentlyUsedCacheMap<K, V>::value(const K& key, const V& defaultValue) const
{
    QMutexLocker locker(&mutex);
    if(cache.contains(key))
    {
        history.removeAll(key);
        history.push_back(key);
        return cache.value(key);
    }

    return defaultValue;
}


template <typename K, typename V>
void ctkEALeastRecentlyUsedCacheMap<K, V>::insert(const K& key, const V& value)
{
    QMutexLocker locker(&mutex);
    if(cache.contains(key))
    {
        cache.removeAll(key);
    }

    cache.insert(key, value);
    history.push_back(key);

    if(maxSize<cache.size())
    {
        cache.remove(history.takeFirst());
    }
}

template <typename K, typename V>
const V ctkEALeastRecentlyUsedCacheMap<K, V>::remove(const K& key)
{
    QMutexLocker locker(&mutex);
    if(cache.contains(key))
    {
        history.removeAll(key);
    }

    return cache.take(key);
}

template <typename K, typename V>
int ctkEALeastRecentlyUsedCacheMap<K, V>::size() const
{
    QMutexLocker locker(&mutex);
    return cache.size();
}

template <typename K, typename V>
void ctkEALeastRecentlyUsedCacheMap<K, V>::clear()
{
    QMutexLocker locker(&mutex);
    cache.clear();
    history.clear();
}

