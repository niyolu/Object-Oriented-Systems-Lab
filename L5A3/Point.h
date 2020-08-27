#pragma once
#include <string> //for everything
#include <iostream> //for cout
#include <sstream>
#include <iomanip> //for setprecision
#include "DrawingObject.h"

using namespace std;

extern bool debugConstructor;

class Point : public DrawingObject
{
private:
	double x, y;
public:
	Point(double x = 0, double y = 0);
	Point(const char* c);
	Point(const string& str);
	Point(const Point& p);

	~Point();

	virtual Point* clone() const override;

	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);
	void setXY(double x, double y);

	void move(double dx, double dy);

	void print(bool b = true) const;
	virtual void print() const override;

	virtual string toString() const override;

	virtual Point& operator= (const MyData&) override;

	virtual bool operator==(const MyData&) const override;
	virtual bool operator!=(const MyData&) const override;

	friend istream& operator >> (istream& is, Point& p);
	friend ostream& operator << (ostream& out, const Point& p);

	Point& operator + (const Point& p);
	Point& operator - (const Point& p);

	Point& operator -();

	Point& operator + (double const d);
	Point& operator - (double const d);

	Point& operator ++();
	Point& operator ++(int);

	Point& operator --();
	Point& operator --(int);

	friend Point& operator+(double const d, Point const p1);

	Point& operator=(Point& p);
};


Point::Point(double x, double y) : x(x), y(y) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Point, Objekt: " << getId() << endl;
};

Point::Point(const char* c) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Point, Objekt: " << getId() << endl;
	stringstream buf(c);
	buf >> *this;
}

Point::Point(const string& str) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Point, Objekt: " << getId() << endl;
	stringstream buf(str);
	buf >> *this;
}

Point::Point(const Point& p) : Point(p.x, p.y) {}

Point::~Point() {
	if (debugConstructor)
		cout << "Destruktor der Klasse Point, Objekt: " << getId() << endl;
}

Point* Point::clone() const {
	return new Point(*this);
}

Point& Point::operator=(const MyData& p) {
	const Point* ptr =
		dynamic_cast<Point*>(const_cast<MyData*>(&p));
	x = ptr->x;
	y = ptr->y;
	return *this;
}

double Point::getX() const {
	return x;
}

double Point::getY() const {
	return y;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->x = y;
}

void Point::setXY(double x, double y) {
	this->x = x;
	this->y = y;
}

void Point::move(double dx, double dy) {
	x += dx;
	y += dy;
}

void Point::print(bool b) const {
	std::cout << "(" << x << ", " << y << ")";
	if (b) std::cout << std::endl;
}

void Point::print() const {
	print(true);
}

string Point::toString() const {
	stringstream buf;
	buf << "(" << this->x << ", " << this->y << ")";
	return buf.str();
}

istream& operator >> (istream& is, Point& p) {
	bool started = false;
	bool done = false;
	while (!is.eof() && !done) {
		switch (is.get()) {
		case '(':
			if (!started) {
				is >> p.x;
			}
			started = true;
			break;
		case ',':
			if (started) {
				is >> p.y;
			}
			break;
		case ')':
			done = true;
			break;
		default:
			break;
		}
	}
	return is;
}
ostream& operator << (ostream& out, const Point& p) {
	out << p.toString();
	return out;
}

Point& Point::operator-() {
	Point* p = new Point(-x, -y);
	return *p;
}

Point& Point::operator+(const Point& p1) {
	Point* p2 = new Point(this->x + p1.getX(), this->y + p1.getY());
	return *p2;
}

Point& Point::operator-(const Point& p1) {
	Point* p2 = new Point(this->x - p1.getX(), this->y - getY());
	return *p2;
}
Point& Point::operator + (double const d) {
	Point* p = new Point(this->x + d, this->y + d);
	return *p;
}

Point& Point::operator - (double const d) {
	Point* p = new Point(this->x - d, this->y - d);
	return *p;
}

Point& Point::operator++() {
	this->move(1.0, 1.0);
	return *this;
}

Point& Point::operator++(int) {
	Point* p = new Point(this->x, this->y);
	this->move(1.0, 1.0);
	return *p;
}

Point& Point::operator--() {
	this->move(-1.0, -1.0);
	return *this;
}

Point& Point::operator--(int) {
	Point* p = new Point(this->x, this->y);
	this->move(-1.0, -1.0);
	return *p;
}

Point& operator+(double const d, Point const p1) {
	Point* p2 = new Point(p1.getX() + d, p1.getY() + d);
	return *p2;
}

Point& Point::operator=(Point& p) {
	this->x = p.x;
	this->y = p.y;
	return *this;
}

bool Point::operator==(const MyData& other) const{
	const Point* p = dynamic_cast<Point*>(const_cast<MyData*>(&other));
	return x == p->x && y == p->y;
}

bool Point::operator!=(const MyData& other) const {
	return !(*this == other);
}