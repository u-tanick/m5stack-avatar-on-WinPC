// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class MeganeEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    MeganeEye(uint16_t r, bool isLeft)
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

      int mgn_r1 = 24;
      int mgn_r2 = 22;
      int mgn_r3 = 18;
      int mgn_r4 = 16;
      if (openRatio > 0) {
        spi->fillCircle(x + offsetX, y + offsetY, mgn_r1, TFT_BLACK);
        spi->fillCircle(x + offsetX, y + offsetY, mgn_r2, TFT_WHITE);
        spi->fillCircle(x + offsetX, y + offsetY, mgn_r3, TFT_BLACK);
        spi->fillCircle(x + offsetX, y + offsetY, mgn_r4, TFT_WHITE);
      } else {
        int x1 = x - mgn_r1 + offsetX;
        int y1 = y - 2 + offsetY;
        int w = mgn_r1 * 2;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }
    }
  };

  class MeganeEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    MeganeEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);

      int fix_pos_y = isLeft? -5 : 0;
      spi->drawRoundRect(x-55, y-8+fix_pos_y, 100, 70, 20, TFT_RED);
      spi->fillRect(x+45, y+22+fix_pos_y, 35, 5, TFT_RED);
      spi->fillRect(x-90, y+22+fix_pos_y, 35, 5, TFT_RED);

    }
  };

  class MeganeMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    MeganeMouth() : MeganeMouth(0, 0, 0, 0) {}
    MeganeMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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

      x = x + 22;
      spi->fillEllipse(x, y, 12, 8, primaryColor);
      spi->fillEllipse(x, y, 10, 6, backgroundColor);
      spi->fillEllipse(x, y+15, 12, 8, primaryColor);
      spi->fillEllipse(x, y+15, 10, 6, backgroundColor);
      spi->fillEllipse(x+10, y+1, 10, 6, backgroundColor);
      spi->fillEllipse(x+10, y+12, 10, 6, backgroundColor);
    }
  };

  /**
   * Faceクラスを継承したMegane顔描画用のクラス
  */
  class MeganeFace : public Face
  {
  public:
    MeganeFace()
        : Face(new MeganeMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new MeganeEye(8, false),         new BoundingRect(93, 90),
              new MeganeEye(8, true),          new BoundingRect(96, 230),
              new MeganeEyeblow(32, 0, false), new BoundingRect(67, 96),
              new MeganeEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar