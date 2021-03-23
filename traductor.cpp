#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#define m 30
#define d 300

using namespace std;

const char *nombe_archivo = "traductor.dat";
const char *nom_temporal = "tempo10.dat";

struct Palabra
{
   char palabra[m];
	char traduccion[m];
	char definicion[d];
};

void menu();
void ingresar();
void modificar();
void mostrar();
void buscar();
void eliminar();
void traducir();

int main()
{
    menu();
}

void menu()
{
    int a, b, c;
    do
    {

        system("cls");
    	cout<<"PROYECTO TRADUCTOR C++"<<endl;
		cout<<"----------------------"<<endl;
		cout<<"QUE DESEA HACER: "<<endl<<endl;
		cout<<" INGRESAR DATOS                 [1]"<<endl;
		cout<<" BUSCAR DATO                    [2]"<<endl;
		cout<<" ACTUALIZAR DATOS               [3]"<<endl;
		cout<<" ELIMINAR DATOS                 [4]"<<endl;
		cout<<" LEER LISTA DE DATOS COMPLETA   [5]"<<endl;
		cout<<" TRADUCIR CODIGO                [6]"<<endl;
		cout<<" SALIR                          [7]"<<endl;
        cout<<" Ingrese opcion: [ ]\b\b";
        cin >> a;
        switch (a)
        {
        case 1:
            system("cls");
            ingresar();
            break;
        case 2:
            system("cls");
            buscar();
            break;
        case 3:
            system("cls");
            modificar();
            break;
        case 4:
            system("cls");
            eliminar();
            break;

        case 5:
            system("cls");
            mostrar();
            break;
        case 6:
        	system("cls");
        	traducir();
        }
    } while (a != 7);
}

