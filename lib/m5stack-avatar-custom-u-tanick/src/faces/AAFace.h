// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef FACES_AAFACE_H_
#define FACES_AAFACE_H_

#include <M5Unified.h> // TODO(meganetaaan): include only the Sprite function not a whole library
#include "../BoundingRect.h"
#include "../DrawContext.h"
#include "../Drawable.h"

namespace m5avatar
{

  class AAEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    AAEye(uint16_t r, bool isLeft)
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
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

      // eyetype-test-code
      uint16_t et = ctx->getEyeType();
      if(et==0){ r = r;}
      else {r = r*2;}

      if (openRatio > 0)
      {
        if (exp == Expression::Happy)
        {
          y -= 15;
        }
        spi->fillCircle(x + offsetX, y + offsetY, r, primaryColor);
        if (exp == Expression::Happy || exp == Expression::Sleepy)
        {
          int x0, y0, w, h;
          x0 = x + offsetX - r;
          y0 = y + offsetY - r;
          w = r * 2 + 4;
          h = r + 2;
          if (exp == Expression::Happy)
          {
            y0 += r;
            spi->fillCircle(x + offsetX, y + offsetY, r / 1.5, backgroundColor);
          }
          spi->fillRect(x0, y0, w, h, backgroundColor);
        }
      }
      else
      {
        int x1 = x - r + offsetX;
        int y1 = y - 2 + offsetY;
        int w = r * 2;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }
    }
  };

  /**
    * 
    * 
    * 
    * 
  */
  class AAEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    AAEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      if (width == 0 || height == 0)
      {
        return;
      }
      // draw two triangles to make rectangle
      if (exp == Expression::Neutral || exp == Expression::Sad)
      {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        int a = isLeft ^ (exp == Expression::Sad) ? -1 : 1;
        int dx = a * 3;
        int dy = a * 5;
        x1 = x - width / 2;
        x2 = x1 - dx;
        x4 = x + width / 2;
        x3 = x4 + dx;
        y1 = y - height / 2 - dy;
        y2 = y + height / 2 - dy;
        y3 = y - height / 2 + dy;
        y4 = y + height / 2 + dy;
        spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
        spi->fillTriangle(x2, y2, x3, y3, x4, y4, primaryColor);
      }
    }
  };

  /**
   * 
   * 
   * 
  */
  class AAMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    AAMouth() : AAMouth(0, 0, 0, 0) {}
    AAMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();

      // speech mode
      float openRatio = ctx->getMouthOpenRatio();
      uint32_t h = (minHeight + (maxHeight - minHeight) * openRatio)*pow(cos(openRatio), 3.0)*2.5;
      uint32_t mx = 162;
      uint32_t my = 120;
      uint32_t mrx = 13;
      if (h > minHeight) {
        spi->fillEllipse(mx, my, mrx, h, TFT_RED);
      }

      uint32_t offset_y = 0;

      // 口の ω 部分として2つの楕円を描画
      uint32_t rx = 150;
      uint32_t lx = 173;
      uint32_t ry = 103 - offset_y;
      uint32_t ly = 103 - offset_y;

      uint32_t erx = 15;
      uint32_t ery = 19;

      spi->fillEllipse(rx, ry, erx, ery, primaryColor);
      spi->fillEllipse(lx, ly, erx, ery, primaryColor);

      // 口の ω を形成するために、少し小さい背景色の楕円を被せる
      uint32_t over_rx = 150;
      uint32_t over_lx = 173;
      uint32_t over_ry = 102 - offset_y;
      uint32_t over_ly = 102 - offset_y;

      uint32_t over_erx = 9;
      uint32_t over_ery = 15;

      spi->fillEllipse(over_rx, over_ry, over_erx, over_ery, backgroundColor);
      spi->fillEllipse(over_lx, over_ly, over_erx, over_ery, backgroundColor);

      // 口の ω を形成するために、楕円の上部に背景色の四角を被せる
      uint32_t r1x = x + 2;
      uint32_t r2x = x + 9;
      uint32_t r3x = x + 15;
      uint32_t r4x = x + 29;

      uint32_t r1y = y - offset_y;
      uint32_t r2y = y + 11 - offset_y;
      uint32_t r3y = y + 22 - offset_y;
      uint32_t r4y = y + 22 - offset_y;

      uint32_t r1w = 48;
      uint32_t r2w = 34;
      uint32_t r3w = 8;
      uint32_t r4w = 8;

      uint32_t r1h = 16;
      uint32_t r2h = 11;
      uint32_t r3h = 8;
      uint32_t r4h = 8;

      spi->fillRect(r1x, r1y, r1w, r1h, backgroundColor);
      spi->fillRect(r2x, r2y, r2w, r2h, backgroundColor);
      spi->fillRect(r3x, r3y, r3w, r3h, backgroundColor);
      spi->fillRect(r4x, r4y, r4w, r4h, backgroundColor);
    }
  };

  /**
   * Faceクラスを継承したAA顔描画用のクラス
  */
  class AAFace : public Face
  {
  public:
    AAFace()
        : Face(new AAMouth(), new BoundingRect(74, 136),
               new AAEye(8, false), new BoundingRect(93, 90),
               new AAEye(8, true), new BoundingRect(96, 230),
               new AAEyeblow(18, 3, false), new BoundingRect(71, 50),
               new AAEyeblow(18, 3, true), new BoundingRect(73, 270)) {}
  };

} // namespace m5avatar

#endif // FACES_AAFACE_H_
