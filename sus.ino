//määritellään pinnit raajojen niveliin
#define EOY 1 //EtuOikeaYlänivel
#define EOA 2 //EtuOikeaAla
#define EVY 3 //EtuVasen...
#define EVA 4

#define TOY 5 //TakaOikeaYlä
#define TOK 6 //TakaOikeaKeski
#define TOA 7 //TakaOikeaAlanivel
#define TVY 8 //TakaVasen...
#define TVK 9
#define TVA 10

const int LKM = 10; //nivelten lukumäärä

//ja laitetaan ne taulukkoon
int nivelet[LKM] = {EOY, EOA, EVY, EVA, TOY, TOK, TOA, TVY, TVK, TVA};

//ajoitukset eri nivelille. kauanko ko pumpulla kestää siirtyä asennosta toiseen.
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

void loop() {
  // put your main code here, to run repeatedly:

}
