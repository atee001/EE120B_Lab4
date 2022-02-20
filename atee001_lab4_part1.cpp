const int b0 = 2;
const int b1 = 3;
const int b2 = 4;

void setup() {
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
//  digitalWrite(b7,LOW);
//  digitalWrite(b6,LOW);
//  digitalWrite(b5,LOW);
//  digitalWrite(b4,LOW);
//  digitalWrite(b3,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}

enum led_states {start, led_0, led_1, led_2} led_state = start;

void Tick(){
  
  switch(led_state){
    case start:
      led_state = led_0;
      resetB();
      delay(1000);
      break;
    case led_0:
      digitalWrite(b0, HIGH);      
      delay(1000);
      led_state = led_1;
      break;
     case led_1: 
      resetB();
      digitalWrite(b1, HIGH);
      delay(1000);
      led_state = led_2;
      break;
     case led_2:
      resetB();
      digitalWrite(b2, HIGH);
      delay(1000);
      led_state = start;
      break;    
    
  }  
  
}

void loop() {
  Tick();
}
