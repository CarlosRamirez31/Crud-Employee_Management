#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

struct Empleados{
	char cedula[20], nombre[20], apellido[20], gmail[30], telefono[20];
	char departamento[20], cargo[20];
	char codigo[10];
	int cHora,sNeto, hTrabaja, edad;
}Em;

void accesoAdmin();
void menu();
void crearEmpleado(ofstream &);
void cargo(Empleados &);
void departamento(Empleados &);
void ver(ifstream &);
void eliminar(ifstream &);
void modificar(ifstream &);
bool verificar(Empleados, char[]);
void exportar(ifstream &);
void cobrar(ifstream &);
void ordenar();
void ordenarEdad(ifstream &);
void burbujaN(Empleados [], int);
void burbujaCN(Empleados [], int);
void burbujaCA(Empleados [], int);
void cobrar(ifstream &);
void recibosPagos(ifstream &);
void reporte(ifstream &);

ofstream imprimir;
ifstream leer;
int cont = 0, opcion;
Empleados *array;

void accesoAdmin(){
	string nombre, contra;
	char letra;
	
	do{
		cout << "\tControl de Acceso" << endl;
		cout << "Digite su nombre: "; getline(cin, nombre);
		cout << "Digite la contrasena: "; 
		
		letra = getch();
		contra = "";
		while(letra != 13){
			if(letra!=8){
				contra.push_back(letra);
				cout << "*";
			}
			else{
				if(contra.length() > 0){
					cout << "\b \b";
					contra = contra.substr(0,contra.length() -1);
				}
			}
			letra = getch();
		}
		
		if((nombre == "admin") && (contra == "admin")){
			system("cls");
			menu();
		}
		else{
			cout << "\n\nEl usuario y la contrasena es incorrecto " << endl;
			system("pause");
		}
		system("cls");
	}
	while((nombre != "12345") || (contra != "12345"));
}

void menu(){
	do{
		cout << "\tAplicacion que maneja la creacion de empleado" << endl;
		cout << "1. Crear empleado" << endl;
		cout << "2. Ver todos los empleados existentes" << endl;
		cout << "3. Eliminar un empleado" << endl;
		cout << "4. Modificar un empleado" << endl;
		cout << "5. Exportar Empleados" << endl;
		cout << "6. Ordenar(nombre, apellido, edad)" << endl;
		cout << "7. Cobrar" << endl;
		cout << "8. Recibos de pagos" << endl;
		cout << "9. Reporte" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				crearEmpleado(imprimir); break;
			case 2:
				ver(leer); break;
			case 3:
				eliminar(leer); break;
			case 4:
				modificar(leer); break;
			case 5:
				exportar(leer); break;
			case 6:
				ordenar(); break;
			case 7:
				cobrar(leer); break;
			case 8:
				recibosPagos(leer); break;
			case 9: 
				reporte(leer); break;
			case 10:
				cout << "Gracias por usar el menu" << endl;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 10);
}

void crearEmpleado(ofstream &empleado){
	char rpt;
	
	empleado.open("Empleados.dat", ios::out | ios::binary | ios::app);
	
	if(empleado.fail()){
		cerr << "Error no se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	do{
		fflush(stdin);
		cin.clear();
		cout << "\tNuevo empleado" << endl;
		cout << "Digite su nombre: "; cin.getline(Em.nombre,20,'\n');
		cout << "Digite su apellido: "; cin.getline(Em.apellido,20,'\n');
		cout << "Digite su edad: "; cin >> Em.edad;
		fflush(stdin);
		cout << "Digite su cedula: "; cin.getline(Em.cedula,20,'\n');
		cout << "Digite su numero telefonico: "; cin.getline(Em.telefono,20,'\n');
		cout << "Digite su Gmail: "; cin.getline(Em.gmail,30,'\n');
		departamento(Em);
		cargo(Em);
		cout << "\nCobro por hora: "; cin >> Em.cHora;
		cout << Em.codigo << endl;
		
		if(verificar(Em,Em.cedula)){
			empleado.write((char*)&Em,sizeof(Empleados));
		}
		
		cout << "\tQuiere agragar otro empleado(s/n)? "; cin >> rpt;
		system("cls");
	}
	while((rpt == 's') || (rpt == 'S'));
	
	empleado.close();
}

