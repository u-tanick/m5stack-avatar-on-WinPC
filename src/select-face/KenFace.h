// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{

  class KenEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    KenEye(uint16_t r, bool isLeft)
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

/**
 * LX : 90
 * RX : 230
*/
      int x0 = isLeft ? x - 35 : x - 40;
      int y0 = y - 8;
//      spi->fillRect(x0, y0, 1, 1, TFT_RED);
      int w0 = 80;
      int w1 = 75;
      // 瞳
      int x0e = isLeft ? x0 - 3 : x0 + 3;
      spi->fillEllipse(x0e + w0/2, y0 + 10, 18, 10, primaryColor);
      spi->fillEllipse(x0e + w0/2 - 7, y0 + 8, 7, 5, backgroundColor);
      spi->fillEllipse(x0e + w0/2 + 9, y0 + 8, 5, 3, backgroundColor);
      // 瞼
      spi->fillRect(x0, y0, w0, 5, primaryColor);
      int x01 = isLeft ? x0 + 5 : x0;
      // 二重
      spi->fillRect(x01, y0-8, w1, 3, primaryColor);
      int x02 = isLeft ? x01 - 5  : x01 + 5;
      // 目の下
      spi->fillRect(x02, y0+22, w1, 3, primaryColor);

      if (!isLeft) {
        // 目じり
        int x1e1 = x0;
        int x2e1 = x0 - 10;
        int x3e1 = x0 - 8;
        int y1e1 = y0;
        int y2e1 = y0 + 12;
        int y3e1 = y0 + 15;
        spi->fillTriangle(x1e1, y1e1, x2e1, y2e1, x3e1, y3e1, primaryColor);
        int x1e2 = x3e1;
        int x2e2 = x1e1;
        int x3e2 = x1e1 + 2;
        int y1e2 = y3e1;
        int y2e2 = y1e1;
        int y3e2 = y1e1 + 3;
        spi->fillTriangle(x1e2, y1e2, x2e2, y2e2, x3e2, y3e2, primaryColor);
        // 涙点
        int x1t1 = x0 + w0;
        int x2t1 = x0 + w0 + 10;
        int x3t1 = x0 + w0 + 8;
        int y1t1 = y0;
        int y2t1 = y0 + 17;
        int y3t1 = y0 + 20;
        spi->fillTriangle(x1t1, y1t1, x2t1, y2t1, x3t1, y3t1, primaryColor);
        int x1t2 = x3t1;
        int x2t2 = x1t1;
        int x3t2 = x1t1 - 2;
        int y1t2 = y3t1;
        int y2t2 = y1t1;
        int y3t2 = y1t1 + 3;
        spi->fillTriangle(x1t2, y1t2, x2t2, y2t2, x3t2, y3t2, primaryColor);
      } else {
        // 目じり
        x0 = x0 + w0;
        int x1e1 = x0;
        int x2e1 = x0 + 10;
        int x3e1 = x0 + 8;
        int y1e1 = y0;
        int y2e1 = y0 + 12;
        int y3e1 = y0 + 15;
        spi->fillTriangle(x1e1, y1e1, x2e1, y2e1, x3e1, y3e1, primaryColor);
        int x1e2 = x3e1;
        int x2e2 = x1e1;
        int x3e2 = x1e1 - 2;
        int y1e2 = y3e1;
        int y2e2 = y1e1;
        int y3e2 = y1e1 + 3;
        spi->fillTriangle(x1e2, y1e2, x2e2, y2e2, x3e2, y3e2, primaryColor);
        // 涙点
        int x1t1 = x0 - w0;
        int x2t1 = x0 - w0 - 10;
        int x3t1 = x0 - w0 - 8;
        int y1t1 = y0;
        int y2t1 = y0 + 17;
        int y3t1 = y0 + 20;
        spi->fillTriangle(x1t1, y1t1, x2t1, y2t1, x3t1, y3t1, primaryColor);
        int x1t2 = x3t1;
        int x2t2 = x1t1;
        int x3t2 = x1t1 + 2;
        int y1t2 = y3t1;
        int y2t2 = y1t1;
        int y3t2 = y1t1 + 3;
        spi->fillTriangle(x1t2, y1t2, x2t2, y2t2, x3t2, y3t2, primaryColor);
      }
    }
  };

  class KenEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    KenEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : ctx->getColorPalette()->get(COLOR_PRIMARY);


      int x0 = isLeft ? x - 45: x + 45;
      int y0 = y + 15;

