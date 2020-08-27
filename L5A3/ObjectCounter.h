#pragma once

class ObjectCounter
{
private:

	const unsigned int id;
	static unsigned int maxId, number;

public:

	ObjectCounter() : id(++ObjectCounter::maxId) {
		ObjectCounter::number++;
	}

	//explicitly delegate the copy constructor to the default constructor
	ObjectCounter(const ObjectCounter& obj) : ObjectCounter() {  };

	~ObjectCounter() {
		ObjectCounter::number--;
	}

	unsigned int getId() const {
		return id;
	}

	static unsigned int getMaxId() {
		return maxId;
	}

	static unsigned int getNumber() {
		return number;
	}

};

unsigned int ObjectCounter::maxId = 0;
unsigned int ObjectCounter::number = 0;