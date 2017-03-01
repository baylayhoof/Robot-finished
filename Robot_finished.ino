
#include <SoftwareSerial.h>
int bluetoothTx = 3;
int bluetoothRx = 4;

int motor1A=5;
int motor1B=6;

int motor2A=10;
int motor2B=11;

int TriggerPin = 12;
int EchoPin = 9;

//her kalder vi de forskellige pins så hver pin har et navn man kan kalde senere


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx
char msg;
int counter = 0;
void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  bluetooth.begin(115200);//standard bluetooth mate

  pinMode(motor1A,OUTPUT);
  pinMode(motor1B,OUTPUT);
  
  pinMode(motor2A,OUTPUT);
  pinMode(motor2B,OUTPUT);

  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT); 

  //her fortæller vi de forskellige pins lidt om hvad de skal gøre
  
}


void loop(){
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  {
  int val = pulseIn(EchoPin, HIGH);
  val=val/58;
  if (val >= 400) {
    Serial.print("Out of range.");
    Serial.println();
  }
  else {
    Serial.print("Distance: ");
    Serial.print(val);
    Serial.print(" cm, ");
    Serial.println();
  }
  delay(50);
  }
  
  bluetooth.listen();
  modtagFraBluetooth();
  //Serial.println(counter);
  bluetooth.println(counter);
  counter++;
  delay(1000);

  //Her fortæller vi arduinoen en komando som den skal gentage konstant
}


void modtagFraBluetooth(){
  //her gør vi så arduinoen kan få et signal via Bluetooth samtidig med at vi også kalder nogle komandoer
  char msg;
  Serial.print("data:");
  if(bluetooth.available()){
    msg= (char)bluetooth.read();
    Serial.println(msg); 
    if(msg =='b'){
    bach();
    }  
    
     else if(msg =='s'){
      stop();
     }

   else if (msg =='f'){
    frem();
   }

   else if (msg =='v'){
    left();
   }

   else if (msg =='h'){
    right();
   }
    }
    bluetooth.print(msg);
  }

void frem(){
  //her får vi arduinoen til at sende et signal til de to motorere som får dem til at køre frem
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void bach(){
  //her sender den signal til at bakke
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1A, LOW);

  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2A, LOW);
}

void right(){
  //her får den, den til at dreje til højre
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);

  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2A, LOW);
}

void left(){
  //her får den, den til at dreje til venstre
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1A, LOW);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void stop(){
  //her stopper den bække motorere helt
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1A, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}