void ingresar(){
    char continuar;
    FILE *archivo = fopen(nombe_archivo, "ab");
    Palabra palabra;
    string pal,trad,def;
    do
    {
        system("cls");
        fflush(stdin);
        cout<<"INGRESE PALABRA: ";
        getline(cin,pal);
        strcpy(palabra.palabra,pal.c_str());
        
        cout<<"INGRESE SU TRADUCCION: ";
        getline(cin,trad);
        strcpy(palabra.traduccion,trad.c_str());
        
        cout<<"INGRESE LA DEFINICION: ";
        getline(cin,def);
        strcpy(palabra.definicion,def.c_str());
 
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    
        cout << "Desea Agregar otro Dato s/n : ";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}
void mostrar()
{
    system("cls");
    FILE *archivo = fopen(nombe_archivo, "rb");
    if (!archivo)
    {
        archivo = fopen(nombe_archivo, "w+b");
    }

    Palabra palabra;
    int registro = 0;
    fread(&palabra, sizeof(Palabra), 1, archivo);
    do
    {
    	cout<<"PALABRA:    "<<palabra.palabra<<endl;
		cout<<"TRADUCCION: "<<palabra.traduccion<<endl;
		cout<<"DEFINICION: "<<palabra.definicion<<endl;
		cout<<"_______________________________________________________________________________"<<endl;
        fread ( &palabra, sizeof(Palabra), 1, archivo );
        registro += 1;
        
    } while (feof(archivo) == 0);

    cout << endl; 
    fclose(archivo);
    getch();
}

void eliminar()
{
    Palabra palabra;
    
    FILE *temporal = fopen(nom_temporal, "w+b");
    FILE *archivo = fopen(nombe_archivo, "r+b");
    
    int x,existe=0,indice=0,pos=0;
    string pal;
    char p[m],sino;
    
    cout<<"INGRESE PALABRA RESERVADA"<<endl;
	fflush(stdin);
	getline(cin,pal);
	strcpy(p,pal.c_str());

	fread(&palabra,sizeof(Palabra),1,archivo);	
	do{
        x=strcmp(p,palabra.palabra);	
		if(x!=0){
			fwrite(&palabra,sizeof(Palabra),1,temporal);
		}
		if(x==0){
		existe=1;
		pos=indice;
		}
	fread(&palabra,sizeof(Palabra),1,archivo);	
	indice++;
	}while (feof( archivo ) == 0);
	
	if(existe==1){
	fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
	fread(&palabra,sizeof(Palabra),1,archivo);	
	cout<<"PALABRA:   \t"<<palabra.palabra<<endl;
    cout<<"TRADUCCION:\t"<<palabra.traduccion<<endl;
    cout<<"DEFINICION:\t"<<palabra.definicion<<endl;
    cout<<"---------------------------------------\n";
    fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
	cout<<"SEGURO QUE QUIERE ELIMINAR ESTE REGISTRO: [S/N]"<<endl;
	cin>>sino;
	if((sino=='s') || (sino=='S') ){
	fclose(archivo);
	fclose(temporal);
	remove("traductor.dat");
    rename("tempo10.dat","traductor.dat");
    cout<<"REGISTRO ELIMINADO CON EXITO"<<endl;
	}
	else{
	cout<<"EL REGISTRO NO HA SIDO ELIMINADO"<<endl;
	fclose(archivo);
	fclose(temporal);
	remove("tempo10.dat");
	}
	}
	else{
		cout<<"DATO NO ENCONTRADO"<<endl;
	fclose(archivo);
	fclose(temporal);
	remove("tempo10.dat");	
	}
    system("PAUSE");
}

void buscar(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	Palabra palabra;
	int x,existe=0,indice=0,pos=0;
    	string pal;
    	char p[m],sino;
    
    	cout<<"Ingrese palabra a Buscar: "<<endl;
	fflush(stdin);
	getline(cin,pal);
	strcpy(p,pal.c_str());

	fread(&palabra,sizeof(Palabra),1,archivo);	
	do{
        x=strcmp(p,palabra.palabra);
	
    	if(x==0){
		existe=1;
		pos=indice;
		}
	fread(&palabra,sizeof(Palabra),1,archivo);	
	indice++;
	}while (feof( archivo ) == 0);
	
	if(existe==1){
	fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
	fread(&palabra,sizeof(Palabra),1,archivo);	
	cout<<"PALABRA:   \t"<<palabra.palabra<<endl;
    cout<<"TRADUCCION:\t"<<palabra.traduccion<<endl;
    cout<<"DEFINICION:\t"<<palabra.definicion<<endl;
    cout<<"---------------------------------------\n";
    fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
    
    fclose(archivo);
    system("PAUSE");
}
}

void modificar(){
	FILE *archivo = fopen(nombe_archivo, "r+b");
	Palabra palabra;
	string pal1, tra1, def1, pal;
	int x,existe=0,indice=0,pos=0;
	char p[m];
	char respuesta[m];
	cout<< "Ingrese la palabra a modificar"<<endl;
	fflush(stdin);
	getline(cin,pal);
	strcpy(p,pal.c_str());
	
	fread(&palabra,sizeof(Palabra),1,archivo);
	fseek(archivo,pos * sizeof(Palabra), SEEK_SET);	
	do{
        x=strcmp(p,palabra.palabra);
	

	
	 if(x==0){
		existe=1;
		pos=indice;
		}
	fread(&palabra,sizeof(Palabra),1,archivo);	
	indice++;
	}while(feof(archivo) == 0);
	
	cout << ("------------   Datos Encontrados -------------")<<endl;
    
    cout << ("Palabra:  [") << palabra.palabra << ("]")<<endl;
    
    cout << ("Traduccion:  [") << palabra.traduccion << ("]")<<endl;
    
    cout << ("Definicion:  [") << palabra.definicion << ("]")<<endl;
	fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
	cout <<"\n"<<palabra.palabra<<endl;
	cout <<"Desea modificar la palabra?"<<endl;
	cin>>respuesta, m;
	if (strcmp(respuesta, "s") == 0){
        fseek(archivo, pos * sizeof(Palabra), SEEK_SET);
        cin.ignore();
        cout << ("Nueva Palabra : ")<<endl;
        getline(cin, pal1, '\n');
        strcpy(palabra.palabra, pal1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
    
	cout << "\n\nTraduccion: " << palabra.traduccion << endl;
    cout << ("Desea modificar la traduccion? [s/n]: ");
    cin >> respuesta, m;
	if (strcmp(respuesta, "s") == 0){
        fseek(archivo, pos * sizeof(Palabra), SEEK_SET);
        cin.ignore();
        cout << ("Nueva Traduccion: ")<<endl;
        getline(cin, tra1);
        strcpy(palabra.traduccion, tra1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
	cout << "\n\nDefinicion: " << palabra.definicion << endl;
    cout << ("Desea modificar la definicion? [s/n]: ");
	cin >> respuesta, m;	
	if (strcmp(respuesta, "s") == 0){
        fseek(archivo, pos * sizeof(Palabra), SEEK_SET);
        cin.ignore();
        cout << ("Nueva Traduccion: ")<<endl;
        getline(cin, def1);
        strcpy(palabra.definicion, def1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
    system("cls");
    cout << ("Los datos han sido actualizados.");
    system("PAUSE");
    fclose(archivo);
    

}

void traducir(){
}

