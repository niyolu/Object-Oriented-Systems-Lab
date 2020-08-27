#include <cassert>
#include <ostream>
#include <iostream>
#include "MyList.h"

MyListElement::MyListElement(const MyData& d) 
	: data(d.clone()), next(nullptr)
{
}

MyListElement::MyListElement(const MyData& d, MyListElement* n)
	: data(d.clone()), next(n)
{
}

MyListElement::MyListElement(const MyListElement& other)
	: data(other.getData().clone()), next(nullptr)
{
	//recursive construction
	if(other.next != nullptr)
		next = new MyListElement(*other.next);
}

MyListElement::~MyListElement() {
	//if (data) //trivial
		delete data;

	//recursive destruction
	if (next != nullptr)
		delete next;
}

void MyListElement::setNext(MyListElement* n) {
	assert(this != nullptr);
	//assert(n != nullptr);
	this->next = n;
}

MyListElement* MyListElement::getNext() const {
	return next;
}

MyData& MyListElement::getData() const {
	return *data;
}

bool MyListElement::hasNext() const {
	return next != nullptr;
}

std::ostream& operator<<(std::ostream& os, const MyListElement& e) {
	os << e.getData();
	return os;
}

MyList::MyList()
	: first(nullptr), last(nullptr), size(0)
{
}

MyList::MyList(const MyList& other)
	:size(0), first(nullptr), last(nullptr)
{
	MyListElement* current = other.first;
	while (current != nullptr) {
		push_back(current->getData());
		current = current->getNext();
	}
}

MyList::~MyList() {
	if(first)
		delete first;
}

void MyList::push_back(const MyData& d) {
	MyListElement* ne = new MyListElement(d);
	if (first && last) {
		assert(last != nullptr);
		last->setNext(ne);
		last = ne;
	}
	else {
		assert(last == nullptr);
		first = last = ne;
	}
	size++;
}

void MyList::pop_back() {

	if (empty() || last == nullptr) {
		assert(first == nullptr);
		return;
	}
	assert(first != nullptr);

	if (first == last) {
		size = 0;
		delete first;
		first = last = nullptr;
	}
	else {

		MyListElement* current = first;

		//traverse until before last
		while (current->getNext() != last) {
			assert(current->getNext() != nullptr);
			current = current->getNext();
		}

		delete last;
		current->setNext(nullptr);
		last = current;
		assert(size > 0);
		size--;
	}
}

MyData& MyList::front() const {
	return first->getData();
}

MyData& MyList::back() const {
	return last->getData();
}

void MyList::clear() {
	delete first;
	first = last = nullptr;
	size = 0;
}

bool MyList::empty() const {
	return size == 0;
}

unsigned int MyList::Size() const {
	return size;
}

void MyList::print() const {
	std::cout << *this << std::endl;
}

MyList& MyList::operator=(const MyList& other) {
	if (this != &other) {
		if (other.empty()) {
			delete first;
			first = last = nullptr;
			size = 0;
		}
		else {
			if (first != nullptr) {
				delete first;
			}
			MyList nl(other);
			first = nl.first;
			last = nl.last;
			size = nl.size;

			//prevent nl's destructor from deleting this
			nl.first = nullptr;
			nl.last = nullptr;
		}
	}
	return *this;
}

MyList MyList::operator+(const MyList& other) {
	MyList left(*this);
	MyList right(other);
	left.last->setNext(right.first);
	left.last = right.last;

	//right's destructor is called before the return
	right.first = right.last = nullptr;
	return left;
}

std::ostream& operator<< (std::ostream& os, const MyList& list) {
	os << "[";
	MyListElement* current = list.first;
	while (current != nullptr) {
		os << *current << " ";
		current = current->getNext();
	}
	os << "]";
	return os;
}