int pin_steps1 = 9;       // pin step1 9
int pin_direccion1 = 8;   // pin direccion1 8
int pin_steps2 = 9;       // pin step2 7
int pin_direccion2 = 8;   // pin direccion2 6
int velocidad_1 = 0;
int velocidad_2 = 0;
int x;
void setup() {                
    
  pinMode(pin_steps1, OUTPUT); 
  pinMode(pin_direccion1, OUTPUT); 
  pinMode(pin_steps2, OUTPUT); 
  pinMode(pin_direccion2, OUTPUT);
}
 
void loop() {
   
}

void ANDAR(int velocidad_1, int velocidad_2, int direccion_1, int direccion_2){
    digitalWrite(pin_direccion1, direccion_1);    
    digitalWrite(pin_direccion2, direccion_2);
    digitalWrite(pin_steps1, HIGH);   
    delayMicroseconds(5); 
    digitalWrite(pin_steps1, LOW);    
    delayMicroseconds(velocidad_1); 
    digitalWrite(pin_steps2, HIGH);
    delayMicroseconds(5); 
    digitalWrite(pin_steps2, LOW);
    delayMicroseconds(velocidad_2); 
}
