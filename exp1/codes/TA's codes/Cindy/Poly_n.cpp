//
//  main.cpp
//  Poly_n
//
//  Created by Konjac on 2019/10/8.
//  Copyright © 2019年 test. All rights reserved.
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
    int JudgeEmpty() const;
    int JudgeExist();
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
    
}

void Polynomial::AddTerms(double c, int e) {
    
}

void Polynomial::AddTerms(istream &in) {
    
}

void Polynomial::Clear() {
    
}

void Polynomial::Create() {
    
}

void Polynomial::Delete(int e) {
    
}

void Polynomial::Derivative() {
    
}

void Polynomial::Destroy() {
    
}

double Polynomial::Evaluate(double x) {
    double ans = 0;
    
    return ans;
}

void Polynomial::Integration() {
    
}

void Polynomial::Normalization() {
    
}

void Polynomial::PolyAdd(const Polynomial &r, double c = 1, int e = 0) {
    
}

Polynomial Polynomial::PolyPow(int n) {
    Polynomial ans;
    
    return ans;
}

ostream &operator << (ostream &out, const Polynomial &x) {
    return out;
}

Polynomial Polynomial::operator+(const Polynomial& x) {
    Polynomial ans;
    
    return ans;
}

Polynomial Polynomial::operator-(const Polynomial& x) {
    Polynomial ans;
    
    return ans;
}

Polynomial Polynomial::operator*(const Polynomial& x) {
    Polynomial ans;
    
    return ans;
}

Polynomial Polynomial::operator/(const Polynomial& x) {
    Polynomial ans;
    
    return ans;
}

Polynomial Polynomial::operator%(const Polynomial& x) {
    Polynomial ans;
    
    return ans;
}

Polynomial& Polynomial::operator=(const Polynomial& x) {
    
    return *this;
}

void Poly_GCD(Polynomial &x, Polynomial &y, Polynomial &z) {
    
}

void Poly_LCM(Polynomial &x, Polynomial &y, Polynomial &z) {
    
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

