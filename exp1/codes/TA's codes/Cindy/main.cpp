//
//  main.cpp
//  homework_1
//
//  Created by Konjac on 2019/10/16.
//  Copyright © 2017年 homework. All rights reserved.
//

#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
#define N 10
#define epsilon 1e-8

class Polynomial;

class Term {
public:
    Term() : coef(0), exp(-1), link(nullptr) {}
    Term(double c, int e, Term *next) : coef(c), exp(e), link(next) {}
    Term* Insert(double c, int e) {link = new Term(c, e, link); return link;}
    
private:
    double coef;
    int exp;
    Term *link;
    
    friend class Polynomial;
    friend ostream &operator << (ostream &, const Term &);
    friend ostream &operator << (ostream &, const Polynomial &);
};

ostream &operator << (ostream &out, const Term &x) {
    out << setprecision(4) << fixed;
    if (x.coef == 0) return out;
    out << x.coef;
    switch (x.exp) {
        case 0:
            break;
        case 1:
            out << "x";
            break;
        default:
            out << "x^" << x.exp;
            break;
    }
    return out;
}

class Polynomial {
public:
    Polynomial() : List(nullptr) {Create();}
    ~Polynomial();
    void AddTerms(double c, int e);
    void AddTerms(istream& in);
    void Clear();
    void Create();
    void Delete(int e);
    void Derivative();
    void Destroy();
    double Evaluate(double x);
    void Integration();
    int JudgeEmpty() const {return List->link == List;}
    int JudgeExist() {return List ? 1 : 0;}
    void Normalization();
    void PolyAdd(const Polynomial &r, double c, int e);
    Polynomial PolyPow(int n);
    Polynomial& operator=(const Polynomial&);
    Polynomial operator+(const Polynomial&);
    Polynomial operator-(const Polynomial&);
    Polynomial operator*(const Polynomial&);
    Polynomial operator/(const Polynomial&);
    Polynomial operator%(const Polynomial&);
    
private:
    Term *List;
    friend ostream &operator << (ostream &, const Polynomial &);
};

Polynomial::~Polynomial() {
    if (!List) return;
    Term *temp = List->link;
    while (temp != List) {
        List->link = temp->link;
        delete temp;
        temp = List->link;
    }
    delete List;
}

void Polynomial::AddTerms(double c, int e) {
    if (abs(c) < epsilon) return;
    Term *temp = List, *p;
    while (temp->link->exp > e)
        temp = temp->link;
    if (temp->link->exp - e)
        temp = temp->Insert(c, e);
    else {
        temp->link->coef += c;
        if (abs(temp->link->coef) < epsilon) {
            p = temp->link;
            temp -> link = p ->link;
            delete p;
        }
    }
}

void Polynomial::AddTerms(istream &in) {
    double c;
    int e;
    in >> c >> e;
    while (c || e) {
        AddTerms(c, e);
        in >> c >> e;
    }
}

void Polynomial::Clear() {
    Term *p = List->link;
    while (p != List) {
        List->link = p->link;
        delete p;
        p = List->link;
    }
}

void Polynomial::Create() {
    List = new Term;
    List -> link = List;
}

void Polynomial::Delete(int e) {
    Term *temp = List, *p;
    while ((temp->link != List) && (temp->link->exp >= e)) {
        if (temp->link->exp == e) {
            p = temp ->link;
            temp -> link = p->link;
            delete p;
            return;
        }
        temp = temp->link;
    }
}

void Polynomial::Derivative() {
    Term *p = List;
    while (p->link->exp > 0) {
        p->link->coef = p->link->coef * p->link->exp--;
        p = p->link;
    }
    if (!p->link->exp) {
        delete p->link;
        p->link = List;
    }
}

void Polynomial::Destroy() {
    if (!List) return;
    Clear();
    delete List;
    List = nullptr;
}

double Polynomial::Evaluate(double x) {
    double ans = 0;
    Term *p = List->link;
    while (p -> exp + 1) {
        ans += p->coef * pow(x, p->exp);
        p = p->link;
    }
    return ans;
}

void Polynomial::Integration() {
    Term *p = List->link;
    while (p->exp + 1) {
        p->coef = p->coef / ++p->exp;
        p = p->link;
    }
}

void Polynomial::Normalization() {
    Term *p = List->link;
    double x = p->coef;
    while (p != List) {
        p->coef /= x;
        p = p->link;
    }
}

void Polynomial::PolyAdd(const Polynomial &r, double c = 1, int e = 0) {
    Term *p = r.List->link, *qAhead = List, *q = List->link;
    while (p->exp + 1) {
        while (q->exp > p->exp + e) {
            qAhead = q;
            q = q->link;
        }
        if (q->exp == p->exp + e) {
            q->coef += p->coef * c;
            if (abs(q->coef) < epsilon) {
                qAhead->link = q->link;
                delete q;
                q = qAhead->link;
            }
        }
        else
            qAhead = qAhead->Insert(p->coef * c, p->exp + e);
        p = p->link;
    }
}

Polynomial Polynomial::PolyPow(int n) {
    Polynomial ans;
    if (!n)
        ans.AddTerms(1, 0);
    else {
        ans = PolyPow(n / 2);
        ans = (n % 2) ? (ans * ans * *this) : (ans * ans);
    }
    return ans;
}

