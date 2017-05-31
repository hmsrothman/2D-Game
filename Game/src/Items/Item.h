/*
 * Item.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef ITEM_H_
#define ITEM_H_
#include <string>

class Item {
public:
	Item();
	virtual ~Item();
	std::string name;

	bool operator==(const Item& rhs) {
		return this->name == rhs.name;
	}
};

#endif /* ITEM_H_ */
