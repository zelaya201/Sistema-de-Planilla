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
#define ANSI_COLOR_RED   "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[92m"
#define ANSI_COLOR_YELLOWLIGTH     "\x1b[93m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;

struct planilla
{
    float Adescontar;
};
struct porcentajeRetenciones {
    float porAfp = 7.25;
    float porIsss = 3;
    float porRenta1 = 10;
    float porRenta2 = 20;
    float porRenta3 = 30;
}porcentajes;

struct Historial {
    int estado = 1;
    string accion[100] = {"Valores predeterminados"};
    porcentajeRetenciones p[100];
}h[100];

struct Empleados {
    char dui[10];
    char nom[50];
    char ape[50];
    char cargo[50];
    float salario;
    float descuento[12];
    float salarioN[12];
    float afp;
    float isss;
    char mesEmpleado[50];
    float renta;
    float salarioAfpIss;
    planilla pl;
}e[100];

void header(); //Diseño completo (Cabecera y cuadro del cuerpo)
void ampliar_pantalla(int c); //Solo cabecera
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
bool verificarEmpleado(char [50],int, int&);
void impresionBuscar(int&, int[], int&, int&, int);
int verificarDoble(int);
void mostrarEmpleados(char [50], int, int [], int&, int&);
void planillaMensual(int&);
void mostrarEmpleadoPlanilla(char recep[50], int indice, int& p, int& y);
void BuscarEmpleadoPlanilla(char recep[50], int indice, char [50], char[50], int&, int&);
bool verificarMes(char[50], int);

void cuadroPlanillas(int x1, int y1, int x2, int y2);/* inter[], int& y, int& x)  */
void menuMeses();
void registroRetenciones(int);
void registroRetenciones_verPorcentajes(int);
void registroRetenciones_modificar(int);
void registroRetenciones_historial(int);
void registroRetenciones_historial_detalles(int, int);
void calculoRetenciones(int);

/* DECLARACION DE VARIABLES GLOBALES */
int conteoModificaciones = 1;

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
        {"Antonio Alejandro"},
        {"Vladimir Antonio"},
        {"Carlos Valerio"},
        {"Mario Ernesto"},
        {"Shelsy Yamileth"},
        {"Karla Beatriz"},
        {"Luis Fernando"},
        {"Baltasar Francisco"}
    };

    char ape[row][cols] = {
        {"Ayala Ayala"},
        {"Morales Constanza"},
        {"Torres Torres"},
        {"Asensio Gavidia"},
        {"Zelaya Torres"},
        {"Rodriguez Perez"},
        {"Cruz Nulas"},
        {"Martinez Guarnizo"},
        {"Constanza Osorio"}
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

    for (int i = 1; i < 100; i++) {
        h[i].estado = 0;
    }

    do{
        op = menu(); //opcion

        switch(op){
            case 1: system("cls");registroEmpleados(indice);break; //Modulo 1
            case 2: system("cls");registroRetenciones(indice);break; //Modulo 2
            case 3: system("cls");planillaMensual(indice);break; //Modulo 3
            case 4: system("cls");cout<<"Modulo en proceso";break; //Modulo 3.1
            case 5: system("cls");registroDescuentos(indice);break; //Modulo 5
            case 6: gotoxy(42,22);cout<<ANSI_COLOR_YELLOWLIGTH<<"Mensaje: Hasta luego, vuelva pronto";cuadro(40,21,78,23);cout<<ANSI_COLOR_RESET;Sleep(3000);break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: M"<<"\xA2"<<"dulo incorrecto";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
        }


    }while(op != 6);

    return 0;
}

int menu(){
    char opAux[200];
    int opcion;

    system("cls");
    header();

	gotoxy(10,9);cout<<"Elija una opci\xA2n: ";

	gotoxy(10,11);cout<<"[1] Registro de empleados";
	gotoxy(10,12);cout<<"[2] Registro de retenciones de ley";
	gotoxy(10,13);cout<<"[3] Informe de planillas mensuales";
	gotoxy(10,14);cout<<"[4] Informe de planillas quincenales";
	gotoxy(10,15);cout<<"[5] Registro de descuentos";
	gotoxy(10,16);cout<<"[6] Salir";
	
	gotoxy(10,18);cout<<"Selecciona: ";
    gets(opAux);

    if (strlen(opAux) > 6) { //Si la seleccion recibe demasiados valores
        opcion = -1;
    }else {
        fflush(stdin);
        opcion = validar_numero(opAux); //Validar opcion
    }

    return opcion; 
}

