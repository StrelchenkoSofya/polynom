#include"polynom.h"
#include"monom.h"
#include"list.h"

#include<string>
#include<sstream>

#include"antlr4-runtime.h"
#include"polynomLexer.h"
#include"polynomParser.h"
#include"polynomUserVisitor.h"

Polynom:: Polynom() {
	mon = SkipList<Monom>();
}
Polynom:: Polynom(std::string exp) {
	std::stringstream stream(exp);
	antlr4::ANTLRInputStream input(stream);
	polynomLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	polynomParser parser(&tokens);
	polynomUserVisitor visitor;
	visitor.setPolynom(this);
	visitor.visit(parser.polynom());
}

void Polynom::add(Monom m) {
	Node<Monom>* cur = mon.find(m);
	if (cur != nullptr) {
		cur->val = cur->val + m;
	}
	else mon.add(m);
}
Polynom Polynom:: operator+(const Polynom& p) {
	Polynom res = Polynom();
	SkipListIterator<Monom> i = mon.itr();
	SkipListIterator<Monom> q = p.mon.itr();
	/*while (i.hasNext()) {
		Monom tmp = i.Next();
		res.add(tmp);
	}
	while (q.hasNext()) {
		Monom tmp = q.Next();
		res.add(tmp);
	}*/
	while (i.hasNext() && q.hasNext()) {
		Monom tmp1 = i.Next();
		Monom tmp2 = q.Next();
		while (tmp1 < tmp2 && i.hasNext()) {
			res.mon.addLast(tmp1);
			tmp1 = i.Next();
		}
		if (tmp1 == tmp2) {
			res.mon.addLast(tmp1 + tmp2);
		}
		while (tmp1 > tmp2 && q.hasNext()) {
			res.mon.addLast(tmp2);
			tmp2 = q.Next();
		}
	}
	while (i.hasNext()) {
		Monom tmp = i.Next();
		res.mon.addLast(tmp);
	}
	while (q.hasNext()) {
		Monom tmp = q.Next();
		res.mon.addLast(tmp);
	}
	return res;
}
Polynom Polynom:: operator-(const Polynom& p) {
	/*Polynom res = Polynom();
	Monom m(-1.0);
	Polynom t;
	t.mon.add(m);
	t = t * p;*/
	SkipListIterator<Monom> j = p.mon.itr();
	while (j.hasNext()) {
		Monom tmp = j.Next();
		tmp.set_k(tmp.get_k() * (-1.0));
	}
	/*Polynom res = Polynom();
	SkipListIterator<Monom> i = mon.itr();
	SkipListIterator<Monom> q = p.mon.itr();
	while (i.hasNext()) {
		Monom tmp = i.Next();
		res.add(tmp);
	}
	while (q.hasNext()) {
		Monom tmp = q.Next();
		tmp.set_k(tmp.get_k() * (-1.0));
		res.add(tmp);
	}*/
	return *this + p;
}
Polynom Polynom:: operator*(const Polynom& p) {
	Polynom res = Polynom();
	SkipListIterator<Monom> i = mon.itr();
	while (i.hasNext()) {
		Monom tmp1 = i.Next();
		SkipListIterator<Monom> q = p.mon.itr();
		while (q.hasNext()) {
			Monom tmp2 = q.Next();
			res.add(tmp1 * tmp2);
		}
	}
	return res;
}
double Polynom::init(double x, double y, double z) {
	double res = 0;
	SkipListIterator<Monom> i = mon.itr();
	while (i.hasNext()) {
		res += i.Next().init(x, y, z);
	}
	return res;
}
ostream& operator<<(ostream& ostr, const Polynom& p) {
	SkipListIterator<Monom> i = p.mon.itr();
	int f = 0;
	while (i.hasNext()) {
		Monom tmp = i.Next();
		if (tmp.get_k() != 0) {
			if (tmp.get_k() < 0) {
				ostr << tmp;
			}
			else {
				if (f == 0) {
					ostr << tmp;
				}
				else {
					ostr << '+' << tmp;
				}
			}
		}
		f++;
	}
	return ostr;
}
Monom Polynom::getMonom(int ind) {
	return mon.returnVal(ind);
}
SkipList<Monom> Polynom::retMonom() {
	return mon;
}