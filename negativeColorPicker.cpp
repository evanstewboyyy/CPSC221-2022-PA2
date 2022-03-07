/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  HSLAPixel *color = img.getPixel(p.x, p.y);
  HSLAPixel ret;
  if(color->h < 180)
  {
    ret.h = color->h + 180;
    ret.s = color->s;
    ret.l = 1 - color->l;
    ret.a = color->a;
    return ret;
    // return *(new HSLAPixel(180 + color.h, color.s, 1 - color.l, color.a));
  }
  else
  {
    ret.h = color->h - 180;
    ret.s = color->s;
    ret.l = 1 - color->l;
    ret.a = color->a;
    return ret;
    // return *(new HSLAPixel(color.h - 180, color.s, 1 - color.l, color.a));
  }
}
