#include <iostream>
#include "polynomial.h"
#include "Poly_List.h"
#include <stdio.h>


using namespace std;
int main()
{
	freopen("polyn.in", "r", stdin);
	freopen("polyn.out", "w", stdout);
	Poly_List pl = Poly_List();
	pl.Run();
	return 0;
}
