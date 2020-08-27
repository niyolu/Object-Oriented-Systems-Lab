#pragma once
#include <string>

class MyData
{
public:

	virtual ~MyData();

	virtual std::string toString() const;

	virtual MyData* clone() const = 0;
	virtual void print() const = 0;

	virtual MyData& operator=(const MyData&);

	virtual bool operator==(const MyData&) const = 0;
	virtual bool operator!=(const MyData&) const = 0;

	friend std::ostream& operator <<(std::ostream&, const MyData&);
};