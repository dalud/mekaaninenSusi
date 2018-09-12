//määritellään pinnit raajojen niveliin
#define EOY 0 //EtuOikeaYlänivel
#define EOA 1 //EtuOikeaAla
#define EVY 2 //EtuVasen...
#define EVA 3

#define TOY 4 //TakaOikeaYlä
#define TOK 5 //TakaOikeaKeski
#define TOA 6 //TakaOikeaAlanivel
#define TVY 7 //TakaVasen...
#define TVK 8
#define TVA 9

const int LKM = 10; //nivelten lukumäärä

//ja laitetaan ne taulukkoon
int nivelet[LKM] = {EOY, EOA, EVY, EVA, TOY, TOK, TOA, TVY, TVK, TVA};

//ajoitukset eri nivelille. Kauanko ko. pumpulla kestää siirtyä asennosta toiseen?
//Onko asennosta palautumisaika vakio? Vai jäävätkö "löysiksi"?
const int dY = 1000; //delay Ylänivel
const int dK = 1000; //dKeski
const int dA = 1000; //dAla

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
      digitalWrite(EOA, HIGH);
      delay(dA);
      digitalWrite(EOY, HIGH);
      digitalWrite(EOA, LOW);
      delay(dY);
      digitalWrite(EOY, LOW);
      break;
    case 'V':
      digitalWrite(EVA, HIGH);
      delay(dA);
      digitalWrite(EVY, HIGH);
      digitalWrite(EVA, LOW);
      delay(dY);
      digitalWrite(EVY, LOW);
      break;
  }
}

void taka(char puoli){
  
}

//kävelysykli
void kavely(){
  etu('O');
  taka('V');
  etu('V');
  taka('O');
}

void loop() {
  kavely();
}
