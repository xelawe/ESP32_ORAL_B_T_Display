/*
  This sketch is the same as the Font_Demo_1 example, except the fonts in this
  example are in a FLASH (program memory) array. This means that processors
  such as the STM32 series that are not supported by a SPIFFS library can use
  smooth (anti-aliased) fonts.
*/

/*
  There are four different methods of plotting anti-aliased fonts to the screen.

  This sketch uses method 1, using tft.print() and tft.println() calls.

  In some cases the sketch shows what can go wrong too, so read the comments!

  The font is rendered WITHOUT a background, but a background colour needs to be
  set so the anti-aliasing of the character is performed correctly. This is because
  characters are drawn one by one.

  This method is good for static text that does not change often because changing
  values may flicker. The text appears at the tft cursor coordinates.

  It is also possible to "print" text directly into a created sprite, for example using
  spr.println("Hello"); and then push the sprite to the screen. That method is not
  demonstrated in this sketch.

*/

//  A processing sketch to create new fonts can be found in the Tools folder of TFT_eSPI
//  https://github.com/Bodmer/TFT_eSPI/tree/master/Tools/Create_Smooth_Font/Create_font

//  This sketch uses font files created from the Noto family of fonts:
//  https://www.google.com/get/noto/

//#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

// The font names are arrays references, thus must NOT be in quotes ""
//#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();

int act_angle = 0;
int old_angle;
