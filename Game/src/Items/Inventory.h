/*
 * Inventory.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_
#include <vector>
#include "Item.h"

class Inventory {
public:
	Inventory();
	virtual ~Inventory();
	Item getItem(int index);
	void addItem(Item& item);
	void removeItem(int index);
	int getIndex(Item& item);

private:
	std::vector<Item> _items;
};

#endif /* INVENTORY_H_ */