void departamento(Empleados &Em){
	ostringstream convertir;
	string codigo;
	
	srand(time(NULL));
	
	do{
	
		cout << "\tDepartamento" << endl;
		cout << "1. Recursos Humanos" << endl;
		cout << "2. Produccion" << endl;
		cout << "3. Control de gestion" << endl;
		cout << "4. Marketing" << endl;
		cout << "5. Finanzas" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		convertir << rand() % (10000-1000);
		switch(opcion){
			case 1:
				strcpy(Em.departamento,"Recursos Humanos"); break;
			case 2:
				strcpy(Em.departamento,"Produccion"); break;
			case 3:
				strcpy(Em.departamento,"Control de gestion"); break;
			case 4:
				strcpy(Em.departamento,"Marketing"); break;
			case 5:
				strcpy(Em.departamento,"Finanzas"); break;
			default:
				cout << "\tPor el momento solo exiten 5 departamaneto, elija uno de los mostrado" << endl;
		}
		codigo = Em.departamento;
		strcpy(Em.codigo,(codigo.substr(0,3) + convertir.str()).c_str());
		
	}
	while((opcion < 1) || (opcion > 5));
}

void cargo(Empleados &Em){
	do{
		cout << "\nCargos.- 1. Gerencial. 2.Administrativo. 3. Operativo: "; cin >> opcion;
		
		switch(opcion){
			case 1:
				strcpy(Em.cargo,"Gerencial"); break;
			case 2:
				strcpy(Em.cargo,"Administrativo"); break;
			case 3:
				strcpy(Em.cargo,"Operativo"); break;
			default:
				cout << "\tPor el momento solo tenemos tres cargo, elija uno." << endl;
				
		}
	}
	while((opcion < 1) || (opcion > 3));
}

void ver(ifstream &ver){
	string empleado;
	
	ver.open("Empleados.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "Error no se pudo abrir el archivo" << endl;
		exit(1);
	}

	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		
		if(!ver.eof()){
			cout << "Nombre: " << Em.nombre << endl;
			cout << "Apellido: " << Em.apellido << endl;
			cout << "Edad: " << Em.edad << endl;
			cout << "Cedula: " << Em.cedula << endl;
			cout << "Numero telefonico: " << Em.telefono << endl;
			cout << "Gmail: " << Em.gmail << endl;
			cout << "Departamento: " << Em.departamento << endl;
			cout << "Cargo: " << Em.cargo << endl;
			cout << "Cobro por horas: " << Em.cHora << endl;
			cout << "Codigo: " << Em.codigo << endl;
			cout << "\n";
		}
	}
	
	ver.close(); 
}

void eliminar(ifstream &ver){
	char cAux[10];
	ofstream aux1;
	
	ver.open("Empleados.dat", ios::in | ios::binary);
	aux1.open("noc.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "Error en abrir" << endl;
		exit(1);
	}
	
	if(aux1.fail()){
		cerr << "Error en abrir aux" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del empleado: "; cin.getline(cAux,10,'\n');
	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		
		if(!ver.eof()){
			if(strcmp(cAux,Em.cedula) == 0){
				fflush(stdin);
				cout << "\tEmpleado eliminado" << endl;
			}
			else{
				aux1.write((char*)&Em,sizeof(Empleados));
			}	
		}
	}
	
	ver.close();
	aux1.close();
	
	remove("Empleados.dat");
	rename("noc.dat","Empleados.dat");
}

