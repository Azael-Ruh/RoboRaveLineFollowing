const int NUMERO_PASOS = 200;                     //NUMERO PASOS POR VUELTA NEMA 17
const float LONGITUD_RUEDAS = 0.219911;           //LONGITUD RUEDAS m --> DIAMETRO (0.07m)
const int STEPS_MODE = 1;                         //FULL STEPS (1) - HALF STEPS (2) - FOURTH OF STEP (4)...
float velocidad = 0.3;                            //ROBOT SPEED IN m/s
double TIEMPO_INTERRUPCIONES = 0.000031875;       //(TIMER 8-bit)*PERIODO TIMER --> 255*[1/8MHz]

const int PIN_STEPS = 9;                          //PIN STEP DRIVER 9
const int PIN_DIRECCION = 8;                      //PIN DIRECCION DRIVER 8
int i = 1;                                        //CONTADOR PARA LA INTERRUPCION
int repeticiones = 0;                             //NUMERO DE REPETICIONES DE LA INTERRUPCION PARA AJUSTAR LA VELOCIDAD

bool parar = false;                               //MOTOR PARADO(true) O EN MARCHA(false)
bool direccion_robot = 1;                         //SENTIDO DEL ROBOT DELANTE(1), ATRÁS(0)

void setup(){                

  TCNT2 = 0;                                      //LIMPIA REGISTRO QUE GUARDA LA CUENTA DEL TIMER-2
  TIMSK2 = TIMSK2|0b00000001;                     //HABILITAR BANDERA 0 DEL REGISTRO QUE HABILITA LA INTERRUPCION POR DESBORDAMIENTO DEL TIMER
  TCCR2B = 0b00000001;                            //ESTABLECER FRECUENCIA DEL TIMER [8MHz]
  SREG = (SREG & 0b01111111) | 0b10000000;        //HABILITAR INTERRUPCIONES

  Serial.begin(115200);                           //INICIAR MONITOR SERIE
  
  pinMode(PIN_STEPS, OUTPUT);                     //ESTABLECER EL PIN CONECTADO A STEPS DEL DRIVER COMO SALIDA
  pinMode(PIN_DIRECCION, OUTPUT);                 //ESTABLECER EL PIN CONECTADO A DIRECCION DEL DRIVER COMO SALIDA
  digitalWrite(PIN_DIRECCION, direccion_robot);   //ESTABLECER SENTIDO ADELANTE COMO INICIAL 
}
 
void loop(){
  
}

ISR(TIMER2_OVF_vect){                             //FUNCION QUE SE INICIA CON LA INTERRUPCION DEL TIMER-2
  i++;                                            //SUMAR UNO EN LA CUENTA DE INTERRUPCIONES
  repeticiones = calc_velocidad();                //ESTABLECER NUMUERO DE REPETICIONES NECESARIAS PARA QUE EL ROBOT VAYA A X VELOCIDAD
  if((i%repeticiones) == 0 && parar == false){    //SI YA HAN PASADO X REPETICIONES Y EL ROBOT NO ESTÁ PARADO ENTONCES... (MOVIMIENTO DEL ROBOT)
    //Serial.print("Pulse On - ");                //TESTEO VELOCIDAD MOTORES
    digitalWrite(PIN_STEPS, HIGH);                //ENVIAR PULSO PARA QUE EL MOTOR DE UN PULSO
    delayMicroseconds(5);                         //DELAY DEL PULSO
    //Serial.println("Off");                      //TESTEO VELOCIDAD MOTORES
    digitalWrite(PIN_STEPS, LOW);                 //APAGAR PULSO
    i = 1;                                        //PONER EL CONTADOR A 1 PARA EVITAR DESBORDAMIENTO
  }
}

int calc_velocidad(){                             //FUNCION PARA CALCULAR EL NUMERO DE REPETICIONES NECESARIAS PARA IR A CIERTA VELOCIDAD
  int x;                                          //NUMERO DE REPETICIONES

  x = round(LONGITUD_RUEDAS / ((float)NUMERO_PASOS * (float)STEPS_MODE * TIEMPO_INTERRUPCIONES * velocidad));     //x = (LONGITUD_RUEDAS/(NUMERO_PASOS * STEPS_MODE))/(velocidad * TIEMPO_INTERRUPCIONES)
  //Serial.println(x);                            //TESTEO PARA COMPROBAR QUE EL NUMERO DE REPETICIONES ES CORRECTO      
  return x;                                       //DEVOLVER NUMERO DE REPETICIONES
}
