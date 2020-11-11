//Repositorio
//https://github.com/zelaya201/Sistema-de-Planilla

#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <iomanip>
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
void registroEmpleados(int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_registrar(int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_edit(int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroEmpleados_delete(int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int &);//dui, nombre, apellidos, cargo, salario, indice
void registroDescuentos(int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int);
int buscarEmpleados(char[50], int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int, char[25], char[25], int&, int&);
bool verificarEmpleado(char [50], char [row][cols], int);
void mostrarEmpleados(char [50], char [row][cols], int [row], char [row][cols], char [row][cols], char [row][cols], float [row], int, int [], int&, int&);

int main(){

    int op;

/*    int dui[row] = {'\0'};
    int indice = 0;
    char nom[row][cols] = {'\0'}, ape[row][cols] = {'\0'}, cargo[row][cols] = {'\0'};
    float salario[row]; */

    /* PARA PROBAR Y EVITARSE ESTAR REGISTRANDO DATOS XD */

    int dui[row] = {12345678,87654321,17283782,10293827,29382019,20391827,99281762,28379120};
    int indice = 8;
    char nom[row][cols] = {
        {"Josue Adonay"},
        {"Walter Alejandro"},
        {"Julio Antonio"},
        {"Keneth Valerio"},
        {"Mario Ernesto"},
        {"Shelsy Yamileth"},
        {"Karla Beatriz"},
        {"Luis Fernando"}
    };
    char ape[row][cols] = {
        {"Aguilar Constanza"},
        {"Morales Constanza"},
        {"Torres Constanza"},
        {"Ramirez Constanza"},
        {"Zelaya Constanza"},
        {"Constanza Abarca"},
        {"Aguilar Constanza"},
        {"Vaquerano Constanza"}
    };

    char cargo[row][cols] = {
        {"Programador"},
        {"DBA"},
        {"Analista"},
        {"Redes"},
        {"Ingeniero"},
        {"Servicio Social"},
        {"Disenador Grafico"},
        {"Periodista"}
    }; 
    
    float salario[row] = {2100,900,1400,1000,1830,800,1200,2001};
    system("title Sistema de Planillas");

    do{
   
        op = menu();

        switch(op){
            case 1: system("cls");registroEmpleados(dui, nom, ape, cargo, salario, indice);break;
            case 2: system("cls");cout<<"Modulo en proceso";break;
            case 3: system("cls");cout<<"Modulo en proceso";break;
            case 4: system("cls");cout<<"Modulo en proceso";break;
            case 5: system("cls");registroDescuentos(dui, nom, ape, cargo, salario, indice);break;
            case 6: gotoxy(42,22);cout<<ANSI_COLOR_YELLOWLIGTH<<"Mensaje: Hasta luego, vuelva pronto";cuadro(40,21,78,23);cout<<ANSI_COLOR_RESET;Sleep(3000);break;
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: Modulo incorrecto";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;getch();//Mensaje modulo no encontrado
        }


    }while(op != 6);

    return 0;
}

int menu(){

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
}

void registroEmpleados(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int& indice){

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
            default: gotoxy(48,22);cout<<ANSI_COLOR_RED<<"Error: opcion incorrecta";cuadro(45,21,75,23);cout<<ANSI_COLOR_RESET;;getch();//Mensaje modulo no encontrado
        }

    }while(op != 4);

}

void registroEmpleados_registrar(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int& indice){

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

void registroEmpleados_edit(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int& indice){

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

void registroEmpleados_delete(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int& indice){

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

void registroDescuentos(int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int indice) {
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
        printf("%c Registro de Empleados / Editar / Buscar",254);
        gotoxy(31,14);
        cout<<"Sugerencias: DUI, nombre, apellido o cargo del empleado";
        cuadro(26,11,90,13);
        gotoxy(28,12);
        cout<<"Buscar: ";
        gets(recep);
        recep[0] = toupper(recep[0]);
        DS = validar_numero(recep);
        seleccion = buscarEmpleados(recep, dui, nom, ape, cargo, salario, indice, str1, str2, p, y);
        
        if (p == 2) {
            do {
                idMes = -2;
                system("cls");
                diasD = 0;
                y = 13;
                errores = "\0";
                mensaje = ANSI_COLOR_GREEN;
                mensaje += "Descuentos realizados correctamente.";
                mensaje += ANSI_COLOR_RESET;
                validar = 0;
                headerWithoutsquare();
                cuadro(4,6,114,31);
                cuadro(6,24,112,30);
                gotoxy(8,25);
                cout<<"Mensaje(s): ";
                gotoxy(8,29);
                cout<<"Nota:"<<ANSI_COLOR_YELLOWLIGTH<<" Presiona [Enter] consecutivos si no desea realizar cambios."<<ANSI_COLOR_RESET;
                gotoxy(10,9);
                printf("%c Registro de descuentos",254);
                
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
                cout<<dui[seleccion];

                gotoxy(28,y+2);
                cout<<nom[seleccion];

                gotoxy(28,y+3);
                cout<<ape[seleccion];

                gotoxy(28,y+4);
                cout<<cargo[seleccion];

                gotoxy(28,y+5);
                cout<<"$"<<salario[seleccion];

                salarioDia = salario[seleccion]/22;
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
                }else if((validar_cadena(mesSelec) == '\0') || (validar_cadena(mesSelec) == ' ')){
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
                    descuentoRealizado = salarioDia * diasD;
                    gotoxy(13,20);
                    cout<<fixed<<setprecision(2)<<ANSI_COLOR_GREEN<<"Descuento realizado: $"<<(float)descuentoRealizado<<ANSI_COLOR_RESET;         
                    gotoxy(20,25);
                    cout<<mensaje;
                    validar = 1;
                }else{
                    mensaje = ANSI_COLOR_YELLOWLIGTH;
                    mensaje += "No se realiz\xA2 ning\xA3n descuento.";
                    mensaje += ANSI_COLOR_RESET;
                    gotoxy(20,25);
                    cout<<mensaje;
                    validar = 1;
                }
                getch();
            }while (validar != 1);
        }
    }while (DS != 1);
}

int buscarEmpleados(char recep[50], int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int indice, char str1[25], char str2[25], int& p, int& y) {
    int seleccion, value;
    int auxSeleccion = '\0';
    int Dui;
    bool existNom, existApe, existCargo;
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
                existNom = verificarEmpleado(recep, nom, indice);
                existApe = verificarEmpleado(recep, ape, indice);
                existCargo = verificarEmpleado(recep, cargo, indice);

                if (!existNom && !existApe && !existCargo) {
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
                        
                        if (verificarEmpleado(recep, nom, indice)) {
                            mostrarEmpleados(recep, nom, dui, nom, ape, cargo, salario, indice, pointer, y, c);
                        }

                        if (verificarEmpleado(recep, ape, indice)) {
                            mostrarEmpleados(recep, ape, dui, nom, ape, cargo, salario, indice, pointer, y, c);
                        }

                        if (verificarEmpleado(recep, cargo, indice)) {
                            mostrarEmpleados(recep, cargo, dui, nom, ape, cargo, salario, indice, pointer, y, c);
                        }

                        headerWithoutsquare();
                        if(c > 7){
                            cuadro(4,6,114,20+c);
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
                                gotoxy(31,y+5);
                                cout<<ANSI_COLOR_RED<<"Error: Dato invalido";
                                cuadro(28,y+4,90,y+6);cout<<ANSI_COLOR_RESET;
                                getch();
                            } 
                        }
                    }while(auxSeleccion != seleccion);
                }
            }
        }
    }else{
        for (int i = 0; i < indice; i++) {
            if (Dui == dui[i]) {
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

bool verificarEmpleado(char recep[50], char empleado[row][cols], int indice) {
    bool exist = false;
    char aux[50];

    for (int i = 0; i < indice; i++) {
        strcpy(aux, empleado[i]);
        char *token = strtok(aux, " ");
        if(token != NULL){
            while(token != NULL){
                if (strcmp(recep, token) == 0) {
                    exist = true;
                }
                token = strtok(NULL, " "); 
            }
        }
    }

    return exist;
}

void mostrarEmpleados(char recep[50], char empleado[row][cols], int dui[row], char nom[row][cols], char ape[row][cols], char cargo[row][cols], float salario[row], int indice, int pointer[], int& y, int& x) {
    int a, c;
    char aux[50];

    a = 0;
    c = 0;
    y = 13;
    for (int i = 0; i < indice; i++) {
        strcpy(aux, empleado[i]);
        char *token = strtok(aux, " ");
        if(token != NULL){
            while(token != NULL){
                if (strcmp(recep, token) == 0) {
                    y++;

                    gotoxy(11,y);
                    pointer[c] = a+c;
                    c++;
                    cout<<(i+1)-(a--);
                    
                    gotoxy(16,y);
                    cout<<dui[i];

                    gotoxy(33,y);
                    cout<<nom[i];

                    gotoxy(58,y);
                    cout<<ape[i];

                    gotoxy(80,y);
                    cout<<cargo[i];
                
                    gotoxy(101,y);
                    cout<<"$"<<salario[i];
                }
                token = strtok(NULL, " ");
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