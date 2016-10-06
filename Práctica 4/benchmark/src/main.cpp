#include<benchmark.h>

int main(){
	char option;
	int levels = 3, exp;
	cout << "Benchmark de memorias USB en de tres niveles:" << endl;
	Benchmark nuevo(levels);

	cout << "¿Que experimento deseas realizar? (1,2): ";
	while(exp!=1 && exp!=2)
		cin >> exp;
	
	for(int i=0; i< levels; i++){
		if(i>0)
			cout << "Desconecte el dispositivo.";
		cout << "Nuevo nivel; Introduzca la memoria extraible USB en el mismo puerto, continuar (s,n): ";
		while(option != 's'){
			cin >> option;
			if(option == 'n'){
				return 0;
			}
		}
		nuevo.usbMemoryTest(i,exp);
	}
	nuevo.saveData(exp);
	return 0;
}
