#include <iostream>
#include "fecha.cpp"

using namespace std;

int main(){

	Fecha f(11,9,2001);

	Fecha manana(19,3,2018);

	cout << f << endl;
	//cout << (hoy >= manana);
	//cout << manana.dia() << "/" << manana.mes() << "/"  << manana.anno() << endl;

	return 0;
}