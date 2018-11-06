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
  digitalWrite(NN, LOW);
  digitalWrite(NK, LOW);
  
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

void etu1(char puoli){
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
  delay(300/speed);
  digitalWrite(EY, HIGH);
  delay(100/speed);
  digitalWrite(EK, LOW);
  //delay(300/speed);
  //digitalWrite(EY, LOW);
  //delay(1000/speed);      
}

void etu2(char puoli){
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
  //digitalWrite(EK, HIGH);
  //delay(300/speed);
  //digitalWrite(EY, HIGH);
  //delay(300/speed);
  //digitalWrite(EK, LOW);
  delay(300/speed);
  digitalWrite(EY, LOW);
  //delay(1000/speed);      
}
void taka1(char puoli){
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
  delay(500/speed);
  digitalWrite(TA, HIGH);
  delay(100/speed);
  digitalWrite(TY, LOW);
  delay(600/speed);
  digitalWrite(TA, LOW);
  //delay(1500/speed);
  digitalWrite(TK, HIGH);
  //delay(200/speed);
  //digitalWrite(TY, HIGH);
  //delay(1000/speed);      
}

void taka2(char puoli){
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
  //digitalWrite(TK, LOW);
  //delay(500/speed);
  //digitalWrite(TA, HIGH);
  //delay(100/speed);
  //digitalWrite(TY, LOW);
  //delay(600/speed);
  //digitalWrite(TA, LOW);
  //delay(1500/speed);
  //digitalWrite(TK, HIGH);
  delay(200/speed);
  digitalWrite(TY, HIGH);
  //delay(1000/speed);      
}

void dippaus(char puoli){
    switch(puoli){
      case 'O':
        TK = TVK;
        EK = EOK;
        break;
      case 'V':
        TK = TOK;
        EK = EVK;
        break;
     }
     digitalWrite(TK, LOW);
     digitalWrite(EK, HIGH);
}

//kävelysykli
void kavely(){
  digitalWrite(NK, LOW);
  delay(1000/speed);
  etu1('V');  
  taka1('O');
  dippaus('O');
  etu2('V');
  taka2('O');
  digitalWrite(NK, HIGH);
  delay(1000/speed);
  etu1('O');
  taka1('V');
  dippaus('V');
  etu2('O');
  taka2('V');
}

void veto(){
  digitalWrite(EOY, LOW);
  digitalWrite(EVY, LOW);
  //digitalWrite(TOY, HIGH);
  //digitalWrite(TVY, HIGH);
  delay(6000/speed);
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
    if(measureDist('E') < 20) kavely();
    //else kavely();
    else alkupose();
}
