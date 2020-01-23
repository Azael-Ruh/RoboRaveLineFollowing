const uint8_t PIN_STEPS = 9;                          //PIN STEP DRIVER 9
const uint8_t PIN_DIRECCION = 8;                      //PIN DIRECCION DRIVER 8

const uint8_t NUMERO_PASOS = 200;                     //NUMERO PASOS POR VUELTA NEMA 17
const float LONGITUD_RUEDAS = 0.219911;               //LONGITUD RUEDAS m --> DIAMETRO (0.07m)
const uint8_t STEPS_MODE = 1;                         //FULL STEPS (1) - HALF STEPS (2) - FOURTH OF STEP (4)...
const float VELOCIDAD = 0.3;                        //ROBOT SPEED IN m/s
const double TIEMPO_INTERRUPCIONES = 0.000031875;     //(TIMER 8-bit)*PERIODO TIMER --> 255*[1/8MHz]
const bool PARAR = false;                             //MOTOR PARADO(true) O EN MARCHA(false)
const bool DIRECCION_ROBOT = 1;                       //SENTIDO DEL ROBOT DELANTE(1), ATRÁS(0)
const uint8_t REPETICIONES = LONGITUD_RUEDAS/(NUMERO_PASOS*STEPS_MODE*TIEMPO_INTERRUPCIONES*VELOCIDAD);  //NUMERO DE REPETICIONES DE LA INTERRUPCION PARA AJUSTAR LA VELOCIDAD

uint8_t i = 1;                                         //CONTADOR PARA LA INTERRUPCION

void setup(){                
  TCNT2 = 0;                                          //LIMPIA REGISTRO QUE GUARDA LA CUENTA DEL TIMER-2
  TIMSK2 |= (1 << TOIE2);                             //HABILITAR BANDERA 0 DEL REGISTRO QUE HABILITA LA INTERRUPCION POR DESBORDAMIENTO DEL TIMER
  TCCR2B |= (1 << CS20);                              //ESTABLECER FRECUENCIA DEL TIMER [8MHz]
  TCCR2B &= ~((1 << CS21) | (1 << CS22));
  sei();                                 //HABILITAR INTERRUPCIONES
  
  Serial.begin(115200);                               //INICIAR MONITOR SERIE
  
  pinMode(PIN_STEPS, OUTPUT);                         //ESTABLECER EL PIN CONECTADO A STEPS DEL DRIVER COMO SALIDA
  pinMode(PIN_DIRECCION, OUTPUT);                     //ESTABLECER EL PIN CONECTADO A DIRECCION DEL DRIVER COMO SALIDA
  
  digitalWrite(PIN_DIRECCION, DIRECCION_ROBOT);       //ESTABLECER SENTIDO ADELANTE COMO INICIAL 
}
 
void loop(){
  if(!(i%REPETICIONES) && !PARAR){                    //SI YA HAN PASADO X REPETICIONES Y EL ROBOT NO ESTÁ PARADO ENTONCES... (MOVIMIENTO DEL ROBOT)
    Serial.print("Pulse On - ");                    //TESTEO VELOCIDAD MOTORES
    digitalWrite(PIN_STEPS, HIGH);                    //ENVIAR PULSO PARA QUE EL MOTOR DE UN PULSO
    delayMicroseconds(5);                             //DELAY DEL PULSO
    Serial.println("Off");                          //TESTEO VELOCIDAD MOTORES
    digitalWrite(PIN_STEPS, LOW);                     //APAGAR PULSO
    i = 1;                                            //PONER EL CONTADOR A 1 PARA EVITAR DESBORDAMIENTO
  }
}

ISR(TIMER2_OVF_vect){                             //FUNCION QUE SE INICIA CON LA INTERRUPCION DEL TIMER-2
  i++;                                            //SUMAR UNO EN LA CUENTA DE INTERRUPCIONES
}
