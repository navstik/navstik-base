/*Created By - Rohit Rangan
 *Created On - 06-07-2012
 *
 *Contains important conversion functions.
 */
#include<math.h>

#include "das.h"

inline float convertCounterToMilliseconds(uint32_t start, uint32_t end) {
  return (((float)(end - start) / (float)STM32_SYSCLK) * 1000.0f) ;
}

inline float my_atan2f(float y, float x) {
  if((x > 0) && (y >= 0))
    return atanf(y / x) ;
  else if(x < 0)
    return (M_PI + atanf(y / x)) ;
  else if((x > 0) && (y < 0))
    return (M_TWOPI + atanf(y / x)) ;
  else if((x == 0) && (y < 0))
    return M_PI_2 ;
  else if((x == 0) && (y > 0))
    return (3 * M_PI_2) ;
  else
    return -32768.0 ;
}

void regressionCoeffs(float *x, float *y, float coeff[2], uint8_t N) {
  uint8_t i ;
  float sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xsq = 0.0 ;

  for(i = 0 ; i < N ; i++) {
    sum_x   += x[i] ;
    sum_y   += y[i] ;
    sum_xy  += (x[i] * y[i]) ;
    sum_xsq += (x[i] * x[i]) ;
  }

  coeff[1] = ((sum_xy * N) - (sum_x * sum_y)) / ((N * sum_xsq) - (sum_x * sum_x)) ;
  coeff[0] = (sum_y - (coeff[1] * sum_x)) / N ;
}

float average(float *x, uint8_t N) {
  uint8_t i ;
  float sum = 0.0 ;

  for(i = 0 ; i < N ; i++)
    sum += x[i] ;

  return (sum / (float)N) ;
}
