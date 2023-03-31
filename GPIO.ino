//GPIO
/*
 * D4 - // Обратная связь от переключателя модема
 * D3 - // переключение модема
 * 
 * 
 */

  const int d4_GPIO_pin = 4; // Обратная связь от переключателя модема
  const int d3_GPIO_pin = 3; // переключение модема
  const int d2_GPIO_pin = 2; // Обработка кнопки
  const int a3_GPIO_pin = A3;
  const int a2_GPIO_pin = A2;
  const int a1_GPIO_pin = A1;
  const int a0_GPIO_pin = A0;

void gpioInit(){
  
  pinMode(d4_GPIO_pin,  INPUT);
  pinMode(d3_GPIO_pin, OUTPUT);
  pinMode(d2_GPIO_pin, INPUT_PULLUP); // подтягиваем кнопку к HIGH
  pinMode(a3_GPIO_pin, OUTPUT);
  pinMode(a2_GPIO_pin, OUTPUT);
  pinMode(a1_GPIO_pin, OUTPUT);
  pinMode(a0_GPIO_pin, OUTPUT);

  digitalWrite(d3_GPIO_pin, HIGH); //Включаем М1 по умолчанию
  digitalWrite(a3_GPIO_pin, LOW);
  digitalWrite(a2_GPIO_pin, LOW);
  digitalWrite(a1_GPIO_pin, LOW);
  digitalWrite(a0_GPIO_pin, LOW);
}

void modemSwichWatcher(){
  //коммутация модема
  if(globalState[10] == 1){
    modemSwitch(1);
  } else if(globalState[10] == 2){
    modemSwitch(2);
  }else{
    globalState[10] = 1;
  }

  // состояние обратной связи
  if(digitalRead(d4_GPIO_pin)){
    globalState[10] = 1;
  }else{
    globalState[10] = 0;
  }
}

void modemButtonSwitchWatcher(){

  static unsigned long t = 0;
  static bool buttonPressFlag = false;
  static bool buttonPressFlag_2 = false;
  const int timePressButton = 200;
  if(!digitalRead(d2_GPIO_pin)){
    if(!buttonPressFlag){
      t = millis();
      buttonPressFlag = true;
    }else if(millis() - t > timePressButton && !buttonPressFlag_2){

      if(globalState[11] == 2){
        globalState[11] = 1;
      }else{
        globalState[11]++; 
      }
      
      buttonPressFlag_2 = true;
    }  
  }else{
    buttonPressFlag = false;
    buttonPressFlag_2 = false;
  }
  
}


void watchDogStopReboot(){
  static bool flagInit = false;
  if(!flagInit){
    pinMode(a0_GPIO_pin, INPUT);
    digitalWrite(a0_GPIO_pin, HIGH);
    flagInit = true;
  }else{
    if(digitalRead(a0_GPIO_pin) == LOW){
      globalState[9] = 1;
    }else{
      globalState[9] = 0;
    }
  }
}


void modemSwitch(int M){
  switch (M){
    case 1:
     digitalWrite(d3_GPIO_pin, HIGH);
    break;
    case 2:
     digitalWrite(d3_GPIO_pin, LOW);
    break;
  }
};
