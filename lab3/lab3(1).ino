#define E_659 659 // Hz
#define C_523 523 // Hz
#define G_784 784 // Hz
#define g_392 392 // Hz
#define R_0 0 // Rest, play no sound

/*
#define E_659 1516 // 659 Hz
#define C_523 1911 // 523 Hz
#define G_784 1274 // 784 Hz
#define g_392 2550 // 392 Hz
#define R_0 0 // Rest, play no sound
*/

#define set_bit(port, bit) (port |= (1 << bit));
#define clr_bit(port, bit) (port &= ~(1 << bit));

#include<math.h>


unsigned long int time;

int freqToBit(int freq){
  return ((F_CPU / (2 * freq * 8)) - 1);
}


void task_1(unsigned long time){
  if (time % 1000 <= 250) {
    digitalWrite(13, HIGH);
  } else if (time % 1000 <= 999) {
    digitalWrite(13, LOW);
  }
}


int song[] = {E_659, R_0, E_659, R_0, R_0, E_659, R_0, R_0, C_523, R_0, E_659, R_0, R_0, G_784, R_0, R_0, R_0, R_0, R_0, g_392, R_0};

int size = sizeof(song) / 2; // size of song[]. 2 is the size of an int
int i = 0;
char flag2 = 1;

void task_2(unsigned long int time) {
  if ((time < 4000) && (time % 100 < 50) && (flag2)) {
    OCR4A = freqToBit(song[i % size]);
    flag2 = 0;
    i++;
  } else if (time % 100 >= 50) flag2 = 1;
  /*for (i = 0; i < size ; i ++) {
    if ((time % 2100 >= (0 + i * 100)) && (time % 2100 < (100 + i * 100)) && (time % 2100 < 2000)) {
      OCR4A = song[i];
    }
  }*/
}


char leds[] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};
//char leds[] = {0b1101111, 0b1111111, 0b0000111, 0b1111101, 0b1101101, 0b1100110, 0b1001111, 0b1011011, 0b0000110, 0b0111111}; // flipped version oops
char pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // choosing which pins we use for the 7seg
//char pins[] = {3, 6, 7, 1, 5, 15, 16, 17, 18, 23, 24, 25};
char flag3 = 1;
int num3 = 0;

void seg7(int x) {
  char xDigit;
  char xLEDs;
  char xBit;

  digitalWrite(pins[7], 0);
  digitalWrite(pins[8], !0); 
  digitalWrite(pins[9], !0); 
  digitalWrite(pins[10], !0); 
  digitalWrite(pins[11], !0);
  // delay(2);

  for (char i = 0; i < 4; i++) { // iterate through digits of x

    digitalWrite(pins[(i % 4) + 8], !1); digitalWrite(pins[((3 + i) % 4) + 8], !0);
    xDigit = ((int) (x / pow(10, i - 1))) % 10; // extract the i-th digit of x
    xLEDs = leds[xDigit];
    //delay(20);

    for (char j = 0; j < 7; j++) { // iterate through segments of the display
      xBit = (xLEDs >> j) % 2;
      digitalWrite(pins[j], xBit);
      //delay(20);
    }

  }
}

void task_3(unsigned long int time) {
  if ((time < 4000) && (time % 100 < 50) && (flag3)) {
    seg7(num3);
    flag3 = 0;
    num3++;
  } else if (time % 100 >= 50) flag3 = 1;
}


int index = 0;

void task_4(unsigned long int time) {
  if (song[(time / 100) % size] == 0) task_4p1(time);
  else task_4p2(time);
}

void task_4p1(unsigned long int time) {
  int remaining;
  for (remaining = 1; remaining < size; remaining++) {
    if (song[(remaining + (time / 100)) % size] == 0) break;
  }
  seg7(remaining);
}

void task_4p2(unsigned long int time) {
  seg7(song[(time / 100) % size]);
}


void task_5(unsigned long int time) {
  task_1(time);

  if (time < 100 * size) task_2(time);
  else if ((time >= 100 * size) && (time < 100 * size + 3000)) seg7(3 + (100 * size - time) / 1000);
  else if ((time >= 100 * size + 3000) && (time < 200 * size + 3000)) task_2(time - 3000);
  else if ((time >= 200 * size + 3000) && (time < 200 * size + 5000)) { // DISPLAY A :D
    digitalWrite(1, 1); digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, 0);
    digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); digitalWrite(9, 1); digitalWrite(10, 0); digitalWrite(11, 0); // delay(2);

    digitalWrite(2, 1); digitalWrite(1, 0);
    digitalWrite(5, 1); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 1); digitalWrite(9, 0); digitalWrite(10, 0); digitalWrite(11, 0); // delay(2);

    digitalWrite(3, 1); digitalWrite(2, 0);
    digitalWrite(5, 1); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 1); digitalWrite(9, 0); digitalWrite(10, 0); digitalWrite(11, 0); // delay(2);

    digitalWrite(4, 1); digitalWrite(3, 0);
    digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, 1); digitalWrite(8, 0); digitalWrite(9, 0); digitalWrite(10, 0); digitalWrite(11, 0); // delay(2);
  }
  else if ((time < 200 * size + 5000) && (time < 200 * size + 6000)) {
    // turn all the digits off lol, not hard but do this later
  }
  
  if (((time >= 100 * size) && (time < 100 * size + 1000)) || ((time >= 200 * size + 3000) && (time < 200 * size + 4000))) OCR4A = 0;
}



void setup() {
  // set timer 4 mode to CTC
  TCCR4A = 0x00;
  TCCR4B = 0x00;

  // Set to CTC mode
  set_bit(TCCR4B, WGM42);

  // set prescaler to 8
  clr_bit(TCCR4B, CS42);
  set_bit(TCCR4B, CS41);
  clr_bit(TCCR4B, CS40);

  //Toggle compare match
  clr_bit(TCCR4A, COM4A1);
  set_bit(TCCR4A, COM4A0);

  for (int i = 1; i <= 12; i++) pinMode(pins[i], OUTPUT);

  // > debug
  Serial.begin(9600);
  
  // > task 1
  // pinMode(13, OUTPUT);

  // > task 2
  // set_bit(DDRH, DDH3);

  // > task 3
  // UNFINISHED

  // > task 4
  // UNFINISHED, similar to task 3?
}

void loop() {

  time = millis();

  // > debug
  // Serial.println(freqToBit(392));

  // > task 1
  // task_1(time);

  // > task 2
  // task_2(time);

  // > task 3
  task_3(time);

  // > test for task ~3
  //digitalWrite(pins[8], 0); digitalWrite(pins[9], 1); digitalWrite(pins[10], 1); digitalWrite(pins[11], 0);
  //digitalWrite(pins[7], 0);
  //digitalWrite(pins[0], 0); digitalWrite(pins[1], 0); digitalWrite(pins[2], 1); digitalWrite(pins[3], 0); digitalWrite(pins[4], 1); digitalWrite(pins[5], 1); digitalWrite(pins[6], 0);

  // > task 4
  // task_4(time);

  // > task 4
  // task_5(time);

}