void planillaMensual(int& indice){
    int y, p;
    char meses[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int MesSeleccion, PL;
    char recep[50];
    char str[50] = "Planilla Mensual", str2[80] = "Planilla Quincenal";
    // system("mode con: cols=120 lines=31");

    gotoxy(56,3);cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";
        do{
            p = 0;
            system("cls");
            header();
            cuadro(6,20,112,27);
            gotoxy(8, 21);
            cout<<"Mensaje(s): ";
            gotoxy(8,23);
            cout<<"Nota: "<<ANSI_COLOR_YELLOWLIGTH<<" Digita [1] para volver."<<ANSI_COLOR_RESET;
            gotoxy(10,9);
            printf("%c Planilla Mensual / ... ",254);
            gotoxy(30, 14);
            cout<<"Indicaci\xA2n: Escriba el mes a buscar";
            cuadro(26,11,90,13);
            gotoxy(28,12);
            cout<<"Buscar: ";
            fflush(stdin);
            gets(recep);
            recep[0] = toupper(recep[0]);
            PL = validar_numero(recep);
            BuscarEmpleadoPlanilla(recep, indice, str, str2, p, y);
            
        } while (PL != 1);
}
void BuscarEmpleadoPlanilla(char recep[50], int indice, char str[50], char str2[50], int& p, int& y){
    int seleccion;
    int auxSeleccion = '\0';
    int mes;
    bool exist;
    int pointer[indice], a;
    char Releccion[2];
    y = 13;
    int idM = -2;

    mes = validar_numero(recep);

    if (mes == -1){
        if (validar_cadena(recep) > 0 || (recep[0] == '\0') || (recep[0] == ' ')){
            gotoxy(20,21);
            cout << ANSI_COLOR_RED<<"Dato Incorrecto"<<ANSI_COLOR_RESET;
            getch();
        }else{
            if (indice <= 0){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No hay empleados registrados."<<ANSI_COLOR_RESET;
                getch();
            }else{
                exist = verificarMes(recep, indice);

                if(!exist){
                    gotoxy(20,21);
                    cout<<ANSI_COLOR_RED<<"Empleados no econtrados en este mes."<<ANSI_COLOR_RESET;
                    getch();
                }else{
                    do{
                        system("mode con: cols=169 lines=30");
                        
                        system("cls");
                        gotoxy(10, 9);
                        printf("%c %s / %s",254, str, recep);

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

                        gotoxy(127, 12);
                        cout<<"RENTA";
                        cuadro(125,11,136,13);
                        
                        gotoxy(138,12);
                        cout<<"Descuentos";
                        cuadro(136,11,150,13);

                        gotoxy(151,12);
                        cout<<"Salario N";
                        cuadro(150,11,161,13);

                        gotoxy(56,3);
                        cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";
                        if(indice > 6){
                            cuadroPlanillas(4,6,165,20+indice);
                        }else{
                            cuadroPlanillas(4,6,165,30);
                        }
                        cuadroPlanillas(4,1,165,5);
                        if (exist) {
                            fflush(stdin);
                            mostrarEmpleadoPlanilla(recep, indice, y, a);
                            cout <<endl;
                        }
                        
                        gotoxy(10, y+3);
                        cout<< "Presione Doble [Enter] para volver: ";
                        fflush(stdin);
                        gets(Releccion);
                        seleccion = validar_numero(Releccion);
                        fflush(stdin);
                        
                        if (seleccion != 0){
                            if (seleccion != -1){
                                seleccion = pointer[seleccion-1];
                                auxSeleccion = seleccion;
                                p = 2;
                            }
                        }
                        fflush(stdin);
                    }while(auxSeleccion != seleccion);
                }
            }
            
        }
    }else{
        for (int i = 0; i < indice; i++){
            if (strcmp(e[i].mesEmpleado, recep) == 0){
                idM = i;
            }
        }

        if (idM == -2){
            if (mes != 1 && indice > 0 && recep[0] != '\0')
            {
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"Ingrese solamente el nombre de los meses."<<ANSI_COLOR_RESET;
                seleccion = 0;
                getch();
            }else if(indice == 0 && mes != 1){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No hay empleados registrados, por favor ingrese datos."<<ANSI_COLOR_RESET;
                seleccion = 0;
                getch();
            }else if(recep[0] == '\0'){
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"Dato inv\xA0lido"<<ANSI_COLOR_RESET;
                getch();
            }
        }    
    }
    system("mode con: cols=120 lines=30");
}
bool verificarMes(char recep[50], int indice){
    bool exist = false;
    char AuxMes[50] = "\0";

    for (int j = 0; j < indice; j++)
    {
        strcpy(AuxMes, e[j].mesEmpleado);
        char *tokenMes = strtok(AuxMes, " ");

        if (tokenMes != NULL){
            while (tokenMes != NULL){
                if(strcmp(recep, tokenMes) == 0) {
                    exist = true;
                }
                tokenMes = strtok(NULL, " ");
            }       
        }
    }
    return exist;
}
void mostrarEmpleadoPlanilla(char recep[50], int indice, int& y, int& x){
    int b, v;
    char auxMes[20] = "\0";
    b = 0;
    v = 0;
    y = 13;
    

    for (int i = 0; i < indice; i++){
        /* IMPRESION POR EL MES */
        strcpy(auxMes, e[i].mesEmpleado);
        char *tokenMes = strtok(auxMes, " ");
        if (tokenMes != NULL){
            while (tokenMes != NULL){
                if (strcmp(recep, tokenMes) == 0){
                    y++;

                    gotoxy(10,y);
                    cout<<e[i].dui;

                    gotoxy(22,y);
                    cout<<e[i].nom;
                    
                    gotoxy(44,y);
                    cout<<e[i].ape;
                    
                    gotoxy(68,y);
                    cout<<e[i].cargo;
                    
                    gotoxy(89,y);
                    printf("$%.2f\n", e[i].salario);
                    
                    calculoRetenciones(indice);
                    gotoxy(101,y); // AFP
                    printf("$%.2f",e[i].afp);

                    gotoxy(115,y); // ISSS
                    printf("$%.2f",e[i].isss);
                    
                    gotoxy(127, y);
                    printf("$%.2f", e[i].renta); // RENTA

                    gotoxy(138,y);
                        if(e[i].pl.Adescontar <= 0){
                            printf(" N / A \n");
                        }else{
                            printf("$%.2f\n", e[i].pl.Adescontar);
                        }
                    
                    gotoxy(152, y); // NETO
                    printf("$%.2f", (e[i].salario - (e[i].afp + e[i].isss + e[i].renta + e[i].pl.Adescontar)));
                }
                tokenMes = strtok(NULL, " ");
                gotoxy(10, y+3);
            }
        }
        ++b;
    }
                    cout<< "Presione Doble [Enter] para volver: ";
    if (v > 0){
        x = v;
    }
    getch();
}

// Aqui inicia el modulo de Adonay @xdesprox
void registroEmpleados(int& indice){
    char select[200];
    int op;

    do{
        system("mode con: cols=120 lines=30");
        header();
        gotoxy(10,9); printf("%c Registro de empleados",254);
        gotoxy(10,11); cout<<"[1] Registrar";
        gotoxy(10,12); cout<<"[2] Editar";
        gotoxy(10,13); cout<<"[3] Eliminar";
        gotoxy(10,14); cout<<"[4] Atras";
        gotoxy(10,16); cout<<"Selecciona: ";
        gets(select);
        fflush(stdin);
        
        if (strlen(select) > 4){ //Si la seleccion recibe demasiados valores
            op = -1;
        }else {
            op = validar_numero(select);
        }

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
    //Variables
    int cant, dui, centinela;
    char SV[10];
    char *salarioAux;
    string errores, mensaje;

    system("cls");

    //Diseño
    header();
    cuadro(6,20,112,27); //Cuadro de mensajes
    gotoxy(8,21); cout<<"Mensaje(s): ";
    gotoxy(8,23); cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Dig\xA1ta [1] en cualquier campo para volver."<<ANSI_COLOR_RESET;
    gotoxy(10,9); printf("%c Registro de empleados / Registrar",254);

    /* DUI */

    do{
        centinela = 1;
        cant = 1;

        cls(strlen(e[indice].dui) + 13, 11, 11); //Borra lineas en pantalla

        gotoxy(11,11); printf("N%c de DUI: ",167);
        gets(e[indice].dui);
        fflush(stdin);

        dui = validar_numero(e[indice].dui); //Para saber si lo que se ha escrito es un numero

        //Validacion por si hay otro dui igual
        for(int i = 0; i < indice; i++){
            if((strcmp(e[indice].dui, e[i].dui) == 0) && (i != indice)){
                cant++;
            }
        }

        //Si digita uno regresa
        if(strcmp(e[indice].dui, "1") == 0){
            goto salir;
        }

        //Condiciones y mensajes
        if(strlen(e[indice].dui) != 9 || dui == -1){ 
            errores = "N\xA3mero de DUI mayor o menor a 9 cifras y/o incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            centinela = 0;
            getch();
            cls(errores.length(), 20, 21);
        }else if(cant > 1){
            errores = "N\xA3mero de DUI ya existente, ingrese otro.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            centinela = 0;
            getch();
            cls(errores.length(), 20, 21);
        }

        
    }while(centinela != 1);   

    /* NOMBRE */

    do{
        centinela = 1;
        cls(strlen(e[indice].nom) + 9, 11, 12);

        gotoxy(11,12); cout<<"Nombre: ";
        gets(e[indice].nom);

        //Si digita uno regresa
        if(strcmp(e[indice].nom, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].nom) > 0 || (e[indice].nom[0] == '\0') || (e[indice].nom[0] == ' ')){
            errores = "Nombre incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);  

    /* APELLIDOS */

    do{
        centinela = 1;
        cls(strlen(e[indice].ape) + 12, 11, 13);

        gotoxy(11,13); cout<<"Apellidos: ";
        gets(e[indice].ape);

        //Si digita uno regresa
        if(strcmp(e[indice].ape, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].ape) > 0 || (e[indice].ape[0] == '\0') || (e[indice].ape[0] == ' ')){
            errores = "Apellidos incorrectos.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);

    /* CARGO */
    
    do{
        centinela = 1;
        cls(strlen(e[indice].cargo) + 8, 11, 14);

        gotoxy(11,14); cout<<"Cargo: ";
        gets(e[indice].cargo);

        //Si digita uno regresa
        if(strcmp(e[indice].cargo, "1") == 0){
            goto salir;
        }

        if(validar_cadena(e[indice].cargo) > 0 || (e[indice].cargo[0] == '\0') || (e[indice].cargo[0] == ' ')){
            errores = "Cargo escrito incorrectamente.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);

    /* SALARIO */
    do{
        centinela = 1;
        cls(strlen(SV) + 11, 11, 15);

        gotoxy(11,15); cout<<"Salario: $";
        gets(SV);
        fflush(stdin);
        e[indice].salario = strtod(SV, &salarioAux);
        //Si digita uno regresa
        if(e[indice].salario == 1){
            goto salir;
        }

        if(e[indice].salario == 0 || salarioAux[0] != '\0'){
            errores = "Cantidad de salario incorrecta.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            centinela = 0;
        }

    }while(centinela != 1);

    //Mensajes
    mensaje = "Registrado correctamente.";
    gotoxy(20,21); cout<<ANSI_COLOR_GREEN<<mensaje<<ANSI_COLOR_RESET;

    indice++;
    getch();
    salir: cout<<""; //La instruccion goto necesita una instruccion delante para que no de error 
}

void registroEmpleados_edit(int& indice){

    //Variables declaradas
    int seleccion, DS, y, p, validar, conteo, centinela, num, cifras;
    float auxSueldo;
    string errores, mensaje;
    char recep[50], auxNom[cols], auxApe[cols], auxCargo[cols], temp[cols];
    char *salarioAux;
    char SV[10] = {'\0'};
    char str1[25] = "empleados", str2[25] = "Editar / Seleccionar";
    
    do{
        p = 0; 
        seleccion = 0;
        system("mode con: cols=120 lines=30");
        header();
        cuadro(6,20,112,27);
        gotoxy(8,21); cout<<"Mensaje(s): ";
        gotoxy(8,23); cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" dig\xA1ta [1] para volver."<<ANSI_COLOR_RESET;
        gotoxy(10,9); printf("%c Registro de Empleados / Editar / Buscar",254);
        gotoxy(31,14); cout<<"Sugerencias: DUI, Nombre, Apellido o Cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12); cout<<"Buscar: ";
        gets(recep);
        
        recep[0] = toupper(recep[0]);//Primera mayuscula
        DS = validar_numero(recep);
        seleccion = buscarEmpleados(recep, indice, str1, str2, p, y); //Funcion buscar

        if(p == 2){

            conteo = 0;
            mensaje = ANSI_COLOR_GREEN;
            mensaje += "Cambios realizados correctamente.";
            mensaje += ANSI_COLOR_RESET; 
            //Diseño 
            system("cls");
            header();
            cuadro(6,20,112,27);
            gotoxy(8,21); cout<<"Mensaje(s): ";
        
            gotoxy(10,9);
            printf("%c Registro de empleados / Editar / DUI: %s",254,e[seleccion].dui);
            gotoxy(8,23); cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Presiona [Enter] consecutivos si no desea realizar cambios."<<ANSI_COLOR_RESET;

            /* EDITAR NOMBRE */
            do{
                centinela = 1;
                cls(strlen(e[seleccion].nom) + strlen(temp) + 17, 11, 12); //Borra linea de la pantalla

                gotoxy(11,12); cout<<"Nuevo nombre "<<"("<<e[seleccion].nom<<"): ";
                strcpy(auxNom, e[seleccion].nom);
                gets(e[seleccion].nom);

                if(validar_cadena(e[seleccion].nom) > 0){
                    strcpy(temp, e[seleccion].nom);
                    strcpy(e[seleccion].nom, auxNom);
                    errores = "Nuevo nombre incorrecto.";
                    gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length(), 20, 21);
                    centinela = 0;
                }else if((e[seleccion].nom[0] == '\0') || (e[seleccion].nom[0] == ' ')){
                    strcpy(e[seleccion].nom, auxNom);
                    centinela = 1;
                    conteo++;
                }

            }while(centinela != 1);    

            /* EDITAR APELLIDOS */
            do{
                centinela = 1;
                cls(strlen(e[seleccion].ape) + strlen(temp) + 22, 11, 13);

                gotoxy(11,13); cout<<"Nuevos apellidos "<<"("<<e[seleccion].ape<<"): ";
                strcpy(auxApe, e[seleccion].ape);
                gets(e[seleccion].ape);

                if(validar_cadena(e[seleccion].ape) > 0){
                    strcpy(temp, e[seleccion].ape);
                    strcpy(e[seleccion].ape, auxApe);
                    errores = "Nuevos apellidos incorrectos.";
                    gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length(), 20, 21);
                    centinela = 0;
                }else if((e[seleccion].ape[0] == '\0') || (e[seleccion].ape[0] == ' ')){
                    strcpy(e[seleccion].ape, auxApe);
                    centinela = 1;
                    conteo++;
                }

            }while(centinela != 1);

            /* EDITAR CARGO */
            do{
                centinela = 1;
                cls(strlen(e[seleccion].cargo) + strlen(temp) + 17, 11, 14);

                gotoxy(11,14); cout<<"Nuevo cargo "<<"("<<e[seleccion].cargo<<"): ";
                strcpy(auxCargo, e[seleccion].cargo);
                gets(e[seleccion].cargo);

                if(validar_cadena(e[seleccion].cargo) > 0){
                    strcpy(temp, e[seleccion].cargo);
                    strcpy(e[seleccion].cargo, auxCargo);
                    errores = "Nuevo cargo incorrecto.";
                    gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length(), 20, 21);
                    centinela = 0;
                }else if((e[seleccion].cargo[0] == '\0') || (e[seleccion].cargo[0] == ' ')){
                    strcpy(e[seleccion].cargo, auxCargo);
                    centinela = 1;
                    conteo++;
                }

            }while(centinela != 1);

            /* EDITAR SALARIO */
            cifras = 0;
            do{
                centinela = 1;
                cls(cifras + strlen(temp) + 24, 11, 15);

                gotoxy(11,15); cout<<"Nuevo salario "<<"($"<<fixed<<setprecision(2)<<e[seleccion].salario<<"): $";
                auxSueldo = e[seleccion].salario;
                gets(SV);

                e[seleccion].salario = strtod(SV, &salarioAux);

                if(((e[seleccion].salario == 0) && (SV[0] != '\0')) || salarioAux[0] != '\0'){
                    strcpy(temp, SV);
                    e[seleccion].salario = auxSueldo;
                    errores = "Cantidad de nuevo salario incorrecta.";
                    gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    getch(); 
                    
                    //Obteniendo cantidad de cifras
                    num = trunc(e[seleccion].salario);
                    while(num >= 10){
                        num /= 10;
                        cifras++;
                    }

                    cls(errores.length(), 20, 21);
                    centinela = 0;
                }else if(e[seleccion].salario == 0){
                    e[seleccion].salario = auxSueldo;
                    centinela = 1;
                    conteo++;
                }

            }while(centinela != 1);

            if(conteo == 4){
                mensaje = ANSI_COLOR_YELLOWLIGTH;
                mensaje += "No se realiz\xA2 ning\xA3n cambio.";
                mensaje += ANSI_COLOR_RESET;
            }

            //Mensaje
            gotoxy(20,21); cout<<mensaje;
            getch();

        }

    }while(DS != 1);

}//Adonay

void registroEmpleados_delete(int& indice){

    int duiDrop, j, opD, y, p, validar, seleccion;
    float auxsalario;
    char auxdui[10], auxNom[cols], auxApe[cols], auxCargo[cols], DV[8], opDrop[cols], recep[50];
    char drop[10] = {'\0'};
    char str1[25] = "empleados", str2[25] = "Eliminar / Seleccionar";

    do{
        p = 0; 
        seleccion = 0;
        system("mode con: cols=120 lines=30");
        header();
        cuadro(6,20,112,27);
        gotoxy(8,21); cout<<"Mensaje(s): ";
        gotoxy(8,23); cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" dig\xA1ta [1] para volver."<<ANSI_COLOR_RESET;
        gotoxy(10,9); printf("%c Registro de Empleados / Eliminar / Buscar",254);
        gotoxy(31,14); cout<<"Sugerencias: DUI, Nombre, Apellido o Cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12); cout<<"Buscar: ";
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
                cout<<"Salario: $"<<fixed<<setprecision(2)<<e[seleccion].salario;
                gotoxy(43,22);
                cout<<"[1] Cancelar - [2] Eliminar";

                //Crea una linea
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

                        validar = 1; //bandera para salir del bucle

                        //Disminuir al indice
                        indice--;

                        //Mensaje
                        gotoxy(47,23); cout<<ANSI_COLOR_GREEN<<" (X) Registro eliminado";
                        cuadro(45,22,73,24); cout<<ANSI_COLOR_RESET;
                        getch();

                }else if(opD == 1){
                        validar = 1;
                }else{
                    
                    validar = 0;

                    //Mensaje
                    gotoxy(47,23); cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";
                    cuadro(44,22,73,24); cout<<ANSI_COLOR_RESET;
                    getch();
                    
                }

            }while(validar != 1);
        }   

    }while(duiDrop != 1);
}

