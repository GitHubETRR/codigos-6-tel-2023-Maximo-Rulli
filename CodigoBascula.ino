#include "HX711.h"

HX711 bascula;

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); //LiquidCrystal lcd(<pin RS>, <pin enable>, <pin D4>, <pin D5>, <pin D6>, <pin D7>) sin RS

#define BOTON1 2
#define BOTON2 3
#define BOTONR 0
#define BOTONS 1
#define DATA 13
#define CLK 12
#define TIEMPOS 500
#define GRANULARIDAD 1000

float calibracion = 1000;

typedef enum{
  MENU,
  PESO,
  CALIBRAR
} basculaState_t;

basculaState_t state;

void basculaInit();  
void basculaUpdate();

void calibrar();
void peso();
void menu();

void setup() {
  pinMode(BOTON1, INPUT);
  pinMode(BOTON2, INPUT);
  pinMode(BOTONS, INPUT);
  pinMode(BOTONR, INPUT);
  lcd.begin(20, 4);
  lcd.setCursor (0,0);
  //Serial.begin(9600);
  bascula.begin(DATA, CLK); //Inicia el sensor
  bascula.set_scale(calibracion); // Se aplica la calibracion
  bascula.tare(); //Tara, sin aplicar peso
  basculaInit();
}

  
void loop(){
  basculaUpdate();
}


void basculaInit(){
  state = MENU;
}

void basculaUpdate(){
    bool Medboton1 = digitalRead(BOTON1);
    bool Medboton2 = digitalRead(BOTON2);
    switch (state){
      case MENU:
              menu();
              if (Medboton1 && (!Medboton2)) state=PESO;
              if ((!Medboton1) && Medboton2) state=CALIBRAR;
              break;
      case PESO:
              peso();
              if ((!Medboton1) && Medboton2) state=CALIBRAR;
              break;
      case CALIBRAR:
              calibrar();
              if (Medboton1 && (!Medboton2)) state=PESO;
              break;
    }      
}

void menu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Menu:");
  //Serial.print("Menu: \n");
  lcd.setCursor(0,1);
  lcd.print("BP para Pesar");
  //Serial.print("Presione el Boton Peso para medir \n");
  lcd.setCursor(0,2);
  lcd.print("BC para Calibrar");
  //Serial.print("Presione el Boton Calibrar para calibrar \n");
  delay (TIEMPOS);
} 

void calibrar(){
  // Mostrar la información para ajustar el factor de calibración
  //Serial.print("Leyendo: ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("[HX7] Leyendo: ");
  //Serial.print(bascula.get_units(), 1);
  lcd.setCursor(1,1);
  lcd.print(bascula.get_units());
  lcd.print(" Kgs");
  //Serial.print(" Kgs \n");
  lcd.setCursor(0,2);
  lcd.print("Factor  Calibracion: ");
  //Serial.print("Factor  Calibracion: ");
  lcd.setCursor(0,3);
  lcd.print(calibracion);
  //Serial.print(calibracion);
  //Serial.println();
  delay(TIEMPOS);
 
  // Sumar o Restar a la calibracion
  bool MedbotonS = digitalRead(BOTONS);
  bool MedbotonR = digitalRead(BOTONR);
  if (MedbotonS && !MedbotonR) calibracion += GRANULARIDAD;
  else if (!MedbotonS && MedbotonR) calibracion -= GRANULARIDAD;
}

void peso(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("[HX7] Pesando: ");
  //Serial.print("[HX7] Leyendo: ");
  //Serial.print(bascula.get_units(), 4);
  //Serial.print(" Kgs");
  lcd.setCursor(1,1);
  lcd.print(bascula.get_units());
  lcd.print(" Kgs");
  //Serial.println();
  delay(TIEMPOS);
}
