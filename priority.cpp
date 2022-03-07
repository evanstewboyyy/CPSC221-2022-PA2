/*
* File:        priority.cpp
* Description: Implements a priority ordering structure specially made for determining the
*              order of neighbours visited in PA2's filler::fill function.
*              Note that this does NOT serve the same purpose as the stack/queue
*              ordering structure which you have also been asked to implement.
*
*              Ignoring resize costs, any single insertion or removal operation
*              should cost at most O(n), where n is the number of PixelPoints
*              stored in the collection.
*
* Date:        2022-02-10 02:04
*
*/

#include "priority.h"
#include <assert.h>

using namespace cs221util;
using namespace std;

/*
*  Default constructor
*  Initializes refcolor to the default color according to the HSLAPixel implementation.
*/
PriorityNeighbours::PriorityNeighbours() 
{
  HSLAPixel *pixel = new HSLAPixel();
  refcolor = *pixel;
}

/*
*  Parameterized constructor
*  Initializes refcolor to the supplied value.
*/
PriorityNeighbours::PriorityNeighbours(HSLAPixel ref) 
{
  refcolor = ref; 
}

/*
*  Inserts an item into the collection
*  PARAM: p - item to be inserted
*  POST:  the collection contains p, along with all previously existing items.
*/
void PriorityNeighbours::Insert(PixelPoint p) 
{
  points.push_back(p); 
}

/*
*  Removes and returns an item from the collection satisfying the priority condition
*  PRE:    the collection is not empty (but it would be good to check anyway!).
*  POST:   the item satisfying the priority condition is removed from the collection.
*  RETURN: the item satisfying the priority condition
*
*  Priority condition:
*    The PixelPoint in the collection whose color is the minimum distance away
*    from the reference color is the priority item to be returned.
*
*    In case of multiple items with the same priority value (i.e. minimal distance
*    away from the reference color), the one with the minimal y-coordinate will be
*    selected.
*    In case of multiple items with the same priority value and the same y-coordinate,
*    the one with the minimal x-coordinate will be selected.
*
*    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
*
*  Combined with Insert(), think about the time complexity of maintaining the
*  priority order and/or accessing the priority element in this specific application!
*/
PixelPoint PriorityNeighbours::Remove() 
{
  double min;

  for(int i = 0; i < points.size(); i++)
  {
    if(i == 0)
    {
      min = refcolor.dist(points[i].color);
    }
    if(refcolor.dist(points[i].color) < min)
    {
      min = refcolor.dist(points[i].color);
    }
  }

  vector<PixelPoint> pointEQdist;
  vector<int> EQDindexes;

  for(int i = 0; i < points.size(); i++)
  {
    if(refcolor.dist(points[i].color) == min)
    {
      pointEQdist.push_back(points[i]);
      EQDindexes.push_back(i);
    }
  }

  if(pointEQdist.size() == 1)
  {
    PixelPoint temp = points[points.size() - 1];
    points[points.size() - 1] = pointEQdist[0];
    points[EQDindexes[0]] = temp;
    points.pop_back();

    return pointEQdist[0];
  }

  unsigned int miny;

  for(int i = 0; i < pointEQdist.size(); i++)
  {
    if(i == 0)
    {
      miny = pointEQdist[i].y;
    }
    if(pointEQdist[i].y < miny)
    {
      miny = pointEQdist[i].y;
    }
  }

  vector<PixelPoint> pointEQy;
  vector<int> EQYindexes;

  for(int i = 0; i < pointEQdist.size(); i++)
  {
    if(pointEQdist[i].y == miny)
    {
      pointEQy.push_back(pointEQdist[i]);
      EQYindexes.push_back(EQDindexes[i]);
    }
  }

  if(pointEQy.size() == 1)
  {
    PixelPoint temp = points[points.size() - 1];
    points[points.size() - 1] = pointEQy[0];
    points[EQYindexes[0]] = temp;
    points.pop_back();

    return pointEQy[0];
  }

  unsigned int minx;
  int index = 0;
  int pointsInd = 0;

  for(int i = 0; i < pointEQy.size(); i++)
  {
    if(i == 0)
    {
      minx = pointEQy[i].x;
      index = i;
      pointsInd = EQYindexes[i];
    }
    if(pointEQdist[i].x < minx)
    {
      minx = pointEQy[i].x;
      index = i;
      pointsInd = EQYindexes[i];
    }
  }

  PixelPoint temp = points[points.size() - 1];
  points[points.size() - 1] = pointEQy[index];
  points[pointsInd] = temp;
  points.pop_back();

  return pointEQy[index];

}

/*
*  Checks if the collection is empty
*  RETURN: true, if the collection is empty
*          false, otherwise
*/
bool PriorityNeighbours::IsEmpty() const 
{
  if(points.size() == 0)
  {
    return true;
  }
  
  return false; 
}

/*
*  Returns the value of the reference color
*/
HSLAPixel PriorityNeighbours::GetReferenceColor() const 
{ 
  return refcolor; 
}

/*
*  Sets the reference color attribute
*  POST: refcolor is set to the supplied value
*/
void PriorityNeighbours::SetReferenceColor(HSLAPixel ref) 
{
  refcolor = ref;  
}
