int perbaikan(){
  int a = loop_mpu();
  
  if(a < -1){
        putar_kiri();
        // delayStart = currentMillis;
      }
  if(a == 0 || a == -1 || a == 1 ){
      stop();
      return 1;
        
    }
  if(a > 1){
        putar_kanan();
        // delayStart = currentMillis;
    }
}

int shoot(int derajat){
  int a = loop_mpu();
  
  if(a < derajat - 1){
        putar_kiri();
        return 0;
        // delayStart = currentMillis;
      }
  if(a == derajat || a == derajat - 1 || a == derajat + 1 ){
      stop();
      return 1;
        
    }
  if(a > derajat + 1){
        putar_kanan();
        return 0;
        // delayStart = currentMillis;
    }
}




// void maju_custom(int roda_x, int roda_y){
//     analogWrite(l_pwmx, roda_x); /// roda kanan maju
//     analogWrite(r_pwmy, roda_y); /// roda kiri maju
    
    
//     analogWrite(r_pwmx, 0);
//     analogWrite(l_pwmy, 0);
    
//     analogWrite(l_pwmz, 0);
//     analogWrite(r_pwmz, 0);
// }