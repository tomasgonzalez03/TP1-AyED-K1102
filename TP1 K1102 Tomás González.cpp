#include<iostream>
#include<fstream>

using namespace std;
const int cprod {5};

//Punto 1
void listado(float kg[][cprod], int cont[], int cantclientes, int cantprod, string nclientes[], string nprod[]){ 
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 kg acumulados: "<< endl;
    for(int i=0; i<cantclientes; ++i){
            cout << nclientes[i] << ": ";
        for(int j=0; j<cantprod; ++j){
            if(kg[i][j] > 13000){
                cout << nprod[j] << " ";
                cont[i]++;
            }
        }
        cout << endl;
    }
}

int posmay(int cantclientes[], int cclientes){
    int pos;
	int mayor=cantclientes[0];
    for(int i=0; i<cclientes; ++i){
        if(cantclientes[i] > mayor){
            mayor=cantclientes[i];
            pos=i;
        }
    }
    return pos;
}

//Punto 2
void listadoclientes(float km[][cprod], int var[], int seg[], int cclientes, string nclientes[], string nprod[]){
    float a;
	float b;
	int pos=posmay(var,cclientes);
    cout << endl << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;
	
	do{
		a=0;
		for(int i=1; i<cprod; ++i){
			if(km[pos][i] < km[pos][i-1]){
				b=km[pos][i-1];
            	km[pos][i-1]=km[pos][i];
            	km[pos][i]=b;
            	b=seg[i-1];
            	seg[i-1]=seg[i];
            	seg[i]=b;
            	a++;
			}
        }
    }
    while(a!=0);
    for(int i=0; i<cprod; ++i){
        cout <<nprod[seg[i]] << ": " << km[pos][i] << " km" << endl;
    }
}

//Punto 3
void entregas(float cantkm[][cprod], int cantentregas[][cprod], int seg[], int cantclientes[], int cclientes, string nclientes[], string nprod[]){
    cout << endl << "Cantidad de entregas para el tipo de producto " << nprod[seg[4]] << ": " << endl;
    for(int i=0; i<cclientes; ++i){
        (i == posmay(cantclientes,cclientes)) ? cout << nclientes[i] << ": " << cantentregas[i][4] << " entregas" << endl : cout << nclientes[i] << ": " << cantentregas[i][seg[4]] << " entregas" << endl; 
    }
}

int main(){
    const int cclientes {8};
    
    float peso[cclientes][cprod] {};
    float cantkm[cclientes][cprod] {};
    int cantclientes[cclientes] {};
    int cantentregas[cclientes][cprod] {};
    int seg[cprod] {0,1,2,3,4};
    
    string nclientes[cclientes];
    string nprod[cprod];
    
    ifstream archilec1;
    archilec1.open("Datos.txt");
    if(!archilec1){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    
    int dclientes, dprod;
    float dkg, dkm;
    
    while(archilec1 >> dclientes >> dprod >> dkg >> dkm){
        cantkm[dclientes][dprod]+=dkm;
        peso[dclientes][dprod]+=dkg;
        cantentregas[dclientes][dprod]++;
    }
    
    ifstream archilec2;
    archilec2.open("Nombres.txt");
    if(!archilec2){
        cout << "Error al abrir el archivo";
        return 1;
    }
    
    for(int i=0; i < cclientes; i++){
        archilec2 >> nclientes[i];
    }
    for(int i=0; i < cprod; i++){
        archilec2 >> nprod[i];
    }
    
    //Punto 1
	listado(peso, cantclientes, cclientes, cprod, nclientes, nprod);
	//Punto 2
	listadoclientes(cantkm, cantclientes, seg, cclientes, nclientes, nprod);
	//Punto 3
	entregas(cantkm, cantentregas, seg, cantclientes, cclientes, nclientes, nprod);
    
	archilec1.close();
	archilec2.close();
	
	return 0;
}