void modificar(ifstream &modificar){
	char cAux[10];
	ofstream aux1;
	
	modificar.open("Empleados.dat", ios::in | ios::binary);
	aux1.open("noc.dat", ios::out | ios::binary);
	
	if(modificar.fail()){
		cerr << "Error en abrir el archivo" << endl;
		exit(1);
	}
	
	if(aux1.fail()){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}
	
	
	Empleados aux;
	
	fflush(stdin);
	cout << "Digite la cedula del empleado: "; cin.getline(cAux,10,'\n');
	while(!modificar.eof()){
		modificar.read((char*)&Em,sizeof(Empleados));
		
		if(modificar.eof()){
			if(strcmp(cAux,Em.cedula) == 0){
				fflush(stdin);
				cout << "Digite el nuevo nombre: "; cin.getline(Em.nombre,20,'\n');
				cout << "Digite el nuevo apellido: "; cin.getline(Em.apellido,20,'\n');
				cout << "Digite su nueva edad: "; cin >> Em.edad;
				fflush(stdin);
				cout << "Cedula: " << Em.cedula << endl;
				cout << "Digite su nuevo numero telefonico: "; cin.getline(Em.telefono,20,'\n');
				cout << "Digite su nuevo Gmail: "; cin.getline(Em.gmail,30,'\n');
				departamento(Em);
				cargo(Em);
				cout << "\nDigite el nuevo salario por hora: "; cin >> Em.cHora;
				cout << "Codigo: " << Em.codigo << endl;
				
				aux = Em;
				if(verificar(Em,"-00")){
					aux1.write((char*)&aux,sizeof(Empleados));
				}
				else{
					aux1.write((char*)&Em,sizeof(Empleados));
				}
				cout << "\n";		
			}
			else{
				aux1.write((char*)&Em,sizeof(Empleados));
			}	
		}
	}
	
	modificar.close();
	aux1.close();
	
	remove("Empleados.dat");
	rename("noc.dat","Empleados.dat");
}

bool verificar(Empleados verif, char ced[]){
	ifstream ver;
	ver.open("Empleados.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "Error no se pudo abrir el archivo" << endl;
		exit(1);
	}

	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		
		if(!ver.eof()){
			if((strcmp(verif.cargo,Em.cargo) == 0)){
				leer.close();
				cout << "\nSolo puede haber un empleado de la categoria Gerencial." << endl;
				return false;
			}
			else if(strcmp(ced,Em.cedula) == 0){
				leer.close();
				cout << "\nLo siento la cedula que esta intentado ingresar ya existe, intente mas tarde" << endl;
				return false;
			}
		}
	}
	
	ver.close();
	return true;
}

void exportar(ifstream &ver){
	string nombre;
	ofstream aux1;
	
	cout << "Exportar Empleados cvs" << endl;
	fflush(stdin);
	cout << "Digite la ruta y extencion de archivo: "; getline(cin,nombre);
	
	ver.open("Empleados.dat", ios::in | ios::binary);
	aux1.open(nombre.c_str(), ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "Error en abrir" << endl;
		exit(1);
	}
	
	if(aux1.fail()){
		cerr << "Error en abrir aux" << endl;
		exit(1);
	}
	
	aux1 << "\tEmpleados\n";
	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		
		if(!ver.eof()){
			aux1 << "\nNombre: " << Em.nombre << endl;
			aux1 << "Apellido: " << Em.apellido << endl;
			aux1 << "Edad: " << Em.edad << endl;
			aux1 << "Cedula: " << Em.cedula << endl;
			aux1 << "Numero de telefono: " << Em.telefono << endl;
			aux1 << "Gmail: " << Em.gmail << endl;
			aux1 << "Departamento: " << Em.departamento << endl;
			aux1 << "Cargo: " << Em.cargo << endl;
			aux1 << "Cobro por hora: " << Em.cHora << endl;
			aux1 << "Codigo: " << Em.codigo << endl;
		}
		else{
			cout << "\tEl archivo se ha exportando con exito" << endl;
		}
	}
	
	ver.close();
	aux1.close();
}

