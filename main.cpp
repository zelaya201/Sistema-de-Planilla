//Repositorio
//https://github.com/zelaya201/Sistema-de-Planilla

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

void header();
void headerWithoutsquare();
int isalpha(int);
int isspace(int);
void gotoxy(int, int );// x - y
void cuadro(int, int, int, int);//derecha, arriba, izquierda, abajo
int menu();
int validar_numero(char []);
int validar_cadena(char []);
void registroEmpleados(int [row], char [row][cols], char [row][cols], char [row][25], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_registrar(int [row], char [row][cols], char [row][cols], char [row][25], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_edit(int [row], char [row][cols], char [row][cols], char [row][25], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_delete(int [row], char [row][cols], char [row][cols], char [row][25], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
// prototipos para las planillas
void planillaMensual(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice);
// void repDescuento(int mes /*  */);
void cuadroPlanillas(int x1, int y1, int x2, int y2);
void menuMeses();
int main(){ // Funcion principal

    int op;

/*    int dui[row] = {'\0'};
    int indice = 0;
    char nom[row][cols] = {'\0'}, ape[row][cols] = {'\0'}, cargo[row][25] = {'\0'};
    float salario[row]; */

    /* PARA PROBAR Y EVITARSE ESTAR REGISTRANDO DATOS XD */

    int dui[row] = {12345678,87654321,17283782,10293827,29382019,20391827,99281762,28379120,17283782,10293827,29382019,20391827,99281762,28379120};
    int indice = 8;
    char nom[row][cols] = {
        {"Josue Adonay"},
        {"Walter Alejandro"},
        {"Julio Antonio"},
        {"Keneth Valerio"},
        {"Mario Ernesto"},
        {"Shelsy Yamileth"},
        {"Karla Beatriz"},
        {"Luis Fernando"},
        {"Julio Antonio"},
        {"Keneth Valerio"},
        {"Mario Ernesto"},
        {"Shelsy Yamileth"},
        {"Karla Beatriz"},
        {"Luis Fernando"}
    };
    char ape[row][cols] = {
        {"Aguilar Rivas"},
        {"Morales Quintanilla"},
        {"Torres Rodriguez"},
        {"Ramirez Constanza"},
        {"Zelaya Lainez"},
        {"Constanza Abarca"},
        {"Aguilar Martinez"},
        {"Vaquerano Ramos"},
        {"Aguilar Rivas"},
        {"Morales Quintanilla"},
        {"Torres Rodriguez"},
        {"Ramirez Constanza"},
        {"Zelaya Lainez"},
        {"Constanza Abarca"}
    };

    char cargo[row][25] = {
        {"Programador"},
        {"DBA"},
        {"Analista"},
        {"Redes"},
        {"Ingeniero"},
        {"Servicio Social"},
        {"Disenador Grafico"},
        {"Periodista"},
        {"Analista"},
        {"Redes"},
        {"Ingeniero"},
        {"Servicio Social"},
        {"Disenador Grafico"},
        {"Periodista"}
    }; 
    
    float salario[row] = {2100,900,1400,1000,1830,800,1200,2001,900,1400,1000,1830,800,1200};

    system("title Sistema de Planillas");

    do{
        op = menu();

        switch(op){
            case 1: system("cls");registroEmpleados(dui, nom, ape, cargo, salario, indice);break;
            case 2: system("cls");cout<<"Modulo en proceso";break;
            case 3: system("cls");planillaMensual(dui, nom, ape, cargo, salario, indice);break; // Mi modulo correspondiente, planilla mensual
            case 4: system("cls");cout<<"Modulo en proceso";break; // Modulo planilla quincenal, Julio
            case 5: system("cls");cout<<"Modulo en proceso";break;
            case 6: gotoxy(42,22);cout<<ANSI_COLOR_YELLOWLIGTH<<"Mensaje: Hasta luego, vuelva pronto";cuadro(40,21,78,23);cout<<ANSI_COLOR_RESET;Sleep(3000);break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: Modulo incorrecto";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
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
	cout<<"Elija una opcion: ";

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
    opcion = validar_numero(opAux);

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
void planillaMensual(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice)
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
                cout<<dui[i];

                gotoxy(22,y);
                for(int j = 0; j < strlen(nom[i]); j++){
                    cout<<nom[i][j];
                }
                gotoxy(44,y);
                for(int j = 0; j < strlen(ape[i]); j++){
                    cout<<ape[i][j];
                }

                gotoxy(68,y);
                for(int j = 0; j < strlen(cargo[i]); j++){
                    cout<<cargo[i][j];
                }

                gotoxy(88,y); // AFP
                cout<<"$"<<salario[i];
                
                gotoxy(103,y);
                AFP[i] = (salario[i]*0.0725); // Aqui recibire el calculo del modulo de Walter!!
                cout << "$" << setprecision(5) << AFP[i];
        
                gotoxy(116,y);
                isss[i] = (salario[i]*0.03); // Parte del modulo de Walter
                cout << "$" << ceil(isss[i]) << ".00";

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
void registroEmpleados(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice){

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
            case 1: system("cls"); registroEmpleados_registrar(dui, nom, ape, cargo, salario, indice); break;
            case 2: system("cls"); registroEmpleados_edit(dui, nom, ape, cargo, salario, indice); break;
            case 3: system("cls"); registroEmpleados_delete(dui, nom, ape, cargo, salario, indice);break;
            case 4: break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: opcion incorrecta";
            cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;;getch();//Mensaje modulo no encontrado
        }

    }while(op != 4);

}

void registroEmpleados_registrar(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice){

    int cant, cifras, duiAux, validar, retorno;
    char DV[9], SV[10];
    char *salarioAux;
    string errores, mensaje;
    
    do{
        cant = 1;
        cifras = 1;
        duiAux = 0;
        retorno = 0;
        errores = "\0";

        system("cls");

        header();
        cuadro(6,20,112,27);
        gotoxy(8,21);
        cout<<"Mensaje(s): ";
        gotoxy(10,9);
        printf("%c Registro de empleados / Registrar",254);
        gotoxy(11,11);
        printf("N%c de DUI: ",167);
        gets(DV);
        fflush(stdin);

        dui[indice] = validar_numero(DV);

        for(int i = 0; i < row; i++){
            if((dui[indice] == dui[i]) && (i != indice)){
                cant++;
            }
        }

        duiAux = dui[indice];

        while(duiAux >= 10){
            duiAux /= 10;
            cifras++;
        }

        if(cifras != 8){
            errores += "\n\t\t";
            errores += "- Numero de DUI menor o mayor a 8 cifras y/o incorrecto.";
        }else if(cant > 1){
            errores += "\n\t\t";
            errores += "- Numero de DUI ya existente, ingrese otro.";
        }

        gotoxy(11,12);
        cout<<"Nombre: ";
        gets(nom[indice]);

        if(validar_cadena(nom[indice]) > 0 || (nom[indice][0] == '\0') || (nom[indice][0] == ' ')){
            errores += "\n\t\t";
            errores += "- Nombre incorrecto.";
        }

        gotoxy(11,13);
        cout<<"Apellidos: ";
        gets(ape[indice]);

        if(validar_cadena(ape[indice]) > 0 || (ape[indice][0] == '\0') || (ape[indice][0] == ' ')){
            errores += "\n\t\t";
            errores += "- Apellidos incorrectos.";
        }

        gotoxy(11,14);
        cout<<"Cargo: ";
        gets(cargo[indice]);

        if(validar_cadena(cargo[indice]) > 0 || (cargo[indice][0] == '\0') || (cargo[indice][0] == ' ')){
            errores += "\n\t\t";
            errores += "- Cargo escrito incorrectamente.";
        }

        gotoxy(11,15);
        cout<<"Salario: $";
        gets(SV);
        salario[indice] = strtod(SV, &salarioAux);

        if(salario[indice] == 0){
            errores += "\n\t\t";
            errores += "- Cantidad de salario incorrecta.";
        }

        fflush(stdin);    
            if(errores != "\0"){
                gotoxy(21,21);
                cout<<ANSI_COLOR_RED<<errores<<ANSI_COLOR_RESET;
            }else{
                gotoxy(20,21);
                errores += "Registrado correctamente.";
                cout<<ANSI_COLOR_GREEN<<errores<<ANSI_COLOR_RESET;
                indice++;
                validar = 1;
            }

        getch();
    }while(validar != 1);
}

void registroEmpleados_edit(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice){

    int duiEdit, validar, j;
    float auxSueldo;
    char auxNom[cols];
    char auxApe[cols];
    char auxCargo[cols];
    char nomHeader[cols];
    char apeHeader[cols];
    char DV[8];
    char SV[10] = {'\0'};
    char *salarioAux;
    string errores;
    string mensaje;
        
    do{
        int y = 13;
        int id = -2;
        
        system("cls");
        headerWithoutsquare();
        if(indice > 8){
            cuadro(4,6,114,20+indice);
        }else{
            cuadro(4,6,114,28);
        }
        cuadro(4,1,114,5);
        gotoxy(10,9);
        printf("%c Registro de empleados / Editar",254);

        gotoxy(16,12);
        cout<<"DUI";
        cuadro(8,11,26,13);

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

        if(indice <= 0){
            gotoxy(32,y+2);
            cout<<"No hay empleados registrados, por favor ingrese datos";
            duiEdit = 1;
            getch();
        }else{
            for(int i = 0; i < indice; i++){

                y++;

                gotoxy(13,y);
                cout<<dui[i];

                gotoxy(29,y);
                for(int j = 0; j < strlen(nom[i]); j++){
                    cout<<nom[i][j];
                }

                gotoxy(55,y);
                for(int j = 0; j < strlen(ape[i]); j++){
                    cout<<ape[i][j];
                }

                gotoxy(80,y);
                for(int j = 0; j < strlen(cargo[i]); j++){
                    cout<<cargo[i][j];
                }

                gotoxy(101,y);
                cout<<"$"<<salario[i];
            }

            gotoxy(12,y+3);
            cout<<"Escriba DUI de empleado a editar o [1] para cancelar: ";
            gets(DV);
            fflush(stdin);

            duiEdit = validar_numero(DV);

            for(int i = 0; i < indice; i++){
                if(duiEdit == dui[i]){
                    id = i;
                }
            }

            if(id == -2){
                if(duiEdit != 1){
                    gotoxy(28,y+5);
                    cout<<ANSI_COLOR_RED<<"Error: No se encontro ningun empleado con ese numero de DUI";
                    cuadro(26,y+4,88,y+6);cout<<ANSI_COLOR_RESET;
                    getch();
                }
            }else{

                do{
                    system("cls");
                    errores = "\0";
                    mensaje = "\0";
                    validar = 0;
                    
                    header();
                    cuadro(6,20,112,27);
                    gotoxy(8,21);
                    cout<<"Mensaje(s): ";

                    strcpy(nomHeader, nom[id]); 
                    strcpy(apeHeader, ape[id]); 
                    gotoxy(10,9);
                    printf("%c Registro de empleados / Editar / DUI: %d - %s %s",254,dui[id],strtok(nomHeader, " "), strtok(apeHeader, " "));

                    gotoxy(11,12);
                    cout<<"Nuevo nombre: ";
                    strcpy(auxNom, nom[id]);
                    gets(nom[id]);

                    if(validar_cadena(nom[id]) > 0){
                        strcpy(nom[id], auxNom);
                        errores += "\n\t\t";
                        errores += ANSI_COLOR_RED;
                        errores += "- Nuevo nombre incorrecto.";
                        errores += ANSI_COLOR_RESET;
                    }else if((nom[id][0] == '\0') || (nom[id][0] == ' ')){
                        strcpy(nom[id], auxNom);
                        mensaje += "\n\t\t";
                        mensaje += ANSI_COLOR_GREEN;
                        mensaje += "- Nuevo nombre modificado correctamente.";
                        mensaje += ANSI_COLOR_RESET;
                    }

                    gotoxy(11,13);
                    cout<<"Nuevos apellidos: ";
                    strcpy(auxApe, ape[id]);
                    gets(ape[id]);

                    if(validar_cadena(ape[id]) > 0){
                        strcpy(ape[id], auxApe);
                        errores += "\n\t\t";
                        errores += ANSI_COLOR_RED;
                        errores += "- Nuevos apellidos incorrectos.";
                        errores += ANSI_COLOR_RESET;
                    }else if((ape[id][0] == '\0') || (ape[id][0] == ' ')){
                        strcpy(ape[id], auxApe);
                        mensaje += "\n\t\t";
                        mensaje += ANSI_COLOR_GREEN;
                        mensaje += "- Nuevos apellidos modificados correctamente.";
                        mensaje += ANSI_COLOR_RESET;
                    }

                    gotoxy(11,14);
                    cout<<"Nuevo cargo: ";
                    strcpy(auxCargo, cargo[id]);
                    gets(cargo[id]);

                    if(validar_cadena(cargo[id]) > 0){
                        strcpy(cargo[id], auxCargo);
                        errores += "\n\t\t";
                        errores += ANSI_COLOR_RED;
                        errores += "- Nuevo cargo incorrecto.";
                        errores += ANSI_COLOR_RESET;
                    }else if((cargo[id][0] == '\0') || (cargo[id][0] == ' ')){
                        strcpy(cargo[id], auxCargo);
                        mensaje += "\n\t\t";
                        mensaje += ANSI_COLOR_GREEN;
                        mensaje += "- Nuevo cargo modificado correctamente.";
                        mensaje += ANSI_COLOR_RESET;
                    }

                    gotoxy(11,15);
                    cout<<"Nuevo salario: $";
                    auxSueldo = salario[id];
                    gets(SV);

                    salario[id] = strtod(SV, &salarioAux);

                    if((salario[id] == 0) && (SV[0] != '\0')){
                        salario[id] = auxSueldo;
                        errores += "\n\t\t";
                        errores += ANSI_COLOR_RED;
                        errores += "- Cantidad de nuevo salario incorrecta.";
                        errores += ANSI_COLOR_RESET;
                    }else if(salario[id] == 0){
                        salario[id] = auxSueldo;
                        mensaje += "\n\t\t";
                        mensaje += ANSI_COLOR_GREEN;
                        mensaje += "- Nuevo salario modificado correctamente.";
                        mensaje += ANSI_COLOR_RESET;
                    }else if(salario[id] > 0){
                        mensaje += "\n\t\t";
                        mensaje += ANSI_COLOR_GREEN;
                        mensaje += "- Nuevo salario modificado correctamente.";
                        mensaje += ANSI_COLOR_RESET;
                    }
                    

                    if(errores != "\0" && mensaje != "\0"){
                        gotoxy(21,21);
                        cout<<errores<<mensaje;
                    }else if(errores != "\0"){
                        gotoxy(20,21);
                        cout<<errores;
                    }else{
                        gotoxy(20,21);
                        cout<<mensaje;
                        validar = 1;
                    }

                    getch();

                }while(validar != 1);              
            }
        }

    }while(duiEdit != 1);

}

void registroEmpleados_delete(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][25], float salario[row], int& indice){

    int duiDrop, validar, j, opD;
    int auxdui;
    float auxsalario;
    char auxNom[cols];
    char auxApe[cols];
    char auxCargo[cols];
    char nomHeader[cols];
    char apeHeader[cols];
    char DV[8], opDrop[cols];
    char drop[] = {'\0'};
        
    do{
        int y = 13;
        int id = -2;
        
        system("cls");
        headerWithoutsquare();
        if(indice > 8){
            cuadro(4,6,114,20+indice);
        }else{
            cuadro(4,6,114,28);
        }
        gotoxy(10,9);
        printf("%c Registro de empleados / Eliminar",254);

        gotoxy(16,12);
        cout<<"DUI";
        cuadro(8,11,26,13);

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

        if(indice <= 0){
            gotoxy(32,y+2);
            cout<<"No hay empleados registrados, por favor ingrese datos";
            duiDrop = 1;
            getch();
        }else{
            for(int i = 0; i < indice; i++){

                y++;

                gotoxy(13,y);
                cout<<dui[i];

                gotoxy(29,y);
                for(int j = 0; j < strlen(nom[i]); j++){
                    cout<<nom[i][j];
                }

                gotoxy(55,y);
                for(int j = 0; j < strlen(ape[i]); j++){
                    cout<<ape[i][j];
                }

                gotoxy(80,y);
                for(int j = 0; j < strlen(cargo[i]); j++){
                    cout<<cargo[i][j];
                }

                gotoxy(101,y);
                cout<<"$"<<salario[i];
            }

            gotoxy(12,y+3);
            cout<<"Escriba DUI de empleado a eliminar o [1] para cancelar: ";
            gets(DV);

            duiDrop = validar_numero(DV);

            for(int i = 0; i < indice; i++){
                if(duiDrop == dui[i]){
                    id = i;
                }
            }

            if(id == -2){
                if(duiDrop != 1){
                    gotoxy(28,y+5);
                    cout<<ANSI_COLOR_RED<<"Error: No se encontro ningun empleado con ese numero de DUI";
                    cuadro(26,y+4,88,y+6);cout<<ANSI_COLOR_RESET;
                    getch();
                }
            }else{

                do{
                    system("cls");
                    validar = 0;
                    
                    header();

                    strcpy(nomHeader, nom[id]); 
                    strcpy(apeHeader, ape[id]); 
                    gotoxy(10,9);
                    printf("%c Registro de empleados / Eliminar / DUI: %d - %s %s",254,dui[id],strtok(nomHeader, " "), strtok(apeHeader, " "));

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
                    cout<<"DUI: "<<dui[id];
                    gotoxy(30,17);
                    cout<<"Nombre: "<<nom[id];
                    gotoxy(30,18);
                    cout<<"Apellidos: "<<ape[id];
                    gotoxy(30,19);
                    cout<<"Cargo: "<<cargo[id];
                    gotoxy(30,20);
                    cout<<"Salario: $"<<salario[id];
                    gotoxy(43,22);
                    cout<<"[0] Cancelar - [1] Eliminar";
                    gotoxy(23,23);
                    for(int i = 0; i < 71; i++){
                        printf("%c",196);
                    }
                    gotoxy(53,24);
                    cout<<"Digite: ";
                    gets(opDrop);

                    opD = validar_numero(opDrop);

                        if(opD == 1){
                            
                            dui[id] = -1;

                            for(int i = 0; i < indice; i++){
                                for(int j = 0; j < indice - 1; j++){
                                    if(dui[j] == -1){
                                        auxdui = dui[j];
                                        dui[j] = dui[j + 1];
                                        dui[j + 1] = auxdui;

                                        strcpy(auxNom, nom[j]);
                                        strcpy(nom[j], nom[j+1]);
                                        strcpy(nom[j+1], auxNom);

                                        strcpy(auxApe, ape[j]);
                                        strcpy(ape[j], ape[j+1]);
                                        strcpy(ape[j+1], auxApe);

                                        strcpy(auxCargo, cargo[j]);
                                        strcpy(cargo[j], cargo[j+1]);
                                        strcpy(cargo[j+1], auxCargo);

                                        auxsalario = salario[j];
                                        salario[j] = salario[j + 1];
                                        salario[j+ 1] = auxsalario;
                                    }
                                }
                            }

                            gotoxy(48,26);
                            validar = 1;
                            indice--;

                            system("cls");
                            header();
                            gotoxy(10,9);
                            printf("%c Registro de empleados / Eliminar",254);
                            cuadro(18,11,99,25);
                            gotoxy(43,12);
                            cout<<"E l i m i n a r  E m p l e a d o";
                            gotoxy(23,13);
                            for(int i = 0; i < 71; i++){
                                printf("%c",196);
                            }
                            gotoxy(50,18);
                            cout<<ANSI_COLOR_GREEN<<"Registro eliminado";
                            cuadro(44,17,74,19);
                            cout<<ANSI_COLOR_RESET;
                            getch();

                        }else{
                            validar = 1;
                        }

                }while(validar != 1);              
            }
        }

    }while(duiDrop != 1);
}

//alinear objetos
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
// Hasta aqui llega el modulo de Adonay @xdesprox