// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class Girl1Eye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    Girl1Eye(uint16_t r, bool isLeft)
        : r{r}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getCenterX();
      uint32_t y = rect.getCenterY();
      Gaze g = ctx->getGaze();
      float openRatio = ctx->getEyeOpenRatio();
      uint32_t offsetX = g.getHorizontal() * 3;
      uint32_t offsetY = g.getVertical() * 3;
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? 0 : ctx->getColorPalette()->get(COLOR_BACKGROUND);

          uint16_t eyeColor = 0;
          eyeColor = M5.Lcd.color565(196,64,178);

//          int by = y - 15;
//          int ey = y - 3;
          int by = y - 12;
          int ey = y;
          int offset_eye = 5;
          if (!isLeft)
          {
            int rx = x + offset_eye;
            int erx = rx + 5;
            // まつ毛
            spi->fillTriangle(rx-15, by-25, rx-5, by-7, rx+10, by-10, TFT_BLACK);
            spi->fillEllipse(rx , by, 40, 15, TFT_BLACK);
            spi->fillEllipse(rx , by+10, 50, 14, backgroundColor);
            spi->fillEllipse(rx-38 , by, 8, 13, TFT_BLACK);
            spi->fillTriangle(rx-48, by-25, rx-48, by+15, rx-28, by+15, backgroundColor);
            // 瞳
            spi->fillEllipse(erx-1, ey, 18, 23, eyeColor);
            spi->fillEllipse(erx, ey, 13, 20, backgroundColor);
            spi->fillEllipse(erx, ey, 11, 17, eyeColor);
            spi->fillEllipse(erx, ey, 8, 13, backgroundColor);
            spi->fillEllipse(erx, ey, 6, 11, eyeColor);
            spi->fillEllipse(erx, ey, 4, 6, backgroundColor);
            // 上まつ毛の被せ
            spi->fillArc(rx, by+55, 62, 70, 250, 290, TFT_BLACK);
            // 下まつ毛のスライス
            spi->fillRect(rx-15, by+32, 30, 10, backgroundColor);
          }
          else
          {
            int lx = x - offset_eye;
            int elx = lx - 5;
            // まつ毛
            spi->fillTriangle(lx+15, by-25, lx+5, by-7, lx-10, by-10, TFT_BLACK);
            spi->fillEllipse(lx , by, 40, 15, TFT_BLACK);
            spi->fillEllipse(lx , by+10, 50, 14, backgroundColor);
            spi->fillEllipse(lx+38 , by, 8, 13, TFT_BLACK);
            spi->fillTriangle(lx+48, by-25, lx+48, by+15, lx+28, by+15, backgroundColor);
            // 瞳
            spi->fillEllipse(elx+1, ey, 18, 23, eyeColor);
            spi->fillEllipse(elx, ey, 13, 20, backgroundColor);
            spi->fillEllipse(elx, ey, 11, 17, eyeColor);
            spi->fillEllipse(elx, ey, 8, 13, backgroundColor);
            spi->fillEllipse(elx, ey, 6, 11, eyeColor);
            spi->fillEllipse(elx, ey, 4, 6, backgroundColor);
            // 上まつ毛の被せ
            spi->fillArc(lx, by+55, 62, 70, 250, 290, TFT_BLACK);
            // 下まつ毛のスライス
            spi->fillRect(lx-15, by+32, 30, 10, backgroundColor);
          }

    }
  };

  class Girl1Eyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    Girl1Eyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

/**
        new Girl1Eyeblow(32, 0, false), new BoundingRect(67, 96),
        new Girl1Eyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
*/

        int x1, y1, x2, y2, x3, y3;
        x1 = isLeft ? x + 30 : x - 36;// (60) 96 : 230
        x2 = isLeft ? x1 - 78 : x1 + 78;
        x3 = isLeft ? x1 - 78 : x1 + 78;
        y1 = isLeft ? y -36 : y -31; // (33) 67 : 72
        y2 = y1 - 9;
        y3 = y1 - 5;
        spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);

    }
  };

  class Girl1Mouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    Girl1Mouth() : Girl1Mouth(0, 0, 0, 0) {}
    Girl1Mouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      float breath = fmin(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      int h = minHeight + (maxHeight - minHeight) * openRatio;
      int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      int x = rect.getLeft() - w / 2;
      int y = rect.getTop() - h / 2 + breath * 2;

      int gx = x + minWidth/3*2;
      int gy = y + 12;
      int gw = minWidth/3;
      int gh = minHeight + (maxHeight - minHeight) * openRatio;
      spi->fillRect(gx, gy, gw, gh, primaryColor);
    }
  };

  /**
   * Faceクラスを継承したGirl1顔描画用のクラス
  */
  class Girl1Face : public Face
  {
  public:
    Girl1Face()
        : Face(new Girl1Mouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new Girl1Eye(8, false),         new BoundingRect(93, 90),
              new Girl1Eye(8, true),          new BoundingRect(96, 230),
              new Girl1Eyeblow(32, 0, false), new BoundingRect(67, 96),
              new Girl1Eyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar