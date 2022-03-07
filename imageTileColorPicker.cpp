/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) 
{
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) 
{
  unsigned int newX = p.x;
  unsigned int newY = p.y;

  while(newX >= img_other.width())
  {
    newX -= img_other.width();
  }
  while(newY >= img_other.height())
  {
    newY -= img_other.height();
  }

  HSLAPixel color = *(img_other.getPixel(newX, newY));
  HSLAPixel ret;

  ret.h = color.h;
  ret.s = color.s;
  ret.l = color.l;
  ret.a = color.a;
  
  return ret;
}
