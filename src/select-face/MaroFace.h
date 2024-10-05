// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class MaroEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    MaroEye(uint16_t r, bool isLeft)
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


      int eye_rx = x + 10;
      int eye_lx = x - 10;
      int eye_y = y;
      int eye_r = 30;
      int offset_1 = 10;
      int offset_2 = 10;
      int offset_3 = 15;
      if (!isLeft)
      {
        spi->fillTriangle(eye_rx-eye_r, eye_y-eye_r, eye_rx-eye_r, eye_y+eye_r, eye_rx+eye_r, eye_y, primaryColor);
        spi->fillTriangle(eye_rx-eye_r, eye_y-eye_r+offset_1, eye_rx-eye_r, eye_y+eye_r-offset_2, eye_rx+eye_r-offset_3, eye_y, backgroundColor);
      }
      else
      {
        spi->fillTriangle(eye_lx+eye_r, eye_y-eye_r, eye_lx+eye_r, eye_y+eye_r, eye_lx-eye_r, eye_y, primaryColor);
        spi->fillTriangle(eye_lx+eye_r, eye_y-eye_r+offset_1, eye_lx+eye_r, eye_y+eye_r-offset_2, eye_lx-eye_r+offset_3, eye_y, backgroundColor);
      }
    }
  };

  class MaroEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    MaroEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

      int mx = isLeft ? x-7 : x;
      int my = y - 20;
      int rx = 16;
      int ry = 10;
      int x_offset = isLeft ? -23 : 23;
      int y_offset = isLeft ? -12 : -7;
      spi->fillEllipse(mx+x_offset, my+y_offset, rx, ry, primaryColor);

    }
  };

  class MaroMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    MaroMouth() : MaroMouth(0, 0, 0, 0) {}
    MaroMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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

//      spi->fillRect(x, y, w, h, primaryColor);

      uint16_t doubtMouthColor = 0;
      doubtMouthColor = M5.Lcd.color565(255,180,220);
      int dy = y -20;
      spi->fillRoundRect(x, dy, w, 40, 20, doubtMouthColor);
      spi->fillRoundRect(x, dy+10, w, 30, 10, doubtMouthColor);
      int ex = x + w/2;
      int ey = dy;
      spi->fillEllipse(ex, ey-2, 20, 3, backgroundColor);
      spi->fillEllipse(ex, ey+40, 30, 3, backgroundColor);
    }
  };

  /**
   * Faceクラスを継承したMaro顔描画用のクラス
  */
  class MaroFace : public Face
  {
  public:
    MaroFace()
        : Face(new MaroMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new MaroEye(8, false),         new BoundingRect(93, 90),
              new MaroEye(8, true),          new BoundingRect(96, 230),
              new MaroEyeblow(32, 0, false), new BoundingRect(67, 96),
              new MaroEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar