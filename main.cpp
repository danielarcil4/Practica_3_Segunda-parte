#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

void escribir();

bool lectura(string);

int main()
{
    string contrasena;
    bool verificado;
    //Menú principal del programa
    cout << "Bienvenido al banco electronica: " << endl;
    int Ingreso = 0;
    cout<<"Ingrese como administrador o usuario con el numero que el pertenece: "<<endl;
    cout<<"(1)  Administrador"<<endl;
    cout<<"(2)  Usuario"<<endl;
    cout<<"(3)  Salir "<<endl;
    cout<<"<Numero><Enter>"<<endl;
    cin>>Ingreso;
    //Ingreso según el rol.

    switch (Ingreso)
    {
        //Encriptación y verificación de contraseña.
        case 1:
        //escribir();
        cout<<"Escriba la contrasenia"<<endl;
        //cout<<"Salir"<<endl;
        cin>>contrasena;
        verificado = lectura(contrasena);
        if (verificado==true){
            int a;
            cout<<"Bienvenido administrador"<<endl;
            cout<<"Seleccione el numero de la opcion que desea: "<<endl;
            cout<<"(1) Regitrar un usuario"<<endl;
            cout<<"(2) Salir"<<endl;
            cin>>a;
            if (a==1){
                escribir();
                cout<<"Se ha guardado con exito el usuario"<<endl;
                break;
            }
            else break;

        }
        //archivo = escribir();
        //archivo = cambiar(archivo);
        break;

        case 2:
            cout<<"";
        break;

        case 3:
        cout<<"Se ha salido exitosamente"<<endl;
        break;

        default:
        cout<<"La opcion ingresada no es valida"<<endl;
    }



    return 0;
}


void escribir(){
    //Variables del usuario.
    string cedula,clave,saldo;
    //abrir archivo en escritura y lectura.
    ofstream Usuario;
    Usuario.open("../Practica_3_parte2/Archivos/Usuarios.txt");

    if (!Usuario.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    cin.ignore();
    bool i=true;

    while(i==true){
    cout<<"Ingrese la cedula del usuario(la cedula debe de contener 8 digitos): "<<endl;
    cout<<"<cedula><Enter>"<<endl;
    getline(cin,cedula);
    //verificacion de numero de digitos corectos en la cedula.
    if (cedula.length()==8){
        //Encriptacion de la cedula
        string bin="",binario="";
        int entero = atoi(cedula.c_str());
        while(entero>0){
            bin += entero%2+'0';
            entero /= 2;
        }
        binario=bin;
        int a = bin.length();
        entero= a;
        for(int i=0; i<entero;i++){
            binario[i] = bin[--a];
            }
        Usuario <<binario;
        i=false;
        }
    else{
        cout<<"Verifique el numero ingresado,recuerde que TIENE que ser un numero de 8 digitos"<<endl;
        }
    }
    i=true;
    while(i==true){
        cout<<"Ingrese la clave del usuario(la clave debe de contener 4 digitos): "<<endl;
        getline(cin,clave);
        //verificacion de numero de digitos correctos en la clave.
        if(clave.length()==4){
            //Encriptacion de la clave
            string bin="",binario="";
            int entero = atoi(clave.c_str());
            while(entero>0){
                bin += entero%2+'0';
                entero /= 2;
            }
            binario=bin;
            int a = bin.length();
            entero=a;
            for(int i=0; i<entero;i++){
                binario[i] = bin[--a];
                }
            Usuario <<","<<binario;
            i=false;
        }
        else{
            cout<<"Verifique el numero ingresado,recuerde que TIENE que ser un numero de 4 digitos"<<endl;
        }
    }
    cout<<"Ingrese la saldo del usuario(el saldo debe de contener minimo 2 digitos): "<<endl;
    getline(cin,saldo);
    //Encriptacion de el saldo
    string bin="",binario="";
    int entero = atoi(saldo.c_str());
    while(entero>0){
        bin += entero%2+'0';
        entero /= 2;
    }
    int a = bin.length();
    entero=a;
    if(a%2!=0){
        bin+="0";
        a+=1;
        }
    binario=bin;
    for(int i=0; i<entero;i++){
        binario[i] = bin[--a];
        }

    Usuario <<","<<binario<<" ";

    Usuario.close();


}

bool lectura(string contrasena1){
    //variables.
    string contrasena;
    //Abre archivo en modo lectura.
    ifstream administrador;

    administrador.open("../Practica_3_parte2/Archivos/Contrasenia.txt");

    if (!administrador.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    getline(administrador,contrasena);

    int a = contrasena.length();
    string code1="0000",code,codee = "";
    //desencripta la contraseña
    for(int h=0;h<a;++h){
        for(int i = 0; i<3 ;i++){
            if (i==0)code1[3] = contrasena[h];
            code1[i] = contrasena[h+1];
            ++h;
            }
        code+=code1;
        int suma=0,I=0;
        //vuelve el codigo binario en caracteres.
        if(code.length()%8==0){
            for(int i=code.length()-1;i>=0;i--){
                int digito = code[i]-'0';
                suma+=digito*pow(2,I++);
            }
        codee += suma;
        }
    }
    //verificacion de la contraseña
    if(contrasena1==codee)return true;
    else return false;
    administrador.close();


}

//100110100010010100000100,10011010010,100111000100000
//100110100010010100000100,10011010010,0100111000100000