void registroDescuentos(int indice) {
    int seleccion, DS, y, p, diasD, idMes, centinela; 
    char recep[50], diasDC[2], mesSelec[15] = "\0";
    char str1[25] = "descuentos", str2[25] = "Buscar empleado", meses[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int diasMeses[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    float salarioDia, descuentoRealizado;
    string errores, mensaje;

    do {
        p = 0; 
        system("mode con: cols=120 lines=30");
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

        recep[0] = toupper(recep[0]); //Eleva el primer caracter 
        DS = validar_numero(recep); //Valida el dato ingresado
        seleccion = buscarEmpleados(recep, indice, str1, str2, p, y); //Funcion buscar

        if (p == 2) {
            idMes = -2;
            diasD = 0;
            y = 13;

            ampliar_pantalla(10); //Ampliar la pantalla a 33 de alto
            
            cuadro(6,24,112,30); //Cuadro de mensajes
            gotoxy(8,25);
            cout<<"Mensaje(s): ";
            gotoxy(8,29);
            cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Dig\xA1ta [0] en cualquier campo para volver."<<ANSI_COLOR_RESET;
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

            /* Mes a evaluar */
            do{
                centinela = 1; //La variable se mantendra en 1 mientras no de error
                cls(59, 55, y-2);

                gotoxy(55,y-2);
                cout<<"Mes a evaluar: ";
                gets(mesSelec);
                mesSelec[0] = toupper(mesSelec[0]); //Eleva el primer caracter obtenido

                //Si digita uno regresa
                if(strcmp(mesSelec, "0") == 0){
                    goto salir;
                }

                for (int i = 0; i < 12; i++) {
                    if (strcmp(mesSelec, meses[i]) == 0) {
                        idMes = i; //Obtiene la posicion del mes digitado
                    }

                    if (mesSelec[0] == '\0' || mesSelec[0] == ' ') {
                        idMes = -1; //Devuelve -1 si se encuentra con un salto de linea o espacio
                    }
                }

                if (validar_cadena(mesSelec) > 0 || idMes == -2 && (validar_cadena(mesSelec) == '\0') || (validar_cadena(mesSelec) == ' ' || idMes == -1)) { //Validacion para mostrar error
                    errores = "- Mes ingresado incorrecto.";
                    gotoxy(20,25);
                    cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    gotoxy(13,20);
                    cout<<ANSI_COLOR_RED<<"Descuento realizado: ninguno"<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length(), 20, 25);
                    cls(28, 13, 20);
                    centinela = 0; //Cambia la variable para mantener el ciclo do-while
                }

            }while(centinela != 1);
            strcpy(e[seleccion].mesEmpleado, mesSelec); // Julio Torres

            /* Dias a descontar */
            do{
                centinela = 1; //La variable se mantendra en 1 mientras no de error
                cls(59, 55, y-1);
                
                gotoxy(55,y-1);
                cout<<"Dias a descontar: ";
                gets(diasDC);

                //Si digita uno regresa
                if(strcmp(diasDC, "0") == 0){
                    goto salir;
                }

                diasD = validar_numero(diasDC); //Se valida el dato obtenido

                if (diasD == -1 || diasD == 0) { //Condicion para mostrar error
                    errores = "- Datos invalidos en dias a descontar, ingrese solo numeros";
                    gotoxy(20,25);
                    cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
                    gotoxy(13,20);
                    cout<<ANSI_COLOR_RED<<"Descuento realizado: ninguno"<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length(), 20, 25);
                    cls(28, 13, 20);
                    centinela = 0;
                }else if (diasD > diasMeses[idMes] || diasD < 0) { //Condicion para mostrar error
                    errores = "- Dias a descontar invalidos, debe estar en el intervalo de [1-";
                    gotoxy(20,25);
                    cout<<ANSI_COLOR_RED<<errores<<diasMeses[idMes]<<"]"<<ANSI_COLOR_RESET;
                    gotoxy(13,20);
                    cout<<ANSI_COLOR_RED<<"Descuento realizado: ninguno"<<ANSI_COLOR_RESET;
                    getch();
                    cls(errores.length()+5, 20, 25);
                    cls(28, 13, 20);
                    centinela = 0; //Cambia la variable para mantener el ciclo do-while
                }
                
            }while(centinela != 1);

            salarioDia = e[seleccion].salario/diasMeses[idMes]; //Se obtiene el salario diario dependiendo el mes evaluado

            e[seleccion].descuento[idMes] = diasD * salarioDia; //Se realiza el descuento dependiendo los dias y el salario diario

            gotoxy(13,20);
            cout<<fixed<<setprecision(2)<<ANSI_COLOR_GREEN<<"Descuento realizado: $"<<(float)e[seleccion].descuento[idMes]<<ANSI_COLOR_RESET;         
            gotoxy(20,25);
            mensaje = "Descuentos realizados correctamente.";
            cout<<ANSI_COLOR_GREEN<<mensaje<<ANSI_COLOR_RESET;
                e[seleccion].pl.Adescontar = e[seleccion].descuento[idMes]; // Julio Torres

            getch();
            salir:
            cout<<"";
            system("mode con: cols=120 lines=30");
        }
    }while (DS != 1);   
}
// @Walter
void registroRetenciones(int indice) {
    char select[200];
    int op = 0;

    do{
        system("mode con: cols=120 lines=30");
        header();
        gotoxy(10,9);
        printf("%c Registro de retenciones de ley",254);
        gotoxy(10,11);
        cout<<"[1] Ver porcentajes de retencion activos";
        gotoxy(10,12);
        cout<<"[2] Modificar porcentajes de retencion";
        gotoxy(10,13);
        cout<<"[3] Historial de modificaciones";
        gotoxy(10,14);
        cout<<"[4] Volver";
        gotoxy(10,16);
        cout<<"Selecciona: ";
        gets(select);
        fflush(stdin);
        if (strlen(select) > 4) { //Si la seleccion recibe demasiados valores
            op = -1;
        }else {
            op = validar_numero(select); //Validacion del dato ingresado
        }

        //Submenu
        switch(op){
            case 1: system("cls"); registroRetenciones_verPorcentajes(indice); break;
            case 2: system("cls"); registroRetenciones_modificar(indice); break;
            case 3: system("cls"); registroRetenciones_historial(indice); break;
            case 4: op = 4; break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();break;//Mensaje modulo no encontrado
        }
    }while(op != 4);
}
void registroRetenciones_verPorcentajes(int indice) {
    char recep[200], retupor[200], slcpor[10];
    int op, rpo, spo, valid;

    system("mode con: cols=120 lines=30");
    header();

    gotoxy(10,9);
    printf("%c Ver porcentajes de retencion activos",254);

    cuadro(10,11,108,21);

    cuadro(12,12,106,14);
    
    if(h[0].estado == 1) {
        gotoxy(38,13);
        cout<<ANSI_COLOR_YELLOWLIGTH<<"Porcentajes predeterminados actualmente activos"<<ANSI_COLOR_RESET;
        
        gotoxy(18,16);
        cout<<"AFP";
        cuadro(12,15,26,17);

        gotoxy(32,16);
        cout<<"ISSS";
        cuadro(26,15,42,17);

        gotoxy(45,16);
        cout<<"Renta II Tramo";
        cuadro(42,15,62,17);

        gotoxy(66,16);
        cout<<"Renta III Tramo";
        cuadro(62,15,85,17);

        gotoxy(89,16);
        cout<<"Renta IV Tramo";
        cuadro(85,15,106,17);
        
        for (int i = 0; i < conteoModificaciones; i++) {
            if (h[i].estado == 1) {
                cout<<ANSI_COLOR_GREEN;
                gotoxy(17,18);
                cout<<h[i].p[i].porAfp<<" %";
                gotoxy(33,18);
                cout<<h[i].p[i].porIsss<<" %";
                gotoxy(51,18);
                cout<<h[i].p[i].porRenta1<<" %";
                gotoxy(72,18);
                cout<<h[i].p[i].porRenta2<<" %";
                gotoxy(95,18);
                cout<<h[i].p[i].porRenta3<<" %";
                cout<<ANSI_COLOR_RESET;
            }
        } 

        gotoxy(10,23);
        cout<<ANSI_COLOR_YELLOWLIGTH<<"Nota: "<<ANSI_COLOR_RESET<<"Presione [Enter] si desea volver\n";
        getch();
    }else {
        do {
            ampliar_pantalla(9);

            gotoxy(10,9);
            printf("%c Ver porcentajes de retencion activos",254);

            gotoxy(49,13);
            
            cuadro(10,11,59,21);
            
            cuadro(16,12,53,14);

            gotoxy(19,13);
            cout<<ANSI_COLOR_GREEN<<"Porcentajes actualmente activos"<<ANSI_COLOR_RESET;

            for (int i = 0; i < conteoModificaciones; i++) {
                if(h[i].estado == 1) {
                    for (int j = 15; j < 20; j++) {
                        cls(8,37,j);
                    } 
                    gotoxy(16,15);
                    cout<<"AFP";gotoxy(37,15);cout<<ANSI_COLOR_GREEN<<h[i].p[i].porAfp<<" %"<<ANSI_COLOR_RESET;
                    gotoxy(16,16);
                    cout<<"ISSS";gotoxy(37,16);cout<<ANSI_COLOR_GREEN<<h[i].p[i].porIsss<<" %"<<ANSI_COLOR_RESET;
                    gotoxy(16,17);
                    cout<<"Renta II Tramo";gotoxy(37,17);cout<<ANSI_COLOR_GREEN<<h[i].p[i].porRenta1<<" %"<<ANSI_COLOR_RESET;
                    gotoxy(16,18);
                    cout<<"Renta III Tramo";gotoxy(37,18);cout<<ANSI_COLOR_GREEN<<h[i].p[i].porRenta2<<" %"<<ANSI_COLOR_RESET;
                    gotoxy(16,19);
                    cout<<"Renta IV Tramo";gotoxy(37,19);cout<<ANSI_COLOR_GREEN<<h[i].p[i].porRenta3<<" %"<<ANSI_COLOR_RESET;
                }
            }

            cuadro(60,11,108,21);

            cuadro(66,12,102,14);
            gotoxy(71,13);
            cout<<ANSI_COLOR_YELLOWLIGTH<<"Porcentajes predeterminados"<<ANSI_COLOR_RESET;
            
            gotoxy(66,15);
            cout<<"AFP";gotoxy(87,15);cout<<ANSI_COLOR_YELLOWLIGTH<<h[0].p[0].porAfp<<" %"<<ANSI_COLOR_RESET;
            gotoxy(66,16);
            cout<<"ISSS";gotoxy(87,16);cout<<ANSI_COLOR_YELLOWLIGTH<<h[0].p[0].porIsss<<" %"<<ANSI_COLOR_RESET;
            gotoxy(66,17);
            cout<<"Renta II Tramo";gotoxy(87,17);cout<<ANSI_COLOR_YELLOWLIGTH<<h[0].p[0].porRenta1<<" %"<<ANSI_COLOR_RESET;
            gotoxy(66,18);
            cout<<"Renta III Tramo";gotoxy(87,18);cout<<ANSI_COLOR_YELLOWLIGTH<<h[0].p[0].porRenta2<<" %"<<ANSI_COLOR_RESET;
            gotoxy(66,19);
            cout<<"Renta IV Tramo";gotoxy(87,19);cout<<ANSI_COLOR_YELLOWLIGTH<<h[0].p[0].porRenta3<<" %"<<ANSI_COLOR_RESET;

            gotoxy(10,23);
            cout<<"[1] Implementar porcentajes predeterminados - [2] Volver";
            gotoxy(10,25);
            cout<<"Digite: ";
            gets(recep);

            if (strlen(recep) > 2) { //Si la seleccion recibe demasiados valores
                op = -1;
            }else {
                op = validar_numero(recep);
            }

            switch(op) {
                case 1: 
                    do{
                        system("mode con: cols=120 lines=30");
                        header();
                        gotoxy(10,9);
                        printf("%c Ver porcentajes de retencion activos / Implementar porcentajes predeterminados",254);

                        cuadro(18,11,99,25);
                        gotoxy(37,12);
                        cout<<"P o r c e n t a j e s  P o r  D e f e c t o";
                        
                        gotoxy(23,13);
                        for(int i = 0; i < 71; i++){
                            printf("%c",196);
                        }

                        printf("%c",196);
                        gotoxy(28,14);
                        printf("%cEst%cs seguro de que deseas volver a los valores por defecto?",168,160);
                        gotoxy(30,16);
                        cout<<"AFP: "<<h[0].p[0].porAfp<<" %";
                        gotoxy(30,17);
                        cout<<"ISSS: "<<h[0].p[0].porIsss<<" %";
                        gotoxy(30,18);
                        cout<<"Renta II Tramo: "<<h[0].p[0].porRenta1<<" %";
                        gotoxy(30,19);
                        cout<<"Renta III Tramo: "<<h[0].p[0].porRenta2<<" %";
                        gotoxy(30,20);
                        cout<<"Renta IV Tramo: "<<h[0].p[0].porRenta3<<" %";

                        gotoxy(43,22);
                        cout<<"[1] Aplicar - [2] Cancelar";

                        gotoxy(23,23);
                        for(int i = 0; i < 71; i++){
                            printf("%c",196);
                        }

                        gotoxy(53,24);
                        cout<<"Digite: ";
                        gets(retupor);

                        if (strlen(retupor) > 2) { //Si la seleccion recibe demasiados valores
                            rpo = -1;
                        }else {
                            rpo = validar_numero(retupor);
                        } 

                        cls(27, 43, 22);
                        cls(71, 23, 23);
                        cls(50, 43, 24);

                        if(rpo == 1){
                            h[0].estado = 1;
                            for (int i = 1; i < conteoModificaciones; i++) {
                                h[i].estado = 0;
                            }

                            //Mensaje
                            gotoxy(47,23); cout<<ANSI_COLOR_GREEN<<" (+) Cambios Aplicados";
                            cuadro(45,22,73,24); cout<<ANSI_COLOR_RESET;
                            getch();
                            valid = 1;
                            op = 2;
                        }else if(rpo == 2){
                            valid = 1;
                        }else{                 
                            valid = 0;

                            //Mensaje
                            gotoxy(47,23); cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";
                            cuadro(44,22,73,24); cout<<ANSI_COLOR_RESET;
                            getch();
                            
                        }
                    }while(valid != 1);
                    break;
                case 2: break;
                default: gotoxy(48,27);cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";cuadro(45,26,75,28);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
            }
        } while(op != 2);
    }
}

