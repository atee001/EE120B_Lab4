
const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;

void setup() {
  randomSeed(analogRead(5));
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  Serial.begin(9600);  
}


int led_pins [] = {2, 3, 4, 5, 6};
int index = 0;
unsigned char cnt = 0;
unsigned char curr_led = 0;

bool isValid(int index){
  if(index == 0 && (digitalRead(A0) == HIGH)) return true;
  else if(index == 1 && (digitalRead(A1) == HIGH)) return true;
  else if(index == 2 && (digitalRead(A2) == HIGH)) return true;
  else if(index == 3 && (digitalRead(A3) == HIGH)) return true;
  return false;    
}

void resetB()
{

digitalWrite(b4,LOW);
digitalWrite(b3,LOW);
digitalWrite(b2,LOW);
digitalWrite(b1,LOW);
digitalWrite(b0,LOW);
}

int next_led(int n_led){
    Serial.println(n_led);
     if(n_led == 3) return 0;
     else return (n_led+1);
}

enum states{rand_state, valid, end_game} state = rand_state;

void Tick(){

  switch(state){ //transitions
    case rand_state:
      Serial.println("rand");
      if(cnt <= 5 && isValid(index)) {state = valid;}
      else state = rand_state;
      break;
    case valid:
      Serial.println("valid");
      if(cnt > 6) state = end_game;
      else state = valid; 
      break;
    case end_game:
      Serial.println("end_game");
      state = end_game;
      break;           
    }

   switch(state){ //actions
      case rand_state:   
        resetB();
        ++cnt;     
        if(cnt <= 5 && isValid(index)) cnt = 0;
        else if(cnt == 10) {
          index = random(4); 
          digitalWrite(led_pins[index], HIGH); 
          cnt = 0;
         }
        break;
      case valid:
        resetB();
        ++cnt;
        if(cnt <= 5 && isValid(index)){ 
          index = next_led(index); 
          Serial.println("index: ");
          Serial.println(index);
          cnt = 0;
         } 
        digitalWrite(led_pins[index], HIGH);
        break;
      case end_game:
        resetB();
        digitalWrite(6, HIGH);
        break;    
    }
}
 
void loop() {
  Tick();
  delay(100);
}
