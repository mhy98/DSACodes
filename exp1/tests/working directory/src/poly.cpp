#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <iostream>

struct Term
{
	int expn;
	double coef;
	Term() : expn(0), coef(0){};
	Term(double _coef, int _expn) : expn(_expn), coef(_coef) {}
	Term(const Term &B) : expn(B.expn), coef(B.coef) {}
};

template <typename Elemtype>
struct Node
{
	Elemtype data;
	struct Node *next;
	Node() : next(NULL) {}
	Node(Elemtype _elem) : data(_elem), next(NULL) {}
};

template <typename Elemtype>
struct LinkList
{
protected:
	Node<Elemtype> *head;

public:
	LinkList() : head(new Node<Elemtype>) {}
	~LinkList()
	{
		del();
	}
	void clear()
	{
		for (auto scanPos = head; scanPos;)
		{
			auto nextPos = scanPos->next;
			delete scanPos;
			scanPos = nextPos;
		}
		head = new Node<Elemtype>;
	}
	void del()
	{
		clear();
		delete head;
		head = NULL;
	}
	void addnode(Elemtype elem)
	{
		Node<Elemtype> *tail = head;
		while (tail->next)
			tail = tail->next;
		tail->next = new Node<Elemtype>(elem);
	}
};

class Poly : public LinkList<Term>
{
private:
	void trim();
	Poly division(const Poly &b, bool getremains) const;
	friend std::ostream &operator<<(std::ostream &stream, const Poly &poly);
	friend std::istream &operator>>(std::istream &stream, Poly &poly);

public:
	Poly(){};
	Poly(const Poly &b)
	{
		if (this == &b)
			return;
		clear();
		for (auto ptrB = b.head->next; ptrB; ptrB = ptrB->next)
			addnode(ptrB->data);
	}
	void normalize();
	double evaluate(double x) const;
	double intergrade(double x1, double x2) const;
	Poly operator++(void) const;
	Poly operator--(void) const;
	Poly operator^(int x) const;
	Poly operator=(const Poly &b);
	Poly operator+(const Poly &b) const;
	Poly operator-(const Poly &b) const;
	Poly operator*(const Poly &b) const;
	Poly operator/(const Poly &b) const;
	Poly operator%(const Poly &b) const;
	Poly GCD(const Poly &b) const;
	Poly LCM(const Poly &b) const;
};