void registroRetenciones_modificar(int indice){
    char recepAfp[50], recepIsss[3], recepRenta1[3], recepRenta2[3], recepRenta3[3];
    float afp, isss, renta1, renta2, renta3;
    string errores, mensaje;
    int conteo, centinela, auxConteo, mAfp = 0, mIsss = 0, mRenta1 = 0, mRenta2 = 0, mRenta3 = 0;
    char *recepAux;

    system("mode con: cols=120 lines=30");
    header();

    gotoxy(10,9);
    printf("%c Modificar porcentajes de retencion / Modificar",254);
    
    cuadro(66,9,108,19); //Cuadro exterior de porcentajes
    cuadro(72,10,102,12); //Cuadro interior
    gotoxy(78,11);
    cout<<"Porcentajes Activos";

    /* IMPRESION DE PORCENTAJES ACTIVOS */
    for (int i = 0; i < conteoModificaciones; i++) {
        if (h[i].estado == 1) {
            for (int j = 13; j < 18; j++) {
                cls(8,92,j); //Limpia un trozo de la pantalla
            } 
            gotoxy(71,13);
            cout<<"AFP";gotoxy(92, 13);cout<<h[i].p[i].porAfp<<"%";
            gotoxy(71,14);
            cout<<"ISSS";gotoxy(92, 14);cout<<h[i].p[i].porIsss<<"%";
            gotoxy(71,15);
            cout<<"Renta II Tramo";gotoxy(92, 15);cout<<h[i].p[i].porRenta1<<"%";
            gotoxy(71,16);
            cout<<"Renta III Tramo";gotoxy(92, 16);cout<<h[i].p[i].porRenta2<<"%";
            gotoxy(71,17);
            cout<<"Renta IV Tramo";gotoxy(92, 17);cout<<h[i].p[i].porRenta3<<"%";    
        }
    }

    cuadro(6,20,112,27); //Cuadro de mensajes
    gotoxy(8,21);
    cout<<"Mensaje(s): ";
    gotoxy(8,26);
    cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Presiona [Enter] consecutivos si no desea realizar cambios."<<ANSI_COLOR_RESET;

    conteo = 0; //Variable para llevar el control de "Enters dados"
    mensaje = ANSI_COLOR_GREEN;
    mensaje += "Cambios realizados correctamente.";
    mensaje += ANSI_COLOR_RESET; 
    
    do{
        centinela = 1; //Variable que controla el bucle de la captura de datos
        
        auxConteo = conteoModificaciones; //Variable aux para el control de las modificaciones

        gotoxy(11,11);
        cout<<"Nuevo porcentaje de AFP: ";
        gets(recepAfp); //Captura de dato

        //Validacion del dato capturado
        afp = strtod(recepAfp, &recepAux); //Devuelve 0 cuando se encuentran caracteres y un valores positivo cuando encuentra numeros
        fflush(stdin);

        if(((afp <= 0) && (recepAfp[0] != '\0')) || recepAux[0] != '\0' || afp > 100){ 
            errores = "- Nuevo porcentaje incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            cls(strlen(recepAfp), 36, 11);//Borra linea de la pantalla
            centinela = 0;
        }else if(afp == 0){ //En caso de dar enter, se mantienen los porcentajes actuales
            h[conteoModificaciones].p[conteoModificaciones].porAfp = h[conteoModificaciones-1].p[conteoModificaciones-1].porAfp;
            centinela = 1;
            conteo++;
        }else if (afp != 0) {
            /* Se almacena el dato obtenido ya validado */
            mAfp = 1;
            h[conteoModificaciones].p[conteoModificaciones].porAfp = afp;
            h[conteoModificaciones].accion[conteoModificaciones] += "AFP";
            h[conteoModificaciones].estado = 1;
        }
    }while(centinela != 1);

    do{
        centinela = 1; //Variable que controla el bucle de la captura de datos

        gotoxy(11,12);
        cout<<"Nuevo porcentaje de ISSS: ";
        gets(recepIsss); //Captura de dato

        //Validacion del dato capturado
        isss = strtod(recepIsss, &recepAux); //Devuelve 0 cuando se encuentran caracteres y un valores positivo cuando encuentra numeros
        fflush(stdin);

        if(((isss <= 0) && (recepIsss[0] != '\0')) || recepAux[0] != '\0' || isss > 100){
            errores = "- Nuevo porcentaje incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            cls(strlen(recepIsss), 37, 12); //Borra linea de la pantalla
            centinela = 0;
        }else if(isss == 0){ //En caso de dar enter, se mantienen los porcentajes actuales
            h[conteoModificaciones].p[conteoModificaciones].porIsss = h[conteoModificaciones-1].p[conteoModificaciones-1].porIsss;
            centinela = 1;
            conteo++;
        }else if (isss != 0) {
            /* Se almacena el dato obtenido ya validado */
            mIsss = 1;
            h[conteoModificaciones].p[conteoModificaciones].porIsss = isss;
            if (mAfp == 1) {
                h[conteoModificaciones].accion[conteoModificaciones] += ", ISSS";
            }else {
                h[conteoModificaciones].accion[conteoModificaciones] += "ISSS";
            }
            h[conteoModificaciones].estado = 1;
        }
    }while(centinela != 1);


    do{
        centinela = 1; //Variable que controla el bucle de la captura de datos

        gotoxy(11,13);
        cout<<"Nuevo porcentaje de Renta II Tramo: ";
        gets(recepRenta1);//Captura de dato

        //Validacion del dato capturado
        renta1 = strtod(recepRenta1, &recepAux); //Devuelve 0 cuando se encuentran caracteres y un valores positivo cuando encuentra numeros
        fflush(stdin);

        if(((renta1 <= 0) && (recepRenta1[0] != '\0')) || recepAux[0] != '\0' || renta1 > 100){
            errores = "- Nuevo porcentaje incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            cls(strlen(recepRenta1), 47, 13); //Borra linea de la pantalla
            centinela = 0;
        }else if(renta1 == 0){ //En caso de dar enter, se mantienen los porcentajes actuales
            h[conteoModificaciones].p[conteoModificaciones].porRenta1 = h[conteoModificaciones-1].p[conteoModificaciones-1].porRenta1;
            centinela = 1;
            conteo++;
        }else if (renta1 != 0) {
            mRenta1 = 1;
            h[conteoModificaciones].p[conteoModificaciones].porRenta1 = renta1;
            if (mAfp == 1 || mIsss == 1) {
                h[conteoModificaciones].accion[conteoModificaciones] += ", Renta II Tramo";
            }else {
                h[conteoModificaciones].accion[conteoModificaciones] += "Renta II Tramo";
            }
            h[conteoModificaciones].estado = 1;
        }

    }while(centinela != 1);

    do{
        centinela = 1;

        gotoxy(11,14);
        cout<<"Nuevo porcentaje de Renta III Tramo: ";
        gets(recepRenta2);

        renta2 = strtod(recepRenta2, &recepAux); //Devuelve 0 cuando se encuentran caracteres y un valores positivo cuando encuentra numeros
        fflush(stdin);

        if(((renta2 <= 0) && (recepRenta2[0] != '\0')) || recepAux[0] != '\0' || renta2 > 100){
            errores = "- Nuevo porcentaje incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            cls(strlen(recepRenta2), 48, 14); //Borra linea de la pantalla
            centinela = 0;
        }else if(renta2 == 0){ //En caso de dar enter, se mantienen los porcentajes actuales
            h[conteoModificaciones].p[conteoModificaciones].porRenta2 = h[conteoModificaciones-1].p[conteoModificaciones-1].porRenta2;
            centinela = 1;
            conteo++;
        }else if (renta2 != 0) {
            mRenta2 = 1;
            h[conteoModificaciones].p[conteoModificaciones].porRenta2 = renta2;
            if (mAfp == 1 || mIsss == 1 || mRenta1 == 1) {
                h[conteoModificaciones].accion[conteoModificaciones] += ", Renta III Tramo";
            }else {
                h[conteoModificaciones].accion[conteoModificaciones] += "Renta III Tramo";
            }
            h[conteoModificaciones].estado = 1;
        }
    }while(centinela != 1);    


    do{
        centinela = 1;

        gotoxy(11,15);
        cout<<"Nuevo porcentaje de Renta IV Tramo: ";
        gets(recepRenta3);

        renta3 = strtod(recepRenta3, &recepAux); //Devuelve 0 cuando se encuentran caracteres y un valores positivo cuando encuentra numeros
        fflush(stdin);

        if(((renta3 <= 0) && (recepRenta3[0] != '\0')) || recepAux[0] != '\0' || renta3 > 100){
            errores = "- Nuevo porcentaje incorrecto.";
            gotoxy(20,21); cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            getch();
            cls(errores.length(), 20, 21);
            cls(strlen(recepRenta3), 47, 15); //Borra linea de la pantalla
            centinela = 0;
        }else if(renta3 == 0){ //En caso de dar enter, se mantienen los porcentajes actuales
            h[conteoModificaciones].p[conteoModificaciones].porRenta3 = h[conteoModificaciones-1].p[conteoModificaciones-1].porRenta3;
            centinela = 1;
            conteo++;
        }else if (renta3 != 0) {
            h[conteoModificaciones].p[conteoModificaciones].porRenta3 = renta3;
            if (mAfp == 1 || mIsss == 1 || mRenta1 == 1 || mRenta2 == 1) {
                h[conteoModificaciones].accion[conteoModificaciones] += ", Renta IV Tramo";
            }else {
                h[conteoModificaciones].accion[conteoModificaciones] += "Renta IV Tramo";
            }
            h[conteoModificaciones].estado = 1;
        }
    }while(centinela != 1);

    if (h[conteoModificaciones].estado == 1) {
        for (int i = 0; i <= conteoModificaciones; i++){
            if (i != conteoModificaciones) {
                h[i].estado = 0;
            }
        } 
    }

    conteoModificaciones++;

    if(conteo == 5){
        mensaje = ANSI_COLOR_YELLOWLIGTH;
        mensaje += "No se realiz\xA2 ning\xA3n cambio.";
        mensaje += ANSI_COLOR_RESET;
        conteoModificaciones = auxConteo;
    }

    //Mensaje
    gotoxy(20,21); cout<<mensaje;     

    getch();
}

