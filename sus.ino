//määritellään pinnit raajojen niveliin
#define EOY 0 //EtuOikeaYlänivel
#define EOK 1 //EtuOikeaKeski
#define EVY 99 //EtuVasen...
#define EVK 98

#define TOY 2 //TakaOikeaYlä
#define TOK 3 //TakaOikeaKeski
#define TOA 4 //TakaOikeaAlanivel
#define TVY 7 //TakaVasen...
#define TVK 8
#define TVA 9

#define NISKA 10

const int LKM = 11; //nivelten lukumäärä

//ja laitetaan ne taulukkoon
int nivelet[LKM] = {EOY, EOK, EVY, EVK, TOY, TOK, TOA, TVY, TVK, TVA, NISKA};

const int speed = 2.5;

//ultrasonic Pakki
#define PtrigPin 11
#define PechoPin 12

//Etu
#define EtrigPin 22
#define EechoPin 23


long duration;

void alkupose(){
  digitalWrite(TOY, HIGH);
  digitalWrite(TOK, HIGH);
}

void setup() {
  //konfiguroidaan kaikki nivelet OUTPUTeiksi
  for(int i=0; i<LKM; i++) pinMode(nivelet[i], OUTPUT);    
  alkupose();

  pinMode(EtrigPin, OUTPUT);
  pinMode(EechoPin, INPUT);
  pinMode(PtrigPin, OUTPUT);
  pinMode(PechoPin, INPUT);
}

//alirutiinit raajoille
void etu(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(EOK, HIGH);
      delay(1000/speed);
      digitalWrite(EOY, HIGH);
      delay(1000/speed);
      digitalWrite(EOK, LOW);
      delay(1500/speed);
      digitalWrite(EOY, LOW);
      delay(2000/speed);
      break;
    case 'V':
      digitalWrite(EVK, HIGH);
      delay(1000/speed);
      digitalWrite(EVY, HIGH);
      delay(1000/speed);
      digitalWrite(EVK, LOW);
      delay(1500/speed);
      digitalWrite(EVY, LOW);
      delay(2000/speed);
      break;
  }
}

void taka(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(TOK, LOW);
      delay(1000/speed);
      digitalWrite(TOA, HIGH);
      delay(500/speed);
      digitalWrite(TOY, LOW);
      delay(3000/speed);
      digitalWrite(TOA, LOW);
      //delay(1500/speed);
      digitalWrite(TOK, HIGH);
      delay(1500/speed);
      digitalWrite(TOY, HIGH);
      delay(2000/speed);
      break;
    
    case 'V':
      digitalWrite(TVK, LOW);
      delay(1000/speed);
      digitalWrite(TVA, HIGH);
      delay(500/speed);
      digitalWrite(TVY, LOW);
      delay(3000/speed);
      digitalWrite(TVA, LOW);
      //delay(1500/speed);
      digitalWrite(TVK, HIGH);
      delay(1500/speed);
      digitalWrite(TVY, HIGH);
      delay(2000/speed);
      break;
  }
}

void etuPakki(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(EOY, HIGH);
      delay(2000/speed);
      digitalWrite(EOK, HIGH);
      digitalWrite(EOY, LOW);
      delay(2000/speed);
      digitalWrite(EOK, LOW);
      delay(2000/speed);
  }
}

void takaPakki(char puoli){
  switch(puoli){
    case 'O':
    digitalWrite(TOY, LOW);
    delay(2000/speed);
    digitalWrite(TOK, LOW);
    //delay(2000/speed);
    digitalWrite(TOA, HIGH);
    delay(2000/speed);
    digitalWrite(TOY, HIGH);
    delay(2000/speed);
    digitalWrite(TOA, LOW);
    //delay(2000/speed);
    digitalWrite(TOK, HIGH);
    delay(2000/speed);
  }
}

//kävelysykli
void kavely(){
  //etu('V');
  taka('O');
  etu('O');
 //taka('V');
}

void pakitus(){
  etuPakki('O');
  takaPakki('O');
}

//mittaa distance Pakki
long measureDistP(){
  digitalWrite(PtrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(PtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(PtrigPin, LOW);
  duration = pulseIn(PechoPin, HIGH);
  return duration*0.034/2;  
}

//Etu
long measureDistE(){
  digitalWrite(EtrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(EtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(EtrigPin, LOW);
  duration = pulseIn(EechoPin, HIGH);
  return duration*0.034/2;  
}

void loop() {
  if (measureDistE() < 10) {
    kavely();
  }else if(measureDistP() < 10){
    pakitus();
  }
  else alkupose();
}
