void KananKiriBola(unsigned long currentMillis){
  baca_serial();
  if (sumbuX > 0 && sumbuX <= 200) {  
    kiri_mpu();
    delayStart = currentMillis;
    // _kiri2();
  }
  if (sumbuX > 200 && sumbuX < 365) {  
    // putar_kiri();
    // kiri_compas();
    // _kiri2();
    kiri_mpu();
    delayStart = currentMillis;
  }
        
  if (sumbuX >= 365 && sumbuX <=435 || sumbuX == 0) {  
    stop();
    if (currentMillis - delayStart >= 500){
        perbaikan();
    }
  }
  if (sumbuX > 435 && sumbuX < 600) {  
    // putar_kiri();
    // kiri_compas();
    // _kanan2();
    kanan_mpu();
    delayStart = currentMillis;
  }
        
  if (sumbuX >= 600 && sumbuX < 800) {  
    // putar_kanan();
    // _kanan2();
    kanan_mpu();
    delayStart = currentMillis;
  }


}





void cari_bola() {
  baca_serial();
    
  if (sumbuX >= 350 && sumbuX <=450) {  
    stop();
  }
  if (sumbuX > 0 && sumbuX < 350) {  
    putar_kiri();
    // kiri_compas();
  }
        
  if (sumbuX > 450 && sumbuX < 800) {  
    putar_kanan();
    // kanan_compas();
  }
  
}


// void maju_bola(){
//   baca_serial();
//   if (sumbuX > 0 && sumbuX <= 200) {  
//     kiri_mpu(mpu);
//     delayStart = currentMillis;
//     // _kiri2();
//   }
//   if (sumbuX > 200 && sumbuX < 365) {  
//     // putar_kiri();
//     // kiri_compas();
//     // _kiri2();
//     kiri_mpu(mpu);
//     delayStart = currentMillis;
//   }
        
//   if (sumbuX >= 365 && sumbuX <=435 || sumbuX == 0) {  
//     stop();
//     if (currentMillis - delayStart >= 500){
//         perbaikan(mpu);
//     }
//   }
//   if (sumbuX > 435 && sumbuX < 600) {  
//     // putar_kiri();
//     // kiri_compas();
//     // _kanan2();
//     kanan_mpu(mpu);
//     delayStart = currentMillis;
//   }
        
//   if (sumbuX >= 600 && sumbuX < 800) {  
//     // putar_kanan();
//     // _kanan2();
//     kanan_mpu(mpu);
//     delayStart = currentMillis;
//   }
// }