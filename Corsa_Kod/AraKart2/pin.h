const int butonLeft = PA3;
const int butonRight = PA6;
const int switchLeft = PB9;
const int switchLeftRight = PA2;
const int switchRight = PB5;
const int switchRightLeft = PB8;

void pin_setup(){
  pinMode(butonLeft, INPUT_PULLUP);
  pinMode(butonRight, INPUT_PULLUP);
  pinMode(switchLeft, INPUT_PULLUP);
  pinMode(switchLeftRight, INPUT_PULLUP);
  pinMode(switchRight, INPUT_PULLUP);
  pinMode(switchRightLeft, INPUT_PULLUP);
}

/*
Servo1 PB0
Servo2 PB1
CANTX1 PA12
CANRX1 PA11
gps için TX1 RX1  PA9 PA10
ivme için SCL2 SDA2 PB10 PB11
sıcaklık için SCL1 SDA1 PB6 PB7
röle için PA1
*/


// butonlar, ekran, ekrandaki bilgiler alinacak
// rpm, temps, fuel, //sicaklik sensoruna bakilip baglanacak
// hiz, fren bilgisi //pedal baglaninca fren bilgisi girilecek
// butonlar ayarlanacak tek tek
// anahtarli switch eklenecek
// joystick eklenecek galiba