void registroRetenciones_historial(int indice) {
    int seleccion, bSeleccion;
    int auxSeleccion = '\0';
    int y, pos;
    string auxAccion;
    int auxEstado;
    float auxAfp, auxIsss, auxRenta1, auxRenta2, auxRenta3;
    char recepSeleccion[200];

    for (int i = 1; i < conteoModificaciones; i++) {
        pos = i;
        auxAccion = h[i].accion[i];
        auxEstado = h[i].estado;
        auxAfp = h[i].p[i].porAfp;
        auxIsss = h[i].p[i].porIsss;
        auxRenta1 = h[i].p[i].porRenta1;
        auxRenta2 = h[i].p[i].porRenta2;
        auxRenta3 = h[i].p[i].porRenta3;
        
        while (pos > 1 && auxEstado > h[pos-1].estado) {
            h[pos].accion[pos] = h[pos-1].accion[pos-1];
            h[pos].estado = h[pos-1].estado;
            h[pos].p[pos].porAfp = h[pos-1].p[pos-1].porAfp;
            h[pos].p[pos].porIsss = h[pos-1].p[pos-1].porIsss;
            h[pos].p[pos].porRenta1 = h[pos-1].p[pos-1].porRenta1;
            h[pos].p[pos].porRenta2 = h[pos-1].p[pos-1].porRenta2;
            h[pos].p[pos].porRenta3 = h[pos-1].p[pos-1].porRenta3;
            pos = pos-1;
        }
        h[pos].accion[pos] = auxAccion;
        h[pos].estado = auxEstado;
        h[pos].p[pos].porAfp = auxAfp;
        h[pos].p[pos].porIsss = auxIsss;
        h[pos].p[pos].porRenta1 = auxRenta1;
        h[pos].p[pos].porRenta2 = auxRenta2;
        h[pos].p[pos].porRenta3 = auxRenta3;
    }
        
    do {
        y = 13;

        if (conteoModificaciones >= 7) {
            ampliar_pantalla(conteoModificaciones+12);
        }else {
            system("mode con: cols=120 lines=30");
            header();
        }
        
        gotoxy(10,9);
        printf("%c Registro de retenciones de ley / Historial de modificaciones",254);

        gotoxy(11,12);
        printf("N%c", 167);
        cuadro(8,11,15,13);

        gotoxy(33, 12);
        cout<<"Porcentajes modificados";
        cuadro(15,11,96,13);

        gotoxy(81,12);
        cout<<"Estado de la modificacion";
        cuadro(76,11,110,13);
        
        if (conteoModificaciones == 1) {
            y++;
            gotoxy(41,y);
            cout<<"No se han realizado modificaciones"<<endl;
            
            gotoxy(10,y+4);
            cout<<ANSI_COLOR_YELLOWLIGTH<<"Nota: "<<ANSI_COLOR_RESET<<"Presione [Enter] si desea volver\n";
            getch();
        }else {
            for (int i = 1; i < conteoModificaciones; i++) {
                y++;
                gotoxy(89,y);
                if (h[i].estado == 1) {
                    cout<<ANSI_COLOR_GREEN<<"Activo"<<ANSI_COLOR_RESET;
                    gotoxy(11,y);
                    cout<<"-";
                }else {
                    cout<<ANSI_COLOR_RED<<"Inactivo"<<ANSI_COLOR_RESET;
                    gotoxy(11,y);
                    if (h[1].estado == 0) {
                        cout<<i;
                    }else {
                        cout<<i-1;
                    }
                }
                gotoxy(17,y);
                cout<<h[i].accion[i];
            }
            
            if (conteoModificaciones == 2 && h[0].estado == 0) {
                gotoxy(10,y+6);
                cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" No puedes elegir una modificacion activa. Presione [Enter] si desea volver"<<ANSI_COLOR_RESET;
                getch();
            }else {
                gotoxy(10,y+4);
                cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" No puedes elegir una modificacion activa."<<ANSI_COLOR_RESET;
                gotoxy(10, y+2);
                cout<<"Seleccione una modificacion o presione [Enter] para volver: ";
                gets(recepSeleccion); //Se obtiene la seleccion
                fflush(stdin);

                //Se valida la seleccion
                if (strlen(recepSeleccion) > conteoModificaciones || strlen(recepSeleccion) < 0) { //Si la seleccion recibe demasiados valores
                    seleccion = -1;  
                }else {
                    seleccion = validar_numero(recepSeleccion);
                }

                if (h[1].estado == 1){
                    if (seleccion != 0 && seleccion != -1) {
                        seleccion = seleccion + 1;
                    }
                }
                
                if (seleccion != 0){
                    if (h[seleccion].estado == 1) {
                        gotoxy(49,y+8);
                        cout<<ANSI_COLOR_YELLOWLIGTH <<"Modificacion actualmente activa";
                        cuadro(43,y+7,85,y+9);cout<<ANSI_COLOR_RESET;
                        getch();
                    }else if (seleccion != -1 && seleccion < conteoModificaciones) {
                        registroRetenciones_historial_detalles(seleccion, indice);
                        auxSeleccion = seleccion;
                    }else {
                        gotoxy(49,y+7);
                        cout<<ANSI_COLOR_RED<<"Error: Dato inv\xA0lido";
                        cuadro(46,y+6,71,y+8);cout<<ANSI_COLOR_RESET;
                        getch();
                    }
                }
            }
        }
    }while (seleccion != auxSeleccion);
}

