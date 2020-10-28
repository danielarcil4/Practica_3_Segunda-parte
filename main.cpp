#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

void escribir();

bool lectura(int ,int ,int *,int *);

int cambiobinario(string);

void saldonuevo(int,int,int,int);

int main()
{
    //variables
    int contrasena=0,clave=0,saldo=0,linea=0,retiro=0;
    bool verificar;

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
        verificar = lectura(contrasena,clave,NULL,NULL);
        if (verificar==true){
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
            else{
                cout<<"Se ha salido con exitosamente"<<endl;
                break;
            }
        }
        break;
        case 2:

            cout<<"Senior usuario ingrese porfavor su cedula y luego su clave para poder continuar"<<endl;
            cout<<"<cedula(8 digitos)><Enter>"<<endl;
            //contrasena es igual a la cedula aquí
            cin>>contrasena;
            cout<<"<clave(4 digitos)><Enter>"<<endl;
            cin>>clave;
            //Verificacion de identificacion y clave
            verificar=lectura(contrasena,clave,&saldo,&linea);
            if (verificar==true){
                int a;
                cout<<"Bienvenido usuario "<<contrasena<<endl;
                cout<<"Seleccione el numero de la opcion que desea: "<<endl;
                cout<<"(1) consultar saldo"<<endl;
                cout<<"(2) Retirar dinero"<<endl;
                cout<<"(3) Salir"<<endl;
                cin>>a;
                if (a==1){
                    saldonuevo(contrasena,clave,saldo,linea);
                    break;
                }
                else if (a==2){
                    cout<<"Cuanto dinero desea retirar?"<<endl;
                    cin>>retiro;
                    if(saldo-retiro<0){
                        cout<<"No es posible retirar esa cantidad ya que "<<endl;
                        cout<<"su saldo es menor que lo que desea retirar"<<endl;
                        break;
                    }
                    saldo-=retiro;
                    saldonuevo(contrasena,clave,saldo,linea);
                }
                else{
                    cout<<"Se ha salido con exitosamente"<<endl;
                    break;
                    }
            }
            else{
                cout<<"La identificacion o la clave que usted a ingresado son incorrectas"<<endl;
            }

        break;

        /*default:
        cout<<"Se ha salido exitosamente"<<endl;*/
}

    return 0;

}

