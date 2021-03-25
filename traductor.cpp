#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#define m 30
#define d 300

using namespace std;

void buscar_y_reemplazar(string& frase, string buscar,string rempl){
	int pos= frase.find(buscar);
	while (pos != -1){
		frase.replace(pos,buscar.size(),rempl);
		pos = frase.find(buscar, pos+ rempl.size());
	}
}

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
    
        cout << "DESEA AGREGAR OTRO DATO [S/N] : ";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}
void modificar(){
	FILE *archivo = fopen(nombe_archivo, "r+b");
	Palabra palabra;
	string tra1, def1, pal, pal1;
	int x,existe=0,indice=0,pos=0;
	char p[m];
	char respuesta;
	cout<< "INGRESE LA PALABRA A MODIFICAR"<<endl;
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

	cout << ("------------   DATOS ENCONTRADOS -------------")<<endl;
    
    cout << ("PALABRA:     [") << palabra.palabra << ("]")<<endl;
    
    cout << ("TRADUCCION:  [") << palabra.traduccion << ("]")<<endl;
    
    cout << ("DEDINICION:  [") << palabra.definicion << ("]")<<endl;
	fseek ( archivo,pos * sizeof(Palabra), SEEK_SET );
	cout <<"\n"<<palabra.palabra<<endl;
	cout <<"DESEA MODIFICAR LA PALABRA? [S/N]"<<endl;
	cin>>respuesta;
	if ((respuesta=='s') || (respuesta=='S') ){
        cin.ignore();
        cout << ("NUEVA PALABRA : ");
        getline(cin, pal1, '\n');
        strcpy(palabra.palabra, pal1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
    
	cout << "\n\nTRADUCCION: " << palabra.traduccion << endl;
    cout << ("DESEA MODIFICAR LA TRADUCCION? [S/N]: ");
    cin >> respuesta;
	if ((respuesta=='s') || (respuesta=='S') ){
        cin.ignore();
        cout << ("NUEVA TRADUCCION: ");
        getline(cin, tra1);
        strcpy(palabra.traduccion, tra1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
	cout << "\n\nDEFINICION: " << palabra.definicion << endl;
    cout << ("DESEA MODIFICAR LA DEFINICION? [S/N]: ");
	cin >> respuesta;	
	if ((respuesta=='s') || (respuesta=='S') ){
        cin.ignore();
        cout << ("NUEVA TRADUCCION: ")<<endl;
        getline(cin, def1);
        strcpy(palabra.definicion, def1.c_str());
        fwrite(&palabra, sizeof(Palabra), 1, archivo);
    }
    cout << ("LOS DATOS HAYN SIDO ACTUALIZADOS.");
}
if(existe==0){
	cout<<"PALABRA NO ENCONTRADA";
}
	cout<<endl;
    system("PAUSE");
    fclose(archivo);
    

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
void buscar(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	Palabra palabra;
	int x,existe=0,indice=0,pos=0;
    	string pal;
    	char p[m],sino;
    
    	cout<<"INGRESE PALABRA A BUSCAR: "<<endl;
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

void traducir(){
	system("cls");
	FILE* archivo = fopen(nombe_archivo, "rb");
	string frase,p1,p2;
	Palabra palabra;
	cout<<"INGRESE SU CODIGO Y CUANDO FINALICE INGRESE @: "<<endl<<endl;
	getline(cin,frase,'@');
	fread(&palabra,sizeof(Palabra),1,archivo);	
	do{
	p1=palabra.palabra;
	p2=palabra.traduccion;
	buscar_y_reemplazar(frase, p1, p2);
	fread ( &palabra, sizeof(Palabra), 1, archivo );
	} while (feof( archivo ) == 0);
	cout<<endl<<"SU CODIGO TRADUCIDO ES EL SIGUIENTE:"<<endl;
	cout<<"------------------------------------"<<endl;
	 cout<<frase<<endl;
	fclose(archivo);
	system("PAUSE");
}
