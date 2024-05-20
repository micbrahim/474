/* University of Washington
 * ECE/CSE 474, 5-07-2024
 *
 * Michael Ibrahim
 * Lincoln Lewis
 * Chun Ho Wong
 *
 * Lab 2: Digital I/O and Timing of Outputs
 *
 * Acknowledgments: This is original code unless otherwise noted.
 */

#define BIT_2 1 << 2;
#define BIT_1 1 << 1;
#define BIT_0 1 << 0;


#define set_bit(port, bit) (port |= (1 << bit));
#define clr_bit(port, bit) (port &= ~(1 << bit));


#define c_261 3830 // 261
#define d_294 3400 // 294
#define e_329 3038 // 329
#define f_349 2864 // 349
#define g_329 2550 // 392
#define a_440 2272 // 440
#define b_493 2028 // 493
#define C_523 1912 // 523
#define R_0 0

#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10


// SPI command transfer function for LED matrix
void spiTransfer(volatile byte opcode, volatile byte data);

// Define pins
int DIN = 45;
int CS =  43;
int CLK = 41;

byte spidata[2]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

// global variables
char flag; 
unsigned long int time;


// SPI transfer implementation
void spiTransfer(volatile byte opcode, volatile byte data){
  int offset = 0; //only 1 device
  int maxbytes = 2; //16 bits per SPI command
  
  for(int i = 0; i < maxbytes; i++) { //zero out spi data
    spidata[i] = (byte)0;
  }
  //load in spi data
  spidata[offset+1] = opcode+1;
  spidata[offset] = data;
  digitalWrite(CS, LOW); //
  for(int i=maxbytes;i>0;i--)
    shiftOut(DIN,CLK,MSBFIRST,spidata[i-1]); //shift out 1 byte of data starting with leftmost bit
  digitalWrite(CS,HIGH);
}


int freqToBit(int freq){
 return ((F_CPU / (2 * freq * 8)) - 1);
}

void setup() {
 // put your setup code here, to run once:
 /* // 1.2
 pinMode(47, OUTPUT);
 pinMode(48, OUTPUT);
 pinMode(49, OUTPUT); */ // End 1.2
  // 1.4
 // DDRL |= BIT_2;
 // DDRL |= BIT_1;
 // DDRL |= BIT_0;


 // // Can also do it like this
 // DDRL |= (1<<DDL2);
 // DDRL |= (1<<DDL1);
 // DDRL |= (1<<DDL0); // End 1.4

 // // 2.x
 // set_bit(DDRH, DDH3);


 // // set timer 4 mode to CTC
 // TCCR4A = 0x00;
 // TCCR4B = 0x00;
  // // Set to CTC mode
 // set_bit(TCCR4B, WGM42);


 // // set prescaler to 8
 // clr_bit(TCCR4B, CS42);
 // set_bit(TCCR4B, CS41);
 // clr_bit(TCCR4B, CS40);


 // OCR4A = freqToBit(400); 


 // //Toggle compare match
 // clr_bit(TCCR4A, COM4A1);
 // set_bit(TCCR4A, COM4A0);


 // End 2.x


 // 3.2
 // DDRL |= BIT_2;
 // DDRL |= BIT_1;
 // DDRL |= BIT_0;


 // // Can also do it like this
 // DDRL |= (1<<DDL2);
 // DDRL |= (1<<DDL1);
 // DDRL |= (1<<DDL0);


 // set_bit(DDRH, DDH3);


 // // set timer 4 mode to CTC
 // TCCR4A = 0x00;
 // TCCR4B = 0x00;
  // // Set to CTC mode
 // set_bit(TCCR4B, WGM42);


 // // set prescaler to 8
 // clr_bit(TCCR4B, CS42);
 // set_bit(TCCR4B, CS41);
 // clr_bit(TCCR4B, CS40);


 // OCR4A = freqToBit(400); 


 // //Toggle compare match
 // clr_bit(TCCR4A, COM4A1);
 // set_bit(TCCR4A, COM4A0);


 // end 3.2


 // 3.4
 DDRL |= (1<<DDL2);
 DDRL |= (1<<DDL1);
 DDRL |= (1<<DDL0);
 //trying with CTC mode, which can help us manipulate the on and off time, which translate to frequency later
set_bit(DDRH, DDH3);


 // set timer 4 mode to CTC
 TCCR4A = 0x00;
 TCCR4B = 0x00;
  // Set to CTC mode
 set_bit(TCCR4B, WGM42);


 // set prescaler to 8
 clr_bit(TCCR4B, CS42);
 set_bit(TCCR4B, CS41);
 clr_bit(TCCR4B, CS40);


 //OCR4A = freqToBit(400); 


 //Toggle compare match
 clr_bit(TCCR4A, COM4A1);
 set_bit(TCCR4A, COM4A0);


 // end 3.4

  //4.x
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CS, HIGH);
  spiTransfer(OP_DISPLAYTEST, 0);
  spiTransfer(OP_SCANLIMIT, 7);
  spiTransfer(OP_DECODEMODE, 0);
  spiTransfer(OP_SHUTDOWN, 1);
  Serial.begin(9600); // Start serial communication
  // end 4.x
}

