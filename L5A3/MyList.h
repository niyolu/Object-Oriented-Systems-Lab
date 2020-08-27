#pragma once
#include <iostream>
#include "MyData.h"

class MyListElement
{
private:
	MyListElement* next;
	MyData* const data;

public:

	MyListElement(const MyData&);
	MyListElement(const MyListElement&);
	MyListElement(const MyData&, MyListElement*);

	~MyListElement();

	MyListElement* getNext() const;
	void setNext(MyListElement*);
	bool hasNext() const;

	MyData& getData() const;

	friend std::ostream& operator<<(std::ostream&, const MyListElement&);
};

class MyList
{
private:
	MyListElement* first;
	MyListElement* last;
	unsigned int size;

public:

	MyList();
	MyList(const MyList&);

	~MyList();

	void push_back(const MyData&);
	void pop_back();

	MyData& front() const;
	MyData& back() const;

	void clear();

	bool empty() const;
	unsigned int Size() const;

	void print() const;

	MyList& operator= (const MyList&);
	MyList operator+ (const MyList&);

	friend std::ostream& operator<<(std::ostream&, const MyList&);
};