#include <G35String.h>
#include <G35StringGroup.h>

// Standard Arduino, string 1 on Pin 13, string 2 on Pin 12.
G35String lights_1(8, 35);
G35String lights_2(7, 35);
G35StringGroup string_group;

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
}

void loop() {
  static bool mode = 1;
  static int counter;
  if (mode == 0) {
    clearscreen();
    scroll_text("Maker Faire",COLOR_RED);
    scroll_text("Detroit",COLOR_BLUE);
    scroll_text("HackPGH",COLOR_YELLOW);
    mode = 1;
  }
  else { 
    playPong(true);
    delay(20);
    playPong(false);
    delay(20);
    playPong(false);
    delay(20);
    playPong(false);
    delay(20);
    playPong(false);
    delay(20);
    if (counter > 60*10) {
      counter = 0;
      // mode = 0;
    } else {
      counter++;
    }
  }
}
