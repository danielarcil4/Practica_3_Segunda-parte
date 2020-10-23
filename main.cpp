#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

void escribir();

bool lectura(string);

int main()
{
    string contrasena1;
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
        escribir();
        cout<<"Escriba la contrasenia"<<endl;
        //cout<<"Salir"<<endl;
        cin>>contrasena1;
        verificado = lectura(contrasena1);
        if (verificado==true){
            cout<<"Bienvenido administrador"<<endl;

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
    string contrasena,clave,saldo;
    //abrir archivo en escritura y lectura.
    ofstream Usuario;
    Usuario.open("../Archivos/Contrasenia.txt");

    if (!Usuario.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    cout << "Escribiendo en el archivo" << endl;
    cout << "Ingresa la contrasenia: "<<endl;

    cin.ignore();

    getline(cin,contrasena);

    Usuario <<contrasena;

    /*getline(cin,clave);

    Usuario <<clave;

    getline(cin,saldo);

    Usuario <<saldo;*/

    Usuario.close();


}

bool lectura(string contrasena1){
    //variables.
    string contrasena;
    //Abre archivo en modo lectura.
    ifstream administrador;

    administrador.open("../Archivos/Contrasenia.txt");

    if (!administrador.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    cout << "Leyendo el archivo" << endl;
    getline(administrador,contrasena);

    cout<<contrasena<<endl;

    if(contrasena1==contrasena)return true;
    else return false;
    administrador.close();


}
