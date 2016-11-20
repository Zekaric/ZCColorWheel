// colorWheel.cpp
//
// Quick an dirty program to just create a color wheel.  I needed this to create
// an icon for a program.  Dumps the data to a file as raw RGB.  Used a 
// paint program to read in that raw file to convert to an PNG.
//
// Defines the entry point for the console application.
//
// The image is blending 6 colors together to form a sort of color wheel.
// Three primary  colors  Red,         Yellow,        Blue
// Three seconday colors       orange,         green,      purple.
//

/******************************************************************************
include: 
******************************************************************************/
#include "stdafx.h"

/******************************************************************************
constant:
******************************************************************************/
#define RGB 0

// Image dimentions.  Hard coded.
#define DIM       2048
#define HalfDIM   1024

// BWON
// 0 = Color output
// 1 = Gray scale output
// Produces a disk output from black to white by the distance from the center.
#define BWON      0
// BWONLY
// I honestly don't remember.  Commenting years after writing this. :P
#define BWONLY    1

#define BWSTEP    448.

#define BMIN      128.
#define BMAX      (BMIN + BWSTEP)

#define WMIN      BMAX
#define WMAX      ((double) HalfDIM)

/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   unsigned char r,g,b;
} Rgb;

typedef struct
{
   double r,g,b;
} Rgbf;

/******************************************************************************
prototype:
******************************************************************************/
static double _Get2DAngle(double x, double y);

/******************************************************************************
function:
******************************************************************************/
/******************************************************************************
func: _tmain
******************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
{
   Rgb         *pixel;
   unsigned int x,
                y;
   double       angle,
                dx,
                dy,
                h,
                blend;
   FILE        *file;

   // Create the image buffer.
   pixel = (Rgb *) calloc(1, sizeof(Rgb) * DIM * DIM);
   if (!pixel)
   {
      return 1;
   }

   // For all pixel rows...
   for (y = 0; y < DIM - 1; y++)
   {
      // Get the y graph location.  Center of the image is 0,0
      dy = ((double) y) - ((double) HalfDIM);

      // For all pixel cols...
      for (x = 0; x < DIM - 1; x++)
      {
         // Get the x graph location.
         dx = ((double) x) - ((double) HalfDIM);
         h  = sqrt(dy * dy + dx * dx);

         // Compute the angle.
         angle = (_Get2DAngle(dx, dy) * 180. / M_PI) + 90.;
         if (angle > 360.)
         {
            angle -= 360.;
         }

         // depending on the angle, compute the color.
         if      (angle <= 60.)
         {
            Rgbf a = { 0., 1., 0.},
                 b = { 0., 1., 1.};

            blend = angle / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }
         else if (angle <= 120.)
         {
            Rgbf a = { 0., 1., 1.},
                 b = { 0., 0., 1.};

            blend = (angle - 60.) / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }
         else if (angle <= 180.)
         {
            Rgbf a = { 0., 0., 1.},
                 b = { 1., 0., 1.};

            blend = (angle - 120.) / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }
         else if (angle <= 240.)
         {
            Rgbf a = { 1., 0., 1.},
                 b = { 1., 0., 0.};

            blend = (angle - 180.) / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }
         else if (angle <= 300.)
         {
            Rgbf a = { 1., 0., 0.},
                 b = { 1., 1., 0.};

            blend = (angle - 240.) / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }
         else
         {
            Rgbf a = { 1., 1., 0.},
                 b = { 0., 1., 0.};

            blend = (angle - 300.) / 60.;
            a.r = a.r * (1. - blend) + b.r * blend;
            a.g = a.g * (1. - blend) + b.g * blend;
            a.b = a.b * (1. - blend) + b.b * blend;

            pixel[(y * DIM  + x)].r = (unsigned char) (pow(a.r, 0.4545) * 255.);
            pixel[(y * DIM  + x)].g = (unsigned char) (pow(a.g, 0.4545) * 255.);
            pixel[(y * DIM  + x)].b = (unsigned char) (pow(a.b, 0.4545) * 255.);
         }

         // Producing Gray output.
         if (BWON)
         {
            if      (WMAX < h)
            {
               pixel[(y * DIM  + x)].r = 0;
               pixel[(y * DIM  + x)].g = 0;
               pixel[(y * DIM  + x)].b = 0;
            }
            else if (h < BMIN)
            {
               pixel[(y * DIM  + x)].r = 255;
               pixel[(y * DIM  + x)].g = 255;
               pixel[(y * DIM  + x)].b = 255;
            }
            else if (h < BMAX)
            {
               h = (h - BMIN) / BWSTEP;
               if (BWONLY)
               {
                  pixel[(y * DIM  + x)].r = (unsigned char) (128. * h);
                  pixel[(y * DIM  + x)].g = (unsigned char) (128. * h);
                  pixel[(y * DIM  + x)].b = (unsigned char) (128. * h);
               }
               else
               {
                  pixel[(y * DIM  + x)].r = (unsigned char) (((double) pixel[(y * DIM  + x)].r) * h);
                  pixel[(y * DIM  + x)].g = (unsigned char) (((double) pixel[(y * DIM  + x)].g) * h);
                  pixel[(y * DIM  + x)].b = (unsigned char) (((double) pixel[(y * DIM  + x)].b) * h);
               }
            }
            else
            {
               h = (h - WMIN) / BWSTEP;
               if (BWONLY)
               {
                  pixel[(y * DIM  + x)].r = (unsigned char) (128. * (1. - h) + 255. * h);
                  pixel[(y * DIM  + x)].g = (unsigned char) (128. * (1. - h) + 255. * h);
                  pixel[(y * DIM  + x)].b = (unsigned char) (128. * (1. - h) + 255. * h);
               }
               else
               {
                  pixel[(y * DIM  + x)].r = (unsigned char) (((double) pixel[(y * DIM  + x)].r) * (1. - h) + 255. * h);
                  pixel[(y * DIM  + x)].g = (unsigned char) (((double) pixel[(y * DIM  + x)].g) * (1. - h) + 255. * h);
                  pixel[(y * DIM  + x)].b = (unsigned char) (((double) pixel[(y * DIM  + x)].b) * (1. - h) + 255. * h);
               }
            }
         }
      }
   }

   // Write out the file.
   file = fopen("color.raw", "wb");
   fwrite(pixel, sizeof(Rgb), DIM * DIM, file);
   fclose(file);

   // Clean up.
   free(pixel);

   return 0;
}

/******************************************************************************
local:
funciton:
******************************************************************************/
/******************************************************************************
func: _Get2DAngle

Get the 2D angle based of the x and y coordinates of the pixel.
******************************************************************************/
double _Get2DAngle(double x, double y)
{
   double dtemp;

   // Too close to the origin
   if (fabs(y) < 0.0000001 &&
       fabs(x) < 0.0000001)
   {
      return 0.0;
   }

   // On the x axis
   if (fabs(y) < 0.0000001)
   {
      dtemp = 0.0;
   }
   // Calculate the angle
   else
   {
      dtemp = asin(y / sqrt(x * x + y * y));
   }

   // Opposite side of the y axis
   if (x < 0.0)
   {
      dtemp = M_PI - dtemp;
   }

   if (dtemp < 0)
   {
      dtemp = 2 * M_PI + dtemp;
   }

   return dtemp;
}
