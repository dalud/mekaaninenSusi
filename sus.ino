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
//Etu
#define oeTrigPin 52  //OikeaEtuSilmä
#define oeEchoPin 53

#define veTrigPin 44  //VasenEtu
#define veEchoPin 45

long duration;

const int speed = 2.5;

void alkupose(){
  digitalWrite(NN, HIGH);
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

  pinMode(oeTrigPin, OUTPUT);
  pinMode(oeEchoPin, INPUT);
  pinMode(veTrigPin, OUTPUT);
  pinMode(veEchoPin, INPUT);
}

//alirutiinit raajoille
int EY, EK, TY, TK, TA, L;

void etu(char puoli){
  switch(puoli){
    case 'O':
      EY = EOY;
      EK = EOK;
      L = OL;
      break;
    case 'V':
      EY = EVY;
      EK = EVK;
      L = VL;
      break;
  }
  digitalWrite(EK, HIGH);
  delay(300/speed);
  digitalWrite(EY, HIGH);
  digitalWrite(L, HIGH);
  delay(300/speed);
  digitalWrite(EK, LOW);
  delay(300/speed);
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
  delay(500/speed);
  digitalWrite(TA, HIGH);
  delay(100/speed);
  digitalWrite(TY, LOW);
  delay(600/speed);
  digitalWrite(TA, LOW);
  digitalWrite(TK, HIGH);
  delay(200/speed);
  digitalWrite(TY, HIGH);
  delay(1000/speed);      
}

//kävelysykli
void kavely(){
  digitalWrite(NN, HIGH);
  digitalWrite(NK, LOW);
  etu('V');  
  taka('V');
  digitalWrite(NK, HIGH);
  etu('O');
  taka('O');
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
  delay(1000/speed);
  digitalWrite(EK, HIGH);
  digitalWrite(EY, LOW);
  delay(1000/speed);
  digitalWrite(EK, LOW);
  delay(1000/speed);
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
  delay(1000/speed);
  digitalWrite(TK, LOW);
  digitalWrite(TA, HIGH);
  delay(1000/speed);
  digitalWrite(TY, HIGH);
  delay(1000/speed);
  digitalWrite(TA, LOW);
  digitalWrite(TK, HIGH);
  delay(1000/speed);
}

void pakitus(){
  digitalWrite(NN, LOW);
  digitalWrite(NK, HIGH);
  etuPakki('O');
  takaPakki('V');
  etuPakki('V');
  takaPakki('O');
}

void kumarrus(){
  digitalWrite(EOK, HIGH);
  digitalWrite(EVK, HIGH);
  delay(1000);
  digitalWrite(EOY, HIGH);
  digitalWrite(EVY, HIGH);
  delay(1000);
}

void istuminen(){
  digitalWrite(TOY, LOW);
  digitalWrite(TVY, LOW);
  digitalWrite(TOK, LOW);
  digitalWrite(TVK, LOW);
  digitalWrite(TOA, HIGH);
  digitalWrite(TVA, HIGH);
}

void ponnistus(){
  digitalWrite(TOY, HIGH);
  digitalWrite(TVY, HIGH);
  digitalWrite(TOK, HIGH);
  digitalWrite(TVK, HIGH);
  digitalWrite(TOA, LOW);
  digitalWrite(TVA, LOW);
}

void haistelu(){
  kumarrus();
  digitalWrite(NN, HIGH);
  delay(1000);
  digitalWrite(NK, HIGH);
  delay(1000);
  digitalWrite(NK, LOW);
  delay(2000);
  digitalWrite(NN, LOW);
  delay(2000);
}

void kaannos(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(NK, LOW);
      digitalWrite(EOK, HIGH);
      digitalWrite(OL, HIGH);
      digitalWrite(VL, HIGH);
      delay(1000);
      digitalWrite(EOK, LOW);
      delay(1000);
      taka('V');
      digitalWrite(EVK, HIGH);
      digitalWrite(OL, LOW);
      digitalWrite(VL, LOW);
      delay(1000);
      digitalWrite(EVK, LOW);
      delay(1000);
      break;
    case 'V':
      digitalWrite(NK, HIGH);
      digitalWrite(EVK, HIGH);
      digitalWrite(VL, HIGH);
      digitalWrite(OL, HIGH);
      delay(1000);
      digitalWrite(EVK, LOW);
      delay(1000);
      taka('O');
      digitalWrite(EOK, HIGH);
      digitalWrite(VL, LOW);
      digitalWrite(OL, LOW);
      delay(1000);
      digitalWrite(EOK, LOW);
      delay(1000);
      break;
  }  
}

//silmien etäisyysnäkö
int trig, echo;

long measureDist(String eye){
  
  if(eye == "oe"){
    trig = oeTrigPin;
    echo = oeEchoPin;
  }else if(eye == "ve"){
    trig = veTrigPin;
    echo = veEchoPin;
  }
   
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  return duration*0.034/2;  //cm
}

void randomi(){
  int roll abs(random(10));

  switch(roll){
    case 1:
      kavely();
      kavely();
      kavely();
      break;
    case 2:
      pakitus();
      break;
    case 3:
      kumarrus();
      break;
    case 4:
      haistelu();
      break;
    case 5:
      kaannos('O');
      break;
    case 6:
      kaannos('V');
      break;
    case 8:
      istuminen();
      break;
    default:
      alkupose();
      break;
  }
}

void loop() {
    if(measureDist("ve") < 100) {
      digitalWrite(NN, LOW);
      kaannos('V');
      kaannos('V');
      randomi();
      delay(5000);
    }else if(measureDist("oe") < 100){
      digitalWrite(NN, LOW);
      kaannos('O');
      kaannos('O');
      randomi();
      delay(5000);
    }
    else alkupose();
}
