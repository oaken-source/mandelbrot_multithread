
#include "mandelbrot.h"

#include <stdlib.h>
#include <math.h>

/*********
 * NOTICE:
 * This code is provided for reference, but does not need to be modified.
 */

#define ESCAPE_RADIUS 2.0


static void
hsv2rgb (double h, double s, double v, unsigned char color[3])
{
  if (s == 0.0)
    {
      color[0] = v;
      color[1] = v;
      color[2] = v;
      return;
    }

  h /= 60;
  unsigned int i = floor(h);
  double f = h - i;
  double p = v * (1.0 - s);
  double q = v * (1.0 - s * f);
  double t = v * (1.0 - s * (1 - f));

  switch (i)
    {
    case 0:
      color[0] = p * 255;
      color[1] = t * 255;
      color[2] = v * 255;
      break;
    case 1:
      color[0] = p * 255;
      color[1] = v * 255;
      color[2] = q * 255;
      break;
    case 2:
      color[0] = t * 255;
      color[1] = v * 255;
      color[2] = p * 255;
      break;
    case 3:
      color[0] = v * 255;
      color[1] = q * 255;
      color[2] = p * 255;
      break;
    case 4:
      color[0] = v * 255;
      color[1] = p * 255;
      color[2] = t * 255;
      break;
    case 5:
    default:
      color[0] = q * 255;
      color[1] = p * 255;
      color[2] = v * 255;
      break;
    }
}

void
mandelbrot_get (double dx, double dy, unsigned char color[3], size_t max_iteration, double scale)
{
  double x = 0, y = 0;

  unsigned int i;
  for (i = 0; i < max_iteration; ++i)
    {
      if (x * x + y * y >= ESCAPE_RADIUS * ESCAPE_RADIUS)
        break;

      double xtemp = x * x - y * y + dx;
      y = 2 * x * y + dy;
      x = xtemp;
    }

  if (i == max_iteration)
    {
      color[0]=0;
      color[1]=0;
      color[2]=0;
      return;
    }

  double j = i + 1 - log(log2(fabs(x * x + y * y)));
  double normal = sqrt(2 * sqrt(fabs(1- sqrt(5 * scale)))) * 66.5;

  double h = fmod(180.0 + 360.0 * (1.0 - j / normal), 360.0);
  double s = 0.8;
  double v = 0.8;

  hsv2rgb(h, s, v, color);
}
