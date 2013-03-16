#include <G35String.h>
#include <G35StringGroup.h>
#include <SoftwareSerial.h>

#define PONG_LOOP_RATE 8
#define WAIT_MS (1000/PONG_LOOP_RATE)

#define LCD_P1_AUTO  1
#define LCD_P2_AUTO  0

// Standard Arduino, string 1 on Pin 13, string 2 on Pin 12.
G35String lights_1(8, 35);
G35String lights_2(7, 35);
G35StringGroup string_group;

unsigned char p1_score;
unsigned char p2_score;

SoftwareSerial LCD(2,3);
char line2[17];

void printScore() {
    LCD.write(148); // move to line 1 pos 0
  memset(line2,0,sizeof(line2));
  sprintf(line2,"%02d            %02d", p2_score,p1_score);
  LCD.print(line2);
}

#include "pong.h"
#include "led_utils.h"

void setup() {
  // light board setup
  delay(50);
  lights_1.enumerate();
  lights_2.enumerate();
  delay(50);

  string_group.AddString(&lights_1);
  string_group.AddString(&lights_2);
  
  string_group.fill_color(0,70,0,COLOR_BLACK);
  
  // pong setup
  setupGame();
  
  LCD.begin(9600);
  delay(100);
  LCD.write(12); // Form Feed, clear screen
  delay(100);
  LCD.print("P1    PONG    P2");
  delay(100);

  printScore();
}

void loop() {
    playPong(true);
    delay(WAIT_MS);
}