void escribir(){
    //Variables del usuario.
    string cedula,clave,saldo;
    //abrir archivo en escritura y lectura.
    ofstream Usuario;
    Usuario.open("../Practica_3_parte2/Archivos/Usuarios.txt",ios::app);

    if (!Usuario.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    cin.ignore();
    bool i=true;

    //guardado de la cedula
    while(i==true){
    cout<<"Ingrese la cedula del usuario(la cedula debe de contener 8 digitos): "<<endl;
    cout<<"<cedula><Enter>"<<endl;
    getline(cin,cedula);


    //verificacion de numero de digitos corectos en la cedula.
    //encriptando la informacion
    if (cedula.length()==8){
        //Encriptacion de la cedula
        string bin="",binario="",code,copia="0000";
        int entero = atoi(cedula.c_str());
        while(entero>0){
            bin += entero%2+'0';//70693762
            entero /= 2;        //000100001101101011001110000010
                                //70693762 encriptada
        }                       //0010 1001 0011 1101 1001 0100 0001
        binario=bin;
        int a = bin.length();
        entero= a;
        //Se convierte en numero en par para que sea manejable
        //luego se verifica si es divisor para aplicar mejor la codificacion.
        if(a%4!=0){
            bin+="0";
            a+=1;
            entero+=1;
            if(a%4!=0){
              bin+="0";
              a+=1;
              entero+=1;
              if(a%4!=0){
                bin+="0";
                a+=1;
                entero+=1;
              }
            }
        }

        for(int i=0; i<entero;i++){
            binario[i] = bin[--a];
            }
        for(int h = 0;h<entero;++h){
            for(int i = 0; i<3 ;i++){
                if (binario[h]=='\0')break;
                copia[i+1] = binario[h];
                if (i==2)copia[0] = binario[h+1];
                ++h;
                }
            code+=copia;
        }
        Usuario<<code;
        i=false;
        }
    else{
        cout<<"Verifique el numero ingresado,recuerde que TIENE que ser un numero de 8 digitos"<<endl;
        }
    }

    //guardado de la clave
    i=true;
    while(i==true){
        cout<<"Ingrese la clave del usuario(la clave debe de contener 4 digitos): "<<endl;
        cout<<"<clave><Enter>"<<endl;
        getline(cin,clave);
        //verificacion de numero de digitos correctos en la clave.
        if(clave.length()==4){
            //Encriptacion de la clave
            string bin="",binario="",copia="0000",code;
            int entero = atoi(clave.c_str());
            while(entero>0){
                bin += entero%2+'0';
                entero /= 2;
            }
            binario=bin;
            int a = bin.length();
            entero=a;
            //Se convierte en numero en par para que se manejable
            //luego se verifica si es divisor para aplicar mejor la codificacion.
            if(a%4!=0){
                bin+="0";
                a+=1;
                entero+=1;
                if(a%4!=0){
                  bin+="0";
                  a+=1;
                  entero+=1;
                  if(a%4!=0){
                    bin+="0";
                    a+=1;
                    entero+=1;
                  }
                }
            }

            for(int i=0; i<entero;i++){
                binario[i] = bin[--a];
                }
            for(int h = 0;h<entero;++h){
                for(int i = 0; i<3 ;i++){
                    if (binario[h]=='\0')break;
                    copia[i+1] = binario[h];
                    if (i==2)copia[0] = binario[h+1];
                    ++h;
                    }
                code+=copia;
            }
            Usuario <<","<<code;
            i=false;
        }
        else{
            cout<<"Verifique el numero ingresado,recuerde que TIENE que ser un numero de 4 digitos"<<endl;
        }
    }

    //guardado del saldo
    cout<<"Ingrese el saldo del usuario(el saldo debe de contener minimo 2 digitos): "<<endl;
    cout<<"<saldo><Enter>"<<endl;
    getline(cin,saldo);


    //Encriptacion de el saldo
    string bin="",binario="",code,copia="0000";
    int entero = atoi(saldo.c_str());
    while(entero>0){
        bin += entero%2+'0';
        entero /= 2;
    }
    int a = bin.length();
    entero=a;

    //Se convierte en numero en par para que se manejable
    //luego se verifica si es divisor para aplicar mejor la codificacion.
    if(a%4!=0){
        bin+="0";
        a+=1;
        entero+=1;
        if(a%4!=0){
          bin+="0";
          a+=1;
          entero+=1;
          if(a%4!=0){
            bin+="0";
            a+=1;
            entero+=1;
          }
        }
    }

    binario=bin;
    for(int i=0; i<entero;i++){
        binario[i] = bin[--a];
        }
    for(int h = 0;h<entero;++h){
        for(int i = 0; i<3 ;i++){
            if (binario[h]=='\0')break;
            copia[i+1] = binario[h];
            if (i==2)copia[0] = binario[h+1];
            ++h;
            }
        code+=copia;
    }

    Usuario <<","<<code<<" "<<endl;

    Usuario.close();


}

void saldonuevo(int cedula,int clave,int saldo,int linea){


    cout<<"Su saldo es de: "<<saldo<<endl;
    string bin="",binario="",code,copia="0000",texto,b,c;
    while(cedula>0){
        bin += cedula%2+'0';
        cedula /= 2;
    }
    int a = bin.length();
    cedula=a;

    //Se convierte en numero en par para que se manejable
    //luego se verifica si es divisor para aplicar mejor la codificacion.
    if(a%4!=0){
        bin+="0";
        a+=1;
        cedula+=1;
        if(a%4!=0){
          bin+="0";
          a+=1;
          cedula+=1;
          if(a%4!=0){
            bin+="0";
            a+=1;
            cedula+=1;
          }
        }
    }

    binario=bin;
    for(int i=0; i<cedula;i++){
       binario[i] = bin[--a];
        }
    for(int h = 0;h<cedula;++h){
        for(int i = 0; i<3 ;i++){
            if (binario[h]=='\0')break;
            copia[i+1] = binario[h];
            if (i==2)copia[0] = binario[h+1];
            ++h;
            }
        code+=copia;
    }
    texto+=code;

    bin="",binario="",code="",copia="0000";
    while(clave>0){
        bin += clave%2+'0';
        clave /= 2;
    }
    a = bin.length();
    clave=a;

    //Se convierte en numero en par para que se manejable
    //luego se verifica si es divisor para aplicar mejor la codificacion.
    if(a%4!=0){
        bin+="0";
        a+=1;
        clave+=1;
        if(a%4!=0){
          bin+="0";
          a+=1;
          clave+=1;
          if(a%4!=0){
            bin+="0";
            a+=1;
            clave+=1;
          }
        }
    }

    binario=bin;
    for(int i=0; i<clave;i++){
        binario[i] = bin[--a];
        }
    for(int h = 0;h<clave;++h){
        for(int i = 0; i<3 ;i++){
            if (binario[h]=='\0')break;
            copia[i+1] = binario[h];
            if (i==2)copia[0] = binario[h+1];
            ++h;
            }
        code+=copia;
    }
    texto+=","+code;


    bin="",binario="",code="",copia="0000";
    while(saldo>0){
        bin += saldo%2+'0';//11001011001000
        saldo /= 2;        //1001000101100100
    }
    a = bin.length();
    saldo=a;

    //Se convierte en numero en par para que se manejable
    //luego se verifica si es divisor para aplicar mejor la codificacion.
    if(a%4!=0){
        bin+="0";
        a+=1;
        saldo+=1;
        if(a%4!=0){
          bin+="0";
          a+=1;
          saldo+=1;
          if(a%4!=0){
            bin+="0";
            a+=1;
            saldo+=1;
          }
        }
    }

    binario=bin;
    for(int i=0; i<saldo;i++){
        binario[i] = bin[--a];
        }
    for(int h = 0;h<saldo;++h){
        for(int i = 0; i<3 ;i++){
            if (binario[h]=='\0')break;
            copia[i+1] = binario[h];
            if (i==2)copia[0] = binario[h+1];
            ++h;
            }
        code+=copia;
    }
    texto+=","+code;

    ifstream Usuario;

    Usuario.open("../Practica_3_parte2/Archivos/Usuarios.txt");

    if (!Usuario.is_open())
    {
      cout << "Error abriendo el archivo" << endl;
      exit(1);
    }

    for(int i=1;i<100;i++){
       getline(Usuario,b);
       if(Usuario.eof())break;
       if(linea==i)c+=texto+"\n";
       else c+=b+"\n";
    }


    Usuario.close();

     ofstream usuario;

      usuario.open("../Practica_3_parte2/Archivos/Usuarios.txt");

      if (!usuario.is_open())
      {
        cout << "Error abriendo el archivo" << endl;
        exit(1);
      }

      usuario<<c;

      usuario.close();
}

bool lectura(int contrasena1,int clave,int *ptr1,int *ptr2){
    //variables.
    bool comprobacion1=false;
    string contrasena,clave1,saldo1;
    int a=0,i=0,c=0,suma=0,contador=0;
    //Abre archivo en modo lectura.
    ifstream saldo;

    if(clave!=0){
       saldo.open("../Practica_3_parte2/Archivos/Usuarios.txt");
       if (!saldo.is_open())
       {
         cout << "Error abriendo el archivo" << endl;
         exit(1);
       }

       do{
           string cedula;

           getline(saldo,contrasena);

           contador++;

           if(saldo.eof())break;

           a = contrasena.length();

           for(i=0;i<a;++i){
               if(contrasena[i]==',')break;
               cedula+="0";
           }

           for(i=0;i<a;++i){
             cedula[i]=contrasena[i];
             if(contrasena[i]==',')break;
           }

           //comprobacion cedula
           suma=cambiobinario(cedula);
           if(suma==contrasena1)comprobacion1=true;

       }
       while(comprobacion1!=true);
       if(comprobacion1!=true)return false;

       for(int I=i+1;I<a;++I){
           if(contrasena[I]==',')break;
           clave1+="0";
       }

       for(int I=i+1;I<a;I++,i++){
          if(contrasena[I]==',')break;
          clave1[c++]=contrasena[I];
       }
       //comprobacion clave
       suma=cambiobinario(clave1);
       if(suma!=clave)comprobacion1=false;
       c=0;
       //Averigua el saldo y lo cambia
       for(int I=i+2;I<a;++I){
           if(contrasena[I]==' ')break;
           saldo1+="0";
       }
       for(int I=i+2;I<a;I++){
          if(contrasena[I]==' ')break;
          saldo1[c++]=contrasena[I];
       }
       suma=cambiobinario(saldo1);

       *ptr1 = (suma-1000);
       *ptr2 = contador;
       saldo.close();
    }

    else{
        ifstream administrador;
        administrador.open("../Practica_3_parte2/Archivos/sudo.txt");

        if (!administrador.is_open())
        {
          cout << "Error abriendo el archivo" << endl;
          exit(1);
        }

        getline(administrador,contrasena);
        suma=cambiobinario(contrasena);
        if(contrasena1==suma)comprobacion1=true;

        administrador.close();
        }
    if(comprobacion1!=true)return false;
    else return true;
}

int cambiobinario(string contrasena){
    int a = contrasena.length();
    string code1="0000",code;
    //desencripta la contraseña
    for(int h=0;h<a;++h){
        for(int i = 0; i<3 ;i++){
            if (i==0)code1[3] = contrasena[h];
            code1[i] = contrasena[h+1];
            ++h;
            }
        code+=code1;
        }
        int suma=0;
        //vuelve el codigo binario en un numero entero.

        for(int i=code.length()-1,I=0;i>=0;i--,I++){
            suma+= (code[i]-'0')*pow(2,I);
            }
    return suma;

}

//0001 0000 1101 1010 0110 0111 0000 0100
//70693762
//100001101101011001110000010
//70693762 encriptada
//0010 1001 0011 1101 1001 0100 0001
