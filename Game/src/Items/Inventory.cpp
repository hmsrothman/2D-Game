/*
 * Inventory.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include <Game/src/Items/Inventory.h>

Inventory::Inventory() {

}

Inventory::~Inventory() {
}

Item Inventory::getItem(int index) {
	return _items[index];
}
void Inventory::addItem(Item& item) {
	_items.push_back(item);
}
void Inventory::removeItem(int index) {
	_items.erase(_items.begin() + index);
}
int Inventory::getIndex(Item& item) {
	for (int i = 0; i < _items.size(); i++) {
		if (_items[i] == item) {
			return i;
		}
	}
	return -1;
}
