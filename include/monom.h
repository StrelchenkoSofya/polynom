#pragma once
#include<iostream>

using namespace std;

long long int pow(int a, char d);

union degree {
	int d_int;
	char d_char[4];
};

class Monom {
	degree d;
	double k;
public:
	Monom(double _k = 0, int _d = 0) {
		k = _k;
		d.d_int = _d;
	}
	Monom(double _k, char dx, char dy, char dz) {
		if ((dx < -5) || (dx > 10))throw - 1;
		if ((dy < -5) || (dy > 10))throw - 1;
		if ((dz < -5) || (dz > 10))throw - 1;
		d.d_int = 0;
		d.d_char[0] = dx;
		d.d_char[1] = dy;
		d.d_char[2] = dz;
		k = _k;
	}
	void set_dx(int _d);
	void set_dy(int _d);
	void set_dz(int _d);
	void set_k(double _k);
	char get_dx();
	char get_dy();
	char get_dz();
	double get_k();
	bool operator==(const Monom& m);
	bool operator!=(const Monom& m);
	bool operator<(const Monom& m);
	bool operator>(const Monom& m);
	Monom operator+(const Monom& m);
	Monom operator-(const Monom& m);
	Monom operator*(const Monom& m);
	double init(double x, double y, double z);
	friend ostream& operator<<(ostream& ostr, const Monom& m);
};