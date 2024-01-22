#include <IRremote.h>
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define buton1 16753245
#define buton2 16736925
#define buton3 16769565
#define buton4 16720605
#define buton5 16712445


void setup() {
Serial.begin(9600);
irrecv.enableIRIn();

}

void loop() {
  if(Serial.available()){
    char num = Serial.read();
    if(num == '1'){
      while(1){
        if(irrecv.decode(&results)){
          if(results.value == buton1){
            Serial.write('0');
            irrecv.resume();
            break;
          }
          if(results.value == buton2){
            Serial.write('1');
            irrecv.resume();
            break;
          }
          if(results.value == buton3){
            Serial.write('2');
            irrecv.resume();
            break;
          }
          if(results.value == buton4){
            Serial.write('3');
            irrecv.resume();
            break;
          }
          if(results.value == buton5){
            Serial.write('4');
            irrecv.resume();
            break;
          }
          irrecv.resume();
        }
      }
    }

    }
  }

