#include <MsTimer2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define PUSH_SHORT 0.1
LiquidCrystal_I2C lcd(0x27,16,2);
const float push_shot = 1;
int cnt;
static int point = 0; //合計点

///*unsigned long*/float pushcnt_On;
///*unsigned long*/float pushcnt_Off;
int pins[5] =  {0,0,0,0}; //Inputのpin
float onTime = 1000;
static int randNum;

long totalTime;
long oldSecond = 0;
long currentTime;
long oldTime;
long deltaTime;
long minute = 1;
long second = 0;

static boolean output = false;
 boolean isJudging = false;

boolean oneTouch = false;
boolean isStart = false;
boolean isBoot = true;
boolean isRunning = false;
boolean oneOver = true;

/*
unsigned long pushcnt_On = 0;
  unsigned long pushcnt_Off = 0;*/

void GameStartManager(){
  
  if (digitalRead(2) == 1) {
    totalTime = (minute * 60 + second)*1000;
    point = 0;
    for(int i = 0;i < 5;i++){
      pins[i] = 0;
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(/*"ゲームスタート！"*/"GameStart!!");
    delay(1000);
    lcd.clear();
    MsTimer2::set(onTime, AppearanceMogura);     // 500ms毎にflash( )割込み関数を呼び出す様に設定
    MsTimer2::start();   
    isStart = true;
    isRunning = true;
    oneTouch = true;
   
  }
}

void GameEndManager(){
  //////////ゲーム終了処理(一回だけ)///////////////
  while(isBoot == false){
    while(isStart == false) {
      while(oneOver == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println(/*"ゲームオーバー！"*/"GameOver");
    lcd.setCursor(0,1);
    lcd.print(/*"合計ポイント："*/"Total : ");
    lcd.println(point);

    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("PleasePushReset");
    lcd.setCursor(0,1);
    lcd.print(/*"合計ポイント："*/"Total : ");lcd.println(point);
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

void TimeManager(){
  
  if(isStart == true){
  while(isRunning == true){

///////時間計測///////////////////////////////
   oldTime = currentTime;
   currentTime = millis();
   deltaTime = currentTime - oldTime;
   
   totalTime -= deltaTime;
    
    Mainloop();
    
    minute = (int)(totalTime / 60000);
    second = totalTime - minute * 60000;
  
    if((int)second != (int)oldSecond) {lcd.setCursor(0,0); lcd.print(minute); lcd.print(" : "); lcd.print((int)(second/1000));}
     lcd.setCursor(0,1);
      lcd.print("Total : "); lcd.print(point);
      
        oldSecond = second;
  

   if(totalTime < 0){
    isStart = false;
    isBoot = false;
    oneOver = true;
    isRunning = false;
    }
/////////////////////////////////////////////
     }
     }
}


void AppearanceMogura(){
  output = !output;
  if(output == true){
    isJudging = true;
    randNum = random(3, 8);//3〜7pinからランダムでモグラ出現
    // randNum = random(0, 5);//3〜7pinからランダムでモグラ出現
  }
  digitalWrite(randNum, output);
  //isJudging = !isJudging;
  oneTouch = !oneTouch;
  
  
}

void setup() {

lcd.init(); 
lcd.init();
lcd.backlight();
  isStart = false;
  isBoot = true;
  oneOver = true;
  isRunning = false;
  isJudging = false;
  output = false;
  oneTouch = false;
// onTime = 3000;
   Serial.begin(19200 );

   //pinの初期化////////////////
    for (int i = 2; i < 8; i++) {
    //9〜13pinまでをInputとして使用
    pinMode (i + 7, INPUT);
    //2〜7pinまでをOutputとして使用
    pinMode(i, OUTPUT);
    }

    randomSeed(analogRead(0)); //乱数
    lcd.setCursor(0,0);
    lcd.println("3E-whack-a-mole");
    lcd.setCursor(0,1);
    lcd.println("PleasePushButton");

}

void Mainloop(){
  
    unsigned long pushcnt_On = 0;
    unsigned long pushcnt_Off = 0;
   
    byte val; //格納するバイト型を用意
    byte state; //スイッチの状態

    int add = 0;

  if (cnt == 0) {
    
    for(int i = 0;i < 5 ;i++){pins[i] = digitalRead(9 + i);}
    //Serial.print("output = "); Serial.println(output);
    while(pins[randNum - 3] == HIGH && pushcnt_On < 10.0){
         pushcnt_On += 10.0;
      Serial.println(pushcnt_On);
      
    }

//チャタリング対策後のスイッチ判定

    
     if(pushcnt_On > push_shot){
      /*
       val = val<<1;//上位ビットに古い情報を格納
      val += pins[randNum - 3];//下位ビットに新しい情報を格納*/
     if(isJudging == true){
      point ++;
      isJudging = false;
     }
     }/*
     else{
val = 0;//押されてなければ初期化
}

if(val == 1){
   state = 1 - state;
}
if(state == 1){
   point ++;
}*/

//Serial.println(val);
    
    /*
    while(output == true &&  pins[randNum - 3] == HIGH){
      pushcnt_Off += 10.0;
    }
    
    if(pushcnt_Off > push_shot){
      point --;
      //pushcnt_Off = 0;
    }*/
  }
    
    pushcnt_On = 0;
    pushcnt_Off = 0;
  cnt = (cnt + 25) % 50;
  delay(0.1);
  if(point <= 0){point = 0;}
    if(onTime >= 3000){onTime = 3000;}
    if(onTime <= 300){onTime = 300;}
}

void loop() {
  
  //Serial.println(output);
   oldTime = currentTime;
  currentTime = millis();

  GameStartManager();
      TimeManager();
  GameEndManager();
}
