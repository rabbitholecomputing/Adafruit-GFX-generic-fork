/***********************************
This is a our graphics core library, for all our displays. 
We'll be adapting all the
existing libaries to use this core to make updating, support 
and upgrading easier!

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
****************************************/

/*
 *  Modified by Neal Horman 7/14/2012 for use in mbed
 */

#ifndef _ADAFRUIT_GFX_H_
#define _ADAFRUIT_GFX_H_

#include <string.h>
#include "Adafruit_GFX_Config.h"
#include "gfxfont.h"

static inline void swap(int16_t &a, int16_t &b) {
    int16_t t = a;

    a = b;
    b = t;
}

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

#define BLACK 0
#define WHITE 1


/// A generic graphics superclass that can handle all sorts of drawing. At a
/// minimum you can subclass and provide drawPixel(). At a maximum you can do a
/// ton of overriding to optimize. Used for any/all Adafruit displays!

#ifdef USE_IOABSTRACTION_TCMENU

#include <PrintCompat.h>

class Adafruit_GFX : public Print {
#else
class Adafruit_GFX
{
    public:
        /**
         * Without IoAbstraction at least give the most basic print function, stream has gone and FileHandle just
         * does not look right in code for this type of stuff.
         */
        void print(const char* sz) {
            auto len = strlen(sz);
            for(int i=0;i<len;i++) write(sz[i]);
        }
        void println(const char* sz) {
          print(sz);
          write('\n');
        }
#endif
public:
    Adafruit_GFX(int16_t w, int16_t h); // Constructor

    /**********************************************************************/
    /*!
      @brief  Draw to the screen/framebuffer/etc.
      Must be overridden in subclass.
      @param  x    X coordinate in pixels
      @param  y    Y coordinate in pixels
      @param color  16-bit pixel color.
    */
    /**********************************************************************/
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

    // TRANSACTION API / CORE DRAW API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.
    virtual void startWrite(void);

    virtual void writePixel(int16_t x, int16_t y, uint16_t color);

    virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                               uint16_t color);

    virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

    virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

    virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                           uint16_t color);

    virtual void endWrite(void);

    // CONTROL API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.
    virtual void setRotation(uint8_t r);

    virtual void invertDisplay(bool i);

    // BASIC DRAW API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.

    // It's good to implement those, even if using transaction API
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                          uint16_t color);

    virtual void fillScreen(uint16_t color);

    // Optional and probably not necessary to change
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                          uint16_t color);

    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                          uint16_t color);

    // These exist only with Adafruit_GFX (no subclass overrides)
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
                          uint16_t color);

    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

    void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
                          int16_t delta, uint16_t color);

    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2,
                      int16_t y2, uint16_t color);

    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2,
                      int16_t y2, uint16_t color);

    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                       int16_t radius, uint16_t color);

    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                       int16_t radius, uint16_t color);

    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                    int16_t h, uint16_t color);

    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                    int16_t h, uint16_t color, uint16_t bg);

    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
                    uint16_t color);

    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
                    uint16_t color, uint16_t bg);

    void drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                     int16_t h, uint16_t color);

    void drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                             int16_t w, int16_t h);

    void drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                             int16_t h);

    void drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                             const uint8_t mask[], int16_t w, int16_t h);

    void drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask,
                             int16_t w, int16_t h);

    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w,
                       int16_t h);

    void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w,
                       int16_t h);

    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                       const uint8_t mask[], int16_t w, int16_t h);

    void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask,
                       int16_t w, int16_t h);

    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                  uint16_t bg, uint8_t size);

    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                  uint16_t bg, uint8_t size_x, uint8_t size_y);

    void getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1,
                       int16_t *y1, uint16_t *w, uint16_t *h);

    void setTextSize(uint8_t s);

    void setTextSize(uint8_t sx, uint8_t sy);

    void setFont(const GFXfont *f = nullptr);

    /**********************************************************************/
    /*!
      @brief  Set text cursor location
      @param  x    X coordinate in pixels
      @param  y    Y coordinate in pixels
    */
    /**********************************************************************/
    void setCursor(int16_t x, int16_t y) {
        cursor_x = x;
        cursor_y = y;
    }

    /**********************************************************************/
    /*!
      @brief   Set text font color with transparant background
      @param   c   16-bit 5-6-5 Color to draw text with
      @note    For 'transparent' background, background and foreground
               are set to same color rather than using a separate flag.
    */
    /**********************************************************************/
    void setTextColor(uint16_t c) { textcolor = textbgcolor = c; }

    /**********************************************************************/
    /*!
      @brief   Set text font color with custom background color
      @param   c   16-bit 5-6-5 Color to draw text with
      @param   bg  16-bit 5-6-5 Color to draw background/fill with
    */
    /**********************************************************************/
    void setTextColor(uint16_t c, uint16_t bg) {
        textcolor = c;
        textbgcolor = bg;
    }

    /**********************************************************************/
    /*!
    @brief  Set whether text that is too long for the screen width should
            automatically wrap around to the next line (else clip right).
    @param  w  true for wrapping, false for clipping
    */
    /**********************************************************************/
    void setTextWrap(bool w) { wrap = w; }

    /**********************************************************************/
    /*!
      @brief  Enable (or disable) Code Page 437-compatible charset.
              There was an error in glcdfont.c for the longest time -- one
              character (#176, the 'light shade' block) was missing -- this
              threw off the index of every character that followed it.
              But a TON of code has been written with the erroneous
              character indices. By default, the library uses the original
              'wrong' behavior and old sketches will still work. Pass
              'true' to this function to use correct CP437 character values
              in your code.
      @param  x  true = enable (new behavior), false = disable (old behavior)
    */
    /**********************************************************************/
    void cp437(bool x = true) { _cp437 = x; }


    virtual size_t write(uint8_t);

    /************************************************************************/
    /*!
      @brief      Get width of the display, accounting for current rotation
      @returns    Width in pixels
    */
    /************************************************************************/
    int16_t width(void) const { return _width; };

    /************************************************************************/
    /*!
      @brief      Get height of the display, accounting for current rotation
      @returns    Height in pixels
    */
    /************************************************************************/
    int16_t height(void) const { return _height; }

    /************************************************************************/
    /*!
      @brief      Get rotation setting for display
      @returns    0 thru 3 corresponding to 4 cardinal rotations
    */
    /************************************************************************/
    uint8_t getRotation(void) const { return rotation; }

    // get current cursor position (get rotation safe maximum values,
    // using: width() for x, height() for y)
    /************************************************************************/
    /*!
      @brief  Get text cursor X location
      @returns    X coordinate in pixels
    */
    /************************************************************************/
    int16_t getCursorX(void) const { return cursor_x; }

    /************************************************************************/
    /*!
      @brief      Get text cursor Y location
      @returns    Y coordinate in pixels
    */
    /************************************************************************/
    int16_t getCursorY(void) const { return cursor_y; };

protected:
    void charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx,
                    int16_t *miny, int16_t *maxx, int16_t *maxy);

    int16_t WIDTH;        ///< This is the 'raw' display width - never changes
    int16_t HEIGHT;       ///< This is the 'raw' display height - never changes
    int16_t _width;       ///< Display width as modified by current rotation
    int16_t _height;      ///< Display height as modified by current rotation
    int16_t cursor_x;     ///< x location to start print()ing text
    int16_t cursor_y;     ///< y location to start print()ing text
    uint16_t textcolor;   ///< 16-bit background color for print()
    uint16_t textbgcolor; ///< 16-bit text color for print()
    uint8_t textsize_x;   ///< Desired magnification in X-axis of text to print()
    uint8_t textsize_y;   ///< Desired magnification in Y-axis of text to print()
    uint8_t rotation;     ///< Display rotation (0 thru 3)
    bool wrap;            ///< If set, 'wrap' text at right edge of display
    bool _cp437;          ///< If set, use correct CP437 charset (default is off)
    GFXfont *gfxFont;     ///< Pointer to special font
};

/// A GFX 1-bit canvas context for graphics
class GFXcanvas1 : public Adafruit_GFX {
public:
    GFXcanvas1(uint16_t w, uint16_t h);

    ~GFXcanvas1(void);

    void drawPixel(int16_t x, int16_t y, uint16_t color);

    void fillScreen(uint16_t color);

    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

    bool getPixel(int16_t x, int16_t y) const;
    /**********************************************************************/
    /*!
      @brief    Get a pointer to the internal buffer memory
      @returns  A pointer to the allocated buffer
    */
    /**********************************************************************/
    uint8_t *getBuffer(void) const { return buffer; }

protected:
    bool getRawPixel(int16_t x, int16_t y) const;

    void drawFastRawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

    void drawFastRawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

private:
    uint8_t *buffer;
};

#endif
