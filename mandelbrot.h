#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdlib.h>

/* produce a color value for a point in the mandelbrot set
 *
 * parameters:
 *   dx, dy: coordinates in the plane
 *   color: storage for the produced color value (B, G, R)
 *   max_iteration: the maximum iteration depth to consider
 *   scale: smoothes the color distribution for high zoom levels
 */
void mandelbrot_get(double dx, double dy, unsigned char color[3],
    size_t max_iteration, double scale);

#endif