void Poly::trim()
{
	int nodeNum = 0;
	for (auto scanPos = head->next; scanPos; scanPos = scanPos->next, nodeNum++)
		;
	// bubble sort
	for (int i = 0; i < nodeNum; i++)
		for (auto scanPos = head->next, prePos = head; scanPos && scanPos->next; prePos = scanPos, scanPos = scanPos->next)
			if (scanPos->next->data.expn > scanPos->data.expn)
			{
				prePos->next = scanPos->next;
				scanPos->next = scanPos->next->next;
				prePos->next->next = scanPos;
			}
	// merge
	for (auto scanPos = head->next; scanPos && scanPos->next;)
	{
		if (scanPos->data.expn == scanPos->next->data.expn)
		{
			scanPos->data.coef += scanPos->next->data.coef;
			auto tmpnext = scanPos->next->next;
			delete scanPos->next;
			scanPos->next = tmpnext;
		}
		else
			scanPos = scanPos->next;
	}
	// delete zero
	for (auto scanPos = head; scanPos && scanPos->next;)
	{
		if (fabs(scanPos->next->data.coef) < 1E-08)
		{
			auto tmpnext = scanPos->next->next;
			delete scanPos->next;
			scanPos->next = tmpnext;
		}
		else
			scanPos = scanPos->next;
	}
}
void Poly::normalize()
{
	if (head && head->next)
	{
		double x = head->next->data.coef;
		for (auto ptr = head->next; ptr; ptr = ptr->next)
			ptr->data.coef /= x;
	}
}
double Poly::evaluate(double x) const
{
	double result = 0;
	for (Node<Term> *ptr = head; ptr; ptr = ptr->next)
		if (ptr->data.expn)
			result += ptr->data.coef * pow(x, ptr->data.expn);
		else
			result += ptr->data.coef;
	return result;
}
double Poly::intergrade(double x1, double x2) const
{
	return (++(*this)).evaluate(x2) - (++(*this)).evaluate(x1);
}
Poly Poly::operator++(void) const
{
	Poly result = *this;
	for (Node<Term> *ptr = result.head; ptr; ptr = ptr->next)
		ptr->data.coef /= ++(ptr->data.expn);
	return result;
}
Poly Poly::operator--(void) const
{
	Poly result = *this;
	for (auto ptr = result.head; ptr; ptr = ptr->next)
	{
		ptr->data.coef *= ptr->data.expn;
		if (ptr->data.expn)
			ptr->data.expn--;
	}
	result.trim();
	return result;
}
Poly Poly::operator^(int x) const
{
	Poly result, base = *(this);
	result.addnode(Term(1, 0));
	while (x > 0)
	{
		if (x & 1)
			result = result * base;
		x >>= 1;
		base = base * base;
	}
	return result;
}
Poly Poly::operator=(const Poly &b)
{
	if (this == &b)
		return *this;

	clear();
	for (auto ptrB = b.head->next; ptrB; ptrB = ptrB->next)
		addnode(ptrB->data);
	return *this;
}
Poly Poly::operator+(const Poly &b) const
{
	Poly result;
	auto ptrA = head->next, ptrB = b.head->next;
	while (ptrA && ptrB)
		if (ptrA->data.expn > ptrB->data.expn)
		{
			result.addnode(ptrA->data);
			ptrA = ptrA->next;
		}
		else if (ptrB->data.expn > ptrA->data.expn)
		{
			result.addnode(ptrB->data);
			ptrB = ptrB->next;
		}
		else
		{
			result.addnode(Term(ptrA->data.coef + ptrB->data.coef, ptrA->data.expn));
			ptrA = ptrA->next;
			ptrB = ptrB->next;
		}
	for (; ptrA; ptrA = ptrA->next)
		result.addnode(ptrA->data);
	for (; ptrB; ptrB = ptrB->next)
		result.addnode(ptrB->data);
	result.trim();
	return result;
}
Poly Poly::operator-(const Poly &b) const
{
	Poly opposite = b;
	for (auto ptr = opposite.head; ptr; ptr = ptr->next)
		ptr->data.coef = -ptr->data.coef;
	return (*this) + opposite;
}
Poly Poly::operator*(const Poly &b) const
{
	Poly result;
	for (auto ptrA = head->next; ptrA; ptrA = ptrA->next)
		for (auto ptrB = b.head->next; ptrB; ptrB = ptrB->next)
			result.addnode(Term(ptrA->data.coef * ptrB->data.coef, ptrA->data.expn + ptrB->data.expn));
	result.trim();
	return result;
}
Poly Poly::division(const Poly &b, bool getremains) const
{
	Poly result, remains = *this;
	Node<Term> *headA = remains.head->next, *headB = b.head->next;

	// How we do the polynominal division by hand?
	for (; headA && headB && headA->data.expn >= headB->data.expn; headA = remains.head->next, headB = b.head->next)
	{
		// Delete data From iterA, iterB
		Node<Term> *iterA = headA, *iterB = headB;
		Term term_result(headA->data.coef / headB->data.coef, headA->data.expn - headB->data.expn);

		// Add the term to the result
		result.addnode(term_result);

		for (iterA = headA, iterB = headB; iterB; iterB = iterB->next)
		{
			// Skip the greater terms
			while (iterA && iterA->data.expn > (iterA->data.expn + term_result.expn))
				iterA = iterA->next;

			// If there's a term whose expn should minus
			if (iterA && iterA->data.expn == iterB->data.expn + term_result.expn)
			{
				iterA->data.coef -= term_result.coef * iterB->data.coef;
				iterA = iterA->next;
			}
			// If there isn't, add a term to the result.
			else
			{
				auto insert = remains.head;
				while (insert->next != iterA)
					insert = insert->next;
				insert->next = new Node<Term>(Term(-term_result.coef * iterB->data.coef, iterB->data.expn + term_result.expn));
				insert->next->next = iterA;
				iterA = insert->next;
			}
		}
		remains.trim();
	}
	if (getremains)
		return remains;
	return result;
}
Poly Poly::operator/(const Poly &b) const
{
	return division(b, false);
}
Poly Poly::operator%(const Poly &b) const
{
	return division(b, true);
}
Poly Poly::GCD(const Poly &b) const
{
	Poly copyB = b, remains = (*this) % b;
	if (!remains.head->next)
	{
		copyB.normalize();
		return copyB;
	}
	else
		return copyB.GCD(remains);
}
Poly Poly::LCM(const Poly &b) const
{
	auto result = (*this) * (b / GCD(b));
	result.normalize();
	return result;
}

