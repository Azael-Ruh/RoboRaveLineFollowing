int i = 0;

void setup() {
  TCNT2 = 0;
  TIMSK2 = TIMSK2|0b00000001;
  TCCR2B = 0b00000111;
  SREG = (SREG & 0b01111111) | 0b10000000; 

  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(13,1);
  delay(150);
  digitalWrite(13,0);
  delay(150);
}

ISR(TIMER2_OVF_vect){
   i++;
   mensaje(i);
}

void mensaje(int a){
  if((a%30) == 0){
    Serial.println("Hola");
  }
}
