/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;

  blockyimg = *(new PNG(ceil(img.width() / blockwidth), (ceil(img.height() / blockwidth))));

  for(unsigned int i = 0; i < blockyimg.width(); i += 1) //go through each "block"
  {
    for(unsigned int j = 0; j < blockyimg.height(); j += 1)
    {
      //fill each block
      double totalH = 0;
      double totalS = 0;
      double totalL = 0;
      double totalA = 0;

      int count = 0;

      for(unsigned int x = (blockwidth * i); x < ((i + 1) * blockwidth); x++)
      {
        for(unsigned int y = (blockwidth * j); y < ((j + 1) * blockwidth); y++)
        {
          count++;

          if(x < img.width() && y < img.height())
          {
            HSLAPixel color = *(img.getPixel(x, y));
            totalH += color.h;
            totalS += color.s;
            totalL += color.l;
            totalA += color.a;
          }
          else
          {
            count--;
          }
        }
      }

      double avgH = totalH / count;
      double avgS = totalS / count;
      double avgL = totalL / count;
      double avgA = totalA / count;

      HSLAPixel *bkCol = blockyimg.getPixel(i, j);
      bkCol->h = avgH;
      bkCol->s = avgS;
      bkCol->l = avgL;
      bkCol->a = avgA;
    }
  }
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  double distance = PointDistance(p, center);

  if(distance <= radius)
  {
    unsigned int i = p.x / blockwidth;
    unsigned int j = p.y / blockwidth;

    return *(blockyimg.getPixel(i, j));
  }
  else
  {
    return *(img.getPixel(p.x, p.y));
  }
  
}
