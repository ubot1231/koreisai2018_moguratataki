void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 2; i < 8; i++) {
//9〜13pinまでをInputとして使用
pinMode (i + 7, INPUT);
//2〜7pinまでをOutputとして使用
pinMode(i, OUTPUT);
}
}

void aaa(){
  long time_m = millis();
  //Serial.println(time_m);
}

void loop() {
  // put your main code here, to run repeatedly:

  aaa();

  Serial.println(digitalRead(2));
  
}
