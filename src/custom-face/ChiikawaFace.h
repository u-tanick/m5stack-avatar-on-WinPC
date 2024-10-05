// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class ChiikawaEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    ChiikawaEye(uint16_t r, bool isLeft)
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

      // 黒目全体
      int x0 = isLeft ? x - 17 : x + 19;
      int y0 = isLeft ? y - 3 + 20 : y - 1 + 20;
      int r0 = 18;
      spi->fillCircle(x0 + offsetX, y0 + offsetY, r0, primaryColor);
      // 下の三日月
      int x1 = x0;
      int y1 = y0 + 4;
      int r1x = 12;
      int r1y = 10;
      spi->fillEllipse(x1 + offsetX, y1 + offsetY, r1x, r1y, backgroundColor);
      // 上の白目の枠
      int x2 = x0;
      int y2 = y0;
      int r2x = 15;
      int r2y = 11;
      spi->fillEllipse(x2 + offsetX, y2 + offsetY, r2x, r2y, primaryColor);
      // 上の白目
      int x3 = x0;
      int y3 = y0 - 4;
      int r3x = 13;
      int r3y = 10;
      spi->fillEllipse(x3 + offsetX, y3 + offsetY, r3x, r3y, backgroundColor);
    }
  };

  class ChiikawaEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    ChiikawaEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

      int h0 = 6;
      int w0 = isLeft ? 38 : 42;
      int x_offset = 2;
      int y_offset = -25;
      int x0 = isLeft ? x - x_offset*3 : x;
      int y0 = isLeft ? y + y_offset - 8 : y + y_offset - 2;
      y0 = y0 + 20;

      int x1, y1, x2, y2, x3, y3, x4, y4;
      int a = isLeft ? 1 : -1;
      int dx = a * 5;
      int dy = a * 5;
      x1 = isLeft ? x0 - w0 / 2 : x0 - w0 / 2;
      x2 = isLeft ? x1 - x_offset  : x1 + x_offset;
      x4 = isLeft ? x0 + w0 / 2 : x0 + w0 / 2;
      x3 = isLeft ? x4 + x_offset  : x4 - x_offset;
      y1 = y0 - h0 / 2 - dy;
      y2 = y0 + h0 / 2 - dy;
      y3 = y0 - h0 / 2 + dy;
      y4 = y0 + h0 / 2 + dy;
      spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
      spi->fillTriangle(x2, y2, x3, y3, x4, y4, primaryColor);
    }
  };

  class ChiikawaMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    ChiikawaMouth() : ChiikawaMouth(0, 0, 0, 0) {}
    ChiikawaMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? 0 : ctx->getColorPalette()->get(COLOR_BACKGROUND);
      float breath = fmin(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      int h = minHeight + (maxHeight - minHeight) * openRatio;
      int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      int x = rect.getLeft() - w / 2;
      int y = rect.getTop() - h / 2 + breath * 2;

      int x0 = rect.getLeft();
      int y0 = rect.getTop() + 20;

      // 口
      uint32_t mx = x0;
      uint32_t my = y0 - 10;
      uint32_t mrx = 10 +  6 * openRatio;
      uint32_t mry = 28 * openRatio;
      spi->fillEllipseArc(mx, my, 0, mrx, 0, mry, 0, 180, primaryColor);
      spi->fillEllipseArc(mx, my, 0, mrx-5, 0, mry-5, 0, 180, TFT_RED);

      // まずる
      int ag0r = -30;
      int ag1r = 150;
      int ag0l = 30;
      int ag1l = 210;
      int irx = 11;
      int iry = 15;
      int orx = 16;
      int ory = 20;
      int cxr = x0 - (orx - (orx - irx)/2);
      int cyr = y0 - 18;
      int cxl = x0 + (orx - (orx - irx)/2);
      int cyl = y0 - 18;
      spi->fillEllipseArc(cxr, cyr, 0, irx, 0, iry, ag0r, ag1r, backgroundColor);
      spi->fillEllipseArc(cxl, cyl, 0, irx, 0, iry, ag0l, ag1l, backgroundColor);
      spi->fillEllipseArc(cxr, cyr, irx, orx, iry, ory, ag0r, ag1r, primaryColor);
      spi->fillEllipseArc(cxl, cyl, irx, orx, iry, ory, ag0l, ag1l, primaryColor);
      spi->fillRect(x0-5, y0-30, 10, 10, backgroundColor);
      // 下唇
      int xsk = x0 - 8;
      int ysk = y0 + 8  + 18 * openRatio;
      spi->fillRect(xsk, ysk, 16, 4, primaryColor);

      uint16_t cheekColor = 0;
      cheekColor = M5.Lcd.color565(250,180,200);
      // 右ほほ
      int chk_x0r = x0 - 90;
      int chk_y0r = y0 - 20;
      int chk_rx = 25;
      int chk_ry = 16;
      spi->fillEllipse(chk_x0r, chk_y0r, chk_rx, chk_ry, cheekColor);
      // 左ほほ
      int chk_x0l = x0 + 90;
      int chk_y0l = chk_y0r;
      spi->fillEllipse(chk_x0l, chk_y0l, chk_rx, chk_ry, cheekColor);

      // 右ほほのスラッシュ３つ
      int x1a = chk_x0r;
      int x2a = x1a - 5;
      int x3a = x1a;
      int x4a = x1a + 5;
      int y1a = chk_y0r - 13;
      int y2a = y1a + 18;
      int y3a = y2a + 3;
      int y4a = y3a - 18;
      spi->fillTriangle(x1a, y1a, x2a, y2a, x3a, y3a, primaryColor);
      spi->fillTriangle(x1a, y1a, x3a, y3a, x4a, y4a, primaryColor);

      int x1b = chk_x0r - 13;
      int x2b = x1b - 5;
      int x3b = x1b;
      int x4b = x1b + 5;
      int y1b = chk_y0r - 10;
      int y2b = y1b + 18;
      int y3b = y2b + 3;
      int y4b = y3b - 18;
      spi->fillTriangle(x1b, y1b, x2b, y2b, x3b, y3b, primaryColor);
      spi->fillTriangle(x1b, y1b, x3b, y3b, x4b, y4b, primaryColor);

      int x1c = chk_x0r + 13;
      int x2c = x1c - 5;
      int x3c = x1c;
      int x4c = x1c + 5;
      int y1c = chk_y0r - 10;
      int y2c = y1c + 18;
      int y3c = y2c + 3;
      int y4c = y3c - 18;
      spi->fillTriangle(x1c, y1c, x2c, y2c, x3c, y3c, primaryColor);
      spi->fillTriangle(x1c, y1c, x3c, y3c, x4c, y4c, primaryColor);

      // 左ほほのスラッシュ３つ
      x1a = chk_x0l;
      x2a = x1a - 5;
      x3a = x1a;
      x4a = x1a + 5;
      y1a = chk_y0l - 13;
      y2a = y1a + 18;
      y3a = y2a + 3;
      y4a = y3a - 18;
      spi->fillTriangle(x1a, y1a, x2a, y2a, x3a, y3a, primaryColor);
      spi->fillTriangle(x1a, y1a, x3a, y3a, x4a, y4a, primaryColor);

      x1b = chk_x0l - 13;
      x2b = x1b - 5;
      x3b = x1b;
      x4b = x1b + 5;
      y1b = chk_y0l - 10;
      y2b = y1b + 18;
      y3b = y2b + 3;
      y4b = y3b - 18;
      spi->fillTriangle(x1b, y1b, x2b, y2b, x3b, y3b, primaryColor);
      spi->fillTriangle(x1b, y1b, x3b, y3b, x4b, y4b, primaryColor);

      x1c = chk_x0l + 13;
      x2c = x1c - 5;
      x3c = x1c;
      x4c = x1c + 5;
      y1c = chk_y0l - 10;
      y2c = y1c + 18;
      y3c = y2c + 3;
      y4c = y3c - 18;
      spi->fillTriangle(x1c, y1c, x2c, y2c, x3c, y3c, primaryColor);
      spi->fillTriangle(x1c, y1c, x3c, y3c, x4c, y4c, primaryColor);
    }
  };

  /**
   * Faceクラスを継承したChiikawa顔描画用のクラス
  */
  class ChiikawaFace : public Face
  {
  public:
    ChiikawaFace()
        : Face(new ChiikawaMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new ChiikawaEye(8, false),         new BoundingRect(93, 90),
              new ChiikawaEye(8, true),          new BoundingRect(96, 230),
              new ChiikawaEyeblow(32, 0, false), new BoundingRect(67, 96),
              new ChiikawaEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar