/*PROGRAMA DISEÑADO POR: PONTNAU GONZALO - ESTUDAINTE EN INGENIERIA*/
/*PROGRAMA DISEÑADO PARA EL TP N°1 */ 

#include <iostream>
#include <fstream>
using namespace std;


void selection_sort(float v[], int dim, int vpos[]){ //Ordenamiento de seleccion

    for(int pos = 0; pos < dim; pos++){
        int min = pos;
        for(int i = pos + 1; i < dim; i++){
            if(v[i] < v[min]){
                min = i;
            }
        }
        swap(v[pos], v[min]); //intercambia valores.
        swap(vpos[pos], vpos[min]); //intercambia posicion de esos valores.
    } 
}

void mostrarmat(float m[][5], int dfil) {
    
    for (int i=0; i<dfil; i++) {
        for (int j=0; j<5; j++)
            cout << m[i][j] << '\t';
        cout << endl;
    }
}

void mostrarvector (float v[], int dim) {
    
    for (int i = 0; i < dim; i++) {
        cout << i << ": " << v[i] << endl;
        }
}
    
int mayorvector(int v[], int dim){  //busca un valor maximo de un array y devuelve la posicion de ese valor
    
    int max = v[0];
    int pos{0};

    for(int i = 1; i < dim; i++) {
        if (v[i] > max) {
            max = v[i];
            pos = i;
        }
    }
    return pos;
}


int main()
{
    
    ifstream archilec;
    
    archilec.open("Nombres.txt");
    if (!archilec) {
        cout << " No se pudo abrir el archivo de datos" << endl;
        return 1;
    }
    
    const int nclie{8};  //clientes
    const int nprod{5};  //productos
    
    int cont{0};
    
    float entregxpesos[nclie][nprod]{}; // Entregas por pesos
    float entregxdist[nclie][nprod]{}; // Entregas por distancia
    float kmxprod[nprod]{}; //km por producto
    int entregas[nclie]{}; //Tipo de prod con mas de 13kg por cliente
    int vpos[nprod]{}; //Vector de posiciones
    

    string productos[nprod] ;  //Nombra prod
    string clientes[nclie] ;  //Nombra clien
    
    for (int i=0; i<nclie; i++) {       //
        archilec >> clientes[i];        //
    }                                   //
                                        //  Carga los strings
    for (int i=0; i<nprod; i++) {       //
        archilec >> productos[i];       //
    }                                   //
    
    archilec.close();
    
    archilec.open("Datos.txt");
    if (!archilec) {
        cout << " No se pudo abrir el archivo de datos" << endl;
        return 1;
    }

    int iclient, itprod;
    float peso, dist;
    
    while(archilec >> iclient >> itprod >> peso >> dist) {
        
        entregxpesos[iclient][itprod] += peso;   // Sumador de peso por cliente-producto
        entregxdist[iclient][itprod] += dist;  // Sumador de distancia por cliente-producto
        if (productos[itprod] == "Textiles"){
            cont++;
        }
    }    
    
    cout << "Listado de clientes, de los tipos de productos que superan los 13000 kg: " << endl;

    bool flag = true; 

    for(int i=0; i<nclie; i++) {
        flag = true;
        for(int j=0; j<nprod; j++) {
          if(entregxpesos[i][j] > 13000){
                entregas[i]++;
                if(flag == true){              
                    cout << clientes[i] << ": ";   
                    flag = false;
                } else {
                    cout << ", ";
                }
                cout << productos[j]; 
            }
        } 
        cout << endl; 
    } 
    cout << endl;

    int max = mayorvector(entregas, nclie);

    cout <<  "Cliente con mayor cantidad de tipos de productos que hayan superado los 13000 kg: " << clientes[max] << endl << endl;

    cout << "Listado en forma ascendente de kilometros recorridos por tipo de producto :" << endl;
    
    for(int i=0; i<nprod; i++){
        kmxprod[i] = entregxdist[max][i]; 
    }

    for(int i=0; i<nprod; i++){  //vposs
        vpos[i] = i;
    }

    selection_sort(kmxprod, nprod, vpos);

    for(int i=0; i<nprod; i++){  //Forma ascendente.
        cout << productos[vpos[i]] << ": " << kmxprod[i] << endl;  
    } cout << endl;                                                

    cout << "Entregas para Textiles: " << cont << endl;

    archilec.close();

    return 0; 
}