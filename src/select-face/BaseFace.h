// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class BaseEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    BaseEye(uint16_t r, bool isLeft)
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

      if (openRatio > 0) {
        spi->fillCircle(x + offsetX, y + offsetY, r, primaryColor);
        // TODO(meganetaaan): Refactor
        if (exp == Expression::Angry || exp == Expression::Sad) {
          int x0, y0, x1, y1, x2, y2;
          x0 = x + offsetX - r;
          y0 = y + offsetY - r;
          x1 = x0 + r * 2;
          y1 = y0;
          x2 = !isLeft != !(exp == Expression::Sad) ? x0 : x1;
          y2 = y0 + r;
          spi->fillTriangle(x0, y0, x1, y1, x2, y2, backgroundColor);
        }
        if (exp == Expression::Happy || exp == Expression::Sleepy) {
          int x0, y0, w, h;
          x0 = x + offsetX - r;
          y0 = y + offsetY - r;
          w = r * 2 + 4;
          h = r + 2;
          if (exp == Expression::Happy) {
            y0 += r;
            spi->fillCircle(x + offsetX, y + offsetY, r / 1.5, backgroundColor);
          }
          spi->fillRect(x0, y0, w, h, backgroundColor);
        }
      } else {
        int x1 = x - r + offsetX;
        int y1 = y - 2 + offsetY;
        int w = r * 2;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }
    }
  };

  class BaseEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    BaseEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);
      if (width == 0 || height == 0) {
        return;
      }
      // draw two triangles to make rectangle
      if (exp == Expression::Angry || exp == Expression::Sad) {
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
      } else {
        int x1 = x - width / 2;
        int y1 = y - height / 2;
        if (exp == Expression::Happy) {
          y1 = y1 - 5;
        }
        spi->fillRect(x1, y1, width, height, primaryColor);
      }
    }
  };

  class BaseMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    BaseMouth() : BaseMouth(0, 0, 0, 0) {}
    BaseMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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
      spi->fillRect(x, y, w, h, primaryColor);
    }
  };

  /**
   * Faceクラスを継承したBase顔描画用のクラス
  */
  class BaseFace : public Face
  {
  public:
    BaseFace()
        : Face(new BaseMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new BaseEye(8, false),         new BoundingRect(93, 90),
              new BaseEye(8, true),          new BoundingRect(96, 230),
              new BaseEyeblow(32, 0, false), new BoundingRect(67, 96),
              new BaseEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar