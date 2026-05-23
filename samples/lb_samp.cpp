#include <iostream>
#include"polynom.h"
#include"list.h"
#include"monom.h"

#include<string>

int main()
{
	/*std::string a = "-1.0-y^5";
	Polynom p = Polynom(a);
	std::cout << p << '\n';*/
	Polynom q = Polynom();
	q.add(Monom(2));
	q.add(Monom(9,5));
	Polynom a = Polynom();
	a.add(Monom(-1));
	std::cout << a-q;
	//Polynom p = Polynom();
	//p.add(m);
}
