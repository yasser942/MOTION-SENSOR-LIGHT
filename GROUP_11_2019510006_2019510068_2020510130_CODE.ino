#define LED_PIN 11
#define MOTION_PIN 10
// Pins of 7 Segments
const int A = 7;
const int B = 6;
const int C = 3;
const int D = 4;
const int E = 5;
const int F = 8;
const int G = 9;
const int H = 2;
int TIMER_START = 20;
int TIMER_SPEED = 500;
int ANIMATION_SPEED = 200;
void (*functions[16])();                     // Array of functions of 7 segment numbers
int animation_arr[] = { 7, 6, 3, 4, 5, 8 };  // For animation
int index_count = 0;                         // For animation
int temp_time = 0;                           // Animation time
// animation: 7-6-3-4-5-8
void setup() {
  pinMode(MOTION_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  Serial.begin(9600);
}
void animation(int index) {  // Controlling Animation
  for (int i = 0; i < sizeof(animation_arr) / sizeof(int); i++) {
    if (index == i) {
      digitalWrite(animation_arr[i], LOW);
    } else
      digitalWrite(animation_arr[i], HIGH);
  }
  digitalWrite(G, HIGH);
  digitalWrite(H, HIGH);
}
void off() {                          // Turn of the light and 7 segment
  for (int i = 2; i < 10; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(LED_PIN, LOW);
}
// Function of the numbers 0 to F
void zero() {
  for (int i = 2; i < 10; i++) {
    if (i == 9 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void one() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 3)
      digitalWrite(i, LOW);
    else
      digitalWrite(i, HIGH);
  }
}
void two() {
  for (int i = 2; i < 10; i++) {
    if (i == 8 || i == 3 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void three() {
  for (int i = 2; i < 10; i++) {
    if (i == 8 || i == 5 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void four() {
  for (int i = 2; i < 10; i++) {
    if (i == 7 || i == 5 || i == 4 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void five() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 5 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void six() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void seven() {
  for (int i = 2; i < 10; i++) {
    if (i == 7 || i == 3 || i == 6)
      digitalWrite(i, LOW);
    else
      digitalWrite(i, HIGH);
  }
}
void eight() {
  for (int i = 2; i < 10; i++) {
    if (i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void nine() {
  for (int i = 2; i < 10; i++) {
    if (i == 5 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void ten() {
  for (int i = 2; i < 10; i++) {
    if (i == 4 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void eleven() {
  eight();
}
void twelve() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 9 || i == 3 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void thirteen() {
  zero();
}
void fourteen() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 3 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void fifteen() {
  for (int i = 2; i < 10; i++) {
    if (i == 6 || i == 3 || i == 4 || i == 2)
      digitalWrite(i, HIGH);
    else
      digitalWrite(i, LOW);
  }
}
void loop(void) {
  int motion = digitalRead(MOTION_PIN);  // Read PIR sensor
  Serial.println(motion);
  if (motion == HIGH) {                  // If for motion detected
    digitalWrite(LED_PIN, HIGH);         // Turn on LED
    temp_time = 0;
    index_count = 0;
    while (temp_time < (TIMER_START * 1000) - (15 * TIMER_SPEED)) {     // Computing the time until reaching F
      animation(index_count);
      index_count++;
      temp_time += ANIMATION_SPEED;
      delay(ANIMATION_SPEED);               // Speed of leds in animation
      if (index_count == sizeof(animation_arr) / sizeof(int))     
        index_count = 0;
      if ((TIMER_START * 1000) - (15 * TIMER_SPEED) - temp_time <= ANIMATION_SPEED)     // Synchronizing the total animation time with timer start
        break;
    }
    Serial.print(temp_time);
    count();        // Functions for print numbers
  } else
    off();      // Off 7 segment
}
void count() {                    /// Assignings number functions to the indexes.
  functions[0] = zero;
  functions[1] = one;
  functions[2] = two;
  functions[3] = three;
  functions[4] = four;
  functions[5] = five;
  functions[6] = six;
  functions[7] = seven;
  functions[8] = eight;
  functions[9] = nine;
  functions[10] = ten;
  functions[11] = eleven;
  functions[12] = twelve;
  functions[13] = thirteen;
  functions[14] = fourteen;
  functions[15] = fifteen;
  for (int i = 15; i >= 0; i--) {       // Calling each function depending on the index.
    (*functions[i])();
    delay(TIMER_SPEED);
  }
}