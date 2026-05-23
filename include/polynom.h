#pragma once

#include"list.h"
#include"monom.h"

class Polynom {
	SkipList<Monom> mon;
public:
	Polynom();
	Polynom(std::string exp);
	SkipList<Monom> ret_list() { return mon; };
	void add(Monom m);
	Polynom operator+(const Polynom& p);
	Polynom operator-(const Polynom& p);
	Polynom operator*(const Polynom& p);
	double init(double x, double y, double z);
	friend ostream& operator<<(ostream& ostr, const Polynom& p);
	Monom getMonom(int ind);
	SkipList<Monom> retMonom();
};