ostream &operator << (ostream &out, const Polynomial &x) {
    out << setprecision(4) << fixed;
    if (!x.List) {
        out << "NULL" << endl;
        return out;
    }
    int h = 0;
    Term *temp = x.List->link;
    if (temp == x.List)
        out << 0.0000;
    else
        for (;temp != x.List; temp = temp->link) {
            if (h++ && (temp->coef > 0))
                out << "+";
            out << *temp;
        }
    out << endl;
    return out;
}

Polynomial Polynomial::operator+(const Polynomial& x) {
    Polynomial ans;
    ans = *this;
    ans.PolyAdd(x, 1, 0);
    return ans;
}

Polynomial Polynomial::operator-(const Polynomial& x) {
    Polynomial ans;
    ans = *this;
    ans.PolyAdd(x, -1, 0);
    return ans;
}

Polynomial Polynomial::operator*(const Polynomial& x) {
    Polynomial ans;
    Term *p = List->link;
    while (p->exp + 1) {
        ans.PolyAdd(x, p->coef, p->exp);
        p = p->link;
    }
    return ans;
}

Polynomial Polynomial::operator/(const Polynomial& x) {
    Polynomial ans, temp;
    temp = *this;
    if (x.JudgeEmpty())
        return ans;
    while (temp.List->link->exp >= x.List->link->exp) {
        ans.AddTerms(temp.List->link->coef / x.List->link->coef, temp.List->link->exp - x.List->link->exp);
        temp.PolyAdd(x, - temp.List->link->coef / x.List->link->coef, temp.List->link->exp - x.List->link->exp);
    }
    return ans;
}

Polynomial Polynomial::operator%(const Polynomial& x) {
    Polynomial ans;
    ans = *this;
    if (x.JudgeEmpty())
        return ans;
    while (ans.List->link->exp >= x.List->link->exp)
        ans.PolyAdd(x, -ans.List->link->coef / x.List->link->coef, ans.List->link->exp - x.List->link->exp);
    return ans;
}

Polynomial& Polynomial::operator=(const Polynomial& x) {
    if (JudgeExist())
        Clear();
    else
        Create();
    Term *p = x.List->link, *q = List->link;
    while (p -> exp + 1) {
        q = q->Insert(p->coef, p->exp);
        p = p->link;
    }
    return *this;
}

void Poly_GCD(Polynomial &x, Polynomial &y, Polynomial &z) {
    if (y.JudgeEmpty()) {
        z = x;
        z.Normalization();
    }
    else {
        Polynomial temp = x % y;
        Poly_GCD(y, temp, z);
    }
}

void Poly_LCM(Polynomial &x, Polynomial &y, Polynomial &z) {
    Poly_GCD(x, y, z);
    z = x * y / z;
    z.Normalization();
}

Polynomial Poly[N];

int main(int argc, const char * argv[]) {
    int ch, m, m1, m2, m3, k;
    double x, x1, x2;
    Polynomial temp, temp1, temp2;
    cin >> ch;
    cout << setprecision(4) << fixed;
    for (int i = 0; i <= 9; i++)
        Poly[i].Destroy();
    while (ch) {
        switch (ch) {
            case 1:
                cin >> m;
                if (Poly[m].JudgeExist())
                    Poly[m].Clear();
                else
                    Poly[m].Create();
                Poly[m].AddTerms(cin);
                break;
            case 2:
                cin >> m;
                cout << Poly[m];
                break;
            case 3:
                cin >> m1 >> m2;
                Poly[m2] = Poly[m1];
                break;
            case 4:
                cin >> m1 >> m2 >> m3;
                Poly[m3] = Poly[m1] + Poly[m2];
                break;
            case 5:
                cin >> m1 >> m2 >> m3;
                Poly[m3] = Poly[m1] - Poly[m2];
                break;
            case 6:
                cin >> m1 >> m2 >> m3;
                Poly[m3] = Poly[m1] * Poly[m2];
                break;
            case 7:
                cin >> m >> x;
                cout << Poly[m].Evaluate(x) << endl;
                break;
            case 8:
                cin >> m;
                Poly[m].Destroy();
                break;
            case 9:
                cin >> m;
                Poly[m].Clear();
                break;
            case 10:
                cin >> m1 >> m2;
                Poly[m2] = Poly[m1];
                Poly[m2].Derivative();
                break;
            case 11:
                cin >> m1 >> m2;
                Poly[m2] = Poly[m1];
                Poly[m2].Integration();
                break;
            case 12:
                cin >> m >> x1 >> x2;
                temp = Poly[m];
                temp.Integration();
                cout << temp.Evaluate(x2) - temp.Evaluate(x1) << endl;
                break;
            case 13:
                cin >> m1 >> m2 >> m3;
                Poly_GCD(Poly[m1], Poly[m2], Poly[m3]);
                break;
            case 14:
                cin >> m1 >> m2 >> m3;
                Poly_LCM(Poly[m1], Poly[m2], Poly[m3]);
                break;
            case 15:
                cin >> m1 >> m2 >> m3;
                Poly[m3] = Poly[m1] / Poly[m2];
                break;
            case 16:
                cin >> m1 >> m2 >> m3;
                Poly[m3] = Poly[m1] % Poly[m2];
                break;
            case 17:
                cin >> m1 >> m2 >> k;
                Poly[m2] = Poly[m1].PolyPow(k);
                break;
            default:
                break;
        }
        cin >> ch;
    }
    return 0;
}

