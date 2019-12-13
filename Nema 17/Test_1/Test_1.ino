int steps = 9;       // pin step 9
int direccion = 8;   // pin direccion 3
int x;
void setup() {                
  
  // inicializamos pin como salidas.
  
  pinMode(steps, OUTPUT); 
  pinMode(direccion, OUTPUT); 
}
 
void loop() {

 for(x = 0; x < 800; x++){
    digitalWrite(direccion, 1);    
    digitalWrite(steps, HIGH);         // Aqui generamos un flanco de bajada HIGH - LOW
    delayMicroseconds(5);              // Pequeño retardo para formar el pulso en STEP
    digitalWrite(steps, LOW);         // y el A4988 de avanzara un paso el motor
    delayMicroseconds(400); // generamos un retardo con el valor leido del potenciometro
 }
 delay(1000);
 for(x = 0; x < 800; x++){
    digitalWrite(direccion, 0);    
    digitalWrite(steps, HIGH);         // Aqui generamos un flanco de bajada HIGH - LOW
    delayMicroseconds(5);              // Pequeño retardo para formar el pulso en STEP
    digitalWrite(steps, LOW);         // y el A4988 de avanzara un paso el motor
    delayMicroseconds(400); // generamos un retardo con el valor leido del potenciometro
 }
 delay(1000);
   
}
