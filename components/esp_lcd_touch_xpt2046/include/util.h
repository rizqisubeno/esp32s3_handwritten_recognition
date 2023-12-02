#ifndef __UTIL__
#define __UTIL__

double scale(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
  return (double)((x - in_min) * (out_max - out_min)) / (double)((in_max - in_min)) + (double)out_min;
}

#endif