//      spi->fillRect(x, y, 2, 2, TFT_RED);
//      spi->fillRect(x0, y0, 2, 2, TFT_BLUE);

      // 微調整
      x0 = isLeft ? x0 - 10: x0;
      y0 = isLeft ? y0 - 2: y0;
      // 眉毛本体
      int x1eb1 = isLeft ? 360 - x0 : x0;
      int x2eb1 = isLeft ? 360 - (x0 - 85) : x0 - 85;
      int x3eb1 = isLeft ? 360 - (x0 + 8) : x0 + 8;
      int y1eb1 = y0;
      int y2eb1 = y0 - 45;
      int y3eb1 = y0 - 32;
      spi->fillTriangle(x1eb1, y1eb1, x2eb1, y2eb1, x3eb1, y3eb1, primaryColor);
      int x1eb2 = x1eb1;
      int x2eb2 = x2eb1;
      int x3eb2 = isLeft ? x2eb1 + 8 : x2eb1 - 8;
      int y1eb2 = y1eb1;
      int y2eb2 = y2eb1;
      int y3eb2 = y2eb1 + 28;
      spi->fillTriangle(x1eb2, y1eb2, x2eb2, y2eb2, x3eb2, y3eb2, primaryColor);
      int x1eb3 = x2eb2;
      int x2eb3 = x3eb2;
      int x3eb3 = isLeft ? x2eb2 + 16 : x2eb2 - 16;
      int y1eb3 = y2eb2;
      int y2eb3 = y3eb2;
      int y3eb3 = y2eb2;
      spi->fillTriangle(x1eb3, y1eb3, x2eb3, y2eb3, x3eb3, y3eb3, primaryColor);

      // 眉間
      //spi->fillCircle(x0, y0, 2, TFT_RED);
      int x1m1 = isLeft ? x0 + 4 : x0 + 7;
      int x2m1 = isLeft ? x1m1 - 5 : x1m1 + 5;
      int x3m1 = isLeft ? x1m1 - 7 : x1m1 + 9;
      int y1m1 = isLeft ? y0 + 2 : y0;
      int y2m1 = isLeft ? y1m1 + 1 : y1m1 + 2;
      int y3m1 = isLeft ? y1m1 - 30 : y1m1 - 28;
      spi->fillTriangle(x1m1, y1m1, x2m1, y2m1, x3m1, y3m1, primaryColor);

      // 眉の端１
      int x1ebe1 = isLeft ? x3eb3 + 3 : x3eb3 - 3;
      int y1ebe1 = y3eb3 + 2;
//      spi->fillCircle(x1ebe1, y1ebe1, 1, TFT_RED);
      int x1ebe2 = isLeft ? x1ebe1 - 8 : x1ebe1 + 8;
      int y1ebe2 = y3eb2 + 1;
//      spi->fillCircle(x1ebe2, y1ebe2, 1, TFT_BLUE);
      int x1ebe3 = isLeft ? x1ebe2 + 4 : x1ebe2 - 4;
      int y1ebe3 = y1ebe2 + 1;
//      spi->fillCircle(x1ebe3, y1ebe3, 1, TFT_GREEN);
      int x1ebe4 = isLeft ? x1ebe1 + 5 : x1ebe1 - 5;
      int y1ebe4 = y1ebe1 + 2;
//      spi->fillCircle(x1ebe4, y1ebe4, 1, TFT_GOLD);
      spi->fillTriangle(x1ebe1, y1ebe1, x1ebe2, y1ebe2, x1ebe3, y1ebe3, primaryColor);
      spi->fillTriangle(x1ebe1, y1ebe1, x1ebe3, y1ebe3, x1ebe4, y1ebe4, primaryColor);
      // 眉の端２
      int x2ebe1 = isLeft ? x1ebe4 + 3 : x1ebe4 - 3;
      int y2ebe1 = y1ebe4 + 6;
//      spi->fillCircle(x2ebe1, y2ebe1, 1, TFT_RED);
      int x2ebe2 = isLeft ? x2ebe1 - 8 : x2ebe1 + 8;
      int y2ebe2 = y2ebe1 + 21;
//      spi->fillCircle(x2ebe2, y2ebe2, 1, TFT_BLUE);
      int x2ebe3 = isLeft ? x2ebe1 -4 : x2ebe1 + 4;
      int y2ebe3 = y2ebe2 + 2;
//      spi->fillCircle(x2ebe3, y2ebe3, 1, TFT_GREEN);
      int x2ebe4 = isLeft ? x2ebe1 + 5 : x2ebe1 - 5;
      int y2ebe4 = y2ebe1 + 2;
//      spi->fillCircle(x2ebe4, y2ebe4, 1, TFT_GOLD);
      spi->fillTriangle(x2ebe1, y2ebe1, x2ebe2, y2ebe2, x2ebe3, y2ebe3, primaryColor);
      spi->fillTriangle(x2ebe1, y2ebe1, x2ebe3, y2ebe3, x2ebe4, y2ebe4, primaryColor);
      // 眉の端３
      int x3ebe1 = isLeft ? x2ebe4 + 3 : x2ebe4 - 3;
      int y3ebe1 = y2ebe4 + 8;
//      spi->fillCircle(x3ebe1, y3ebe1, 1, TFT_RED);
      int x3ebe2 = isLeft ? x3ebe1 - 8 : x3ebe1 + 8;
      int y3ebe2 = y3ebe1 + 15;
//      spi->fillCircle(x3ebe2, y3ebe2, 1, TFT_BLUE);
      int x3ebe3 = isLeft ? x3ebe1 - 4 : x3ebe1 + 4;
      int y3ebe3 = y3ebe2 + 2;
//      spi->fillCircle(x3ebe3, y3ebe3, 1, TFT_GREEN);
      int x3ebe4 = isLeft ? x3ebe1 + 4 : x3ebe1 - 4;
      int y3ebe4 = y3ebe1 + 4;
//      spi->fillCircle(x3ebe4, y3ebe4, 1, TFT_GOLD);
      spi->fillTriangle(x3ebe1, y3ebe1, x3ebe2, y3ebe2, x3ebe3, y3ebe3, primaryColor);
      spi->fillTriangle(x3ebe1, y3ebe1, x3ebe3, y3ebe3, x3ebe4, y3ebe4, primaryColor);

    }
  };

  class KenMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    KenMouth() : KenMouth(0, 0, 0, 0) {}
    KenMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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

      int x0 = rect.getLeft() - minWidth;
      int y0 = rect.getTop() + 25;
      spi->fillRect(x0+minWidth/2+5, y0, minWidth-10, 4, primaryColor);
      int x1r = x0;
      int x2r = x0 + 2;
      int x3r = x0 + minWidth + 10;
      int y1r = y0 + 10;
      int y2r = y0 + 15;
      int y3r = y0 - 8;
      spi->fillTriangle(x1r, y1r, x2r, y2r, x3r, y3r, primaryColor);
      int x1l = x0 + maxWidth + 10;
      int x2l = x0 + maxWidth + 10 - 2;
      int x3l = x0 + maxWidth + 10 - minWidth -10;
      int y1l = y0 + 10;
      int y2l = y0 + 15;
      int y3l = y0 - 8;
      spi->fillTriangle(x1l, y1l, x2l, y2l, x3l, y3l, primaryColor);
      spi->fillRect(x0+minWidth/2, y0-20, minWidth, 20, backgroundColor);
      spi->fillRect(x0+minWidth/2+5, y0+20, minWidth-10, 15, primaryColor);

    }
  };

  /**
   * Faceクラスを継承したKen顔描画用のクラス
  */
  class KenFace : public Face
  {
  public:
    KenFace()
        : Face(new KenMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new KenEye(8, false),         new BoundingRect(93, 90),
              new KenEye(8, true),          new BoundingRect(96, 230),
              new KenEyeblow(32, 0, false), new BoundingRect(67, 96),
              new KenEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar