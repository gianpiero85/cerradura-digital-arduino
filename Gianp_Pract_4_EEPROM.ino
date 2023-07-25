#include <Wire.h>
#include <LiquidCrystal_I2C.h>// LIBRERIA
#include <EEPROM.h>
#include <Key.h>
#include <Keypad.h>
//#include <LiquidCrystal.h>
//Progama para LCD de dos fila y 16 columnas
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LiquidCrytal lcd( RS, E, D4, D5, D6, D7) Pines a utilizar en Arduino
                                     // RS = pin 4 de la LCD y E = pin 6 de la LCD.
                                     // El pin 5 = W'/R  va a tierra, ya que solo vamos 
                                     // a escribir en la LCD. 
LiquidCrystal_I2C lcd(0x27,16,2);// la dirección 0x3f es para la LCD REAL, las direcciones
                                // 0x27 o 0x20 es para el Proteus                                    

const byte filas =4;  //numero de filas del teclado
const byte columnas =4; // numero de columnas del teclado
char digitos [filas][columnas]={   // El mapa del teclado que es una matriz.
  
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'},
    
};

byte row [filas] = {A0,A1,A2,A3}; //Pines donde estan conectadas las filas. 
                                //La variable "row" es un Array o Arreglo.
byte column [columnas] = {12,11,10,9}; //Pines donde estan conectadas las columnas.
                                    //La variable "column" es un Array o Arreglo.

Keypad Tecla = Keypad(makeKeymap(digitos),row,column,filas,columnas); // Objeto para usar el teclado

char a,dato[5], claveUsuario[5] = "7733", numero,dato1,dato3;//
char claveActualUsuario[5], claveActualUsuario1[5]="0000";
char guardar[5],guardar1[5]="0000";   
char claveSupervisor[5],claveSupervisor1[5]="1234";//por defecto clave Usuario = "1234"
char claveBorrar[5],claveBorrarFija[5]="1111";
  // La variable "claveSupervisor1" siempre será la clave actual guardada
                                 
byte indice = 0, inc = 0, inc1 = 0, inc2=0,inc3 = 0,inc4 = 0,inc5=0,inc6=0;
byte inc7=0, inc8=0,inc9=0, inc10=0,inc11=0, inc12=0,inc13=0, inc14=0;
byte inc15=0, inc16=0,inc17=0, inc18=0,inc19=0, inc20=0,inc21=0, inc22=0;
byte max=0,max1=0,ee=0, veces=0,veces2=0;
void setup() {
  Serial.begin(9600);
  Wire.begin();  
  pinMode(5,OUTPUT);pinMode(6,OUTPUT);
  lcd.begin(16,2); // Indica que es una LCD de 16x2
  lcd.backlight();
  digitalWrite(6,LOW); //El buzzer arranque apagado 
  digitalWrite(5,LOW);  //La cerradura arranque cerrada
  saludo(); // Función saludo

}

void loop() {
  menu();
}

void saludo(){
  lcd.begin(16,2); // Indica que es una LCD de 16x2
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4,0); // (columnas,filas)
  lcd.print("Se ira al");
  lcd.setCursor(2,1); // (columnas,filas)
  lcd.print("Menu Principal");  
  Serial.println("Menu Principal");  
  delay (1500);

}
void menu(){
    lcd.clear();
    lcd.setCursor(3,0); // (columnas,filas) 
    lcd.print("Se tiene el");
    lcd.setCursor(2,1); // (columnas,filas)
    lcd.print("Siguiente Menu"); 
    delay (1000);
    lcd.clear();
    lcd.setCursor(0,0); // (columnas,filas) 
    lcd.print("1->SuperVisor");
    lcd.setCursor(0,1); // (columnas,filas)
    lcd.print("2->Usuario"); 
      
   do{ a= Tecla.getKey();    
     }while(a==0);
     
     Serial.println(a);
     delay(500);
     
    if(a == '1')
      {  
       supervisor();   
      }else if(a == '2')
        {
         usuario(); 
        }else
          {
            lcd.clear();
            lcd.setCursor(0,0); // (columnas,filas) 
            lcd.print("Error en el");
            lcd.setCursor(0,1); //(columnas,filas)
            lcd.print("Dato Colocado"); 
            delay (2000);
            menu();            
          }        
}

void supervisor(){
    lcd.clear();     
    lcd.setCursor(3,0); // (columnas,filas) 
    lcd.print("Estamos con");
    lcd.setCursor(0,1); // (columnas,filas)
    lcd.print("el SuperUsuario"); 
    delay (1500);
    lcd.clear();     
    lcd.setCursor(2,0); // (columnas,filas) 
    lcd.print("Se tiene el");
    lcd.setCursor(1,1); // (columnas,filas)
    lcd.print("Siguiente Menu"); 
    delay (1500);
    lcd.clear();
    lcd.setCursor(0,0); // (columnas,filas) 
    lcd.print("1=Entra Sistema");
    lcd.setCursor(0,1); // (columnas,filas)
    lcd.print("2=Cambiar Clave"); 
    //delay (500);
  
   do{ a= Tecla.getKey();    
     }while(a==0);

    if(a == '1')
      {  
       EntrarSistemaSuper();   // aqui puede ver las claves 
      }else if(a == '2')
        {
         CambiarClaveSuper(); // aqui cambia su propia clave
        } else
            {
            lcd.clear();
            lcd.setCursor(0,0); // (columnas,filas) 
            lcd.print("Error en el");
            lcd.setCursor(0,1); //(columnas,filas)
            lcd.print("dato colocado"); 
            delay (1000);
            supervisor();
            }
}

void usuario(){
    a='0';
    lcd.clear();     
    lcd.setCursor(1,0); // (columnas,filas) 
    lcd.print("Estamos con");
    lcd.setCursor(1,1); // (columnas,filas)
    lcd.print("el USUARIO"); 
    delay (1500);
    lcd.clear();     
    lcd.setCursor(3,0); // (columnas,filas) 
    lcd.print("Se tiene el");
    lcd.setCursor(1,1); // (columnas,filas)
    lcd.print("Siguiente Menu"); 
    delay (1500);
    lcd.clear();
    lcd.setCursor(0,0); // (columnas,filas) 
    lcd.print("1=Cambiar_Clave");
    lcd.setCursor(0,1); // (columnas,filas) 
    lcd.print("2=Activa_Cerrad");
    //delay (1000);
  
   do{ a= Tecla.getKey();    
     }while(a==0);

    if(a == '1')
      { 
       lcd.clear(); lcd.setCursor(0,0); // (columnas,filas) 
       lcd.print("Cambiar CLAVE");
       delay(2000); 
       CambiarClaveUsuario(); // aqui puede cambiar su clave Usuario
      }else if(a == '2')
        {
        lcd.clear(); lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("Activar_Cerradura");
        delay(2000); 
        ActivarCerradura(); // Aqui puede activar la CERRADURA
 
        }else
            {
            lcd.clear();
            lcd.setCursor(0,0); // (columnas,filas) 
            lcd.print("Error en el");
            lcd.setCursor(0,1); //(columnas,filas)
            lcd.print("dato colocado"); 
            delay (1000);
            menu();
            }
}

//*********** Funciones del SuperUsuario************
void CambiarClaveSuper(){ //Cambiar clave del super Usuario
 if(veces>0){
   for(byte w=0;w<=3;w++)
         {
          claveSupervisor1[w]=EEPROM[w];// se actualiza la clave nueva
          //en la variable "claveSupervisor1[]"" y queda guardada en la EEPROM.      
         }                  
 }
  veces++;//variable para que cuando entre la 1era vez no entre al if(veces>0)   
          // y entonces claveSupervisor1[] arraque con su clave por defecto
          // que es "1234", despues de la segunda vuelta ya la claveSupervisor1[]
          // se quedará con la que se cambie en esta parte.                      
    lcd.clear();
    lcd.setCursor(0,0); // (columnas,filas) 
    lcd.print("Introduzca su");
    lcd.setCursor(0,1); // (columnas,filas)
    lcd.print("Clave actual"); 
    delay (1500);
   
    while(!(inc==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);
         claveSupervisor[inc]=a;// se guardando la clave introducida
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc++;     
      }
      inc = 0;//
      
  if (!strcmp(claveSupervisor,claveSupervisor1))
    {                                           //se compara la clave
        lcd.clear();                            //intruducida con la actual
        lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
        lcd.print("Puede cambiar");             // si son iguales se cambia
        lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
        lcd.print("la Clave Actual"); 
        delay (800);       
       while(!(inc1==4))
       
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);
         EEPROM[inc1]=a;// se coloca la clave nueva en la EEPROM y la guarda
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc1++;     
      }
      inc1=0;//
         for(byte z=0;z<=3;z++)
         {
            claveSupervisor1[z]=EEPROM[z];// se actualiza la clave nueva
                   //en la variable claveSupervisor1[] y queda guardada en la      
         }         // EEPROM.                      
       lcd.clear();                                  
       for(byte y=0;y<=3;y++)
         {
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(y+6,1);
            lcd.print(claveSupervisor1[y]);// para verificar la clave
            delay(500);                     // nueva
         } 
      supervisor();
          
    }else{
         max1++;
         lcd.clear();
         lcd.setCursor(1,0); // (columnas,filas) 
         lcd.print("Introdujo una");
         lcd.setCursor(1,1); // (columnas,filas)
         lcd.print("Clave ERRADA."); 
         delay (1000);
         }
     if (max1==3)
           {
           max1=0;
           lcd.clear();
           lcd.setCursor(0,0); // (columnas,filas) 
           lcd.print("Ha colocado 3");
           lcd.setCursor(0,1); //(columnas,filas)
           lcd.print("Claves erradas"); 
           delay (2000);
           menu();           
           }
  CambiarClaveSuper(); 
         
}

void EntrarSistemaSuper(){ //El super Usuario puede ver las claves o Borrarlas
    
    lcd.clear();
    lcd.setCursor(0,0); // (columnas,filas) 
    lcd.print("Introduzca su");
    lcd.setCursor(0,1); // (columnas,filas)
    lcd.print("Clave Actual"); 
    delay (1500);
   
    while(!(inc3==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);
         claveSupervisor[inc3]=a;// se guardando la clave introducida
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc3++;     
      }
      inc3=0;
     if (!strcmp(claveSupervisor,claveSupervisor1))
      { //se compara la clave intruducida con la actual
        //que esta en claveSupervisor1 si son iguales se manda a
        //un menu para que elija si quiere ver o borrar todas las claves
     
        lcd.clear();     
        lcd.setCursor(2,0); // (columnas,filas) 
        lcd.print("Se tiene el");
        lcd.setCursor(1,1); // (columnas,filas)
        lcd.print("Siguiente Menu"); 
        delay (1500);
        lcd.clear();
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("1=Ver_Claves");
        lcd.setCursor(0,1); // (columnas,filas)
        lcd.print("2=Borrar_Claves"); 
        //delay (500);
      
      do{ a= Tecla.getKey();    
        }while(a==0);

        if(a == '1')
          {  
          VerClaves();   // aqui puede ver las claves 
          }else if(a == '2')
            {
            BorrarClaveSuper(); // aqui cambia su propia clave
            } else 
               {
                lcd.clear();
                lcd.setCursor(0,0); // (columnas,filas) 
                lcd.print("Error en el");
                lcd.setCursor(0,1); //(columnas,filas)
                lcd.print("dato colocado"); 
                delay (1000);
                EntrarSistemaSuper();                
                }
                

     } else
           {
            lcd.clear();
            lcd.setCursor(4,0); // (columnas,filas) 
            lcd.print("CLAVE");
            lcd.setCursor(4,1); //(columnas,filas)
            lcd.print("ERRADA"); 
            delay (1000);
            max++;
           }
     if (max==3)
           {
           max=0;
           lcd.clear();
           lcd.setCursor(0,0); // (columnas,filas) 
           lcd.print("Ha colocado 3");
           lcd.setCursor(0,1); //(columnas,filas)
           lcd.print("Claves erradas"); 
           delay (2000);
           menu();           
           }
  EntrarSistemaSuper(); 
                          
}

void BorrarClaveSuper(){
        lcd.clear();
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("Desea Borrar");
        lcd.setCursor(0,1); //(columnas,filas)
        lcd.print("todas las Claves");
        delay (2000);   
        lcd.clear();
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("1--- Borrar");
        lcd.setCursor(0,1); //(columnas,filas)
        lcd.print("2--- No Borrar");
        delay (10);

        do{ a= Tecla.getKey();    
          }while(a==0);

        if (a=='1'){
           borrar_clave_usuario();
           }else{
             menu();
           }             
}

void VerClaves(){
    lcd.clear();
    byte i;     
     for(i = 50;i<=53;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 1:");
        lcd.setCursor((i-50)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 54;i<=57;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 2:");
        lcd.setCursor((i-54)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 58;i<=61;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 3:");
        lcd.setCursor((i-58)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 62;i<=65;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 4:");
        lcd.setCursor((i-62)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 66;i<=69;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 5:");
        lcd.setCursor((i-66)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 70;i<=73;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 6:");
        lcd.setCursor((i-70)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
        lcd.clear();
     for(i = 74;i<=77;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 7:");
        lcd.setCursor((i-74)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
       for(i = 78;i<=81;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 8:");
        lcd.setCursor((i-78)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
       for(i = 82;i<=85;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 9:");
        lcd.setCursor((i-82)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
       for(i = 86;i<=89;i++){
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("ClaveUsuario 10:");
        lcd.setCursor((i-86)+6,1); //(columnas,filas)
        dato1 = EEPROM[i];
        lcd.print(dato1); 
        delay (800);
     
      }
    
       lcd.clear();
       lcd.setCursor(0,0); // (columnas,filas) 
       lcd.print("Se mostraron");
       lcd.setCursor(0,1); //(columnas,filas)
       lcd.print("Las 10 Claves."); 
       delay (2000);
       lcd.clear();
       menu();       
}
void borrar_clave_usuario(){
        lcd.clear();
        lcd.setCursor(0,0); // (columnas,filas) 
        lcd.print("Para Borrar todo");
        lcd.setCursor(0,1); //(columnas,filas)
        lcd.print("coloque 1111");
        delay (1500);
       
         while(!(inc4==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (10);
          do{ a= Tecla.getKey();    
          }while(a==0);
          claveBorrar[inc4]=a;// se guardando la clave introducida por teclado
          lcd.clear();        // para poder borrar todo que es 1111
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc4++;     
          }
         inc4= 0;//
        
         if (!strcmp(claveBorrar,claveBorrarFija))
          {                                            
                for(byte ii=50;ii<=89;ii++){
                   EEPROM[ii]='0'; 
                   delay (10);
                }
                  lcd.clear();
                  lcd.setCursor(0,0); // (columnas,filas) 
                  lcd.print("Borradas todas");
                  lcd.setCursor(0,1); //(columnas,filas)
                  lcd.print("las claves."); 
                  delay (2000);
                  veces2=0;//Se inicializa veces2 = 0 para que se empiece a
                           //a guardar las claves desde la dirección 50                  
                  menu();  //de la EEPROM
          } else{
                  lcd.clear();
                  lcd.setCursor(2,0); // (columnas,filas) 
                  lcd.print("Coloco mal");
                  lcd.setCursor(2,1); //(columnas,filas)
                  lcd.print("la clave."); 
                  delay (2000);
                  lcd.clear();
                  BorrarClaveSuper();
          }        


}

//*********** funciones del Usuario********
void CambiarClaveUsuario(){
byte c;
    Serial.println(veces2); delay(1000);  
  if(veces2 == 0)
  {
      Serial.println("veces2 = 0"); delay(1000);   
       /* claveActualUsuario1[5]="0000";//clave por defecto
         for(byte hh=0;hh<=3;hh++){
         Serial.print(hh);
         //char datoprueba2=claveActualUsuario1[hh];
         //Serial.println(datoprueba2);
         delay(1000);
         }*/
      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave_porDefecto"); 
      delay (1500);
   
     while(!(inc5==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc5]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario 
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc5++;     
      }
         for(byte h=0;h<=3;h++){
         char datoprueba=claveActualUsuario[h];
         Serial.print(datoprueba);
         delay(1000);
         }
      inc5= 0;//
      
     if (!strcmp(claveActualUsuario1,claveActualUsuario))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la actual
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
          lcd.print("Puede cambiar");             // si son iguales se cambia
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("la Clave Actual"); 
          delay (1000);

        while(!(inc6==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (10);
          do{ a= Tecla.getKey();    
          }while(a==0);
          
          EEPROM[inc6+50]=a;// se coloca la clave nueva 1 en la EEPROM desde 
          lcd.clear();      // la dirección 50 hasta la 53 y se guarda
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc6++;     
         }
        inc6=0;//
      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada"); 
           delay (2000);
           usuario();         
          }
      for(byte yy=0;yy<=3;yy++)
         {               
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(yy+6,1);
            dato3= EEPROM[yy+50];
            lcd.print(dato3);// para verificar la clave
            delay(800);              // nueva 
          }
            lcd.clear();                         
            lcd.setCursor(1,0);
            lcd.print("Se ha cambiado "); 
            lcd.setCursor(3,1);
            lcd.print("La clave ");
            delay(1200);   
      veces2++;
      usuario();
  }
  
  if(veces2 == 1)
  {
      Serial.println("veces2 = 1"); delay(1000); 
       for (c =50;c<=53;c++)
          {
           claveActualUsuario1[c-50]=EEPROM[c];// se actualiza la variable
           delay(10);                       //claveActualUsuario1 con el ultimo 
                                            // valor guardado en el sistema                                 
          }
      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave actual"); 
      delay (1500);
   
     while(!(inc7==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc7]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario 
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc7++;     
      }
      inc7= 0;//
      
     if (!strcmp(claveActualUsuario1,claveActualUsuario))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la actual
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
          lcd.print("Puede cambiar");             // si son iguales se cambia
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("la Clave Actual"); 
          delay (800);

        while(!(inc8==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (100);
          do{ a= Tecla.getKey();    
          }while(a==0);
          
          EEPROM[inc8+54]=a;// se coloca la clave nueva 2 en la EEPROM desde 
          lcd.clear();      // la dirección 54 hasta la 57 y se guarda
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc8++;     
         }
        inc8=0;//
      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada"); 
           delay (800);
           usuario();         
          }
      for(byte yy=0;yy<=3;yy++)
         {               
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(yy+6,1);
            char dato4 = EEPROM[yy+54];
            lcd.print(dato4);// para verificar la clave
            delay(800);              // nueva 
            lcd.clear();                         
            lcd.setCursor(1,0);
            lcd.print("Se ha cambiado "); 
            lcd.setCursor(3,1);
            lcd.print("La clave ");                     
         } 
      veces2++;// aqui la variable veces2 pasa a valer 2.
      usuario();
  }
  if(veces2 == 2)
  {
       Serial.println("veces2 = 2"); delay(1000); 
       for (c =54;c<=57;c++ )
          {
           claveActualUsuario1[c-54]=EEPROM[c];// se actualiza la variable
           delay(10);                       //claveActualUsuario1 con el ultimo 
                                            // valor guardado en el sistema                                 
          }
      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave actual"); 
      delay (1500);
   
     while(!(inc9==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc9]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario 
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc9++;     
      }
      inc9= 0;//
      
     if (!strcmp(claveActualUsuario,claveActualUsuario1))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la actual
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
          lcd.print("Puede cambiar");             // si son iguales se cambia
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("la Clave Actual"); 
          delay (800);

        while(!(inc10==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (100);
          do{ a= Tecla.getKey();    
          }while(a==0);
          
          EEPROM[inc10+58]=a;// se coloca la clave nueva 2 en la EEPROM desde 
          lcd.clear();      // la dirección 54 hasta la 57 y se guarda
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc10++;     
         }
        inc10=0;//
      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada"); 
           delay (800);
           usuario();         
          }
      for(byte yy=0;yy<=3;yy++)
         {               
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(yy+6,1);
            char dato5 = EEPROM[yy+58];
            lcd.print(dato5);// para verificar la clave
            delay(800);              // nueva 
            lcd.clear();                         
            lcd.setCursor(1,0);
            lcd.print("Se ha cambiado "); 
            lcd.setCursor(3,1);
            lcd.print("La clave ");                     
         } 
      veces2++;// aqui la variable veces2 pasa a valer 3.
      usuario();
  }
  if(veces2 == 3)
  {
       Serial.println("veces2 = 3"); delay(1000); 
       for (c =58;c<=61;c++ )
          {
           claveActualUsuario1[c-58]=EEPROM[c];// se actualiza la variable
           delay(10);                       //claveActualUsuario1 con el ultimo 
                                            // valor guardado en el sistema                                 
          }
      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave actual"); 
      delay (1500);
   
     while(!(inc11==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc11]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario 
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc11++;     
      }
      inc11= 0;//
      
     if (!strcmp(claveActualUsuario,claveActualUsuario1))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la actual
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
          lcd.print("Puede cambiar");             // si son iguales se cambia
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("la Clave Actual"); 
          delay (800);

        while(!(inc12==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (100);
          do{ a= Tecla.getKey();    
          }while(a==0);
          
          EEPROM[inc12+62]=a;// se coloca la clave nueva 2 en la EEPROM desde 
          lcd.clear();      // la dirección 54 hasta la 57 y se guarda
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc12++;     
         }
        inc12=0;//
      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada"); 
           delay (800);
           usuario();         
          }
      for(byte yy=0;yy<=3;yy++)
         {               
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(yy+6,1);
            char dato6 =EEPROM[yy+62]; 
            lcd.print(dato6);// para verificar la clave
            delay(800);              // nueva 
            lcd.clear();                         
            lcd.setCursor(1,0);
            lcd.print("Se ha cambiado "); 
            lcd.setCursor(3,1);
            lcd.print("La clave ");                     
         } 
      veces2++;// aqui la variable veces2 pasa a valer 3.
      usuario();
  }
  if(veces2 == 4)
  {
    Serial.println("veces2 = 4"); delay(1000); 
    for (c =62;c<=65;c++ )
      {
        claveActualUsuario1[c-62]=EEPROM[c];// se actualiza la variable
        delay(10);                       //claveActualUsuario1 con el ultimo 
                                        // valor guardado en el sistema                                 
      }
      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave actual"); 
      delay (1500);
   
     while(!(inc13==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (100);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc13]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario 
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc13++;     
      }
      inc13= 0;//
      
     if (!strcmp(claveActualUsuario,claveActualUsuario1))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la actual
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveSupervisor1
          lcd.print("Puede cambiar");             // si son iguales se cambia
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("la Clave Actual"); 
          delay (800);

        while(!(inc14==4))
         {
          lcd.clear();
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("Introduzca un");
          lcd.setCursor(6,1); // (columnas,filas)
          lcd.print("digito"); 
          delay (100);
          do{ a= Tecla.getKey();    
          }while(a==0);
          
          EEPROM[inc14+66]=a;// se coloca la clave nueva 3 en la EEPROM desde 
          lcd.clear();      // la dirección 66 hasta la 69 y se guarda
          lcd.setCursor(2,0); // (columnas,filas) 
          lcd.print("El numero es:");
          lcd.setCursor(7,1); // (columnas,filas)
          lcd.print(a); 
          delay (800);         
          inc14++;     
         }
        inc14=0;//
      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada"); 
           delay (800);
           usuario();         
          }
      for(byte yy=0;yy<=3;yy++)
         {               
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave nueva:");
            lcd.setCursor(yy+6,1);
            char dato7 =EEPROM[yy+66]; 
            lcd.print(dato7);// para verificar la clave
            delay(800);              // nueva 
            lcd.clear();                         
            lcd.setCursor(1,0);
            lcd.print("Se ha cambiado "); 
            lcd.setCursor(3,1);
            lcd.print("La clave ");                     
         } 
      veces2++;// aqui la variable veces2 pasa a valer 5.
      usuario();
  }

   if(veces2 == 5)
  {
    Serial.println("veces2 = 5"); delay(1000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Se a excedido");
    lcd.setCursor(0,1);
    lcd.print("El nro de claves");
    delay (1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Seguirá usando");
    lcd.setCursor(0,1);
    lcd.print("Su Clave Actual");// aqui la variable veces2 pasa a valer 5.
    delay (1500);
    veces2 = 5;
    usuario();
  } 
     
}

void ActivarCerradura(){
    Serial.println(veces2); delay(1000);  
if(veces2 == 0)
{
      Serial.println("veces2 = 0"); delay(1000);   

      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave_porDefecto"); 
      delay (1500);
   
     while(!(inc15==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc15]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario por teclado
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc15++;     
      }
         for(byte hh=0;hh<=3;hh++){
         char datoprueba=claveActualUsuario[hh];//se muestra por monitor serial
         Serial.print(datoprueba);              // la clave introducida por el  
         delay(1000);                           // usuario
         }
      inc15= 0;//
  revisar: // etiqueta revisar
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Ahora Coloque");
         lcd.setCursor(2,1); // (columnas,filas)
         lcd.print("el simbolo * "); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);
                 
   if(a =='*')
   {
     
    if (!strcmp("0000",claveActualUsuario)) 
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la clave por defecto
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveUsuario1[]=0000
          lcd.print("Clave Correcta");             // si son iguales se pasa a otro menu
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("Cerradua abierta");
          digitalWrite(5,HIGH);// en el Pin 5 está el RELE que activa la          
          digitalWrite(6,LOW);// en el Pin 6 está el Buzzer                     // cerradura
          delay (1000);
          menu();        

      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada");
           digitalWrite(5,LOW);// en el Pin 5 está el RELE
           digitalWrite(6,HIGH);// en el Pin 6 está el Buzzer     
           delay (5000);
           digitalWrite(6,LOW);// en el Pin 6 está el Buzzer            
           usuario();         
          }
   } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("NO COLOCO");
           lcd.setCursor(1,1); // (columnas,filas)
           lcd.print("el Simbolo * ");
           delay (2000);            
           goto revisar; // para que vuelva a colocar * y compare las claves        
          }              // del usuario actual y la colocada por teclado
} 

if(veces2 == 1)
{
      Serial.println("veces2 = 1"); delay(1000);   

      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave Actual"); 
      delay (1500);
   
     while(!(inc17==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc17]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario por teclado
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc17++;     
      }
         for(byte aa=0;aa<=3;aa++){
         char datoprueba1=claveActualUsuario[aa];//se muestra por monitor serial
         Serial.print(datoprueba1);              // la clave introducida por el  
         delay(1000);                           // usuario
         }
      inc17= 0;//
  revisar1: // etiqueta revisar
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Ahora Coloque");
         lcd.setCursor(1,1); // (columnas,filas)
         lcd.print("el simbolo * "); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);
                 
   if(a =='*')
   {
     for(byte bb=0;bb<=3;bb++)
      {
        claveActualUsuario1[bb]=EEPROM[50+bb];//Se actualiza la variable 
        char clave1=claveActualUsuario1[bb];  //claveActualUsuario1 y se pasa      
        Serial.print(clave1); delay(1000);    //a clave1 y se imprime
      }
     
     if (!strcmp(claveActualUsuario1,claveActualUsuario))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la clave por defecto
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveUsuario1[]=0000
          lcd.print("Clave Correcta");             // si son iguales se pasa a otro menu
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("Cerradua abierta");
          digitalWrite(5,HIGH);// en el Pin 5 está el RELE         
          digitalWrite(6,LOW);// en el Pin 6 está el Buzzer                     
          delay (1000);
          menu();        

      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada");
           digitalWrite(5,LOW);// en el Pin 5 está el RELE
           digitalWrite(6,HIGH);// en el Pin 6 está el Buzzer     
           delay (5000);
           digitalWrite(6,LOW);// en el Pin 6 está el Buzzer            
           usuario();         
          }
   } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("NO COLOCO");
           lcd.setCursor(1,1); // (columnas,filas)
           lcd.print("el Simbolo * ");
    
           delay (2000);            
           goto revisar1; // para que vuelva a colocar * y compare las claves        
          }              // del usuario actual y la colocada por teclado
}

if(veces2 == 2)
{
      Serial.println("veces2 = 2"); delay(1000);   

      lcd.clear();
      lcd.setCursor(0,0); // (columnas,filas) 
      lcd.print("Introduzca su");
      lcd.setCursor(0,1); // (columnas,filas)
      lcd.print("Clave Actual"); 
      delay (1500);
   
     while(!(inc19==4))
      {
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Introduzca un");
         lcd.setCursor(6,1); // (columnas,filas)
         lcd.print("digito"); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);

         claveActualUsuario[inc19]=a;// se guardando la clave introducida
         lcd.clear();               // por el usuario por teclado
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("El numero es:");
         lcd.setCursor(7,1); // (columnas,filas)
         lcd.print(a); 
         delay (800);         
         inc19++;     
      }
         for(byte cc=0;cc<=3;cc++){
         char datoprueba2=claveActualUsuario[cc];//se muestra por monitor serial
         Serial.print(datoprueba2);              // la clave introducida por el  
         delay(1000);                           // usuario
         }
      inc19= 0;//
  revisar2: // etiqueta revisar
         lcd.clear();
         lcd.setCursor(2,0); // (columnas,filas) 
         lcd.print("Ahora Coloque");
         lcd.setCursor(1,1); // (columnas,filas)
         lcd.print("el simbolo * "); 
         delay (5);
         do{ a= Tecla.getKey();    
         }while(a==0);
                 
   if(a =='*')
   {
     for(byte dd=0;dd<=3;dd++)
      {
        claveActualUsuario1[dd]=EEPROM[54+dd];//Se actualiza la variable 
        char clave2=claveActualUsuario1[dd];  //claveActualUsuario1 y se pasa      
        Serial.print(clave2); delay(1000);    //a clave1 y se imprime
      }
     
     if (!strcmp(claveActualUsuario1,claveActualUsuario))
      {                                          //se compara la clave
          lcd.clear();                            //intruducida con la clave por defecto
          lcd.setCursor(0,0); // (columnas,filas) //que esta en claveUsuario1[]=0000
          lcd.print("Clave Correcta");             // si son iguales se pasa a otro menu
          lcd.setCursor(0,1); // (columnas,filas) // sino se pasa al "else"
          lcd.print("Cerradua abierta");
          digitalWrite(5,HIGH);// en el Pin 5 está el RELE (LED) que activa la          
          digitalWrite(6,LOW);// en el Pin 6 está el Buzzer                     // cerradura
          delay (2000);
          menu();        

      } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("Introdujo una");
           lcd.setCursor(2,1); // (columnas,filas)
           lcd.print("Clave Errada");
           digitalWrite(5,LOW);// en el Pin 5 está el RELE
           digitalWrite(6,HIGH);// en el Pin 6 está el Buzzer     
           delay (5000);
           digitalWrite(6,LOW);// en el Pin 6 está el Buzzer            
           usuario();         
          }
   } else
          {
           lcd.clear();
           lcd.setCursor(1,0); // (columnas,filas) 
           lcd.print("NO COLOCO");
           lcd.setCursor(1,1); // (columnas,filas)
           lcd.print("el Simbolo * ");
    
           delay (2000);            
           goto revisar2; // para que vuelva a colocar * y compare las claves        
          }              // del usuario actual y la colocada por teclado
}
 usuario(); 
 
}
 
