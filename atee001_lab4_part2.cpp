const int b2 = 4;
const int b3 = 5;
const int b4 = 6;

#define a0 digitalRead(A0)? 1 : 0

void setup() {
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void resetB()
{
  //  digitalWrite(b7,LOW);
  //  digitalWrite(b6,LOW);
  //  digitalWrite(b5,LOW);
  //  digitalWrite(b4,LOW);
  //  digitalWrite(b3,LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);

}

unsigned long previousMillis = 0;
unsigned long interval = 300;
unsigned char state = 0;

enum led_states {start, led_0, led_1, led_2, pressed, released} led_state = led_0;

int led_pin[] = {4, 5, 6};

void Tick() {  
  switch (led_state) { //transitions
    case led_0:
      led_state = (a0) ? pressed : led_1;     
      break;
    case led_1:
      led_state = (a0) ? pressed : led_2;    
      break;
    case led_2:
      led_state = (a0) ? pressed : led_0;      
      break;
    case pressed:
      led_state = (a0) ? pressed : released;              
      break;
    case released:
      led_state = (a0) ? led_0 : released;              
      break;
  }
  
    switch(led_state){ //actions
      case led_0:
        state = 0;
        resetB();
        digitalWrite(led_pin[state], HIGH);
        break;
      case led_1:
        state = 1;
        resetB();
        digitalWrite(led_pin[state], HIGH);
        break;
       case led_2:
        state = 2;
        resetB();
        digitalWrite(led_pin[state], HIGH);
        break;
       case pressed: 
        digitalWrite(led_pin[state], HIGH);
        Serial.println(state);
        break;
       case released:
        digitalWrite(led_pin[state], HIGH);
        Serial.println(state);
        break;      
    }     
  }




void loop() {  
    Tick();
    delay(300);
}
    
