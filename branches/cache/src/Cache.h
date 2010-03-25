/**
 * @file Cache.h
 *
 * A generic cache class - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.6.0
 * @since 2.6.0
 */

#ifndef CACHE_H
#define CACHE_H

//#define AQUILA_CACHE_STATS 0

#include <map>
#ifdef AQUILA_CACHE_STATS
#include <iostream>
static int s_cacheHits = 0, s_cacheLookups = 0;
#endif


namespace Aquila
{
    /**
     * A generic calculation cache.
     *
     * The cache class holds results of possibly expensive calculations, for
     * example intermediate values in FFT transform. The values (which can
     * be scalars, C-style arrays, vectors etc.) are identified by a cache
     * key of type Cache::KeyType.
     *
     * Cache object constructor call needs to be supplied with a generator
     * function. It can be a standalone function or a static class method
     * which takes a const reference to a cache key type and returns a value
     * of the cache value type. For example, if the cache stores integer
     * values identified by a string, the generator signature should match
     * int generate(const string& key).
     */
    template <typename K, typename V>
    class Cache
    {
    public:
        /**
         * Cache key type.
         */
        typedef K KeyType;

        /**
         * Cache value type.
         */
        typedef V ValueType;

        /**
         * Generator function pointer type.
         */
        typedef ValueType (*GeneratorFunction)(const KeyType&);

        /**
         * Creates the cache and sets the pointer to a generator function.
         *
         * @param fn a pointer to a generator function or static class method
         */
        Cache(GeneratorFunction fn): generator(fn) {}

        /**
         * Clears the cache.
         *
         * If AQUILA_CACHE_STATS is defined, displays a small cache lookup stats
         * to stdout.
         */
        ~Cache()
        {
#ifdef AQUILA_CACHE_STATS
            std::cout << "[Aquila::Cache] hits/lookups: " << s_cacheHits <<
                "/" << s_cacheLookups << ", hit rate: " <<
                100 * s_cacheHits / static_cast<double>(s_cacheLookups) << "%\n";
#endif
        }

        /**
         * Returns a value associated with the given key.
         *
         * If the value is in cache, it is returned immediately. In other case,
         * the generator function is called with the key as the argument and
         * its return value is stored in cache and returned to the caller.
         *
         * @param key cache key
         * @return cache value
         */
        ValueType get(const KeyType& key)
        {
#ifdef AQUILA_CACHE_STATS
            s_cacheLookups++;
#endif
            if (m_map.find(key) != m_map.end())
            {
#ifdef AQUILA_CACHE_STATS
            s_cacheHits++;
#endif
                return m_map[key];
            }

            ValueType result = generator(key);
            m_map[key] = result;
            return result;
        }

    private:
        /**
         * A pointer to generator function.
         */
        GeneratorFunction generator;

        /**
         * Internal representation of the cache as a key-value map.
         */
        std::map<KeyType, ValueType> m_map;
    };
}


#endif // CACHE_H
