// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class KappaEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    KappaEye(uint16_t r, bool isLeft)
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
        // 目が開いているとき
        int x0 = x - r + offsetX;
        int y0 = y - 2 + offsetY;
        int w = r;
        int h = 44;
        spi->fillRect(x0, y0, w, h, primaryColor);
      } else {
        // 目をつむったとき
        int x1 = x - r*1.5 + offsetX;
        int y1 = y + 24 + offsetY;
        int w = r * 4;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }

    }
  };

  class KappaEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    KappaEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

      int x1, y1, x2, y2, x3, y3;
      height = 30;
      y = y - 22;
      if (isLeft) {
        y = y - 4;
        x1 = x + width*0.6;
        height = height + 3;
      } else {
        x1 = x - width;
      }
      x2 = x - width*1.5;
      x3 = x + width*0.9;
      y1 = y;
      y2 = y + height;
      y3 = y + height;
      spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
    }
  };

  class KappaMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    KappaMouth() : KappaMouth(0, 0, 0, 0) {}
    KappaMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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

      int h = 25;
      int w = 64;
      int x = rect.getLeft() - 8;
      int y = rect.getTop() + 20;
      spi->fillEllipse(x, y, w, h, TFT_RED);

      int edge_x1_l = x-w-5;
      int edge_x2_l = x-w+7;
      int edge_x3_l = x-w+7;
      int edge_x1_r = x+w+5;
      int edge_x2_r = x+w-7;
      int edge_x3_r = x+w-7;
      int edge_y1 = y;
      int edge_y2 = y+h/2;
      int edge_y3 = y-h/2;
      spi->fillTriangle(edge_x1_l, edge_y1, edge_x2_l, edge_y2, edge_x3_l, edge_y3, TFT_RED);
      spi->fillTriangle(edge_x1_r, edge_y1, edge_x2_r, edge_y2, edge_x3_r, edge_y3, TFT_RED);

      spi->drawLine(edge_x1_l, edge_y1, edge_x1_r, edge_y1, TFT_BLACK);
      int offset_y = 14;
      int philtrum_w = 14;
      int philtrum_h = 20;
      int x1_ptm = x;
      int x2_ptm = x - philtrum_w;
      int x3_ptm = x + philtrum_w;
      int y1_ptm = y - offset_y;
      int y23_ptm = y - philtrum_w - offset_y;
      spi->fillTriangle(x1_ptm, y1_ptm, x2_ptm, y23_ptm, x3_ptm, y23_ptm, backgroundColor);
    }
  };

  /**
   * Faceクラスを継承したKappa顔描画用のクラス
  */
  class KappaFace : public Face
  {
  public:
    KappaFace()
        : Face(new KappaMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new KappaEye(8, false),         new BoundingRect(93, 90),
              new KappaEye(8, true),          new BoundingRect(96, 230),
              new KappaEyeblow(32, 0, false), new BoundingRect(67, 96),
              new KappaEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar