// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class AsciiEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    AsciiEye(uint16_t r, bool isLeft)
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

      int x1 = x - 18 + offsetX;
      int y1 = y - 2 + offsetY;
      int x2 = x1;
      int y2 = y1 + 15;
      int w = 38;
      int h = 6;
      spi->fillRect(x1, y1, w, h, primaryColor);
      spi->fillRect(x2, y2, w, h, primaryColor);

    }
  };

  class AsciiEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    AsciiEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

      height = 3;
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

  class AsciiMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    AsciiMouth() : AsciiMouth(0, 0, 0, 0) {}
    AsciiMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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

      float breath = fmin(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      int h = minHeight + (maxHeight - minHeight) * openRatio;
      int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      int x = rect.getLeft();
      int y = rect.getTop();

      int x2 = x*0.71;
      // 口の ω 部分として2つの楕円を描画
      int e_rx = 140;
      int e_ry = y;
      int e_lx = 183;
      int e_ly = y;
      int e_ex = 25;
      int e_ey = 29;
      spi->fillEllipse(e_rx, e_ry, e_ex, e_ey, primaryColor);
      spi->fillEllipse(e_lx, e_ly, e_ex, e_ey, primaryColor);

      // 口の ω を形成するために、少し小さい背景色の楕円を被せる
      int over_e_rx = e_rx;
      int over_e_ry = e_ry;
      int over_e_lx = e_lx;
      int over_e_ly = e_ly;
      int over_e_wx = 18;
      int over_e_wy = 24;
      spi->fillEllipse(over_e_rx, over_e_ry, over_e_wx, over_e_wy, backgroundColor);
      spi->fillEllipse(over_e_lx, over_e_ly, over_e_wx, over_e_wy, backgroundColor);

      // 口の ω を形成するために、楕円の上部に背景色の四角を被せる
      int over_r1_rx = x2 - 5;
      int over_r1_ry = y - 40;
      int over_r1_rw = 105;
      int over_r1_rh = 30;
      spi->fillRect(over_r1_rx, over_r1_ry, over_r1_rw, over_r1_rh, backgroundColor);
      int over_r2_rx = x2 + 35;
      int over_r2_ry = y - 10;
      int over_r2_rw = 25;
      int over_r2_rh = 12;
      spi->fillRect(over_r2_rx, over_r2_ry, over_r2_rw, over_r2_rh, backgroundColor);

    }
  };

  /**
   * Faceクラスを継承したAscii顔描画用のクラス
  */
  class AsciiFace : public Face
  {
  public:
    AsciiFace()
        : Face(new AsciiMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new AsciiEye(8, false),         new BoundingRect(93, 90),
              new AsciiEye(8, true),          new BoundingRect(96, 230),
              new AsciiEyeblow(32, 0, false), new BoundingRect(67, 96),
              new AsciiEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar