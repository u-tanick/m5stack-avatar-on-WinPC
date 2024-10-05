// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <M5Unified.h>
#include <Avatar.h>

namespace m5avatar
{
  /**
   * 0 : BaseFace
   * 1 : AsciiFace
   * 2 : DanboFace
   * 3 : KappaFace
   * 
   * 4 : MaroFace
   * 5 : ChiikawaFace
   * 6 : SunglassFace
   * 7 : KenFace
   * 8 : Girl1Face
   * 9 : Other
  */

  class AllEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    AllEye(uint16_t r, bool isLeft)
        : r{r}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

      Expression exp = ctx->getExpression();
      uint32_t x = rect.getCenterX();
      uint32_t y = rect.getCenterY();
      Gaze g = ctx->getGaze();
      float openRatio = ctx->getEyeOpenRatio();
      uint32_t offsetX = g.getHorizontal() * 3;
      uint32_t offsetY = g.getVertical() * 3;

      int eyetype = ctx->getEyeType();
      if (eyetype == 0) {  // BaseFace
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
      else if (eyetype == 1) { // AsciiFace
        int x1 = x - 18 + offsetX;
        int y1 = y - 2 + offsetY;
        int x2 = x1;
        int y2 = y1 + 15;
        int w = 38;
        int h = 6;
        spi->fillRect(x1, y1, w, h, primaryColor);
        spi->fillRect(x2, y2, w, h, primaryColor);
      }
      else if (eyetype == 2) { // DanboFace
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
      else if (eyetype == 3) { // KappaFace
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
      else if (eyetype == 4) { // MaroFace
        int eye_rx = x + 10;
        int eye_lx = x - 10;
        int eye_y = y + 20;
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
      else if (eyetype == 5) { // ChiikawaFace
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
      else if (eyetype == 6) { // SunglassFace
        int fix_pos_y = isLeft? -3 : 0;
        int lens_x = x - 55;
        int lens_y = y - 25 + fix_pos_y;
        int lens_w = 105;
        int lens_h = 70;
        int lens_r = 20;
        spi->fillRoundRect(lens_x, lens_y, lens_w, lens_h, lens_r, TFT_NAVY);

        int temple_xr = x + 45;
        int temple_yr = y - 10 + fix_pos_y;
        int temple_wr = 50;
        int temple_hr = 20;
        int temple_xl = x - 90;
        int temple_yl = y - 10 + fix_pos_y;
        int temple_wl = 35;
        int temple_hl = 20;
        spi->fillRect(temple_xr, temple_yr, temple_wr, temple_hr, TFT_NAVY);
        spi->fillRect(temple_xl, temple_yl, temple_wl, temple_hl, TFT_NAVY);

        int reflect_x_top1 = x - 10;
        int reflect_x_top2 = reflect_x_top1 + 25;
        int reflect_x_btm1 = x - 33;
        int reflect_x_btm2 = reflect_x_btm1 + 25;
        int reflect_y_top = y - 25 + fix_pos_y;
        int reflect_y_btm = y + 44 + fix_pos_y;
        uint16_t reflectColor = 0;
        reflectColor = isLeft ? M5.Lcd.color565(160,246,253) : M5.Lcd.color565(255,180,220);
        spi->fillTriangle(reflect_x_top1, reflect_y_top, reflect_x_top2, reflect_y_top, reflect_x_btm1, reflect_y_btm, reflectColor);
        spi->fillTriangle(reflect_x_top2, reflect_y_top, reflect_x_btm1, reflect_y_btm, reflect_x_btm2, reflect_y_btm, reflectColor);
      }
      else if (eyetype == 7) { // KenFace
        int x0 = isLeft ? x - 35 : x - 40;
        int y0 = y - 8;
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
      else if (eyetype == 8) { // Girl1Face
        uint16_t eyeColor = 0;
        eyeColor = M5.Lcd.color565(196,64,178);
        int by = y - 12 + 20;
        int ey = y + 20;
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
      else if (eyetype == 9) { // Girl2Face
        uint16_t eyeColor = 0;
        eyeColor = M5.Lcd.color565(107,130,230);
        int by = y - 12 + 20;
        int ey = y + 20;
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
      else {
      }

    }
  };

  class AllEyeblow : public Drawable
  {

  private:
    uint16_t width;
    uint16_t height;
    bool isLeft;

  public:
    AllEyeblow(uint16_t w, uint16_t h, bool isLeft)
        : width{w}, height{h}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getLeft();
      uint32_t y = rect.getTop();

      int eyeblowtype = ctx->getEyeBlowType();
      if (eyeblowtype == 0) {  // BaseFace
        /* Nothing */
      } 
      else if (eyeblowtype == 1) { // AsciiFace 1(pien)
        int x0 = x;
        int y0 = isLeft ? y - 22: y -18;
        int angl0 = isLeft ? 80: 350;
        int angl1 = isLeft ? 190: 100;
        spi->fillEllipseArc(x0, y0, 17, 20, 12, 15, angl0, angl1, primaryColor);
      }
      else if (eyeblowtype == 2) { // AsciiFace 2(ryotu)
        int x0 = isLeft ? x - 25 : x + 25;
        int y0 = isLeft ? y + 8: y + 12;
        int angl0 = isLeft ? 180: 200;
        int angl1 = isLeft ? 340: 360;
        spi->fillEllipseArc(x0, y0, 30, 50, 50, 70, angl0, angl1, primaryColor);
        spi->fillEllipseArc(x0, y0, 30, 50, 50, 70, angl0, angl1, primaryColor);
      }
      else if (eyeblowtype == 3) { // KappaFace
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
      else if (eyeblowtype == 4) { // MaroFace
        int mx = isLeft ? x-7 : x;
        int my = y - 20 + 20;
        int rx = 16;
        int ry = 10;
        int x_offset = isLeft ? -23 : 23;
        int y_offset = isLeft ? -12 : -7;
        spi->fillEllipse(mx+x_offset, my+y_offset, rx, ry, primaryColor);
      }
      else if (eyeblowtype == 5) { // ChiikawaFace
        height = 6;
        width = isLeft ? 38 : 42;
        int x_offset = 2;
        int y_offset = -25;
        int x0 = isLeft ? x - x_offset*3 : x;
        int y0 = isLeft ? y + y_offset - 8 : y + y_offset - 2;
        y0 = y0 + 20;

        int x1, y1, x2, y2, x3, y3, x4, y4;
        int a = isLeft ? 1 : -1;
        int dx = a * 5;
        int dy = a * 5;
        x1 = isLeft ? x0 - width / 2 : x0 - width / 2;
        x2 = isLeft ? x1 - x_offset  : x1 + x_offset;
        x4 = isLeft ? x0 + width / 2 : x0 + width / 2;
        x3 = isLeft ? x4 + x_offset  : x4 - x_offset;
        y1 = y0 - height / 2 - dy;
        y2 = y0 + height / 2 - dy;
        y3 = y0 - height / 2 + dy;
        y4 = y0 + height / 2 + dy;
        spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
        spi->fillTriangle(x2, y2, x3, y3, x4, y4, primaryColor);
      }
      else if (eyeblowtype == 6) { // SunglassFace
        int gx = x;
        int gy = isLeft ? y - 2: y + 2;
        spi->fillEllipseArc(gx, gy - 20, 34, 40, 24, 26, 200, 340, primaryColor);
      }
      else if (eyeblowtype == 7) { // KenFace
        int x0 = isLeft ? x - 45: x + 45;
        int y0 = y + 15;
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
        int x1ebe2 = isLeft ? x1ebe1 - 8 : x1ebe1 + 8;
        int y1ebe2 = y3eb2 + 1;
        int x1ebe3 = isLeft ? x1ebe2 + 4 : x1ebe2 - 4;
        int y1ebe3 = y1ebe2 + 1;
        int x1ebe4 = isLeft ? x1ebe1 + 5 : x1ebe1 - 5;
        int y1ebe4 = y1ebe1 + 2;
        spi->fillTriangle(x1ebe1, y1ebe1, x1ebe2, y1ebe2, x1ebe3, y1ebe3, primaryColor);
        spi->fillTriangle(x1ebe1, y1ebe1, x1ebe3, y1ebe3, x1ebe4, y1ebe4, primaryColor);
        // 眉の端２
        int x2ebe1 = isLeft ? x1ebe4 + 3 : x1ebe4 - 3;
        int y2ebe1 = y1ebe4 + 6;
        int x2ebe2 = isLeft ? x2ebe1 - 8 : x2ebe1 + 8;
        int y2ebe2 = y2ebe1 + 21;
        int x2ebe3 = isLeft ? x2ebe1 -4 : x2ebe1 + 4;
        int y2ebe3 = y2ebe2 + 2;
        int x2ebe4 = isLeft ? x2ebe1 + 5 : x2ebe1 - 5;
        int y2ebe4 = y2ebe1 + 2;
        spi->fillTriangle(x2ebe1, y2ebe1, x2ebe2, y2ebe2, x2ebe3, y2ebe3, primaryColor);
        spi->fillTriangle(x2ebe1, y2ebe1, x2ebe3, y2ebe3, x2ebe4, y2ebe4, primaryColor);
        // 眉の端３
        int x3ebe1 = isLeft ? x2ebe4 + 3 : x2ebe4 - 3;
        int y3ebe1 = y2ebe4 + 8;
        int x3ebe2 = isLeft ? x3ebe1 - 8 : x3ebe1 + 8;
        int y3ebe2 = y3ebe1 + 15;
        int x3ebe3 = isLeft ? x3ebe1 - 4 : x3ebe1 + 4;
        int y3ebe3 = y3ebe2 + 2;
        int x3ebe4 = isLeft ? x3ebe1 + 4 : x3ebe1 - 4;
        int y3ebe4 = y3ebe1 + 4;
        spi->fillTriangle(x3ebe1, y3ebe1, x3ebe2, y3ebe2, x3ebe3, y3ebe3, primaryColor);
        spi->fillTriangle(x3ebe1, y3ebe1, x3ebe3, y3ebe3, x3ebe4, y3ebe4, primaryColor);
      }
      else if (eyeblowtype == 8) { // Girl1Face
        int x1, y1, x2, y2, x3, y3;
        int y0 = y + 20;
        x1 = isLeft ? x + 30 : x - 36;// (60) 96 : 230
        x2 = isLeft ? x1 - 78 : x1 + 78;
        x3 = isLeft ? x1 - 78 : x1 + 78;
        y1 = isLeft ? y0 -36 : y0 -31; // (33) 67 : 72
        y2 = y1 - 9;
        y3 = y1 - 5;
        spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
      }
      else if (eyeblowtype == 9) { // Girl2Face
        int x1, y1, x2, y2, x3, y3;
        int y0 = y + 20;
        x1 = isLeft ? x + 30 : x - 36;// (60) 96 : 230
        x2 = isLeft ? x1 - 78 : x1 + 78;
        x3 = isLeft ? x1 - 78 : x1 + 78;
        y1 = isLeft ? y0 -36 : y0 -31; // (33) 67 : 72
        y2 = y1 + 9;
        y3 = y1 + 5;
        spi->fillTriangle(x1, y1, x2, y2, x3, y3, primaryColor);
      }
      else {
      }
    }
  };

  class AllMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    AllMouth() : AllMouth(0, 0, 0, 0) {}
    AllMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
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
      Expression exp = ctx->getExpression();
      float breath = fmin(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      int h = minHeight + (maxHeight - minHeight) * openRatio;
      int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      int x = rect.getLeft() - w / 2;
      int y = rect.getTop() - h / 2 + breath * 2;

      int mouthtype = ctx->getMouthType();
      if (mouthtype == 0) {  // BaseFace
        spi->fillRect(x, y, w, h, primaryColor);
      }
      else if (mouthtype == 1) { // AsciiFace
        int x0 = rect.getLeft(); // 163
        int y0 = rect.getTop();  // 148

        uint32_t mx = x0 - 1;  // 162;
        uint32_t my = y0 - 18; // 130;
        uint32_t mrx = 15;
        uint32_t mry = 35 + 25 * openRatio;
        spi->fillEllipseArc(mx, my, 0, mrx, 0, mry, 0, 180, TFT_RED);

        int x2 = x0*0.71;
        // 口の ω 部分として2つの楕円を描画
        int e_rx = 140;
        int e_ry = y0;
        int e_lx = 183;
        int e_ly = y0;
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
        int over_r1_ry = y0 - 40;
        int over_r1_rw = 105;
        int over_r1_rh = 30;
        spi->fillRect(over_r1_rx, over_r1_ry, over_r1_rw, over_r1_rh, backgroundColor);
        int over_r2_rx = x2 + 35;
        int over_r2_ry = y0 - 10;
        int over_r2_rw = 25;
        int over_r2_rh = 12;
        spi->fillRect(over_r2_rx, over_r2_ry, over_r2_rw, over_r2_rh, backgroundColor);
      }
      else if (mouthtype == 2) { // DanboFace
        int w0 = 53;
        int h0 = 33;
        int x0 = rect.getLeft() - w0/2;
        int y0 = rect.getTop() + 42;
        int x1 = x0 + w0;
        int y1 = y0;
        int x2 = x0 + w0/2;
        int y2 = y0 - h0*(openRatio/2 + 0.5);
        spi->fillTriangle(x0, y0, x1, y1, x2, y2, primaryColor);
      }
      else if (mouthtype == 3) { // KappaFace
        int h0 = 25;
        int w0 = 64;
        int x0 = rect.getLeft() - 8;
        int y0 = rect.getTop() + 20 - openRatio*20;
        spi->fillEllipse(x0, y0, w0, h0, TFT_RED);

        int edge_x1_l = x0-w0-5;
        int edge_x2_l = x0-w0+7;
        int edge_x3_l = x0-w0+7;
        int edge_x1_r = x0+w0+5;
        int edge_x2_r = x0+w0-7;
        int edge_x3_r = x0+w0-7;
        int edge_y1 = y0;
        int edge_y2 = y0+h0/2;
        int edge_y3 = y0-h0/2;
        spi->fillTriangle(edge_x1_l, edge_y1, edge_x2_l, edge_y2, edge_x3_l, edge_y3, TFT_RED);
        spi->fillTriangle(edge_x1_r, edge_y1, edge_x2_r, edge_y2, edge_x3_r, edge_y3, TFT_RED);

        spi->drawLine(edge_x1_l, edge_y1, edge_x1_r, edge_y1, TFT_BLACK);
        int offset_y = 14;
        int philtrum_w = 14;
        int philtrum_h = 20;
        int x1_ptm = x0;
        int x2_ptm = x0 - philtrum_w;
        int x3_ptm = x0 + philtrum_w;
        int y1_ptm = y0 - offset_y;
        int y23_ptm = y0 - philtrum_w - offset_y;
        spi->fillTriangle(x1_ptm, y1_ptm, x2_ptm, y23_ptm, x3_ptm, y23_ptm, backgroundColor);
      }
      else if (mouthtype == 4) { // MaroFace
        uint16_t doubtMouthColor = 0;
        doubtMouthColor = M5.Lcd.color565(255,180,220);
        int dy = y - 20 + 20;
        spi->fillRoundRect(x, dy, w, 40, 20, doubtMouthColor);
        spi->fillRoundRect(x, dy+10, w, 30, 10, doubtMouthColor);
        int ex = x + w/2;
        int ey = dy;
        spi->fillEllipse(ex, ey-2, 20, 3, backgroundColor);
        spi->fillEllipse(ex, ey+40, 30, 3, backgroundColor);
      }
      else if (mouthtype == 5) { // ChiikawaFace
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
      else if (mouthtype == 6) { // SunglassFace
        int x0 = rect.getLeft();
        int y0 = rect.getTop() + 20;
        int rx1 = 0;
        int rx2 = 26;
        int ry1 = 0;
        int ry2 = 35 - (1 - openRatio)*15;
        spi->fillEllipseArc(x0, y0, rx1, rx2, ry1, ry2, 0, 180, primaryColor);
        int x1 = x0;
        int y1 = y0 + 24 - (1 - openRatio)*12;
        int rxt = 15;
        int ryt = 10 - (1 - openRatio)*3;
        spi->fillEllipse(x1, y1, rxt, ryt, TFT_RED);
      }
      else if (mouthtype == 7) { // KenFace
        int x0 = rect.getLeft() - minWidth;
        int y0 = rect.getTop() + 25;

        int xm = x0+minWidth/2+5;
        int ym = y0;
        int wm = minWidth-10;
        int hm = 4;
        int xmo = xm - openRatio * 24;
        int ymo = ym + openRatio * 12;
        int wmo = wm + openRatio * 48;
        int hmo = hm;
        spi->fillRect(xmo, ymo, wmo, hmo, primaryColor);
        spi->fillRect(xm, ym, wm, hm, primaryColor);
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
        int x2 = x0 + minWidth/2 + 5;
        int y2 = y0 + 20 + openRatio * 4;
        int w2 = minWidth - 10;
        int h2 = 12;
        spi->fillRect(x2, y2, w2, h2, primaryColor);
      }
      else if (mouthtype == 8) { // Girl1Face
        int x0 = rect.getLeft() - 10;
        int y0 = rect.getTop() + 30;
        int w0 = minWidth/3;
        int h0 = minHeight + (maxHeight/5 - minHeight) * openRatio;
        spi->fillRect(x0, y0, w0, h0, primaryColor);
      }
      else if (mouthtype == 9) { // MeganeFace
        int x0 = rect.getLeft() - 22;
        int y0 = rect.getTop() + 20 - openRatio*8;
        spi->fillEllipse(x0, y0, 12, 8, primaryColor);
        spi->fillEllipse(x0, y0, 10, 6, backgroundColor);
        spi->fillEllipse(x0, y0+15, 12, 8, primaryColor);
        spi->fillEllipse(x0, y0+15, 10, 6, backgroundColor);
        spi->fillEllipse(x0+10, y0+1, 10, 6, backgroundColor);
        spi->fillEllipse(x0+10, y0+12, 10, 6, backgroundColor);
      }
      else {
      }
    }
  };

  /**
   * Faceクラスを継承した全ての顔パーツ描画用のクラス
  */
  class AllFaces : public Face
  {
  public:
    AllFaces()
        : Face(new AllMouth(50, 90, 4, 60), new BoundingRect(148, 163),
              new AllEye(8, false),         new BoundingRect(93, 90),
              new AllEye(8, true),          new BoundingRect(96, 230),
              new AllEyeblow(32, 0, false), new BoundingRect(67, 96),
              new AllEyeblow(32, 0, true),  new BoundingRect(72, 230)) {}
  };

} // namespace m5avatar
