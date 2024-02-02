#include <Arduino.h> //Platformio inserted
#include <Wire.h> //Arduino Header File for I/O
#include <LiquidCrystal_I2C.h> //Find in Platformio Libraries gets appended to platformio.ini

//Variables
int sensorIrRed = 3;
int sensorIrYellow = 4;
int yellowButtonPlus = 5;
int yellowButtonMinus = 6;
LiquidCrystal_I2C lcd(0x27,20,4);
int resultRedCurrent = 0;
int resultYellowCurrent = 0;


//Prototipos
void ShowResultOnLCD();
void setupLCD();
void SensorsRead();
void ButtonRead();

//Inicio
void setup(){
  setupLCD();
  pinMode(sensorIrRed, INPUT);
  pinMode(sensorIrYellow, INPUT); 
  pinMode(yellowButtonPlus, INPUT);
  pinMode(yellowButtonMinus, INPUT);
}

void loop(){
  SensorsRead();
  ButtonRead();
}


//Funciones
void setupLCD(){
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("Rojo: ");
  lcd.setCursor(0,1);
  lcd.print("Amarillo: ");
  resultRedCurrent = 0;
  resultYellowCurrent = 0;
  ShowResultOnLCD();
}

void SensorsRead(){
  if (digitalRead(sensorIrRed) == LOW){
    resultRedCurrent++;
    ShowResultOnLCD();
    delay(1000);
  }
  if (digitalRead(sensorIrYellow) == LOW){
    resultYellowCurrent++;
    ShowResultOnLCD();
    delay(1000);
  }
}

void ButtonRead(){
  if (digitalRead(yellowButtonPlus) == HIGH && resultYellowCurrent < 99){
    resultYellowCurrent++;
    ShowResultOnLCD();
    delay(500);
  }
  if (digitalRead(yellowButtonMinus) == HIGH && resultYellowCurrent > 0){
    resultYellowCurrent--;
    ShowResultOnLCD();
    delay(500);
  }
}

void ShowResultOnLCD(){
  lcd.setCursor(6,0);
  lcd.print(resultRedCurrent);
  lcd.setCursor(10,1);
  lcd.print(resultYellowCurrent);
}