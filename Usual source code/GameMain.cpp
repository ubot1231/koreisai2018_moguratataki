#include "GameMain.h"
#include "Arduino.h"
//#include "Serial.h"

GameMain::GameMain(){

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
  
}