void ordenar(){	
	do{
		cout << "Seleccione como quiere ordenar el archivo" << endl;
		cout << "1. Nombre" << endl;
		cout << "2. Apellido" << endl;
		cout << "3. Edad" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				ordenarEdad(leer); break;
			case 2:
				ordenarEdad(leer); break;
			case 3:
				ordenarEdad(leer); break;
			default:
				cout << "Selecciones unas de las opciones mostradas" << endl;
		}
		system("pause");
		system("cls");
	}
	while((opcion<=0) || (opcion>=4));
}

void ordenarEdad(ifstream &ver){
    int tamanio = sizeof(Empleados);
    int i = 0, numRegistros;
    ofstream aux1;
    

    ver.open("Empleados.dat", ios::in | ios::binary);
    aux1.open("noc.dat", ios::out | ios::binary);
    
    if(ver.fail()){
       cerr << "Error al abrir el archivo" << endl;
       exit(1);
    }
    
    if(aux1.fail()){
    	cerr << "Error al abrir el archivo" << endl;
    	exit(1);
	}
    


    ver.seekg(0,ios::end);
    numRegistros=ver.tellg()/tamanio;

    array = new Empleados[numRegistros];
    if(array==NULL){
       cerr << "Error en la asignación de memoria\n";
       exit(1);
    }

    ver.seekg(0);
    
    ver.read((char *) &array[i], tamanio);
    while(!ver.eof()){
    	i++;
        ver.read((char *) &array[i], tamanio);
    }
    
    if(opcion == 1){
    	burbujaCN(array,numRegistros);
	}
	else if(opcion == 2){
		burbujaCA(array,numRegistros);
	}
	else{
		burbujaN(array,numRegistros);
	}
   
	for(i=0;i<numRegistros;i++){
		cout << "Nombre: " << array[i].nombre << endl;
		cout << "Apellido: " << array[i].apellido << endl;
		cout << "Edad: " << array[i].edad << endl;
		cout << "Cedula: " << array[i].cedula << endl;
		cout << "Numero telefonico: " << array[i].telefono << endl;
		cout << "Gmail: " << array[i].gmail << endl;
		cout << "Departamento: " << array[i].departamento << endl;
		cout << "Cargo: " << array[i].cargo << endl;
		cout << "Cobro por horas: " << array[i].cHora << endl;
		cout << "Codigo: " << array[i].codigo << endl;
		cout << "\n";
		aux1.write((char*)&array[i],tamanio);
    }
    
    ver.close();
    aux1.close();
    delete [] array;
    
    remove("Empleados.dat");
    rename("noc.dat","Empleados.dat");
}


void burbujaCN(Empleados A[], int N){
	Empleados aux;
	
	for(int i=0;i<N-1;i++){
		for(int j=0;j<N-i-1;j++){
   			if(strcmp(A[j+1].nombre,A[j].nombre) < 0){               
    			aux=A[j+1];   
    			A[j+1]=A[j];  
    			A[j]=aux;
    		}
		}
	}  
}

void burbujaCA(Empleados A[], int N){
	Empleados aux;
	
	for(int i=0;i<N-1;i++){
		for(int j=0;j<N-i-1;j++){
   			if(strcmp(A[j+1].apellido,A[j].apellido) < 0){               
    			aux=A[j+1];   
    			A[j+1]=A[j];  
    			A[j]=aux;
    		}
		}
	}  
}

void burbujaN(Empleados A[], int N){
	Empleados aux;
	
	for(int i=0;i<N-1;i++){
		for(int j=0;j<N-i-1;j++){
   			if(A[j+1].edad<A[j].edad){               
    			aux=A[j+1];   
    			A[j+1]=A[j];  
    			A[j]=aux;
    		}
		}
	}  
}