void loop() {
 // put your main code here, to run repeatedly:
 // 1.2
 /* digitalWrite(49, LOW);
 digitalWrite(47, HIGH);
 delay(333);


 digitalWrite(47, LOW);
 digitalWrite(48, HIGH);
 delay(333);


 digitalWrite(48, LOW);
 digitalWrite(49, HIGH);
 delay(333); */ // End 1.2




 // // 1.4
 // PORTL &= !BIT_0;
 // PORTL |=  BIT_2;
 // delay(333);


 // PORTL &= !BIT_2;
 // PORTL |=  BIT_1;
 // delay(333);


 // PORTL &= !BIT_1;
 // PORTL |=  BIT_0;
 // delay(333); // End 1.4




  // 2.x


 // OCR4A = freqToBit(400); // 400 Hz
 // delay(1000); // Wait 1 second
 // OCR4A = freqToBit(250); // 250 Hz
 // delay(1000); // Wait 1 second
 // OCR4A = freqToBit(800); // 800 Hz
 // delay(1000); // Wait 1 second
 // // stop for a second
 // OCR4A = 0;
 // delay(1000); // Wait 1 second


 // 3.2
 // time = millis() % 17000;
 // taskC(time);
 // end 3.x


 /* // 3.4
 time = millis() % 17000;
 part3_4_taskC(time);
 // end 3.4 */


  // 4.x
  time = millis() % 17000;
  part3_4_taskC(time);
  part4_task(time);
  // end 4.x
}

void clearLED() {
 PORTL &= !BIT_0;
 PORTL &= !BIT_1;
 PORTL &= !BIT_2;
}

void clearSpeaker() {
 OCR4A = 0;
}