std::ostream &operator<<(std::ostream &stream, const Poly &poly)
{
	if (!poly.head)
	{
		stream << "NULL" << std::endl;
		return stream;
	}
	else if (!poly.head->next)
	{
		stream << "0.0000" << std::endl;
		return stream;
	}
	auto scanptr = poly.head->next;
	for (bool first = false; scanptr; scanptr = scanptr->next)
	{
		if (first == false)
			first = true;
		else if (scanptr->data.coef > 0)
			stream << "+";
		if (scanptr->data.coef < 0)
			stream << "-";
		stream << std::setprecision(4) << std::fixed << fabs(scanptr->data.coef);
		if (scanptr->data.expn)
		{
			stream << "x";
			if (scanptr->data.expn != 1)
				stream << "^" << scanptr->data.expn;
		}
	}
	stream << std::endl;
	return stream;
}

std::istream &operator>>(std::istream &stream, Poly &poly)
{
	Term addTerm;
	poly.clear();
	while (1)
	{
		stream >> addTerm.coef >> addTerm.expn;
		if (!addTerm.coef && !addTerm.expn)
			break;
		poly.addnode(addTerm);
	}
	poly.trim();
	return stream;
}

int main()
{
	const int polynum = 10;
	Poly polyn[polynum], result;
	int menu, optn1, optn2, optn3;
	double x1, x2;
	//std::istream& instream = std::cin;
	//std::ostream& outstream = std::cout;
	std::ifstream instream("polyn.in");
	std::ofstream outstream("polyn.out");
	for (int i = 0; i < polynum; i++)
		polyn[i].del();
	while (1)
	{
		instream >> menu;
		switch (menu)
		{
		case 0:
			exit(0);
		case 1:
			instream >> optn1;
			instream >> polyn[optn1];
			break;
		case 2:
			instream >> optn1;
			outstream << polyn[optn1];
			break;
		case 3:
			instream >> optn1 >> optn2;
			polyn[optn2] = polyn[optn1];
			break;
		case 4:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1] + polyn[optn2];
			break;
		case 5:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1] - polyn[optn2];
			break;
		case 6:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1] * polyn[optn2];
			break;
		case 7:
			instream >> optn1 >> x1;
			outstream << std::setprecision(4) << std::fixed << polyn[optn1].evaluate(x1) << std::endl;
			break;
		case 8:
			instream >> optn1;
			polyn[optn1].del();
			break;
		case 9:
			instream >> optn1;
			polyn[optn1].clear();
			break;
		case 10:
			instream >> optn1 >> optn2;
			polyn[optn2] = --polyn[optn1];
			break;
		case 11:
			instream >> optn1 >> optn2;
			polyn[optn2] = ++polyn[optn1];
			break;
		case 12:
			instream >> optn1 >> x1 >> x2;
			outstream << std::setprecision(4) << std::fixed << polyn[optn1].intergrade(x1, x2) << std::endl;
			break;
		case 13:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1].GCD(polyn[optn2]);
			break;
		case 14:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1].LCM(polyn[optn2]);
			break;
		case 15:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1] / polyn[optn2];
			break;
		case 16:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn3] = polyn[optn1] % polyn[optn2];
			break;
		case 17:
			instream >> optn1 >> optn2 >> optn3;
			polyn[optn2] = polyn[optn1] ^ optn3;
			break;
		}
	}
	// Use this in Visual Studio can detect memory leaks.
	// _CrtDumpMemoryLeaks();
}