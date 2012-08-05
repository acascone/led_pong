#define XMIN 0
#define XMAX 9

#define YMIN 0
#define YMAX 6

int ball_x = XMAX/2;
int ball_y = YMAX/2;

int ball_tempX = ball_x;
int ball_tempY = ball_y;

int p1_x = XMIN;
int p1_y = YMAX/2;

int p1_tempX = p1_x;
int p1_tempY = p1_y;

int p2_x = XMAX;
int p2_y = YMAX/2;

int p2_tempX = p2_x;
int p2_tempY = p2_y;

int dir;     //This will keep track of the circles direction
//1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

void drawPlayer(int px, int py, color_t p_color) {
  unsigned char c;

  c = (px*7)+(abs( ((px & 0x01 )  ? 6 : 0 )  - py+1));
  string_group.set_color(c,255,p_color);
  c = (px*7)+(abs( ((px & 0x01 )  ? 6 : 0 )  - py));
  string_group.set_color(c,255,p_color);
  c = (px*7)+(abs( ((px & 0x01 )  ? 6 : 0 )  - py-1));
  string_group.set_color(c,255,p_color);
}

void moveBall(){

  ball_tempX = ball_x;
  ball_tempY = ball_y;

  if (dir == 1 && ball_x > XMIN && ball_y > YMIN){
    if( ball_x + 1 == p2_x && (ball_y >= p2_y - 1) && (ball_y <= p2_y + 1)){
      dir = random(2) + 3;
    }
    else{    
      ++ball_x;
      --ball_y;
    }    

  } 
  else if (dir == 2 && ball_x > XMIN && ball_y < YMAX){

    if( ball_x + 1 == p2_x  && (ball_y >= p2_y - 1)&& (ball_y <= p2_y + 1)){
      dir = random(2) + 3;
    }
    else{    
      ++ball_x;
      ++ball_y;
    }

  } 
  else if (dir == 3 && ball_x > XMIN && ball_y > YMIN){
    if( (ball_x == p1_x + 1) && (ball_y >= p1_y - 1) && ( ball_y <= p1_y + 1)){
      dir = random(2) + 1;
    }
    else{    
      --ball_x;
      --ball_y;
    }

  } 
  else if (dir == 4 && ball_x < XMAX && ball_y < YMAX){
    if( (ball_x  == p1_x+ 1) && (ball_y >= p1_y - 1) && (ball_y <= p1_y + 1)){
      dir = random(2) + 1;
    }
    else{    
      --ball_x;
      ++ball_y;
    }

  } 
  else { 

    if (dir == 1 || dir == 3)    ++dir;
    else if (dir == 2 || dir == 4)    --dir;

  }
  unsigned char c;
  c = (ball_tempX*7)+(abs( ((ball_tempX & 0x01 )  ? 6 : 0 )  - ball_tempY));
  string_group.set_color(c,255,COLOR_BLACK);

  c = (ball_x*7)+(abs( ((ball_x & 0x01 )  ? 6 : 0 )  - ball_y));
  string_group.set_color(c,255,COLOR_GREEN);

}    

void p1Move(){
  p1_tempY = p1_y;

  // computer controlled
  //  p1_y = ball_y;

  // player controlled
  p1_y = analogRead(5) * 6 / 1024;

  if      (p1_y <= YMIN) p1_y = YMIN + 1;
  else if (p1_y >= YMAX) p1_y = YMAX - 1;

  drawPlayer(p1_x,p1_tempY, COLOR_BLACK);
  drawPlayer(p1_x,p1_y, COLOR_RED);             
}  

void p2Move(){
  p2_tempY = p2_y;

  // computer controlled
  //p2_y = ball_y;

  // player controlled
  p2_y = analogRead(4) * 6 / 1024;

  if      (p2_y <= YMIN) p2_y = YMIN + 1;
  else if (p2_y >= YMAX) p2_y = YMAX - 1;

  drawPlayer(p2_x,p2_tempY, COLOR_BLACK);
  drawPlayer(p2_x,p2_y, COLOR_BLUE);
}    

void startNew(){
  string_group.fill_color(0,70,0,COLOR_BLACK);
  drawPlayer(p1_x,p1_y, COLOR_RED);
  drawPlayer(p2_x,p2_y, COLOR_BLUE);
  ball_x = XMAX/2;
  ball_y = random(7);
  unsigned char c;
  c = (ball_x*7)+(abs( ((ball_x & 0x01 )  ? 6 : 0 )  - ball_y));
  for (int cnt = 0; cnt < 7; cnt++) {
  delay(20);
  p1Move();
  p2Move();
  delay(20);
  p1Move();
  p2Move();
  string_group.set_color(c,255,COLOR_BLACK);
  delay(20);
  p1Move();
  p2Move();
  delay(20);
  p1Move();
  p2Move();
  string_group.set_color(c,255,COLOR_GREEN);
  }

}    

void checkWin(){

  if ( ball_x <= p1_x){
    Serial.println("Player 2 Wins!");
    string_group.fill_color(0,70,255, COLOR_BLUE);
    delay(250);
    startNew();
  } 
  else if ( ball_x >= p2_x){
    Serial.println("Player 1 Wins!"); 
    string_group.fill_color(0,70,255, COLOR_RED);
    delay(250);
    startNew();
  }    

}

void setupGame(){
  // draw p1
  drawPlayer(p1_x,p1_y, COLOR_RED);
  // draw p2
  drawPlayer(p2_x,p2_y, COLOR_BLUE);
  // draw ball
  ball_y = random(YMAX);
  unsigned char c = (ball_x*7)+(abs( ((ball_x & 0x01 )  ? 6 : 0 )  - ball_y));
  string_group.set_color(c,255,COLOR_GREEN);

  // seed random direction
  dir = random(4) + 1;
}    

void playPong(boolean move_ball) {
  p1Move();
  p2Move();
  if (move_ball) {
    moveBall();
    checkWin();
  }
}