void cobrar(ifstream &ver){
	char ced[20];
	int hTrabaja;
	ofstream aux1;
	
	ver.open("Empleados.dat", ios::in | ios::binary);
	aux1.open("Recibos.dat", ios::out | ios::binary | ios::app);
	
	if(ver.fail()){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}
	
	if(aux1.fail()){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}
	
	cout << "Digite su cedula: "; cin >> ced;
	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		if(!ver.eof()){
			if(strcmp(Em.cedula,ced) == 0){	
			cout << "Digite las horas trabajadas: "; cin >> Em.hTrabaja;
			
			if(strcmp(Em.cargo,"Gerencial") == 0){
				Em.sNeto = (Em.cHora * Em.hTrabaja) + ((Em.cHora * Em.hTrabaja)*0.50);
			}
			else if(strcmp(Em.cargo,"Administrativo") == 0){
				Em.sNeto = (Em.cHora * Em.hTrabaja) + ((Em.cHora * Em.hTrabaja)*0.25);
			}
			else{
				Em.sNeto = (Em.cHora * Em.hTrabaja) + ((Em.cHora * Em.hTrabaja)*0.10);
			}
			cout << "\tSu pago se ha realizado correctamente" << endl;
			
			aux1.write((char*)&Em,sizeof(Empleados));
			}
		}
	}
	
	ver.close();
	aux1.close();
}

void recibosPagos(ifstream &ver){
	ver.open("Recibos.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}

	while(!ver.eof()){
		ver.read((char*)&Em,sizeof(Empleados));
		if(!ver.eof()){
			cout << "Codigo: " << Em.codigo << endl;
			cout << "Nombre: " << Em.nombre << endl;
			cout << "Apellido: " << Em.apellido << endl;
			cout << "Cargo: " << Em.cargo << endl;
			cout << "Precio por hora: " << Em.cHora << endl;
			cout << "Horas Trabajadas: " << Em.hTrabaja << endl;
			cout << "Salario neto: " << Em.sNeto << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void reporte(ifstream &ver){
	int tamanio = sizeof(Empleados);
    int i = 0, numRegistros,cont1 = 0, cont2 = 0, cont3 = 0, j,k;
    ofstream aux1;
    Empleados mayor,menor;

    ver.open("Empleados.dat", ios::in | ios::binary);
    
    if(ver.fail()){
       cerr << "Error al abrir el archivo" << endl;
       exit(1);
    }

    ver.seekg(0,ios::end);
    numRegistros=ver.tellg()/tamanio;

    array = new Empleados[numRegistros];
    if(array==NULL){
       cerr << "Error en la asignación de memoria\n";
       exit(1);
    }

    ver.seekg(0);
    
    ver.read((char *) &array[i], tamanio);
    while(!ver.eof()){
    	i++;
        ver.read((char *) &array[i], tamanio);
    }
    
    mayor.cHora = 0;
    menor.cHora = 999999;
    for(int i=0;i<numRegistros;i++){
    	if(array[i].cHora > mayor.cHora){
    		mayor = array[i];
		}
		
		if(array[i].cHora < menor.cHora){
			menor = array[i];
		}
		
		if(strcmp(array[i].cargo,"Gerencial") == 0){
			cont1++;
		}
		else if(strcmp(array[i].cargo,"Administrativo") == 0){
			cont2++;
		}
		else{
			cont3++;
		}
	}
	
	cout << "\tEmpleado mejor pagado" << endl;
	cout << "Codigo: " << mayor.codigo << endl;
	cout << "Nombre: " << mayor.nombre << endl;
	cout << "Apellido: " << mayor.apellido << endl;
	cout << "Cargo: " << mayor.cargo << endl;
	cout << "Cobro por hora: " << mayor.cHora << endl;
	
	cout << "\n\tEmpleado menor pagado" << endl;
	cout << "Codigo: " << menor.codigo << endl;
	cout << "Nombre: " << menor.nombre << endl;
	cout << "Apellido: " << menor.apellido << endl;
	cout << "Cargo: " << menor.cargo << endl;
	cout << "Cobro por hora: " << menor.cHora << endl;
	
	cout << "\nEmpleados Gerencial: " << cont1 << endl;
	cout << "Empleados Administrativo: " << cont2 << endl;
	cout << "Empleados Operativo: " << cont3 << endl;
	
	
	ver.close();
	delete [] array;
}