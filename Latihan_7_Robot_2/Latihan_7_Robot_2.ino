#include <Encoder.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define tStart 50 /// tombol start

int angleZ_Mpu;

// Pin Motor Kiri (Y)
int r_eny = 39;
int l_eny = 41;
int r_pwmy = 6;
int l_pwmy = 7;

// Pin Motor Kanan (X)
int r_enx = 35;
int l_enx = 37;
int r_pwmx = 4;
int l_pwmx = 5;

int r_enz = 43;
int l_enz = 45;
int r_pwmz = 8;
int l_pwmz = 9;

Encoder myEncoderX(18, 19);
Encoder myEncoderZ(2, 3);



//penendang
const int Relay_pin1 = 47;
const int Relay_pin2 = 49;
const int Relay_pin3 = 51;

int16_t sumbuX = 0;
int16_t sumbuY = 0;


// handling
const int proximityPin = 40;
const int Relay_pin4 = 53;

unsigned long delayStart = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  setup_motor();
  setup_mpu();
  // Serial.println("mulai");
  setup_pin_relay();
  pinMode(tStart, INPUT_PULLUP);
  pinMode(proximityPin, INPUT);  
  berhenti_isi();
  
  setupServo(13, 12);
  
  servo(2, 0);
  delay(300);
  servo(2, 20);
  servo(1, 0);
}


int c = 100;
int d = 100;  



bool ActivatedSystem = false;
bool oper = true;
int JumlahOperan;

// void loop(){
//   unsigned long currentMillis = millis();
//   int proximityValue = digitalRead(proximityPin);
//   long encoderX = myEncoderX.read();
//   long encoderZ = myEncoderZ.read();
//   maju_custom();
//   // perbaikan();
//   // Serial.print(mpu); Serial.print(" || "); Serial.println(encoderZ);
  
//   // perbaikan(mpu);
//   if (digitalRead(tStart) == 0 && ActivatedSystem == false){
//     ActivatedSystem = true;
//     myEncoderX.write(0);
//     Serial.println("Start");
//     c = 0; 
//     JumlahOperan = 4;
//     reset_nilai_PidMpu();
//     delayStart = currentMillis; 
//   }

//   if (digitalRead(tStart) == 0 && ActivatedSystem == true && currentMillis - delayStart >= 300){
//     delayStart = currentMillis;
//     // Serial.println("Stop");
//     c = 200; 
//     stop();
//   }

//   digitalWrite(Relay_pin4, proximityValue == 1 ? HIGH : LOW);

//   switch (c){
//     case 0:
//       if (JumlahOperan == 4 ){isi_keras(); }
//       else {isi_pelan();}
//       oper = true;

//       if(proximityValue == 1){
//         KananKiriBola(currentMillis);
//         delayStart = currentMillis;
//       }
//       if(proximityValue == 0){
//         perbaikan();
//         if(currentMillis - delayStart >= 500){
//           myEncoderZ.write(0);
//           if (JumlahOperan == 4 ){c = 11;delayStart = currentMillis;}
//           else {c = 1;}
          
//         }
//       }
//     break;
    

//     case 1:
//       if (encoderZ < 2000){
//         kanan_mpu();
//         delayStart = currentMillis;
//       }
      
//       else if(encoderZ >= 2000 && proximityValue == 0){
//         perbaikan();
//         if ((proximityValue == 0) && (currentMillis - delayStart >= 300)){
//             berhenti_isi();
//             if (oper == true && JumlahOperan < 4){
//               JumlahOperan += 1;
//               oper = false;
//             }
//             c = 2;
//             delayStart = currentMillis;
            
//         }   
//       }

//     break;
//     case 2:
//       tendang();
//       if((currentMillis - delayStart >= 300) && (proximityValue == 1)){
//         perbaikan();
//         berhenti_isi();
//         delayStart = currentMillis;
//         c = 0;
//       }
//     break;

//     case 11:
      
//       if(proximityValue == 0){
//         int sh = shoot(-70);
//         if (sh == 1){
//           tendang();
//           delayStart = currentMillis;
//           c = 12;
          
//         }
//       }
//     break;

//     case 12:
//       if(currentMillis - delayStart >= 1000 && proximityValue == 1){
//         perbaikan();
//         berhenti_isi();
//       }
//       else{stop();}
//     break;


//     // case 12:
//     //   maju_custom();
//     //   // isi_keras();
//     //   // if (proximityValue == 0){
//     //   //   delayStart = currentMillis;
//     //   //   c = 13;
//     //   // }    
//     // break;
    
//     case 13:
//       // perbaikan();
//       // if ( angleZ_Mpu == 0 || angleZ_Mpu == -1 || angleZ_Mpu == 1){
//       //   tendang();
//       // }

//     break;
//   }

//   if (c == 200){
//     emergency();
//   }
// }


void loop(){
  unsigned long currentMillis = millis();
  int proximityValue = digitalRead(proximityPin);
  long encoderX = myEncoderX.read();
  long encoderZ = myEncoderZ.read();
  // perbaikan();
  // Serial.print(mpu); Serial.print(" || "); Serial.println(encoderZ);
  
  // perbaikan(mpu);
  if (digitalRead(tStart) == 0 && ActivatedSystem == false){
    ActivatedSystem = true;
    Serial.println("Start");
    c = 20; 
    JumlahOperan = 0;
    reset_nilai_PidMpu();
    delayStart = currentMillis; 
  }

  digitalWrite(Relay_pin4, proximityValue == 1 ? HIGH : LOW);

  switch (c){
    case 100:
      perbaikan();
    break;

    case 0:
      if (JumlahOperan == 4 ){isi_keras(); }
      else {isi_pelan();}
      oper = true;

      if(proximityValue == 1){
        KananKiriBola(currentMillis);
        delayStart = currentMillis;
      }
      if(proximityValue == 0){
        perbaikan();
        if(currentMillis - delayStart >= 500){
          myEncoderZ.write(0);
          if (JumlahOperan == 4 ){c = 11;delayStart = currentMillis;}
          else {c = 1;}
          
        }
      }
    break;
    

    case 1:
      if (encoderZ < 1000){
        kanan_mpu();
        delayStart = currentMillis;
      }
      
      else if(encoderZ >= 1000 && proximityValue == 0){
        perbaikan();
        if ((proximityValue == 0) && (currentMillis - delayStart >= 300)){
            // berhenti_isi();
            // if (oper == true && JumlahOperan < 4){
            //   JumlahOperan += 1;
            //   oper = false;
            // }
            // c = 2;
            delayStart = currentMillis;
            
        }   
      }

    break;
    case 2:
      tendang();
      if((currentMillis - delayStart >= 300) && (proximityValue == 1)){
        perbaikan();
        berhenti_isi();
        delayStart = currentMillis;
        c = 0;
      }
    break;

    case 20:
      if (proximityValue == 1){
        maju_custom();
        delayStart = currentMillis; 
      }

      else if(proximityValue == 0){
        motor_HIGH();
        stop();
        if (currentMillis - delayStart >= 5000){
          myEncoderZ.write(0);
          c = 100;
          
        }
        
      }
    break;

    case 21:
      perbaikan();
  }
}

















