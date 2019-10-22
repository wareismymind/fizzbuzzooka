#ifndef FLEXIBUZZ_H
#define FLEXIBUZZ_H 1

#include <functional>
#include <map>

template<class K, class V>
class flexibuzz
{
public:

    flexibuzz(
        std::function<bool(const K&, const K&)> match,
        std::function<V(const K&)> map,
        std::map<K,V> values) :
            _match(match),
            _map(map),
            _values(values)
    {}

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