void registroRetenciones_historial_detalles(int seleccion, int indice) {
    char recep[200], recepM[200];
    int op, validar, opM;
    
    do {
        ampliar_pantalla(9);

        gotoxy(10,9);
        printf("%c Registro de retenciones de ley / Historial de modificaciones / Detalles",254);

        gotoxy(10,11);
        cout<<"Porcentajes modificados: "<<h[seleccion].accion[seleccion];

        gotoxy(22,14);
        cout<<"Porcentajes a implementar";
        cuadro(10,13,59,15);
        
        gotoxy(74,14);
        cout<<"Porcentajes actuales";
        cuadro(59,13,108,15);

        gotoxy(24,16);
        cout<<ANSI_COLOR_GREEN<<"+"<<ANSI_COLOR_RESET<<" AFP: "<<h[seleccion].p[seleccion].porAfp<<"%";

        gotoxy(24,17);
        cout<<ANSI_COLOR_GREEN<<"+"<<ANSI_COLOR_RESET<<" ISSS: "<<h[seleccion].p[seleccion].porIsss<<"%";

        gotoxy(24,18);
        cout<<ANSI_COLOR_GREEN<<"+"<<ANSI_COLOR_RESET<<" Renta II Tramo: "<<h[seleccion].p[seleccion].porRenta1<<"%";

        gotoxy(24,19);
        cout<<ANSI_COLOR_GREEN<<"+"<<ANSI_COLOR_RESET<<" Renta III Tramo: "<<h[seleccion].p[seleccion].porRenta2<<"%";

        gotoxy(24,20);
        cout<<ANSI_COLOR_GREEN<<"+"<<ANSI_COLOR_RESET<<" Renta IV Tramo: "<<h[seleccion].p[seleccion].porRenta3<<"%";

        int y = 15;
        for (int j = 0; j < 5; j++) {
            y++;
            gotoxy(55, y);
            cout<<ANSI_COLOR_GREEN<<"--------->"<<ANSI_COLOR_RESET;
        }

        for (int i = 0; i < conteoModificaciones; i++) {
            if (h[i].estado == 1) {
                gotoxy(74,16);
                cout<<ANSI_COLOR_RED<<"-"<<ANSI_COLOR_RESET<<" AFP: "<<h[i].p[i].porAfp<<"%";
                gotoxy(74,17);
                cout<<ANSI_COLOR_RED<<"-"<<ANSI_COLOR_RESET<<" ISSS: "<<h[i].p[i].porIsss<<"%";
                gotoxy(74,18);
                cout<<ANSI_COLOR_RED<<"-"<<ANSI_COLOR_RESET<<" Renta II Tramo: "<<h[i].p[i].porRenta1<<"%";
                gotoxy(74,19);
                cout<<ANSI_COLOR_RED<<"-"<<ANSI_COLOR_RESET<<" Renta III Tramo: "<<h[i].p[i].porRenta2<<"%";
                gotoxy(74,20);
                cout<<ANSI_COLOR_RED<<"-"<<ANSI_COLOR_RESET<<" Renta IV Tramo: "<<h[i].p[i].porRenta3<<"%";
            }
        }

        gotoxy(10,23);
        cout<<"[1] Implementar cambios - [2] Volver";
        gotoxy(10,25);
        cout<<"Digite: ";
        gets(recep);

        if (strlen(recep) > 2) { //Si la seleccion recibe demasiados valores
            op = -1;
        }else {
            op = validar_numero(recep);
        }

        switch(op){
            case 1: 
                
                do {
                    system("cls");
                    header();
                    gotoxy(10,9);
                    printf("%c Registro de retenciones de ley / Historial de modificaciones / Detalles / Implementar cambios",254);
                    cuadro(18,11,99,25);
                    gotoxy(41,12);
                    cout<<"I m p l e m e n t a r  C a m b i o s";

                    gotoxy(23,13);
                    for(int i = 0; i < 71; i++){
                        printf("%c",196);
                    }
                    
                    printf("%c",196);
                    gotoxy(33,14);
                    printf("%cDeseas implementar estos cambios en los porcentajes?",168,160);
                    gotoxy(30,16);
                    cout<<"AFP: "<<h[seleccion].p[seleccion].porAfp<<" %";
                    gotoxy(30,17);
                    cout<<"ISSS: "<<h[seleccion].p[seleccion].porIsss<<" %";
                    gotoxy(30,18);
                    cout<<"Renta II Tramo: "<<h[seleccion].p[seleccion].porRenta1<<" %";
                    gotoxy(30,19);
                    cout<<"Renta III Tramo: "<<h[seleccion].p[seleccion].porRenta2<<" %";
                    gotoxy(30,20);
                    cout<<"Renta IV Tramo: "<<h[seleccion].p[seleccion].porRenta3<<" %";
                    gotoxy(43,22);
                    cout<<"[1] Aplicar - [2] Cancelar";

                    //Crea una linea
                    gotoxy(23,23);
                    for(int i = 0; i < 71; i++){
                        printf("%c",196);
                    }

                    gotoxy(53,24);
                    cout<<"Digite: ";
                    gets(recepM);

                    if (strlen(recepM) > 2) { //Si la seleccion recibe demasiados valores
                        opM = -1;
                    }else {
                        opM = validar_numero(recepM);
                    }
                
                    cls(27, 43, 22);
                    cls(71, 23, 23);
                    cls(50, 43, 24);

                    if (opM == 1) {
                        h[seleccion].estado = 1;
                        for (int i = 0; i < conteoModificaciones; i++) {
                            if (i != seleccion) {
                                h[i].estado = 0;
                            }
                        }

                        validar = 1; //bandera para salir del bucle

                        //Mensaje
                        gotoxy(47,23); cout<<ANSI_COLOR_GREEN<<" (+) Cambios aplicados";
                        cuadro(45,22,73,24); cout<<ANSI_COLOR_RESET;
                        getch();
                        op = 2;
                    }else if (opM == 2){
                        validar = 1;
                    }else {
                        validar = 0;

                        //Mensaje
                        gotoxy(47,23); cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";
                        cuadro(44,22,73,24); cout<<ANSI_COLOR_RESET;
                        getch();
                    }
                } while (validar != 1);
                //getch();
                break;
            case 2: system("cls"); registroRetenciones_historial(indice);break;
            default: gotoxy(48,27);cout<<ANSI_COLOR_RED<<"Error: Opci\xA2n incorrecta";cuadro(45,26,75,28);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
        }
    } while(op != 2);    
}

