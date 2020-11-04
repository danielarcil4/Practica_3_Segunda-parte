// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>
#define numUsuarios (int)40

//---------------------------------------------------------
//Instrucciones Importantes:

//La aplicacion usa el "*" como enter
//(uselo cuando termine de escribir los datos que se le piden).

//Es necesario esperar a que aparezca la " -> "
//para poder escribir en el teclado.

//El administrador puede agregar máximo 40 usuarios.

//al crear un usuario es necesario ingresar mínimno 1 numero
//en ID,clave y saldo para que el programa funcione.

//La clave del administrador es 1234.

//El programa solo funciona si se le ingresa numeros
//exceptuando el "*" cuando se necesite.

//---------------------------------------------------------


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {7,6,5,4}; 
byte colPins[cols] = {3,2,1,0};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols);
char contrasenaAdmin[5]={"1234"};
String usuariosBD[numUsuarios];

void mensajeDeIngreso();
int identificarUsuario();
short int validacionClave(const short int ,short int *);
void mostrarSaldoEnPantalla(const short int ,short int indiceSaldo,short int *);
int verificacionAdmin();
void nuevosUsuarios(unsigned short int);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  
  
  usuariosBD[0] = "10102020&1111#10000";
  usuariosBD[1] = "20201010&2222#20000";
  usuariosBD[2] = "10101010&3333#30000";
  usuariosBD[3] = "20202020&4444#40000";
  usuariosBD[4] = "0&0#40000";
}

void loop() {
  mensajeDeIngreso();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Para ingresar ");
  lcd.setCursor(0,1);
  lcd.print(" favor presione: ");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("(1)Administrador");
  lcd.setCursor(0,1);
  lcd.print("(2)Usuario ");
  char a = keypad.waitForKey();
  switch(a){
    //Administrador
    case '1':
    //verificacion clave admin
    	short int b;
    	b = verificacionAdmin();    	
    if (b!=-1){
      
          unsigned short int numeroDeUsuarios=0;
          for(;numeroDeUsuarios<40;numeroDeUsuarios++)
            if(usuariosBD[numeroDeUsuarios]=="\0")
            	break;
        //Creacion de nuevos usuarios    
          nuevosUsuarios(numeroDeUsuarios);  
    	}
    	break;
    //Usuario
    case '2':
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Bienvenido!");
         lcd.setCursor(0,1);
         lcd.print("Ingrese su ID");
    	 delay(4000);
    	 lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("<ID><*>");
         lcd.setCursor(0,1);
         lcd.print("-> ");
    	 //verificación Id
         short int indiceUsuario = identificarUsuario();
    	 short int indiceClave=0;
		 short int *ptr=&indiceClave;
          if(indiceUsuario != -1){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Ingrese su");
            lcd.setCursor(0,1);
            lcd.print("Clave -> ");
            //Verificación clave
            short int indiceSaldo = validacionClave(indiceUsuario,ptr);
            if(indiceUsuario!=-1){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Usuario ");
  			  lcd.print(usuariosBD[indiceUsuario].substring(0,*ptr));
              lcd.setCursor(0,1);
              lcd.print("usted desea: ");
              delay(4000);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("(1)Retirar ");
              lcd.setCursor(0,1);
              lcd.print("(2)Saber saldo");
              char a = keypad.waitForKey();
              String Retirar;
              bool c=true;
              switch(a){
               //Retirar dinero
               case '1':
                //Numero de retiro
                lcd.clear();
              	lcd.setCursor(0,0);
              	lcd.print("Cuanto desea ");
                lcd.setCursor(0,1);
                lcd.print("Retirar?");
                delay(4000);
                lcd.clear();
              	lcd.setCursor(0,0);
              	lcd.print("Cantidad:");
                lcd.setCursor(0,1);
                lcd.print("-> ");
                for(short int i=0;i<8;i++){
                  char a = keypad.waitForKey();
                  if(a=='*')break;
                  Retirar+=a;
                  lcd.print(a);
                  if(i==7){
                    lcd.clear();
              		lcd.setCursor(0,0);
              		lcd.print("Maximo 6 digitos");
                    delay(4000);
                    c=false;
                  }
                }
                //Retirar dinero
                if(c!=false){
                  String saldo = usuariosBD[indiceUsuario].substring(indiceSaldo);
  				  double b = 1000+Retirar.toDouble();
 				  b = (saldo.toDouble())- b;
                  if (b<0){
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("      Saldo     ");
                    lcd.setCursor(0,1);
                    lcd.print("   insuficiente ");
                    delay(4000);
                    c = false;
                  }
                  if(c!=false){
                    String c;
                    c += b;
                    usuariosBD[indiceUsuario].replace(saldo,c);
                    lcd.setCursor(0,0);
                    lcd.print("                ");
                    lcd.setCursor(0,0);
                    lcd.print("Usuario ");
                    lcd.print(usuariosBD[indiceUsuario].substring(0,*ptr));
                    lcd.setCursor(0,1);
                    lcd.print("                ");
                    lcd.setCursor(0,1);
                    lcd.print("Tiene $");
                    saldo = usuariosBD[indiceUsuario].substring(indiceSaldo);
                    lcd.print(saldo);
                    delay(5000);
                  }
                }
                
                break;
               //Consultar saldo
               case '2':
                mostrarSaldoEnPantalla(indiceUsuario,indiceSaldo,ptr);
                break;
                
              }
              
              
            }
            else{
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Clave invalida"); 
                delay(2000);
            }
          }
    	break;        
   /* default:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Error");
          delay(2000);  */
  }
}


