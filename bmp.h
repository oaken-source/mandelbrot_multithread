#ifndef BMP_H
#define BMP_H

#include <stdio.h>


struct BMP
{
  const char *path;
  FILE *f;
  size_t xres;
  size_t yres;
};


/* create a new BMP file, of a given size, and write the header structure
 *
 * parameters:
 *   bmp: a pointer to a struct BMP to initialize
 *   path: the path to the BMP file, will be created if not exists
 *   xres, yres: the resolution of the image
 *
 * returns:
 *   0 on success, -1 on failure
 *
 * errors:
 *   may fail and set errno for the same reasons as fopen() and fwrite()
 */
int bmp_open(struct BMP *bmp, const char *path, size_t xres, size_t yres);

/* add an array of pixels to the current line of a bitmap. note that the
 * created bitmap file will be corrupt if more pixels are added than fit
 * on the current line, but this function will not report an error.
 *
 * parameters:
 *   bmp: a struct BMP as initialized by bmp_open
 *   color_data: an array of color values for each pixel (B, G, R, B, G, ...)
 *   n: the number of pixels described in the color_data array
 *
 * returns:
 *   0 on success, -1 on failure
 *
 * errors:
 *   may fail and set errno for the same reasons as fwrite()
 */
int bmp_write_pixels(struct BMP bmp, unsigned char *color_data, size_t n);

/* end the currently written line and begin the next one. note that the
 * created bitmap file will be corrupt if the current line does not contain
 * a sufficient amount of pixels, as specified during the invocation of
 * bmp_open(), but this function will not report an error.
 *
 * parameters:
 *   bmp: a struct BMP as initialized by bmp_open
 *
 * returns:
 *   0 on success, -1 on failure
 *
 * errors:
 *   may fail and set errno for the same reasons as fwrite()
 */
int bmp_write_endline(struct BMP bmp);

/* close the bitmap that was opened with bmp_open(). note that the bitmap
 * will be corrupt unless the correct (read: specified during the call to
 * bmp_open()) number of pixels and lines has been added, but this function
 * will not report an error.
 *
 * parameters:
 *   bmp: a completed struct BMP as initialized by bmp_open
 *
 * returns:
 *   0 on success, -1 on failure
 *
 * errors:
 *   may fail and set errno for the same reasons as fclose()
 */
int bmp_close(struct BMP bmp);

#endif
