// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class DanboEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    DanboEye(uint16_t r, bool isLeft)
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

      // 目の位置とサイズ調整、左右の高さをそろえる修正
      int dnb_r = 18;
      if (isLeft == true) {
        y = y - 3;
      }
      y = y - 10 + dnb_r;

      if (openRatio > 0) {
        spi->fillCircle(x + offsetX, y + offsetY, dnb_r, primaryColor);
        // TODO(meganetaaan): Refactor
        if (exp == Expression::Angry || exp == Expression::Sad) {
          int x0, y0, x1, y1, x2, y2;
          x0 = x + offsetX - dnb_r;
          y0 = y + offsetY - dnb_r;
          x1 = x0 + dnb_r * 2;
          y1 = y0;
          x2 = !isLeft != !(exp == Expression::Sad) ? x0 : x1;
          y2 = y0 + dnb_r;
          spi->fillTriangle(x0, y0, x1, y1, x2, y2, backgroundColor);
        }
        if (exp == Expression::Happy || exp == Expression::Sleepy) {
          int x0, y0, w, h;
          x0 = x + offsetX - dnb_r;
          y0 = y + offsetY - dnb_r;
          w = dnb_r * 2 + 4;
          h = dnb_r + 2;
          if (exp == Expression::Happy) {
            y0 += dnb_r;
            spi->fillCircle(x + offsetX, y + offsetY, dnb_r / 1.5, backgroundColor);
          }
          spi->fillRect(x0, y0, w, h, backgroundColor);
        }
      } else {
        int x1 = x - dnb_r + offsetX;
        int y1 = y - 2 + offsetY;
        int w = dnb_r * 2;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }
    }
  };

  class DanboEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    DanboEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      /* Nothing*/
    }
  };

  class DanboMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    DanboMouth() : DanboMouth(0, 0, 0, 0) {}
    DanboMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      float openRatio = ctx->getMouthOpenRatio();

      int w0 = 53;
      int h0 = 33;
      int x0 = rect.getLeft() - w0/2;
      int y0 = rect.getTop() + 42;
      int x1 = x0 + w0;
      int y1 = y0;
      int x2 = x0 + w0/2;
      int y2 = y0 - h0*(openRatio/1.5 + 0.75);
      spi->fillTriangle(x0, y0, x1, y1, x2, y2, primaryColor);
    }
  };

  /**
   * Faceクラスを継承したDanbo顔描画用のクラス
  */
  class DanboFace : public Face
  {
  public:
    DanboFace()
        : Face(new DanboMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new DanboEye(8, false),         new BoundingRect(93, 90),
              new DanboEye(8, true),          new BoundingRect(96, 230),
              new DanboEyeblow(32, 0, false), new BoundingRect(67, 96),
              new DanboEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar