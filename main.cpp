//Repositorio
//https://github.com/zelaya201/Sistema-de-Planilla.git

/*Tildar letras
á –> \xA0; 
é –> \x82; 
í –> \xA1; 
ó –> \xA2; 
ú –> \xA3; 
ñ –> \xA4; 
Ñ –> \xA5;
*/

#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <iomanip>
#include <math.h>
#define row 100
#define cols 50
#define ANSI_COLOR_RED     "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[92m"
#define ANSI_COLOR_YELLOWLIGTH     "\x1b[93m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;

struct Empleados {
    char dui[10];
    char nom[50];
    char ape[50];
    char cargo[50];
    float salario;
    float afp;
    float isss;
    float descuento[12];
    float salarioN[12];
}e[100];

void header(); //Diseño completo (Cabecera y cuadro del cuerpo)
void headerWithoutsquare(); //Solo cabecera
void gotoxy(int, int );// x - y
void cuadro(int, int, int, int);//derecha, arriba, izquierda, abajo
void cls(int, int , int);
int menu();
int validar_numero(char []);
int validar_cadena(char []);
void registroEmpleados(int &);//dui, e.e[i].nombre, apellidos, cargo, salario, indice
void registroEmpleados_registrar(int &);//dui, e.e[i].nombre, apellidos, cargo, salario, indice
void registroEmpleados_edit(int &);//dui, e.e[i].nombre, apellidos, cargo, salario, indice
void registroEmpleados_delete(int &);//dui, e.e[i].nombre, apellidos, cargo, salario, indice
void registroDescuentos(int);
int buscarEmpleados(char[50], int, char[25], char[25], int&, int&);
bool verificarEmpleado(char [50],int);
void mostrarEmpleados(char [50], int, int [], int&, int&);
void planillaMensual(int&);
// void repDescuento(int mes /*  */);

void cuadroPlanillas(int x1, int y1, int x2, int y2);/* inter[], int& y, int& x)  */
void menuMeses();

int main(){

    int op;

    /*int dui[row] = {'\0'};
    int indice = 0;
    char e.e[i].nom[row][cols] = {'\0'}, ape[row][cols] = {'\0'}, cargo[row][cols] = {'\0'};
    float salario[row]; */

    /* PARA PROBAR Y EVITARSE ESTAR REGISTRANDO DATOS XD */

    char dui[row][10] = {{"012345678"},{"087654321"},{"017283782"},{"010293827"},{"029382019"},{"020391827"},{"099281762"},{"028379120"},{"090908990"}};
    int indice = 9;
    char nom[row][cols] = {
        {"Josue Adonay"},
        {"Walter Alejandro"},
        {"Julio Antonio"},
        {"Keneth Valerio"},
        {"Mario Ernesto"},
        {"Shelsy Yamileth"},
        {"Karla Beatriz"},
        {"Luis Fernando"},
        {"Baltasar Francisco"}
    };

    char ape[row][cols] = {
        {"Aguilar Constanza"},
        {"Morales Constanza"},
        {"Torres Constanza"},
        {"Ramirez Ramirez"},
        {"Zelaya Constanza"},
        {"Constanza Abarca"},
        {"Aguilar Constanza"},
        {"Vaquerano Constanza"},
        {"Constanza Aguilar"}
    };

    char cargo[row][cols] = {
        {"Programador"},
        {"DBA"},
        {"Analista"},
        {"Redes"},
        {"Ingeniero"},
        {"Servicio Social"},
        {"Disenador Grafico"},
        {"Periodista"},
        {"Biologo"}
    }; 
    
    float salario[row] = {2100,900,1400,1000,1830,800,1200,2001,900}; 
    system("title Sistema de Planillas"); //Titulo de ventana
    system("mode con: cols=120 lines=30");

    for (int i = 0; i < indice; i++) {
        strcpy(e[i].dui, dui[i]);
        strcpy(e[i].nom, nom[i]);
        strcpy(e[i].ape, ape[i]);
        strcpy(e[i].cargo, cargo[i]);
        e[i].salario = salario[i];
    }

    do{
        op = menu(); //opcion

        switch(op){
            case 1: system("cls");registroEmpleados(indice);break; //Modulo 1
            case 2: system("cls");cout<<"Modulo en proceso";break; //Modulo 2
            case 3: system("cls");planillaMensual(indice);break; //Modulo 3
            case 4: system("cls");cout<<"Modulo en proceso";break; //Modulo 4
            case 5: system("cls");registroDescuentos(indice);break; //Modulo 5
            case 6: gotoxy(42,22);cout<<ANSI_COLOR_YELLOWLIGTH<<"Mensaje: Hasta luego, vuelva pronto";cuadro(40,21,78,23);cout<<ANSI_COLOR_RESET;Sleep(3000);break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: M"<<"\xA2"<<"dulo incorrecto";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
        }


    }while(op != 6);

    return 0;
}

int menu(){// Mis opciones [3] y [4]

    char opAux[2];
    int opcion;

    system("cls");
    header();

	gotoxy(10,9);
	cout<<"Elija una opci\xA2n: ";

	gotoxy(10,11);
	cout<<"[1] Registro de empleados";
	gotoxy(10,12);
	cout<<"[2] Registro de retenciones de ley";
	gotoxy(10,13);
	cout<<"[3] Informe de planillas mensuales";
	gotoxy(10,14);
	cout<<"[4] Informe de planillas quincenales";
	gotoxy(10,15);
	cout<<"[5] Registro de descuentos";
	gotoxy(10,16);
	cout<<"[6] Salir";
	
	gotoxy(10,18);
	cout<<"Selecciona: ";
    gets(opAux);
    fflush(stdin);
    opcion = validar_numero(opAux); //Validar opcion

    return opcion; 
} // Menu para hacer uso
// Modulo Julio Torres
/* void menuMeses(){
    gotoxy(43,3);
    headerWithoutsquare();
    cuadroPlanillas(4,6,153,28);
    char meses[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int i = 12;
    for (int x = 0; x < 1; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            gotoxy(13, i + y);
            cout << y + 1 << '.' << meses[y] << " ";
            cout << endl;
        }
        // cout << endl;
    }
    
    for (int me = 0; me < 12; me++)
    {
        if (strcmp(meses[me], correcto[me]) == 0)
        {
            cout << meses[me];
        }
        
    } 
    getch();
} */
void planillaMensual(int& indice)
{
    int y = 13,i = 12;
    float AFP[100], isss[100]; // podria hacerse con estructura
    char meses[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    // cuadro(4,6,114,28);
    system("mode con: cols=160 lines=30");
    system("cls");
    gotoxy(43,3);
    cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";
        if(indice > 9){
            cuadroPlanillas(4,6,153,20+indice);
        }else{
            cuadroPlanillas(4,6,153,28);
        }
        cuadro(4,1,153,5);
        gotoxy(10,9);
        printf("%c Planilla Mensual / Aqui el mes",254); // El mes elegido del menu
    
    getch();
        gotoxy(12,12);
        cout<<"DUI";
        cuadro(8,11,20,13);

        gotoxy(27,12);
        cout<<"Nombre";
        cuadro(20,11,42,13);

        gotoxy(48,12);
        cout<<"Apellidos";
        cuadro(42,11,66,13);

        gotoxy(71,12);
        cout<<"Cargo";
        cuadro(66,11,86,13);

        gotoxy(89,12);
        cout<<"Salario";
        cuadro(86,11,99,13);
        
        gotoxy(104,12);
        cout<<"AFP";
        cuadro(99,11,112,13);
        
        gotoxy(116,12);
        cout<<"ISSS";
        cuadro(112,11,125,13);
        
        gotoxy(127,12);
        cout<<"Descuentos";
        cuadro(125,11,138,13);

        gotoxy(140,12);
        cout<<"Salario N";
        cuadro(138,11,150,13);
        if(indice <= 0){
            gotoxy(32,y+2);
            cout<<"No hay empleados registrados, por favor ingrese datos";
            getch();
        }else{
            for(int i = 0; i < indice; i++){

                y++;

                gotoxy(10,y);
                cout<<e[i].dui;

                gotoxy(22,y);
                cout<<e[i].nom;
                
                gotoxy(44,y);
                cout<<e[i].ape;
                

                gotoxy(68,y);
                cout<<e[i].cargo;
                

                gotoxy(88,y); // AFP
                cout<<"$"<<e[i].salario;
                
                gotoxy(103,y);
                e[i].afp = (e[i].salario*0.0725); // Aqui recibire el calculo del modulo de Walter!!
                cout << "$" << setprecision(5) << e[i].afp;
        
                gotoxy(116,y);
                e[i].isss = (e[i].salario*0.03); // Parte del modulo de Walter
                cout << "$" << ceil(e[i].isss) << ".00";

                gotoxy(127,y);
                cout << "000.00";
                /* Aqui el mostrar el modulo de Mario */

                gotoxy(141, y);
                cout << "000.00";
            }
        }
    getch();
    system("mode con: cols=120 lines=30");
}
// Aqui inicia el modulo de Adonay @xdesprox
void registroEmpleados(int& indice){

    char select[2];
    int op;

    do{
        system("cls");
        header();
        gotoxy(10,9);
        printf("%c Registro de empleados",254);
        gotoxy(10,11);
        cout<<"[1] Registrar";
        gotoxy(10,12);
        cout<<"[2] Editar";
        gotoxy(10,13);
        cout<<"[3] Eliminar";
        gotoxy(10,14);
        cout<<"[4] Atras";
        gotoxy(10,16);
        cout<<"Selecciona: ";
        gets(select);
        fflush(stdin);

        op = validar_numero(select);

        //Submenu
        switch(op){
            case 1: system("cls"); registroEmpleados_registrar(indice); break;
            case 2: system("cls"); registroEmpleados_edit(indice); break;
            case 3: system("cls"); registroEmpleados_delete(indice);break;
            case 4: break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
        }

    }while(op != 4);

}

void registroEmpleados_registrar(int& indice){

    int cant;
    int dui;
    int centinela;
    char SV[10];
    char *salarioAux;
    string errores, mensaje;

    system("cls");

    header();
    cuadro(6,20,112,27);
    gotoxy(8,21);
    cout<<"Mensaje(s): ";
    gotoxy(8,23);
    cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Dig\xA1ta [1] en cualquier campo para volver."<<ANSI_COLOR_RESET;
    gotoxy(10,9);
    printf("%c Registro de empleados / Registrar",254);

    /* DUI */

    do{
        centinela = 1;
        cant = 1;

        cls(70, 11, 11);

        gotoxy(11,11);
        printf("N%c de DUI: ",167);
        gets(e[indice].dui);
        fflush(stdin);

        dui = validar_numero(e[indice].dui);

        //Si hay otro dui igual
        for(int i = 0; i < indice; i++){
            if((strcmp(e[indice].dui, e[i].dui) == 0) && (i != indice)){
                cant++;
            }
        }

        //Si digita uno regresa
        if(strcmp(e[indice].dui, "1") == 0){
            goto salir;
        }

        if(strlen(e[indice].dui) != 9 || dui == -1){ 
            errores = "N\xA3mero de DUI mayor o menor a 9 cifras y/o incorrecto.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            centinela = 0;
            getch();
            cls(54, 20, 21);
        }else if(cant > 1){
            errores = "N\xA3mero de DUI ya existente, ingrese otro.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            centinela = 0;
            getch();
            cls(54, 20, 21);
        }

        
    }while(centinela != 1);   

    /* NOMBRE */

    do{
        centinela = 1;
        cls(70, 11, 12);

        gotoxy(11,12);
        cout<<"Nombre: ";
        gets(e[indice].nom);

        //Si digita uno regresa
        if(strcmp(e[indice].nom, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].nom) > 0 || (e[indice].nom[0] == '\0') || (e[indice].nom[0] == ' ')){
            errores = "Nombre incorrecto.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(19, 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);  

    /* APELLIDOS */

    do{
        centinela = 1;
        cls(70, 11, 13);

        gotoxy(11,13);
        cout<<"Apellidos: ";
        gets(e[indice].ape);

        //Si digita uno regresa
        if(strcmp(e[indice].nom, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].ape) > 0 || (e[indice].ape[0] == '\0') || (e[indice].ape[0] == ' ')){
            errores = "Apellidos incorrectos.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(23, 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);

    /* CARGO */
    
    do{
        centinela = 1;
        cls(70, 11, 14);

        gotoxy(11,14);
        cout<<"Cargo: ";
        gets(e[indice].cargo);

        //Si digita uno regresa
        if(strcmp(e[indice].cargo, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].cargo) > 0 || (e[indice].cargo[0] == '\0') || (e[indice].cargo[0] == ' ')){
            errores = "Cargo escrito incorrectamente.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(31, 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);

    /* SALARIO */
    
    do{
        centinela = 1;
        cls(70, 11, 15);

        gotoxy(11,15);
        cout<<"Salario: $";
        gets(SV);
        e[indice].salario = strtod(SV, &salarioAux);

        //Si digita uno regresa
        if(e[indice].salario == 1){
            goto salir;
        }

        if(e[indice].salario == 0){
            errores += "Cantidad de salario incorrecta.";
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(32, 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);
  
    gotoxy(20,21);
    mensaje += "Registrado correctamente.";
    cout<<ANSI_COLOR_GREEN<<mensaje<<ANSI_COLOR_RESET;
    indice++;
    getch();
    salir:
    cout<<"";
}

void registroEmpleados_edit(int& indice){

    //Variables declaradas
    int seleccion, DS;
    int y, p, validar;
    int count;
    float auxSueldo;
    char recep[50];
    string errores;
    string mensaje;
    char auxNom[cols];
    char auxApe[cols];
    char auxCargo[cols];
    char *salarioAux;
    char SV[10] = {'\0'};
    char str1[25] = "empleados", str2[25] = "Editar / Seleccionar";
    
    do{
        p = 0; 
        seleccion = 0;
        system("cls");
        header();
        cuadro(6,20,112,27);
        gotoxy(8,21);
        cout<<"Mensaje(s): ";
        gotoxy(8,23);
        cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" dig\xA1ta [1] para volver."<<ANSI_COLOR_RESET;
        gotoxy(10,9);
        printf("%c Registro de Empleados / Editar / Buscar",254);
        gotoxy(31,14);
        cout<<"Sugerencias: DUI, Nombre, Apellido o Cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12);
        cout<<"Buscar: ";
        gets(recep);
        
        recep[0] = toupper(recep[0]);//Primera mayuscula
        DS = validar_numero(recep);
        seleccion = buscarEmpleados(recep, indice, str1, str2, p, y); //Funcion buscar

        if(p == 2){
            do{
                system("cls");
                errores = "\0";
                mensaje = ANSI_COLOR_GREEN;
                mensaje += "Cambios realizados correctamente.";
                mensaje += ANSI_COLOR_RESET;
                validar = 0; //Salir del bucle
                count = 0; //Mostrar mensaje

                //Diseño 
                header();
                cuadro(6,20,112,27);
                gotoxy(8,21);
                cout<<"Mensaje(s): ";
        
                gotoxy(10,9);
                printf("%c Registro de empleados / Editar / DUI: %s",254,e[seleccion].dui);
                gotoxy(8,23);
                cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Presiona [Enter] consecutivos si no desea realizar cambios."<<ANSI_COLOR_RESET;
                //Editar e.e[i].nombre
                gotoxy(11,12);
                cout<<"Nuevo Nombre "<<"("<<e[seleccion].nom<<"): ";
                strcpy(auxNom, e[seleccion].nom);
                gets(e[seleccion].nom);

                if(validar_cadena(e[seleccion].nom) > 0){
                    strcpy(e[seleccion].nom, auxNom);
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Nuevo Nombre incorrecto.";
                    errores += ANSI_COLOR_RESET;
                }else if((e[seleccion].nom[0] == '\0') || (e[seleccion].nom[0] == ' ')){
                    strcpy(e[seleccion].nom, auxNom);
                    count++;
                }

                //Editar apellidos
                gotoxy(11,13);
                cout<<"Nuevos apellidos "<<"("<<e[seleccion].ape<<"): ";
                strcpy(auxApe, e[seleccion].ape);
                gets(e[seleccion].ape);

                if(validar_cadena(e[seleccion].ape) > 0){
                    strcpy(e[seleccion].ape, auxApe);
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Nuevos apellidos incorrectos.";
                    errores += ANSI_COLOR_RESET;
                }else if((e[seleccion].ape[0] == '\0') || (e[seleccion].ape[0] == ' ')){
                    strcpy(e[seleccion].ape, auxApe);
                    count++;
                }

                //Editar cargo
                gotoxy(11,14);
                cout<<"Nuevo cargo "<<"("<<e[seleccion].cargo<<"): ";
                strcpy(auxCargo, e[seleccion].cargo);
                gets(e[seleccion].cargo);

                if(validar_cadena(e[seleccion].cargo) > 0){
                    strcpy(e[seleccion].cargo, auxCargo);
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Nuevo cargo incorrecto.";
                    errores += ANSI_COLOR_RESET;
                }else if((e[seleccion].cargo[0] == '\0') || (e[seleccion].cargo[0] == ' ')){
                    strcpy(e[seleccion].cargo, auxCargo);
                    count++;
                }

                //Editar salario
                gotoxy(11,15);
                cout<<"Nuevo salario "<<"($"<<e[seleccion].salario<<"): $";
                auxSueldo = e[seleccion].salario;
                gets(SV);

                e[seleccion].salario = strtod(SV, &salarioAux);

                if((e[seleccion].salario == 0) && (SV[0] != '\0')){
                    e[seleccion].salario = auxSueldo;
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Cantidad de nuevo salario incorrecta.";
                    errores += ANSI_COLOR_RESET;
                }else if(e[seleccion].salario == 0){
                    e[seleccion].salario = auxSueldo;
                    count++;
                }

                //Mensajes en pantalla
                if(errores != "\0"){
                    //Limpiar mensaje "Nota"
                    for(int i = 0; i < 65; i++){
                        gotoxy(8+i,23);
                        cout<<" ";
                    }
                    gotoxy(20,21);
                    cout<<errores;
                }else if(mensaje != "\0" && count != 4){          
                    gotoxy(20,21);
                    cout<<mensaje;
                    validar = 1;
                }else{
                    mensaje = ANSI_COLOR_YELLOWLIGTH;
                    mensaje += "No se realiz\xA2 ning\xA3n cambio.";
                    mensaje += ANSI_COLOR_RESET;
                    gotoxy(20,21);
                    cout<<mensaje;
                    validar = 1;
                }

                getch();

                seleccion = 0;//Para que no se salga del primer bucle

            }while(validar != 1);
        }

    }while(DS != 1);

}

void registroEmpleados_delete(int& indice){

    int duiDrop, j, opD;
    int y, p, validar;
    int seleccion;
    float auxsalario;
    char auxdui[10];
    char auxNom[cols];
    char auxApe[cols];
    char auxCargo[cols];
    char DV[8], opDrop[cols];
    char recep[50];
    char drop[10] = {'\0'};
    char str1[25] = "empleados", str2[25] = "Eliminar / Seleccionar";

    do{
        p = 0; 
        seleccion = 0;
        system("cls");
        header();
        cuadro(6,20,112,27);
        gotoxy(8,21);
        cout<<"Mensaje(s): ";
        gotoxy(8,23);
        cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" dig\xA1ta [1] para volver."<<ANSI_COLOR_RESET;
        gotoxy(10,9);
        printf("%c Registro de Empleados / Eliminar / Buscar",254);
        gotoxy(31,14);
        cout<<"Sugerencias: DUI, Nombre, Apellido o Cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12);
        cout<<"Buscar: ";
        gets(recep);
        
        recep[0] = toupper(recep[0]);//Primera mayuscula
        duiDrop = validar_numero(recep);
        seleccion = buscarEmpleados(recep, indice, str1, str2, p, y); //Funcion buscar

        if(p == 2){
            do{
                system("cls");
                header();
                gotoxy(10,9);
                printf("%c Registro de empleados / Eliminar / DUI: %s",254,e[seleccion].dui);

                cuadro(18,11,99,25);
                gotoxy(43,12);
                cout<<"E l i m i n a r  E m p l e a d o";

                gotoxy(23,13);
                for(int i = 0; i < 71; i++){
                    printf("%c",196);
                }
                
                printf("%c",196);
                gotoxy(33,14);
                printf("%cEst%cs seguro de que deseas eliminar este empleado?",168,160);
                gotoxy(30,16);
                cout<<"DUI: "<<e[seleccion].dui;
                gotoxy(30,17);
                cout<<"Nombre: "<<e[seleccion].nom;
                gotoxy(30,18);
                cout<<"Apellidos: "<<e[seleccion].ape;
                gotoxy(30,19);
                cout<<"Cargo: "<<e[seleccion].cargo;
                gotoxy(30,20);
                cout<<"Salario: $"<<e[seleccion].salario;
                gotoxy(43,22);
                cout<<"[1] Cancelar - [2] Eliminar";

                gotoxy(23,23);
                for(int i = 0; i < 71; i++){
                    printf("%c",196);
                }

                gotoxy(53,24);
                cout<<"Digite: ";
                gets(opDrop);

                opD = validar_numero(opDrop);
                //Borra parte de la pantalla
                cls(27, 43, 22);
                cls(71, 23, 23);
                cls(50, 43, 24);

                if(opD == 2){
                    strcpy(e[seleccion].dui, "-1");

                    //Proceso de eliminar registro
                    for(int i = 0; i < indice; i++){
                        for(int j = 0; j < indice - 1; j++){
                            if(strcmp(e[j].dui, "-1") == 0){
                                strcpy(auxdui, e[j].dui);
                                strcpy(e[j].dui, e[j+1].dui);
                                strcpy(e[j+1].dui, auxdui);

                                strcpy(auxNom, e[j].nom);
                                strcpy(e[j].nom, e[j+1].nom);
                                strcpy(e[j+1].nom, auxNom);

                                strcpy(auxApe, e[j].ape);
                                strcpy(e[j].ape, e[j+1].ape);
                                strcpy(e[j+1].ape, auxApe);

                                strcpy(auxCargo, e[j].cargo);
                                strcpy(e[j].cargo, e[j+1].cargo);
                                strcpy(e[j+1].cargo, auxCargo);

                                auxsalario = e[j].salario;
                                e[j].salario = e[j+1].salario;
                                e[j+1].salario = auxsalario;
                            }
                        }
                    }

                        validar = 1;
                        seleccion = 0;//Para que no se salga del primer bucle

                        //Disminuir al indice
                        indice--;

                        //Mensaje
                        gotoxy(47,23);
                        cout<<ANSI_COLOR_GREEN<<" (X) Registro eliminado";
                        cuadro(45,22,73,24);
                        cout<<ANSI_COLOR_RESET;
                        getch();

                }else if(opD == 1){
                        validar = 1;
                }else{
                    
                    validar = 0;

                    //Mensaje
                    gotoxy(47,23);
                    cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";
                    cuadro(44,22,73,24);
                    cout<<ANSI_COLOR_RESET;
                    getch();
                    
                }

            }while(validar != 1);
        }   

    }while(duiDrop != 1);
}

void registroDescuentos(int indice) {
    int seleccion, DS, y, p, diasD, idMes; 
    char recep[50], diasDC[2];  
    char str1[25] = "descuentos", str2[25] = "Buscar empleado";
    char meses[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    char mesSelec[15] = "\0";
    float salarioDia, descuentoRealizado;
    string errores;
    string mensaje;
    int count = 0, validar;

    do {
        p = 0; 
        system("cls");
        header();
        cuadro(6,20,112,27);
        gotoxy(8,21);
        cout<<"Mensaje(s): ";
        gotoxy(8,23);
        cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Digita [1] para volver."<<ANSI_COLOR_RESET;
        gotoxy(10,9);
        printf("%c Registro de Descuentos / Buscar",254);
        gotoxy(31,14);
        cout<<"Sugerencias: DUI, Nombre, Apellido o Cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12);
        cout<<"Buscar: ";
        gets(recep);
        recep[0] = toupper(recep[0]);
        DS = validar_numero(recep);
        seleccion = buscarEmpleados(recep, indice, str1, str2, p, y);
        
        if (p == 2) {
            do {
                idMes = -2;
                system("cls");
                system("mode con: cols=120 lines=33");
                diasD = 0;
                y = 13;
                errores = "\0";
                mensaje = ANSI_COLOR_GREEN;
                mensaje += "Descuentos realizados correctamente.";
                mensaje += ANSI_COLOR_RESET;
                validar = 0;
                count = 0;
                headerWithoutsquare();
                cuadro(4,6,114,31);
                cuadro(6,24,112,30);
                gotoxy(8,25);
                cout<<"Mensaje(s): ";
                gotoxy(8,29);
                cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Presiona [Enter] consecutivos si no desea realizar cambios."<<ANSI_COLOR_RESET;
                gotoxy(10,9);
                printf("%c Registro de descuentos / DUI: %s",254,e[seleccion].dui);
                
                cuadro(10,11,50,22);
        
                gotoxy(13,15);
                cout<<"DUI";
                gotoxy(13,16);
                cout<<"Nombres";
                gotoxy(13,17);
                cout<<"Apellidos";
                gotoxy(13,18);
                cout<<"Cargo";
                gotoxy(13,19);
                cout<<"Salario";

                gotoxy(18,13);
                cout<<"Informacion del empleado";
                cuadro(15,12,45,14);

                y++;

                gotoxy(28,y+1);
                cout<<e[seleccion].dui;

                gotoxy(28,y+2);
                cout<<e[seleccion].nom;

                gotoxy(28,y+3);
                cout<<e[seleccion].ape;

                gotoxy(28,y+4);
                cout<<e[seleccion].cargo;

                gotoxy(28,y+5);
                cout<<"$"<<e[seleccion].salario;

                salarioDia = e[seleccion].salario/22;
                gotoxy(55,y-2);
                cout<<"Escriba el mes a evaluar: ";
                gets(mesSelec);
                mesSelec[0] = toupper(mesSelec[0]);

                for (int i = 0; i < 12; i++) {
                    if (strcmp(mesSelec, meses[i]) == 0) {
                        idMes = i;
                    }

                    if (mesSelec[0] == '\0' || mesSelec[0] == ' ') {
                        idMes = -1;
                    }
                }

                if (validar_cadena(mesSelec) > 0 || idMes == -2) {
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Mes ingresado incorrecto.";
                    errores += ANSI_COLOR_RESET;
                }else if((validar_cadena(mesSelec) == '\0') && (validar_cadena(mesSelec) == ' ' && idMes == -1)){
                    count++;
                }
                gotoxy(55,y-1);
                cout<<"Escriba los dias a descontar: ";
                gets(diasDC);
                diasD = validar_numero(diasDC);
                if (diasD == -1) {
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Datos invalidos en dias a descontar, ingrese solo numeros";
                    errores += ANSI_COLOR_RESET;
                }else if (diasD > 22 || diasD < 0) {
                    errores += "\n\t\t";
                    errores += ANSI_COLOR_RED;
                    errores += "- Dias a descontar invalidos, debe estar en el intervalo de [1-22]";
                    errores += ANSI_COLOR_RESET;
                }else {
                    count++;
                }

                if(errores != "\0"){
                    gotoxy(20,25);
                    cout<<errores;
                    gotoxy(13,20);
                    cout<<ANSI_COLOR_RED<<"Descuento realizado: ninguno"<<ANSI_COLOR_RESET;
                }else if(mensaje != "\0" && count != 2 && diasD != 0){ 
                    e[seleccion].descuento[idMes] = salarioDia * diasD;
                    gotoxy(13,20);
                    cout<<fixed<<setprecision(2)<<ANSI_COLOR_GREEN<<"Descuento realizado: $"<<(float)e[seleccion].descuento[idMes]<<ANSI_COLOR_RESET;         
                    gotoxy(20,25);
                    cout<<mensaje;
                    validar = 1;
                }else {
                    mensaje = ANSI_COLOR_YELLOWLIGTH;
                    mensaje += "No se realiz\xA2 ning\xA3n descuento.";
                    mensaje += ANSI_COLOR_RESET;
                    gotoxy(20,25);
                    cout<<mensaje;
                    validar = 1;
                }
                getch();
            }while (validar != 1);
            system("mode con: cols=120 lines=30");
        }
    }while (DS != 1);
}

int buscarEmpleados(char recep[50], int indice, char str1[25], char str2[25], int& p, int& y) {
    int seleccion, value;
    int auxSeleccion = '\0';
    int Dui;
    bool exist;
    int pointer[indice], c;

    int id = -2;
    y = 13;
    Dui = validar_numero(recep);

    if (Dui == -1) {
        if(validar_cadena(recep) > 0 || (recep[0] == '\0') || (recep[0] == ' ')){
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<"Dato inv\xA0lido"<<ANSI_COLOR_RESET;
            getch();
        }else {
            if(indice <= 0){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No hay empleados registrados, por favor ingrese datos."<<ANSI_COLOR_RESET;
                getch();
            }else {
                exist = verificarEmpleado(recep, indice);
                

                if (!exist) {
                    gotoxy(20,21);
                    cout<<ANSI_COLOR_RED<<"Empleado no encontrado."<<ANSI_COLOR_RESET;
                    getch();
                }else {
                    do {
                        system("cls");
                        gotoxy(10,9);
                        printf("%c Registro de %s / %s",254, str1, str2);
                        gotoxy(11,12);
                        printf("N%c", 167);
                        cuadro(8,11,15,13);

                        gotoxy(19,12);
                        cout<<"DUI";
                        cuadro(15,11,26,13);

                        gotoxy(36,12);
                        cout<<"Nombre";
                        cuadro(26,11,52,13);

                        gotoxy(60,12);
                        cout<<"Apellidos";
                        cuadro(52,11,77,13);

                        gotoxy(84,12);
                        cout<<"Cargo";
                        cuadro(77,11,97,13);

                        gotoxy(101,12);
                        cout<<"Salario";
                        cuadro(97,11,110,13);

                        
                        if (exist) {
                            mostrarEmpleados(recep, indice, pointer, y, c);
                        }
                        
                        headerWithoutsquare();
                        if(c > 7){
                            cuadro(4,6,114,21+c);
                        }else{
                            cuadro(4,6,114,28);
                        }
                        
                        char recepSeleccion[2];
                        gotoxy(10, y+3);
                        cout<<"Seleccione empleado o presione [Enter] para volver: ";
                        gets(recepSeleccion);
                        fflush(stdin);
                        seleccion = validar_numero(recepSeleccion);
                        if (seleccion != 0){
                            if (seleccion != -1 && seleccion <= c) {
                                seleccion = pointer[seleccion-1];
                                auxSeleccion = seleccion;
                                p = 2;
                            }else {
                                gotoxy(49,y+6);
                                cout<<ANSI_COLOR_RED<<"Error: Dato inv\xA0lido";
                                cuadro(46,y+5,71,y+7);cout<<ANSI_COLOR_RESET;
                                getch();
                            } 
                        }
                    }while(auxSeleccion != seleccion);
                }
            }
        }
    }else{
        for (int i = 0; i < indice; i++) {
            if (strcmp(e[i].dui, recep) == 0) {
                id = i;
            }

        }
        

        if(id == -2){
            if(Dui != 1 && indice > 0 && recep[0] != '\0'){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No se encontr\xA2 ning\xA3n empleado con ese n\xA3mero de DUI"<<ANSI_COLOR_RESET;
                seleccion = 0;
                getch();
            }else if(indice == 0 && Dui != 1){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No hay empleados registrados, por favor ingrese datos."<<ANSI_COLOR_RESET;
                seleccion = 0;
                getch();
            }else if(recep[0] == '\0'){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"Dato inv\xA0lido"<<ANSI_COLOR_RESET;
                getch();
            }
        }else {
            seleccion = id;
            p = 2;
        }
    }             

    return seleccion;
}

bool verificarEmpleado(char recep[50], int indice) {
    bool exist = false;
    char auxNom[50] = "\0", auxApe[50] = "\0", auxCargo[50] = "\0";

    for (int i = 0; i < indice; i++) {
        strcpy(auxNom, e[i].nom);
        char *tokenNom = strtok(auxNom, " ");
        
        if(tokenNom != NULL){
            while(tokenNom != NULL){
                if (strcmp(recep, tokenNom) == 0) {
                    exist = true;
                }
                tokenNom = strtok(NULL, " "); 
            }
        }

        strcpy(auxApe, e[i].ape);
        char *tokenApe = strtok(auxApe, " ");
        
        if(tokenApe != NULL){
            while(tokenApe != NULL){
                if (strcmp(recep, tokenApe) == 0) {
                    exist = true;
                }
                tokenApe = strtok(NULL, " "); 
            }
        }

        strcpy(auxCargo, e[i].cargo);
        char *tokenCargo = strtok(auxCargo, " ");
        
        if(tokenCargo != NULL){
            while(tokenCargo != NULL){
                if (strcmp(recep, tokenCargo) == 0) {
                    exist = true;
                }
                tokenCargo = strtok(NULL, " "); 
            }
        }
    }

    return exist;
}

void mostrarEmpleados(char recep[50], int indice, int pointer[], int& y, int& x) {
    int a, c;
    char auxNom[50] = "\0", auxApe[50] = "\0", auxCargo[50] = "\0";

    a = 0;
    c = 0;
    y = 13;
    for (int i = 0; i < indice; i++) {
        strcpy(auxNom, e[i].nom);
        char *tokenNom = strtok(auxNom, " ");
        if(tokenNom != NULL){
            while(tokenNom != NULL){
                if (strcmp(recep, tokenNom) == 0) {
                    y++;

                    gotoxy(11,y);
                    pointer[c] = a+c;
                    c++;
                    cout<<(i+1)-(a--);
                    
                    gotoxy(16,y);
                    cout<<e[i].dui;

                    gotoxy(28,y);
                    cout<<e[i].nom;

                    gotoxy(54,y);
                    cout<<e[i].ape;

                    gotoxy(80,y);
                    cout<<e[i].cargo;
                
                    gotoxy(101,y);
                    cout<<"$"<<e[i].salario;
                }
                tokenNom = strtok(NULL, " ");
            }
        }

        strcpy(auxApe, e[i].ape);
        char *tokenApe = strtok(auxApe, " ");
        if(tokenApe != NULL){
            while(tokenApe != NULL){
                if (strcmp(recep, tokenApe) == 0) {
                    y++;

                    gotoxy(11,y);
                    pointer[c] = a+c;
                    c++;
                    cout<<(i+1)-(a--);
                    
                    gotoxy(16,y);
                    cout<<e[i].dui;

                    gotoxy(28,y);
                    cout<<e[i].nom;

                    gotoxy(54,y);
                    cout<<e[i].ape;

                    gotoxy(80,y);
                    cout<<e[i].cargo;
                
                    gotoxy(101,y);
                    cout<<"$"<<e[i].salario;
                }
                tokenApe = strtok(NULL, " ");
            }
        }
        
        strcpy(auxCargo, e[i].cargo);
        char *tokenCargo = strtok(auxCargo, " ");
        if(tokenCargo != NULL){
            while(tokenCargo != NULL){
                if (strcmp(recep, tokenCargo) == 0) {
                    y++;

                    gotoxy(11,y);
                    pointer[c] = a+c;
                    c++;
                    cout<<(i+1)-(a--);
                    
                    gotoxy(16,y);
                    cout<<e[i].dui;

                    gotoxy(28,y);
                    cout<<e[i].nom;

                    gotoxy(54,y);
                    cout<<e[i].ape;

                    gotoxy(80,y);
                    cout<<e[i].cargo;
                
                    gotoxy(101,y);
                    cout<<"$"<<e[i].salario;
                }
                tokenCargo = strtok(NULL, " ");
            }
        }

        ++a;
    }

    if (c > 0) {
        x = c;
    }
}

//alinear objetos-
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//cuadrado para estetica
void cuadro(int x1, int y1, int x2, int y2){

    for(int i = x1; i < x2; i++){	
		gotoxy(i,y1);printf("%c",196); //Linea arriba
		gotoxy(i,y2);printf("%c",196); //Linea abajo
    }

    for (int i = y1; i < y2; i++){	
		gotoxy(x1,i);printf("%c",179); //Linea derecha
		gotoxy(x2,i);printf("%c",179); //Linea izquierda
    }
    
    //Esquinas
    gotoxy(x1,y1);printf("%c",218); 
    gotoxy(x1,y2);printf("%c",192);
    gotoxy(x2,y1);printf("%c",191);
    gotoxy(x2,y2);printf("%c",217);
}
void cuadroPlanillas(int x1, int y1, int x2, int y2){
    for(int i = x1; i < x2; i++){	
		gotoxy(i,y1);printf("%c",196); //Linea arriba
		gotoxy(i,y2);printf("%c",196); //Linea abajo
    }

    for (int i = y1; i < y2; i++){	
		gotoxy(x1,i);printf("%c",179); //Linea derecha
		gotoxy(x2,i);printf("%c",179); //Linea izquierda
    }
    //Esquinas
    gotoxy(x1,y1);printf("%c",218); 
    gotoxy(x1,y2);printf("%c",192);
    gotoxy(x2,y1);printf("%c",191);
    gotoxy(x2,y2);printf("%c",217);
}
//Funcion del texto de cabecera
void header(){
    cuadro(4,6,114,28);
    cuadro(4,1,114,5);
    gotoxy(23,3);
    cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";      
}

//Funcion del texto de cabecera sin cuadro del cuerpo
void headerWithoutsquare(){
    cuadro(4,1,114,5);
    gotoxy(23,3);
    cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";      
}

//Validar enteros
int validar_numero(char numero[2]){
    int opc;

    for(int i = 0; i < strlen(numero); i++){
        if(!(isdigit(numero[i]))){
            return -1;
        }
    }

    opc = atoi(numero);//convertir a entero
    return opc;
}

//Validar una cadena de caracteres
int validar_cadena(char palabra[row]){
    int contador = 0;

    for(int i = 0; i < strlen(palabra); i++){
        if(isalpha(palabra[i]) == 0 && isspace(palabra[i]) == 0){
            contador++;
        }
    }

    return contador;
}

void cls(int longitud, int posicionX, int posicionY){
    for(int i = 0; i < longitud; i++){
        gotoxy(posicionX + i, posicionY);
        cout<<" ";
    }
}