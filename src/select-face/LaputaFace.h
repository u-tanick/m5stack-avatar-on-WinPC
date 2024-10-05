// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class LaputaEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    LaputaEye(uint16_t r, bool isLeft)
        : r{r}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

      uint32_t cx = rect.getCenterX();
      uint32_t cy = rect.getCenterY();

      uint32_t r1 = r * 1.3;
      uint32_t r2 = r * 1.47;

      spi->fillCircle(cx, cy, r2, TFT_BLACK);
      spi->fillCircle(cx, cy, r1, TFT_LIGHTGREY);

      // Happy, Angry, Sad, Doubt, Sleepy, Neutral
      if (exp == Expression::Neutral)
      {
        spi->fillCircle(cx, cy, r, TFT_BLACK);
      }
      else if (exp == Expression::Angry)
      {
        spi->fillCircle(cx, cy, r, TFT_RED);
      }
      else if (exp == Expression::Sleepy)
      {
      spi->fillCircle(cx, cy, r, TFT_PURPLE);
      }
      else if (exp == Expression::Happy)
      {
        spi->fillCircle(cx, cy, r, TFT_MAGENTA);
      }
      else if (exp == Expression::Sad)
      {
        spi->fillCircle(cx, cy, r, TFT_BLUE);
      }
      else
      {
        spi->fillCircle(cx, cy, r, TFT_DARKGREY); // Doubt
      }
    }
  };

  class LaputaMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    LaputaMouth() : LaputaMouth(0, 0, 0, 0) {}
    LaputaMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);
      float openRatio = ctx->getMouthOpenRatio();

      // darkkhaki / #BDB76B
      uint16_t basefaceColor = 0;
      basefaceColor = M5.Lcd.color565(189,183,107);

      // Left : N : 14
      // Top  : 96
      // 2r   : 81
      // r    : 41
      // x   : N + 40
      // y   : 96 + 40
      uint32_t x1 = 54;
      uint32_t y1 = 136;
      uint32_t r1 = 41;
      spi->fillCircle(x1, y1, r1, basefaceColor);

      // Left : EX : 154
      // Top  : 31
      // 2r   : 149
      // r    : 75
      // x   : EX + 74
      // y   : 31 + 74
      uint32_t x2 = 228;
      uint32_t y2 = 105;
      uint32_t r2 = 75;
      spi->fillCircle(x2, y2, r2, basefaceColor);

      // Left : Z : 26
      // Top  : 136
      // 2rx   : 247
      // 2ry   : 51
      // rx   : 124
      // ry   : 26
      // x   : 26 + 124 -1
      // y   : 136 + 26 -1
      uint32_t x3 = 149;
      uint32_t y3 = 161;
      uint32_t rx = 124;
      uint32_t ry = 28;
      spi->fillEllipse(x3, y3, rx, ry, basefaceColor);

      // t0 : AL99 : tx0, ty0 : 38, 99
      // t1 : GQ73 : tx1, ty1 : 199, 37
      // t2 : GQ99 : tx2, ty2 : 199, 99
      uint32_t tx0 = 38;
      uint32_t ty0 = 98;
      uint32_t tx1 = 199;
      uint32_t ty1 = 35;
      uint32_t tx2 = 199;
      uint32_t ty2 = 98;
      spi->fillTriangle(tx0, ty0, tx1, ty1, tx2, ty2, basefaceColor);

      // r0 : BF99 : rx0, ry0 : 58, 99
      uint32_t rx0 = 58;
      uint32_t ry0 = 98;
      uint32_t rw0 = 105;
      uint32_t rh0 = 38;
      spi->fillRoundRect(rx0, ry0, rw0, rh0, 0, basefaceColor);

      // m1 : EV110 : mx0, my1 : 152, 110
      // m2 : EV168 : mx0, my2 : 152, 165
      uint32_t mx0 = 152;
      uint32_t my1 = 110;
      uint32_t my2 = 165;
      uint32_t mr0 = 6;
      if (exp == Expression::Angry)
      {
        spi->fillCircle(mx0, my1, mr0, TFT_RED);
        spi->fillCircle(mx0, my2, mr0, TFT_RED);
      }
      else
      {
        if (openRatio > 0.3) {
          spi->fillCircle(mx0, my1, mr0, TFT_RED);
          spi->fillCircle(mx0, my2, mr0, TFT_RED);
        } else {
          spi->fillCircle(mx0, my1, mr0, backgroundColor);
          spi->fillCircle(mx0, my2, mr0, backgroundColor);
        }
      }

      // e0 : GV183 : ex0, ey0 : 204, 187
      uint32_t ex0 = 204;
      uint32_t ey0 = 187;
      uint32_t er0 = 10;
      spi->fillCircle(ex0, ey0, er0, backgroundColor);
    }
  };

  /**
   * Faceクラスを継承したラピュタロボット顔描画用のクラス
  */
  class LaputaFace : public Face
  {
  public:
    LaputaFace()
        : Face(new LaputaMouth(), new BoundingRect(74, 136),
               new LaputaEye(17, false), new BoundingRect(133, 58),
               new LaputaEye(30, true), new BoundingRect(92, 237),
               new Eyeblow(32, 0, false), new BoundingRect(67, 96),
               new Eyeblow(32, 0, true), new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar