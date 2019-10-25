#ifndef FLEXIBUZZ_H
#define FLEXIBUZZ_H 1

#include <functional>
#include <map>

template<class K, class V, class Map>
class flexibuzz
{
private:

    template<typename T>
    using const_iter_t = typename std::iterator_traits<typename T::const_iterator>::value_type;

public:

    flexibuzz(
        std::function<bool(const K&, const K&)> match,
        std::function<V(const K&)> map,
        std::map<K,V> values) :
            _match(match),
            _map(map),
            _values(values)
    {
        static_assert(
            std::is_same<std::decay_t<K>, std::decay_t<typename const_iter_t<Map>::first_type>>::value,
            "Type 'K' must match the key type of the iterator for type 'Map'");

        static_assert(
            std::is_same<std::decay_t<V>, std::decay_t<typename const_iter_t<Map>::second_type>>::value,
            "Type 'V' must match the value type of the iterator for type 'Map'");
    }

    V operator[] (const K& k) const
    {
        for (auto it = _values.crbegin(); it != _values.rend(); ++it)
            if (_match(k, it->first))
                return it->second;
        
        return _map(k);
    }

private:

    std::function<bool(const K&, const K&)> _match;
    std::function<V(const K&)> _map;
    std::map<K,V> _values;
};

#endif
