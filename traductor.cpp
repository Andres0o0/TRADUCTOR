#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
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
    
    int x,existe=0;
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
		}
	fread(&palabra,sizeof(Palabra),1,archivo);	
	}while (feof( archivo ) == 0);
	
	if(existe==1){
		cout<<"DATO ELIMINADO"<<endl;
	}
	else{
		cout<<"DATO NO ENCONTRADO"<<endl;	
	}
	
    cout<<endl;
	fclose(archivo);
	fclose(temporal);
	remove("traductor.dat");
    rename("tempo10.dat","traductor.dat");
    system("PAUSE");
}

void buscar(){
}

void modificar(){
}

void traducir(){
}
/*void buscar()
{

   FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que Dato desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Planilla), SEEK_SET );
	
	Planilla plan;
    
    fread(&plan, sizeof(Planilla), 1, archivo);

    cout << "Codigo: " <<pos<< endl;
    cout << "Nombre: " << plan.nombre << endl;
    cout << "Apellido: " << plan.apellido << endl;
    cout << "Puesto: " << plan.puesto << endl;
    cout << "Sueldo Base: " << plan.sueldo << endl;
    cout << "Bonificacion: " << plan.bonificacion << endl;
    cout << "Total: " << plan.total << endl;
    cout << endl;

    fclose(archivo);
    system("PAUSE");
}
void modificar()
{
    FILE *archivo = fopen(nombe_archivo, "r+b");
    int id;
    char respuesta[s];
    string nombre, apellido, puesto;
    Planilla plan;

    cout << "Ingrese el ID que desea Modificar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Planilla), SEEK_SET); // esto es lo que permite modificar en la pocision
    fread(&plan, sizeof(Planilla), 1, archivo);

    cout << ("------------   Datos Encontrados -------------")<< endl;
    cout << ("nombre:  [") << plan.nombre << ("]")<< endl;
    cout << ("apellido:  [") << plan.apellido << ("]")<< endl;
    cout << ("Puesto:  [") << plan.puesto << ("]")<< endl;
    cout << ("Sueldo Base:  [") << plan.sueldo << ("]")<< endl;
    cout << ("bonificacion [") << plan.bonificacion << ("]")<< endl;
    cout << ("---------------------------------------------")<< endl;
    cout << "<\n\n Nombre: " << plan.nombre << endl;
    cout << ("Desea modificar [s/n]: ")<< endl;
    cin >> respuesta, s;

    if (strcmp(respuesta, "s") == 0)
    {

        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << ("Nuevo Nombre : ");
        getline(cin, nombre);
        strcpy(plan.nombre, nombre.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nApellido: " << plan.apellido << endl;
    cout << ("Desea Modificar la Apellido [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << "Ingrese Nuevo Apellido: ";
        getline(cin, apellido);
        strcpy(plan.apellido, apellido.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nPuesto: " << plan.puesto << endl;
    cout << ("Desea modificar el puesto [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();

        cout << "Ingrese Nuevo Puesto: ";
        getline(cin, puesto);
        strcpy(plan.puesto, puesto.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nSueldo: " << plan.sueldo << endl;
    cout << ("Desea Modificar el Sueldo [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();

        cout << "Ingrese Nuevo Sueldo: ";
        cin >> plan.sueldo;
        plan.total = plan.sueldo + plan.bonificacion;
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nBonificion: " << plan.bonificacion << endl;
    cout << ("Desea Modificar la Bonificacion [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0){
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << "Ingrese la Neva Bonificacion: ";
        cin >> plan.bonificacion;
        plan.total = plan.sueldo + plan.bonificacion;
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << ("Datos actualizados");
    fclose(archivo);
    getch();
    mostrar();
}
*/
