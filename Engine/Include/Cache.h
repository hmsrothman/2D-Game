/*
 * Cache.h
 *
 *  Created on: Jun 1, 2017
 *      Author: Simon
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <string>
#include <map>
#include "ResourceLoader.h"

namespace Engine {

template<class T>
class Cache {
public:
	T get(const std::string& path);
private:
	T load(const std::string& path);
	std::map<std::string, T> _map;
	ResourceLoader<T> _loader;
};

template<class T>
T Cache<T>::get(const std::string& path) {
	auto iterator = _map.find(path); //grab texture from map

	if (iterator == _map.end()) { //it wasn't in the map
		T newItem = load(path);

		_map.insert(make_pair(path, newItem));

		return newItem;
	}

	return iterator->second;
}

template<class T>
T Cache<T>::load(const std::string& path) {
	return _loader.load(path);
}

} /* namespace Engine */

#endif /* CACHE_H_ */
