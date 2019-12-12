
#include "bmp.h"

#include <stdint.h>

/*********
 * NOTICE:
 * This code is provided for reference, but does not need to be modified.
 */

int
bmp_open (struct BMP *bmp, const char *path, size_t xres, size_t yres)
{
  bmp->path = path;
  bmp->xres = xres;
  bmp->yres = yres;

  bmp->f = fopen(path, "wb+");
  if (!bmp->f)
    return -1;

  char header[54] = {
    0x42, 0x4d,                 // magic number
    0x00, 0x00, 0x00, 0x00,     // file size (comes later)
    0x00, 0x00, 0x00, 0x00,     // reserved
    0x36, 0x00, 0x00, 0x00,     // image offset
    0x28, 0x00, 0x00, 0x00,     // header size
    0x00, 0x00, 0x00, 0x00,     // image width (comes later)
    0x00, 0x00, 0x00, 0x00,     // image height (comes later)
    0x01, 0x00,                 // number of planes
    0x18, 0x00,                 // color depth
    0x00, 0x00, 0x00, 0x00,     // compression
    0x00, 0x00, 0x00, 0x00,     // image size (comes later)
    0x00, 0x00, 0x00, 0x00,     // xres (ignored)
    0x00, 0x00, 0x00, 0x00,     // yres (ignored)
    0x00, 0x00, 0x00, 0x00,     // colortable information (ignored)
    0x00, 0x00, 0x00, 0x00
  };

  *((uint32_t*)&header[0x02]) = xres * yres * 3 + sizeof(header);
  *((uint32_t*)&header[0x12]) = xres;
  *((uint32_t*)&header[0x16]) = yres;
  *((uint32_t*)&header[0x22]) = xres * yres * 3;

  if (sizeof(header) != fwrite(header, 1, sizeof(header), bmp->f))
    {
      fclose(bmp->f);
      bmp->f = NULL;
      return -1;
    }

  return 0;
}

int
bmp_write_pixels (struct BMP bmp, unsigned char *color_data, size_t n)
{
  if (fwrite(color_data, 1, n * 3, bmp.f) != n * 3)
    return -1;

  return 0;
}

int
bmp_write_endline (struct BMP bmp)
{
  // bmp lines must start 4byte aligned
  if (bmp.xres % 4)
    {
      unsigned char padding[4] = { 0 };
      size_t len = 4 - (bmp.xres * 3) % 4;

      if (fwrite(padding, 1, len, bmp.f) != len)
        return -1;
    }

  return 0;
}

int
bmp_close (struct BMP bmp)
{
  return fclose(bmp.f);
}