/***************************************************
 * void modified_taskA(unsigned long period)
 * Argument1: period - Current system time modulo some large period to determine LED state changes.
 *
 * Cycles through LED states based on the current period in milliseconds. This function
 * controls three LEDs using a specific sequence within one second intervals.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void modified_taskA(unsigned long period){
 if (period % 1000 <= 333) {
   PORTL &= !BIT_0;
   PORTL |=  BIT_2;
 } else if (period % 1000 <= 667) {
   PORTL &= !BIT_2;
   PORTL |=  BIT_1;
 } else if (period % 1000 < 999) {
   PORTL &= !BIT_1;
   PORTL |=  BIT_0;
 } else {
   clearLED();
 }
}

/***************************************************
 * void modified_taskB(unsigned long period)
 * Argument1: period - Current system time in milliseconds, adjusted to repeat every 17 seconds.
 *
 * Modulates the speaker output frequency based on the specific time ranges within the 17-second
 * cycle, using predefined frequencies for varied audible tones.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void modified_taskB(unsigned long period){
 // when modified_taskB() is called, period is already 2000. So we can set period < 3000
 if ((period < 3000) || ((period >=8000) && (period<=9000)) || ((period >=12000) &&(period<=13000))) {
   OCR4A = freqToBit(400);
 } else if ((period < 4000) || ((period >=9000) && (period<=10000)) || ((period >=13000) && (period<=14000))){
   OCR4A = freqToBit(250);
 } else if ((period < 5000)|| ((period >= 10000) && (period<=11000)) || ((period >=14000) && (period<=15000))){
   OCR4A = freqToBit(800);
 } else if ((5000 < period)|| ((period>=11000) && (period<=12000)) || ((period >=15000) && (period<=16000))){
   clearSpeaker();
 }
}

/***************************************************
 * void taskC(unsigned long int period)
 * Argument1: period - Current system time in milliseconds, structured to control tasks over a
 *                     17-second repeating cycle.
 *
 * Orchestrates two sub-tasks (modified_taskA and modified_taskB) to perform complex
 * light and sound sequences based on the ongoing period. Clears speaker and LED states
 * at the cycle's end.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void taskC(unsigned long int period) {
 clearSpeaker();
 period = millis() % 17000;
 if (period < 2000) {
   modified_taskA(period);
 } else if ((2000 <= period) && (period < 6000)) {
   modified_taskB(period);
 }
 else if ((6000 <= period) && (period < 16000)) {
   modified_taskA(period);
   modified_taskB(period);
 }
 else if (period >= 16000) {
   clearSpeaker();
   clearLED();
 }
}

/***************************************************
 * void part3_4_taskB(unsigned long int period)
 * Argument1: period - Current time in milliseconds, adjusted to manage tone generation in a musical pattern.
 *
 * Generates a sequence of musical notes based on specific time intervals, alternating between notes
 * and rests, effectively creating a melody line using timer-based frequency output.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void part3_4_taskB(unsigned long int period) {
 if ((period < 2250)) {
   OCR4A = e_329;
 } else if (period < 2300){
   OCR4A = R_0;
 } else if (period < 2550){
   OCR4A = d_294;
 } else if (period < 2600){
   OCR4A = R_0;
 } else if (period < 2850){
   OCR4A = c_261;
 } else if (period < 2900){
   OCR4A = R_0;
 } else if (period < 3150){
   OCR4A = d_294;
 } else if (period < 3200){
   OCR4A = R_0;
 } else if (period < 3450){
   OCR4A = e_329;
 } else if (period < 3500){
   OCR4A = R_0;
 } else if (period < 3750){
   OCR4A = e_329;
 } else if (period < 3800){
   OCR4A = R_0;
 } else if (period < 4300){
   OCR4A = e_329;
 } else if (period < 4350){
   OCR4A = R_0;
 } else if (period < 4600){
   OCR4A = d_294;
 } else if (period < 4650){
   OCR4A = R_0;
 } else if (period < 4900){
   OCR4A = d_294;
 } else if (period < 4950){
   OCR4A = R_0;
 } else if (period < 5450){
   OCR4A = d_294;
 } else if (period < 5500){
   OCR4A = R_0;
 } else if (period < 5750){
   OCR4A = e_329;
 } else if (period < 5800){
   OCR4A = R_0;
 } else if (period < 6050){
   OCR4A = g_329;
 } else if (period < 6100){
   OCR4A = R_0;
 } else if (period < 6600){
   OCR4A = g_329;
 } else if (period < 6650){
   OCR4A = R_0;
 } else if (period < 6900){
   OCR4A = e_329;
 } else if (period < 6950){
   OCR4A = R_0;
 } else if (period < 7200){
   OCR4A = d_294;
 } else if (period < 7250){
   OCR4A = R_0;
 } else if (period < 7500){
   OCR4A = c_261;
 } else if (period < 7550){
   OCR4A = R_0;
 } else if (period < 7800){
   OCR4A = d_294;
 } else if (period < 7850){
   OCR4A = R_0;
 } else if (period < 8100){
   OCR4A = e_329;
 } else if (period < 8150){
   OCR4A = R_0;
 } else if (period < 8400){
   OCR4A = e_329;
 } else if (period < 8450){
   OCR4A = R_0;
 } else if (period < 8700){
   OCR4A = e_329;
 } else if (period < 8750){
   OCR4A = R_0;
 } else if (period < 9000){
   OCR4A = e_329;
 } else if (period < 9050){
   OCR4A = R_0;
 } else if (period < 9300){
   OCR4A = d_294;
 } else if (period < 9350){
   OCR4A = R_0;
 } else if (period < 9600){
   OCR4A = d_294;
 } else if (period < 9650){
   OCR4A = R_0;
 } else if (period < 9900){
   OCR4A = e_329;
 } else if (period < 9950){
   OCR4A = R_0;
 } else if (period < 10200){
   OCR4A = d_294;
 } else if (period < 10250){
   OCR4A = R_0;
 } else if (period < 11250){
   OCR4A = c_261;
 } else{
   clearSpeaker();
 }
}

/***************************************************
 * void part3_4_taskC(unsigned long int period)
 * Argument1: period - Current system time modulo a slightly extended period (22.3 seconds) to manage a
 *                     more complex sequence of tasks.
 *
 * Controls a complex sequence of light and sound tasks, repeating over a 22.3-second cycle,
 * integrating both LED control and musical output through sub-task coordination.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void part3_4_taskC(unsigned long int period) {
 period = millis() % 22300;
 if (period < 2000) {
   modified_taskA(period);
 } else if ((2000 <= period) && (period < 11300)) {
   part3_4_taskB(period);
 }
 else if ((11300 <= period) && (period <= 21300)) {
   modified_taskA(period);
   part3_4_taskB(period - 9250);
 }
 else if (period >= 21300) {
   clearSpeaker();
   clearLED();
 }
}

/***************************************************
 * void part4_task(int period)
 * Argument1: period - Current system time in milliseconds, used to manage visual display updates
 *                     on an LED grid.
 *
 * Controls visual updates on an LED grid based on thumbstick input. The function reads analog
 * inputs to determine positions and updates the grid accordingly. The grid is cleared and redrawn
 * at specific intervals based on the thumbstick's position.
 *
 * Authors: Michael Ibrahim, Lincoln Lewis, Chun Ho Wong
 */
void part4_task(int period) {
  if (period % 50 >= 25) flag = 1;
  if (flag && (period % 50 < 25)) {
    // Clear the grid
    for (int i = 0; i < 8; i++){
      spiTransfer(i, 0b00000000);
    }
    flag = 0;
      // Setup spiTransfer function
    spiTransfer(OP_DISPLAYTEST,0);
    spiTransfer(OP_SCANLIMIT,7);
    spiTransfer(OP_DECODEMODE,0);
    spiTransfer(OP_SHUTDOWN,1);

    // Read the analog inputs from the thumbstick
    int x_value = analogRead(A0) / 128;
    int y_value = analogRead(A1) / 128;

    // Convert the y coordinate to a 8-bit value
    unsigned char y_coordinate = 0b00000000;
    y_coordinate |= (1 << y_value);

    // Update the grid
    spiTransfer(x_value, y_coordinate);
  }
}


