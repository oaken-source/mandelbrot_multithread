
#include "bmp.h"
#include "mandelbrot.h"

#include <string.h>

/* increase this value for better images at very high zoom factors */
#define MAX_ITERATION 10000

/* the size of the output bitmap */
#define XSIZE 800
#define YSIZE 600

/* drawing coordinaties for the complete mandelbrot set... */
#define CX    (-0.5)
#define CY    ( 0.0)
#define WIDTH ( 2.5)

/* ... and for one (of many) interesting close-ups */
//#define CX    (-0.7436447860)
//#define CY    ( 0.1318252536)
//#define WIDTH ( 0.0000029336)

#define HEIGHT (WIDTH * YSIZE / XSIZE)
#define DXMIN (CX - WIDTH / 2)
#define DXMAX (CX + WIDTH / 2)
#define DYMIN (CY - HEIGHT / 2)
#define DYMAX (CY + HEIGHT / 2)
#define SCALE (5.0 / WIDTH)


/* draw the bitmap.
 * TODO: Implement multithreading in this subroutine.
 *
 * parameters:
 *   bmp: a struct BMP as initialized by bmp_open()
 *
 * returns:
 *   0 on success, -1 on error
 *
 * errors:
 *   may fail and set errno for the same reasons as bmp_write_pixels() and
 *   bmp_write_endline()
 */
static int
draw (struct BMP bmp)
{
  unsigned char color[3];

  /* TODO: implement multithreading here, to speed up the image generation */

  size_t x, y;
  for(y = 0; y < YSIZE; y++)
    {
      for(x = 0; x < XSIZE; x++)
        {
          double dx = x * ((DXMAX - DXMIN) / XSIZE) + DXMIN;
          double dy = y * ((DYMAX - DYMIN) / YSIZE) + DYMIN;

          mandelbrot_get(dx, dy, color, MAX_ITERATION, SCALE);

          if (0 != bmp_write_pixels(bmp, color, 1))
            {
              perror("bmp_write_pixels");
              return -1;
            }
        }

      if (0 != bmp_write_endline(bmp))
        {
          perror("bmp_write_endline");
          return -1;
        }
    }

  return 0;
}

int
main (int argc, char *argv[])
{
  /* TODO: read argc/argv and extract the number of threads to create */

  struct BMP bmp;
  if (0 != bmp_open(&bmp, "output.bmp", XSIZE, YSIZE))
    {
      perror("bmp_open");
      return 1;
    }

  if (0 != draw(bmp))
    {
      perror("draw");
      return 1;
    }

  bmp_close(bmp);
  return 0;
}
