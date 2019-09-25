#include<iostream>
#include<string>

using namespace std;

#include "priorityqueue.h"
PriorityQueue PQ;

PriorityQueue::PriorityQueue(Item *array, int length){ //takes a pointer to an input array with Item objects and constructs a heap from it
	if(array == NULL)
		return;
	int firstParent = (length - 2)/2;
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete [] keys;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;

	for(int i = 0; i < length; i++){
		aheap[i] = array[i];
		int ind = aheap[i].key;
		keys[ind] = i;
	}
	for(int j = firstParent; j >= 0; j--)
		reheapifyDown(j);
	
}
PriorityQueue::PriorityQueue(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
}
PriorityQueue& PriorityQueue::operator=(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
	return *this;
}

//Implemented member functions:
		
int getCapacity() {
    return PQ.getCapacity();
}

int getSize() {
    return PQ.getSize();
}

void PriorityQueue::print() {

	int size = getSize();

	for (int i = 0; i < size; i++) {
		cout << aheap[i].priority << " ";
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << aheap[i].key << " ";
	}
	cout << endl;

	for (int i = 0; i < totalKeys; i++) {
		cout << keys[i] << " ";
	}
	cout << endl;
}

void PriorityQueue::reheapifyUp(int i) {

	int parentIndex = (i - 1)/2;

	if ((parentIndex >= 0) && (aheap[parentIndex].priority > aheap[i].priority)) {

		//swap
		Item temp = aheap[parentIndex];
		aheap[parentIndex] = aheap[i];
		aheap[i] = temp;

		keys[aheap[parentIndex].key] = parentIndex;
		keys[aheap[i].key] = i;
		reheapifyUp(parentIndex);
	}

	else {

		return;
	}
}

void PriorityQueue::reheapifyDown(int i) {

	int size = getSize();
	int leftChildIndex = 2 * i + 1;
	int rightChildIndex = 2 * i + 2;
	int amin = i;

	if (leftChildIndex >= size && rightChildIndex >= size) {

		return;
	}

	if ((leftChildIndex < size) && (aheap[leftChildIndex].priority < aheap[i].priority)) {

		amin = leftChildIndex;
	}

	if ((rightChildIndex < size) && (aheap[rightChildIndex].priority < aheap[amin].priority)) {

		amin = rightChildIndex;
	}

	if (amin != i) {

		//swap
		Item temp = aheap[amin];
		aheap[amin] = aheap[i];
		aheap[i] = temp;

		keys[aheap[amin].key] = amin;
		keys[aheap[i].key] = i;
		reheapifyDown(amin);
	}
}

void PriorityQueue::pop() {

	int size = getSize();

	if (size == 0) {

		return;
	}

	keys[aheap[0].key] = -1;
	aheap[0] = aheap[size - 1];
	setSize(size - 1);
	reheapifyDown(0);
}

bool PriorityQueue::isKey(int v) {
    if (keys[v] != -1) {
        return true;
    }
    return false;
}

Item PriorityQueue::getMin() {

	return aheap[0];
}

bool PriorityQueue::empty() {
	if (getSize() == 0) {
		return true;
	}
	return false;
}

bool PriorityQueue::push(int akey, int apr) {

	if (akey != totalKeys) {

		return false;
	}

	if (getSize() == getCapacity()) {

		int size = getCapacity() * 2;

		Item* itemArray = new Item[size];
		int* keyArray = new int[size];

		for (int i = 0; i < getCapacity(); i++) {

			itemArray[i] = aheap[i];
			keyArray[i] = keys[i];
		}

		setCapacity(size);
		delete[] aheap;
		delete[] keys;
		aheap = itemArray;
		keys = keyArray;
	}

	aheap[getSize()].priority = apr;
	aheap[getSize()].key = akey;
	keys[akey] = getSize();
	setSize(getSize() + 1);
	reheapifyUp(getSize() - 1);
	totalKeys++;
	return true;
}

bool PriorityQueue::updatePriority(int akey, int apr) {

	if (keys[akey] == -1) {

		return false;
	}

	if (apr > aheap[keys[akey]].priority) {

		return false;
	}

	aheap[keys[akey]].priority = apr;
	reheapifyUp(keys[akey]);
	return true;
}