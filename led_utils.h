#include "font.h"

void set_col(byte col, byte pattern, byte intesity, color_t color) {
  byte c;
  byte dir = 0;
  if (col & 0x01) dir = 6;
  if (pattern & 0x40) { c = (col*7)+(abs(dir-0)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x20) { c = (col*7)+(abs(dir-1)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x10) { c = (col*7)+(abs(dir-2)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x08) { c = (col*7)+(abs(dir-3)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x04) { c = (col*7)+(abs(dir-4)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x02) { c = (col*7)+(abs(dir-5)); string_group.set_color(c,intesity,color);}
  if (pattern & 0x01) { c = (col*7)+(abs(dir-6)); string_group.set_color(c,intesity,color);}
}

void scroll_sequence(char *seq, byte len, byte intesity, color_t color) {
  for (int p = 0; p < len+10; p++)
  {
    for (int j = 0; j < len; j++) if (((p-j) > -1) && ((p-j) < 10)) set_col(p-j, ((byte)seq[j]) << 1, intesity, color);
    delay(200);
    for (int j = 0; j < len; j++) if (((p-j) > -1) && ((p-j) < 10)) set_col(p-j, (byte)seq[j] << 1, intesity, COLOR_BLACK);
  }
}

void puttinychar(char *seq, char c)
{
  byte dots;
  if (c >= 'A' && c <= 'Z' || (c >= 'a' && c <= 'z') ) {
    c &= 0x1F;   // A-Z maps to 1-26
  } 
  else if (c >= '0' && c <= '9') {
    c = (c - '0') + 31;
  } 
  else if (c == ' ') {
    c = 0; // space
  }
  else if (c == '.') {
    c = 27; // full stop
  }
  else if (c == '\'') {
    c = 28; // single quote mark
  } else if (c == '!') {
    c = 29; // single quote mark
  }  else if (c == '?') {
    c = 30; // single quote mark
  }

  if (c == 0) {*seq++ = 0;}
  else {
    for (char col=0; col< 3; col++)
      *seq++ = pgm_read_byte_near(&mytinyfont[c][col]);
  }
  *seq++ = 0;
  
}

void scroll_text(const char* string, color_t string_color) {
  char scroll_buf[4*50] = {0};
  for (int i = 0; i < strlen(string); i++) puttinychar(scroll_buf+(i*4),string[i]);
  scroll_sequence(scroll_buf,strlen(string)*4,255, string_color);
}

void clearscreen() {
  string_group.fill_color(0,70,0,COLOR_BLACK);
}
