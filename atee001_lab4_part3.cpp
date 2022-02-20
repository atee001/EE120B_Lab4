//#define (digitalRead(A0) == HIGH) digitalRead((digitalRead(A0) == HIGH))?1:0
//#define (digitalRead(A1) == HIGH) digitalRead((digitalRead(A1) == HIGH))?1:0

const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;

void setup() {
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);  
  pinMode(A1, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}
void resetB()
{
digitalWrite(b7,LOW);
digitalWrite(b6,LOW);
digitalWrite(b5,LOW);
digitalWrite(b4,LOW);
digitalWrite(b3,LOW);
digitalWrite(b2,LOW);
digitalWrite(b1,LOW);
digitalWrite(b0,LOW);
}
void writeToB(unsigned char temp)
{

if ((temp>>7) & 0x01){digitalWrite(b7,HIGH);}
else digitalWrite(b7, LOW);
if ((temp>>6) & 0x01){digitalWrite(b6,HIGH);}
else digitalWrite(b6, LOW);
if ((temp>>5) & 0x01){digitalWrite(b5,HIGH);}
else digitalWrite(b5, LOW);
if ((temp>>4) & 0x01){digitalWrite(b4,HIGH);}
else digitalWrite(b4, LOW);
if ((temp>>3) & 0x01){digitalWrite(b3,HIGH);}
else digitalWrite(b3, LOW);
if ((temp>>2) & 0x01){digitalWrite(b2,HIGH);}
else digitalWrite(b2, LOW);
if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
else digitalWrite(b1, LOW);
if (temp & 0x01){digitalWrite(b0,HIGH);}
else digitalWrite(b0, LOW);
}

unsigned char value = 7;
enum States {start, inc, dec, reset, wait} state = start;

void Tick(){
  switch(state){//transitions
    case start:
      Serial.println("start");
      if((digitalRead(A0) == HIGH) && (!(digitalRead(A1) == HIGH))) state = inc;
      else if((!(digitalRead(A0) == HIGH)) && (digitalRead(A1) == HIGH)) state = dec;
      else if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)) state = reset;
      else state = start;
      break;
    case inc:      
      Serial.println("inc");
      if((digitalRead(A0) == HIGH) && (!(digitalRead(A1) == HIGH))) state = inc;
      else if((!(digitalRead(A0) == HIGH)) && (digitalRead(A1) == HIGH)) state = dec;
      else if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)) state = reset;
      else state = wait;
      break;
    case dec:
      Serial.println("dec");
      if((digitalRead(A0) == HIGH) && (!(digitalRead(A1) == HIGH))) state = inc;
      else if((!(digitalRead(A0) == HIGH)) && (digitalRead(A1) == HIGH)) state = dec;
      else if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)) state = reset;
      else state = wait;
      break;
     case reset:
      Serial.println("reset");
      if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)) state = reset;
      else if((digitalRead(A0) == HIGH) && (!(digitalRead(A1) == HIGH))) state = inc;
      else if((!(digitalRead(A0) == HIGH)) && (digitalRead(A1) == HIGH)) state = dec;
      else state = wait;
      break;
     case wait:
      Serial.println("wait");
      if((digitalRead(A0) == HIGH) && (!(digitalRead(A1) == HIGH))) state = inc;
      else if((!(digitalRead(A0) == HIGH)) && (digitalRead(A1) == HIGH)) state = dec;
      else if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)) state = reset;
      else state = wait;
      break;    
  }
  switch(state){//actions
    case start:
      value = 7;
      resetB();
      writeToB(value);
      break;
    case inc:      
      if(value < 255) ++value;
      writeToB(value);
      break;
    case dec:
      if(value > 0) --value;
      writeToB(value);
      break;
     case reset:
      value = 0;
      writeToB(value);
      break;
     case wait:
      break;    
  }
  
}

void loop() {
  Tick();
  delay(100);

}
