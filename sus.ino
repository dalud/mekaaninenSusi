//määritellään pinnit raajojen niveliin
#define EOY 1 //EtuOikeaYlänivel
#define EOK 0 //EtuOikeaKeski
#define EVY 3 //EtuVasen...
#define EVK 2

#define TOY 50 //TakaOikeaYlä
#define TOK 51 //TakaOikeaKeski
#define TOA 48 //TakaOikeaAlanivel
#define TVY 47 //TakaVasen...
#define TVK 46
#define TVA 49

#define OL 14 //Oikea levittäjä
#define VL 17

#define NN 15 //Niska nostaja
#define NK 16 //niskan kääntäjä HIGH = vasemmalle, LOW = oikealle

const int LKM = 14; //nivelten lukumäärä

//ja laitetaan ne taulukkoon
int nivelet[LKM] = {EOY, EOK, EVY, EVK, TOY, TOK, TOA, TVY, TVK, TVA, OL, VL, NN, NK};

//ultrasonic Pakki
#define pTrigPin 99
#define pEchoPin 98

//Etu
#define eTrigPin 52
#define eEchoPin 53

long duration;

const int speed = 2.5;

void alkupose(){
  digitalWrite(NN, HIGH);
  
  digitalWrite(EOY, LOW);
  digitalWrite(EOK, LOW);
  
  digitalWrite(EVY, LOW);
  digitalWrite(EVK, LOW);
  
  digitalWrite(OL, LOW);
  digitalWrite(VL, LOW);
  
  digitalWrite(TOA, LOW);
  digitalWrite(TOK, HIGH);
  digitalWrite(TOY, HIGH);

  digitalWrite(TVA, LOW);
  digitalWrite(TVK, HIGH);
  digitalWrite(TVY, HIGH);
}

void setup() {
  //konfiguroidaan kaikki nivelet OUTPUTeiksi
  for(int i=0; i<LKM; i++) pinMode(nivelet[i], OUTPUT);    
  alkupose();

  pinMode(eTrigPin, OUTPUT);
  pinMode(eEchoPin, INPUT);
  pinMode(pTrigPin, OUTPUT);
  pinMode(pEchoPin, INPUT);
}

//alirutiinit raajoille
int EY, EK, TY, TK, TA;

void etu(char puoli){
  switch(puoli){
    case 'O':
      EY = EOY;
      EK = EOK;
      break;
    case 'V':
      EY = EVY;
      EK = EVK;
      break;
  }
  digitalWrite(EK, HIGH);
  delay(1000/speed);
  digitalWrite(EY, HIGH);
  delay(1000/speed);
  digitalWrite(EK, LOW);
  delay(1500/speed);
  digitalWrite(EY, LOW);
  delay(1000/speed);      
}

void taka(char puoli){
  switch(puoli){
    case 'O':
      TY = TOY;
      TK = TOK;
      TA = TOA;
      break;
    
    case 'V':
      TY = TVY;
      TK = TVK;
      TA = TVA;
      break;
  }
  digitalWrite(TK, LOW);
  delay(1000/speed);
  digitalWrite(TA, HIGH);
  delay(500/speed);
  digitalWrite(TY, LOW);
  delay(3000/speed);
  digitalWrite(TA, LOW);
  //delay(1500/speed);
  digitalWrite(TK, HIGH);
  delay(1500/speed);
  digitalWrite(TY, HIGH);
  delay(1000/speed);      
}

//etujalan pakki
void etuPakki(char puoli){
  switch(puoli){
    case 'O':
      EY = EOY;
      EK = EOK;
      break;

    case 'V':
      EY = EVY;
      EK = EVK;
      break;
  }  
  digitalWrite(EY, HIGH);
  delay(2000/speed);
  digitalWrite(EK, HIGH);
  digitalWrite(EY, LOW);
  delay(2000/speed);
  digitalWrite(EK, LOW);
  delay(2000/speed);
}

void takaPakki(char puoli){
  switch(puoli){
    case 'O':
      TY = TOY;
      TK = TOK;
      TA = TOA;
      break;

    case 'V':
      TY = TVY;
      TK = TVK;
      TA = TVA;
      break;    
  } 
  digitalWrite(TY, LOW);
  delay(2000/speed);
  digitalWrite(TK, LOW);
  //delay(2000/speed);
  digitalWrite(TA, HIGH);
  delay(2000/speed);
  digitalWrite(TY, HIGH);
  delay(2000/speed);
  digitalWrite(TA, LOW);
  //delay(2000/speed);
  digitalWrite(TK, HIGH);
  delay(2000/speed);
}

//kävelysykli
void kavely(){
  digitalWrite(NK, LOW);
  etu('V');
  digitalWrite(NK, HIGH);
  taka('O');
  etu('O');
  digitalWrite(NK, LOW);
  taka('V');
}

void pakitus(){
  etuPakki('O');
  takaPakki('O');
}

void etuNosto(){
  digitalWrite(EOK, LOW);
  digitalWrite(EVK, LOW);
  digitalWrite(EOY, HIGH);
  digitalWrite(EVY, HIGH);
}

//silmien etäisyysnäkö
int trig, echo;

long measureDist(char eye){
  switch(eye){
    case 'E':
      trig = eTrigPin;
      echo = eEchoPin;
      break;

    case 'P':
      trig = pTrigPin;
      echo = pEchoPin;
      break;
  }  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  return duration*0.034/2;  //cm
}

void loop() {
    if(measureDist('E') < 10) alkupose();
    else kavely();
}
