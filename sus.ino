//määritellään pinnit raajojen niveliin
#define EOY 0 //EtuOikeaYlänivel
#define EOK 1 //EtuOikeaKeski
#define EVY 2 //EtuVasen...
#define EVK 3

#define TOY 4 //TakaOikeaYlä
#define TOK 5 //TakaOikeaKeski
#define TOA 6 //TakaOikeaAlanivel
#define TVY 7 //TakaVasen...
#define TVK 8
#define TVA 9

const int LKM = 10; //nivelten lukumäärä

//ja laitetaan ne taulukkoon
int nivelet[LKM] = {EOY, EOK, EVY, EVK, TOY, TOK, TOA, TVY, TVK, TVA};

//ajoitukset eri nivelille. Kauanko ko. pumpulla kestää siirtyä asennosta toiseen?
//Onko asennosta palautumisaika vakio? Vai jäävätkö "löysiksi"?
//Kutsutaan ENNEN ko. niveltä
const int speed = 1;

const int dY = 1000/speed; //delayYlänivel
const int dK = 1000/speed; //delayKeski
const int dA = 1250/speed; //dAla

void setup() {
  //konfiguriodaan kaikki nivelet OUTPUTeiksi
  for(int i=0; i<LKM; i++){
    pinMode(nivelet[i], OUTPUT);
  }  
}
//alirutiinit raajoille
void etu(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(EOK, HIGH);
      delay(dY);
      digitalWrite(EOY, HIGH);
      delay(dK);
      digitalWrite(EOK, LOW);
      delay(dY);
      digitalWrite(EOY, LOW);
      break;
    case 'V':
      digitalWrite(EVK, HIGH);
      delay(dY);
      digitalWrite(EVY, HIGH);
      delay(dK);
      digitalWrite(EVK, LOW);
      delay(dY);
      digitalWrite(EVY, LOW);
      break;
  }
}

void taka(char puoli){
  switch(puoli){
    case 'O':
      digitalWrite(TOY, HIGH);
      delay(dK);
      digitalWrite(TOK, HIGH);
      delay(dY);
      digitalWrite(TOY, LOW);
      delay(dA);
      digitalWrite(TOA, HIGH);
      delay(dK);
      digitalWrite(TOK, LOW);
      digitalWrite(TOA, LOW);
      break;
    case 'V':
      digitalWrite(TVY, HIGH);
      delay(dK);
      digitalWrite(TVK, HIGH);
      delay(dY);
      digitalWrite(TVY, LOW);
      delay(dA);
      digitalWrite(TVA, HIGH);
      delay(dK);
      digitalWrite(TVK, LOW);
      digitalWrite(TVA, LOW);
      break;
  }
}

//kävelysykli
void kavely(){
  etu('V');
  taka('O');
  etu('O');
  taka('V');
}

void loop() {
  kavely();
}
