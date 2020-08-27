#include "MyData.h"

#include <iostream>
#include <string>

MyData::~MyData(){}

std::string MyData::toString() const{
	return "{ /*DATA*/ }";
}

MyData& MyData::operator=(const MyData& other) {
	return *this;
}

std::ostream& operator <<(std::ostream& os, const MyData& data) {
	os << data.toString();
	return os;
}