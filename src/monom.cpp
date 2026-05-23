#include"monom.h"
#include<iostream>

double pow(double a, int d) {
	if (d == 0) return 1.0;
	if (d < 0) return 1.0 / pow(a, -d);

	if (d & 1) {
		return a * pow(a, d - 1);
	}
	else {
		double t = pow(a, d << 1);
		return t * t;
	}
}

void Monom:: set_dx(int _d) { d.d_char[0] = _d; }
void Monom::set_dy(int _d) { d.d_char[1] = _d; }
void Monom::set_dz(int _d) { d.d_char[2] = _d; }
void Monom::set_k(double _k) { k = _k; }
char Monom::get_dx() { return d.d_char[0]; }
char Monom::get_dy() { return d.d_char[1]; }
char Monom::get_dz() { return d.d_char[2]; }
double Monom::get_k() { return k; }
bool Monom:: operator==(const Monom& m) {
	//if (k != m.k)return false;
	if (d.d_int != m.d.d_int)return false;
	return true;
}
bool Monom:: operator!=(const Monom& m) {
	return !(*this == m);
}
bool Monom:: operator<(const Monom& m) {
	return(d.d_int < m.d.d_int);
}
bool Monom:: operator>(const Monom& m) {
	return(d.d_int > m.d.d_int);
}
Monom Monom:: operator+(const Monom& m) {
	if (d.d_int != m.d.d_int)throw - 1;
	return Monom(k + m.k, d.d_int);
}
Monom Monom:: operator-(const Monom& m) {
	if (d.d_int != m.d.d_int)throw - 1;
	return Monom(k - m.k, d.d_int);
}
Monom Monom:: operator*(const Monom& m) {
	int dx = d.d_char[0] + m.d.d_char[0];
	int dy = d.d_char[1] + m.d.d_char[1];
	int dz = d.d_char[2] + m.d.d_char[2];
	int _k = k * m.k;
	if ((dx < -5) || (dx > 10))return Monom(0, 0, 0, 0);
	if ((dy < -5) || (dy > 10))return Monom(0, 0, 0, 0);
	if ((dz < -5) || (dz > 10))return Monom(0, 0, 0, 0);
	return Monom(_k, dx, dy, dz);
}
double Monom:: init(double x, double y, double z) {
	return k * pow(x, d.d_char[0]) * pow(y, d.d_char[1]) * pow(z, d.d_char[2]);
}
ostream& operator<<(ostream& ostr, const Monom& m) {
	if (m.k == 0)return ostr;
	int dx = m.d.d_char[0];
	int dy = m.d.d_char[1];
	int dz = m.d.d_char[2];
	if ((m.k != 1.0) && (m.k != -1.0))ostr << m.k;
	if ((m.k == -1.0)&&((dx!=0)||(dy!=0)||(dz!=0)))ostr << '-';
	if ((m.k == -1.0) && ((dx == 0) && (dy == 0) && (dz == 0)))ostr << m.k;
	if ((m.k == 1.0) && ((dx == 0) && (dy == 0) && (dz == 0)))ostr << m.k;
	if ((dx != 0) && (dx != 1))ostr << "x^" << (int)dx;
	if (dx == 1)ostr << "x";
	if ((dy != 0) && (dy != 1))ostr << "y^" << (int)dy;
	if (dy == 1)ostr << "y";
	if ((dz != 0) && (dz != 1))ostr << "z^" << (int)dz;
	if (dz == 1)ostr << "z";
	return ostr;
}