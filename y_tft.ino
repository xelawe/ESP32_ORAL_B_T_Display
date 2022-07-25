void init_tft( ) {
  tft.begin();

  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour AND the background colour
  // so the anti-aliasing works

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // Large font
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  tft.loadFont(AA_FONT_LARGE); // Load another different font


}

void display_data( ) {
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.setCursor(0, 50);
  tft.print(oralb_mode);
  tft.print(" ");
  // tft.print(oralb_quadrant_percentage);
  // tft.print(" %  ");
  tft.setCursor(0, 90);
  tft.print(oralb_time_min);
  tft.print(":");
  tft.print(oralb_time_sec);
  tft.print("   ");

  // Draw a segmented ring meter type display
  // Centre of screen
  int cx = tft.width()  / 2 + 50;
  int cy = tft.height() / 2;

  // Inner and outer radius of ring
  float r1 = min(cx, cy) - 20.0;
  float r2 = min(cx, cy) - 10.0;

  // Inner and outer line width
  int w1 = r1 / 35;
  int w2 = r2 / 30;

  // The following will be updated by the getCoord function
  float px1 = 0.0;
  float py1 = 0.0;
  float px2 = 0.0;
  float py2 = 0.0;

  old_angle = act_angle;
  act_angle = oralb_quadrant;
  if (act_angle == 0) {
    act_angle = 1;
  }
  act_angle = ((act_angle - 1) * 90) - 90 + map(oralb_quadrant_percentage, 0, 100, 0, 84);

  // Wedge line function, an anti-aliased wide line between 2 points, with different
  // line widths at the two ends. Background colour is black.
  for (int angle = -90 ; angle <= -6; angle += 1) {
    getCoord(cx, cy, &px1, &py1, &px2, &py2, r1, r2, angle);
    uint16_t colour = TFT_BLUE; //rainbow(map(angle, -130, 130, 0, 127));
    if (angle > act_angle) colour = TFT_DARKGREY;
    tft.drawWedgeLine(px1, py1, px2, py2, w1, w2, colour, colour);
  }

  for (int angle = 0; angle <= 84; angle += 1) {
    getCoord(cx, cy, &px1, &py1, &px2, &py2, r1, r2, angle);
    uint16_t colour = TFT_BLUE; //rainbow(map(angle, -130, 130, 0, 127));
    if (angle > act_angle) colour = TFT_DARKGREY;
    tft.drawWedgeLine(px1, py1, px2, py2, w1, w2, colour, colour);
  }

  for (int angle = 90; angle <= 174; angle += 1) {
    getCoord(cx, cy, &px1, &py1, &px2, &py2, r1, r2, angle);
    uint16_t colour = TFT_BLUE; //rainbow(map(angle, -130, 130, 0, 127));
    if (angle > act_angle) colour = TFT_DARKGREY;
    tft.drawWedgeLine(px1, py1, px2, py2, w1, w2, colour, colour);
  }

  for (int angle = 180; angle <= 264; angle += 1) {
    getCoord(cx, cy, &px1, &py1, &px2, &py2, r1, r2, angle);
    uint16_t colour = TFT_BLUE; //rainbow(map(angle, -130, 130, 0, 127));
    if (angle > act_angle) colour = TFT_DARKGREY;
    tft.drawWedgeLine(px1, py1, px2, py2, w1, w2, colour, colour);
  }

  if (act_angle != old_angle) {
    // Smooth black filled circle
    tft.fillSmoothCircle(cx, cy, r1 - 8, TFT_BLACK, TFT_BLACK);
  }

  // Draw a white dial pointer using wedge line function
  getCoord(cx, cy, &px1, &py1, &px2, &py2, 0, r1 - 10, act_angle);
  // Line tapers from radius 5 to zero
  tft.drawWedgeLine(cx, cy, px2, py2, 5, 0, TFT_WHITE, TFT_BLACK);
}


// =========================================================================
// Get coordinates of two ends of a line from r1 to r2, pivot at x,y, angle a
// =========================================================================
// Coordinates are returned to caller via the xp and yp pointers
#define DEG2RAD 0.0174532925
void getCoord(int16_t x, int16_t y, float *xp1, float *yp1, float *xp2, float *yp2, int16_t r1, int16_t r2, float a)
{
  float sx = cos( (a - 90) * DEG2RAD);
  float sy = sin( (a - 90) * DEG2RAD);
  *xp1 =  sx * r1 + x;
  *yp1 =  sy * r1 + y;
  *xp2 =  sx * r2 + x;
  *yp2 =  sy * r2 + y;
}