void mensajeDeIngreso(){
  unsigned const int cReps = 2;
  unsigned const int cDesplazamiento = 1;
  const unsigned int cTiempo1 = 500;
  char key = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     Ingrese     ");
  lcd.setCursor(0,1);
  lcd.print(" Cualquier tecla ");

  while( key == NO_KEY ){
    key = keypad.getKey();
    delay(10);
  }     
}

int identificarUsuario(){
  char IdIngresado[10];
  for (short unsigned int posicionId = 0;posicionId<10;posicionId++){
      IdIngresado[posicionId]=keypad.waitForKey();
   	  if(IdIngresado[posicionId]=='*')
        break;
      lcd.print(IdIngresado[posicionId]); 
      }
  
  for(short unsigned int i=0;i<40;i++){
    if(usuariosBD[i]=="\0")break;
  	short int indiceSeparador = usuariosBD[i].indexOf('&');
  	String IdRegistrado = usuariosBD[i].substring(0,indiceSeparador);
    bool a;
    for (short unsigned int posicionId = 0;posicionId<indiceSeparador;posicionId++){
      if(IdRegistrado[posicionId]!=IdIngresado[posicionId]){
        a=false;
        break;
      }
      else
        a=true;      
    }
  	if(a==true)
      return i;     
  	}	
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No encontrado");
  delay(4000);
  return -1;
	
}

short int validacionClave(const short int IdUsuario,short int *ptr){
  *ptr = usuariosBD[IdUsuario].indexOf('&');
  const unsigned short int indiceSeparador2 = usuariosBD[IdUsuario].indexOf('#');
  String claveRegistrada = usuariosBD[IdUsuario].substring(*ptr+1,indiceSeparador2);
  short int h=claveRegistrada.length();
  char tecla= '\0';
  //unsigned short int contDigitos = 0;
   
  for (short unsigned int posicionClave = 0;posicionClave<h;posicionClave++){
    tecla=keypad.waitForKey();
    lcd.print( "*" );
    if(claveRegistrada[posicionClave]!=tecla){
      return -1;
    }
  }
  return indiceSeparador2+1;
}

void mostrarSaldoEnPantalla(const short int IdUsuario,short int indiceSaldo,short int *ptr){
  String saldo = usuariosBD[IdUsuario].substring(indiceSaldo);
  bool d=true;
  double b = 1000;
  b = (saldo.toDouble())- b;
  if (b<0){
    lcd.clear();
    lcd.setCursor(0,0);
  	lcd.print("No tiene saldo");
    delay(4000);
    d=false;
  }
  if(d!=false){
    String c;
    c += b;
    usuariosBD[IdUsuario].replace(saldo,c);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Usuario ");
    lcd.print(usuariosBD[IdUsuario].substring(0,*ptr));
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("Tiene $");
    saldo = usuariosBD[IdUsuario].substring(indiceSaldo);
    lcd.print(saldo);
    delay(5000);
  }
}
int verificacionAdmin(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ingrese su clave");
  lcd.setCursor(0,1);
  lcd.print("Administrador");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Clave:  ");
  lcd.setCursor(0,1);
  lcd.print(" -> ");

  for(short int i=0;i<4;i++){
    char a = keypad.waitForKey();
    lcd.print("*");
    if(a!=contrasenaAdmin[i]){
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Clave Incorrecta");
      delay(2000);
      return -1;
    } 
  }
  return 1;
}
 
void nuevosUsuarios(unsigned short int numeroDeUsuarios){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("(1)Nuevo Usuario");
  lcd.setCursor(0,1);
  lcd.print("(2)Salir");
  char a = keypad.waitForKey();
  if(a=='1'){
    char a[22];
    short int i=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ingrese el Id");
    lcd.setCursor(0,1);
    lcd.print("(10 digitos max)");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<Identificacion><*>");
    lcd.setCursor(0,1);
    lcd.print("-> ");
    for(;i<11;i++){
      a[i] = keypad.waitForKey();
      if (a[i]=='*'){
        a[i] = '&';
        break;
      }
      else if(i==11){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Error:Id maximo");
        lcd.setCursor(0,1);
        lcd.print("10 digitos");
        delay(3000);
      }
      lcd.print(a[i]);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ingrese la clave");
    lcd.setCursor(0,1);
    lcd.print("(4 digitos max)");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<Clave><*>");
    lcd.setCursor(0,1);
    lcd.print("-> "); 
    for(short int I=0;I<5;I++,i++){
      a[i+1] = keypad.waitForKey();
      if (a[i+1]=='*'){
        a[i+1] = '#';
        break;
      }
      else if(I==5){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Error:Clave maxima");
        lcd.setCursor(0,1);
        lcd.print("4 digitos");
        delay(3000);
      }
      lcd.print(a[i+1]);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ingrese el saldo");
    lcd.setCursor(0,1);
    lcd.print("(6 digitos max)");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<Saldo><*>");
    lcd.setCursor(0,1);
    lcd.print("-> "); 
    for(short int I=0;I<7;I++,i++){
      a[i+2] = keypad.waitForKey();
      if (a[i+2]=='*')break;              
      else if(I==7){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Error:Saldo maximo");
        lcd.setCursor(0,1);
        lcd.print("6 digitos");
        delay(3000);
      }
      lcd.print(a[i+2]);
    }
    String A=a;
    A=A.substring(0,i+2);
    usuariosBD[numeroDeUsuarios]=A;
  }  
}