void calculoRetenciones(int indice) {
    /* Calculo de las retenciones de ley */
    for (int j = 0; j < conteoModificaciones; j++) {
        if (h[j].estado == 1) {
            for (int i = 0; i < indice; i++) {
                e[i].afp = e[i].salario * (h[j].p[j].porAfp/100); //Calculo de afp
                    
                if(e[i].salario >= 1000) {
                    e[i].isss = 30; //Calculo de ISSS en mas de 1000
                }else {
                    e[i].isss = e[i].salario * (h[j].p[j].porIsss/100); //Calculo de ISSS
                }
                
                e[i].salarioAfpIss = e[i].salario - (e[i].afp +  e[i].isss); //Sueldo - (AFP + ISSS) = Descuentos en el sueldo

                //Calculo de renta
                if(e[i].salarioAfpIss < 472){
                    e[i].renta = 0;
                }else if(e[i].salarioAfpIss < 895.24) {
                    e[i].renta = ((e[i].salarioAfpIss - 472) * (h[j].p[j].porRenta1/100)) + 17.67; 
                }else if(e[i].salarioAfpIss < 2038.10) {
                    e[i].renta = ((e[i].salarioAfpIss - 895.24) * (h[j].p[j].porRenta2/100)) + 60; 
                }else if(e[i].salarioAfpIss > 2038.11) {
                    e[i].renta = ((e[i].salarioAfpIss - 2038.10) * (h[j].p[j].porRenta3/100)) + 288.57;
                }
            }
        }
    }
}

