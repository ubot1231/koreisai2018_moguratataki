#include "GameMain.h"

int pins[5] =  {0,0,0,0,0}; //Inputのpin
int point = 0; //合計点

long time_micros;
long time_millis;
long totalTime;
long oldSeconds = 0;
long minute = 2;
long seconds = 0;
long elapsedTime = 1;

//int randNum;
boolean isStart = false;
boolean isBoot = true;
boolean isRunning = false;
boolean oneOver = true;

void TimeManager(){
  while(isStart == true){
    
    
    totalTime = (minute * 60 + seconds);
    //elapsedTime = millis() / 1000;
    totalTime -= elapsedTime;

    minute = ((int)totalTime / 60);
    seconds = (totalTime - (minute * 60));

    if((int)seconds != (int)oldSeconds){
     Serial.print(minute); Serial.print(" : "); Serial.println((int)seconds);
    }
    oldSeconds = seconds;

    delay(1000);
    //Serial.println(totalTime);
    isRunning = true;
    //Serial.println(isRunning);

    
   if(totalTime < 0){
    isStart = false;
    isBoot = false;
    oneOver = true;
    isRunning = false;
    }
     }
}


void GameStartManager(){
  
if (digitalRead(2) == 1) {
  totalTime = (minute * 60 + seconds) * 1000;
  oldSeconds = 0;
  point = 0;
  for(int i = 0;i < 5;i++){
    pins[i] = 0;
  }
  
Serial.println("ゲームスタート！");
delay(1000);
isStart = true;
isRunning = true;
}
}

void GameEndManager(){
  //////////ゲーム終了処理(一回だけ)///////////////
  while(isBoot == false){
while(isStart == false) {
while(oneOver == true){

Serial.print("合計ポイント：");
Serial.println(point);
Serial.println("ゲームオーバー！");
Serial.println("ゲームを再度開始するには、ボタンを押してください");
//////////////////////////////
oneOver = false;
}
//終了後処理(LEDチカチカ)////////
for (int c = 1; c < 10; c++) {
delay(100);
for (int i = 3; i < 8; i++) {digitalWrite(i, HIGH);}
delay(100);
for (int i = 3; i < 8; i++) {digitalWrite(i, LOW);}
}
}
}
///////////////////////////
}

/*
void GameMain(){
//ゲームメイン処理////////
while(isRunning == true) {
randNum = random(3, 8);//3〜7pinからランダムでモグラ出現

//現在得点表示///////////////////
Serial.print("合計ポイント：");
Serial.println(point);

//上のランダム初期化処理で入れたrandNumからランダムにモグラを出現させる/////
digitalWrite(randNum, HIGH);
for(int i = 0;i < 5 ;i++){pins[i] = digitalRead(9 + i);}

Serial.print("pin9 is ");
Serial.println(pins[0]);

Serial.println(randNum);
//HIGHで得点///////////////////////
if (pins[0] + pins[1] + pins[2] + pins[3] + pins[4] == 1) {point++;}
//////////////////////////////////

delay(5000);
digitalWrite(randNum, LOW);
delay(5000);
}
}*/

GameMain gamemain;

void setup() {
  isStart = false;
  isBoot = true;
  oneOver = true;
  isRunning = false;
Serial.begin(9600);

//pinの初期化////////////////
for (int i = 2; i < 8; i++) {
//9〜13pinまでをInputとして使用
pinMode (i + 7, INPUT);
//2〜7pinまでをOutputとして使用
pinMode(i, OUTPUT);
}
//////////////////////////
randomSeed(analogRead(0)); //乱数
Serial.println("モグラ叩きゲーム");
Serial.println("ボタンを押してスタート！！");
}

void loop() {
 GameStartManager();
 TimeManager();
 //GameMain();
 gamemain.GameMain();

 GameEndManager();
}