int buscarEmpleados(char recep[50], int indice, char str1[25], char str2[25], int& p, int& y) {
    int seleccion;
    int auxSeleccion = '\0';
    int Dui;
    bool exist;
    int pointer[indice], c, t;
    char mode[40] = "mode con: cols=120 lines=";
    char tc[5];

    int id = -2;
    y = 13;

    Dui = validar_numero(recep); //Validacion del dato obtenido

    if (Dui == -1) {
        if(validar_cadena(recep) > 0 || (recep[0] == '\0') || (recep[0] == ' ')){ //Condicion para mostrar error
            gotoxy(20,21);
            cout<<ANSI_COLOR_RED<<"Dato inv\xA0lido"<<ANSI_COLOR_RESET;
            getch();
        }else {
            if(indice <= 0){ //Si no existe ningun empleado
                gotoxy(20,21);
                cout<<ANSI_COLOR_RED<<"No hay empleados registrados, por favor ingrese datos."<<ANSI_COLOR_RESET;
                getch();
            }else {
                exist = verificarEmpleado(recep, indice, c); //Verifica si el dato obtenido existe en la lista de empleados
                
                if (!exist) { //En caso de no existir, muestra error
                    gotoxy(20,21);
                    cout<<ANSI_COLOR_RED<<"Empleado no encontrado."<<ANSI_COLOR_RESET;
                    getch();
                }else {
                    do {

                        /* if (exist) {
                            mostrarEmpleados(recep, indice, pointer, y, c); //Obtenemos el valor de la cantidad de resultados
                        } */
 
                        ampliar_pantalla(c); //Alarga la pantalla y el cuadro

                        if (exist) {
                            mostrarEmpleados(recep, indice, pointer, y, c); //Muestra la lista de empleados segun el dato obtenido
                        }

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
                        
                        char recepSeleccion[2];
                        gotoxy(10, y+3);
                        cout<<"Seleccione empleado o presione [Enter] para volver: ";
                        gets(recepSeleccion); //Se obtiene la seleccion
                        fflush(stdin);
                        if (strlen(recepSeleccion) > c) {
                            seleccion = -1;
                        }else {
                            seleccion = validar_numero(recepSeleccion); //Se valida la seleccion
                        }

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
            if (strcmp(e[i].dui, recep) == 0) { //Condicion para buscar el DUI segun el dato ingresado
                id = i;
            }

        }
        

        if(id == -2){ //Condicones para mostrar errores
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

    return seleccion; //Devuelve la seleccion
}
bool verificarEmpleado(char recep[50], int indice, int& c) {
    bool exist = false;
    char auxNom[50] = "\0", auxApe[50] = "\0", auxCargo[50] = "\0";

    c = 0;

    for (int i = 0; i < indice; i++) {
        /* COMPARACION DE NOMBRE */
        strcpy(auxNom, e[i].nom);
        char *tokenNom = strtok(auxNom, " "); //Se divide el nombre en palabras
        
        if(tokenNom != NULL){
            while(tokenNom != NULL){ 
                if (strcmp(recep, tokenNom) == 0) { //Se comparan las palabras con el dato ingresado
                    exist = true;
                    c++;
                }
                tokenNom = strtok(NULL, " "); //Se vacia el token
            }
        }

        /* COMPARACION DE APELLIDOS */
        strcpy(auxApe, e[i].ape);
        char *tokenApe = strtok(auxApe, " "); //Se divide el apellido en palabras
        
        if(tokenApe != NULL){
            while(tokenApe != NULL){
                if (strcmp(recep, tokenApe) == 0) { //Se comparan los apellidos con el dato ingresado
                    exist = true;
                    c++;
                }
                tokenApe = strtok(NULL, " "); 
            }
        }

        /* COMPARACION DE CARGOS */
        strcpy(auxCargo, e[i].cargo);
        char *tokenCargo = strtok(auxCargo, " "); //Se divide el cargo en palabras
        
        if(tokenCargo != NULL){
            while(tokenCargo != NULL){
                if (strcmp(recep, tokenCargo) == 0) { //Se comparan el cargo con el dato ingresado
                    exist = true;
                    c++;
                }
                tokenCargo = strtok(NULL, " "); 
            }
        }
    }

    return exist; //Retorna un booleano, dependiendo si existe o no el empleado
}
void mostrarEmpleados(char recep[50], int indice, int pointer[], int& y, int& x) {
    int a, c, pos[indice], doble, j = 0, k;
    char auxNom[50] = "\0", auxApe[50] = "\0", auxCargo[50] = "\0";

    a = 0;
    c = 0;
    y = 13;

    for (int i = 0; i < indice; i++) {
        /* IMPRESION POR NOMBRE */
        strcpy(auxNom, e[i].nom);
        char *tokenNom = strtok(auxNom, " ");
        if(tokenNom != NULL){
            while(tokenNom != NULL){
                if (strcmp(recep, tokenNom) == 0) { //Compara el dato ingresado con los nombres
                    impresionBuscar(y, pointer, a, c, i);
                }
                tokenNom = strtok(NULL, " ");    
            }    
        }

        k = 0;
        /* IMPRESION POR APELLIDOS */
        strcpy(auxApe, e[i].ape);
        char *tokenApe = strtok(auxApe, " ");
        if(tokenApe != NULL){
            while(tokenApe != NULL){
                if (strcmp(recep, tokenApe) == 0) { //Compara el dato ingresado con los apellidos
                    doble = verificarDoble(i);
                    
                    if (doble == 0) {
                        impresionBuscar(y, pointer, a, c, i);
                    }

                    if (k == 0) {
                        if (doble == 1) {
                            while (doble > 0) {
                                impresionBuscar(y, pointer, a, c, i);

                                doble--;
                                k++;
                            }
                        }
                    }
                    
                    
                }
                tokenApe = strtok(NULL, " ");
            }
        }
        
        /* IMPRESION POR CARGO */
        strcpy(auxCargo, e[i].cargo);
        char *tokenCargo = strtok(auxCargo, " ");
        if(tokenCargo != NULL){
            while(tokenCargo != NULL){
                if (strcmp(recep, tokenCargo) == 0) {  //Compara el dato ingresado con los cargos
                    impresionBuscar(y, pointer, a, c, i);
                }
                tokenCargo = strtok(NULL, " ");
            }
        }
        ++a;
    }

    if (c > 0) {
        x = c; //Devuelve la cantidad de resultados, solo si estos son mayores a 0
    }
}

void impresionBuscar(int& y, int pointer[], int& a, int& c, int i) {
    y++;

    gotoxy(11,y);
    pointer[c] = a+c; //Se almacena en un vector la posicion de cada resultado
    c++;
    cout<<(i+1)-(a--); //Calcula un correlativo de 1 a n resultados
    
    gotoxy(16,y);
    cout<<e[i].dui;

    gotoxy(28,y);
    cout<<e[i].nom;

    gotoxy(54,y);
    cout<<e[i].ape;

    gotoxy(80,y);
    cout<<e[i].cargo;

    gotoxy(99,y);
    cout<<"$"<<fixed<<setprecision(2)<<e[i].salario;
}

int verificarDoble(int i) {
    char auxApe[50] = "\0";
    char apeP[2][15];
    int doble = 0, j = 0;

    strcpy(auxApe, e[i].ape);
    char *tokenApe = strtok(auxApe, " ");

    if (tokenApe != NULL) {
        while (tokenApe != NULL) {
            strcpy(apeP[j], tokenApe);
            tokenApe = strtok(NULL, " ");
            j++;
        }

    }

    if (strcmp(apeP[1], apeP[0]) == 0) {
        doble = 1;
    }

    return doble;
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
void ampliar_pantalla(int c){
    char mode[40] = "mode con: cols=120 lines=";
    char tc[5];
    int t;

    if(c > 7){ //Si hay mas de 7 registro, la pantalla se alarga
        t = 23 + c;
        itoa(t, tc, 10);
        strcat(mode, tc);
        system(mode);
        cuadro(4,6,114,21+c);
    }else{
        system("cls");
        cuadro(4,6,114,28);
    }

    cuadro(4,1,114,5);
    gotoxy(23,3); cout<<"P A N E L  D E  C O N T R O L  |  S I S T E M A  D E  P L A N I L L A S";
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