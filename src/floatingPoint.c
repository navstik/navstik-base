/*Created By - Riya Ray
 *Created On - 18-06-2012
 *
 *This file contains all the floating point functions.
 */

#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "das.h"

#if CORTEX_USE_FPU && DAS_USE_FPUTEST
float fpuTest(BaseSequentialStream *bss, char *operand1, char oper, char *operand2) {
  float float1 = 0.0, float2 = 0.0, ans = 0.0;
  float1 = atof(operand1);
  float2 = atof(operand2);

  switch(oper){
  case '+': ans = float1 + float2;
    break;
  case '-': ans = float1 - float2;
    break;
  case '*': ans = float1 * float2;
    break;
  case '/': ans = float1 / float2;
    break;
  case 's': ans = sinf((float)float1/180*M_PI);
    break;
  case 'c': ans = cosf((float)float1/180*M_PI);
    break;
  case 't': ans = tanf((float)float1/180*M_PI);
    break;
  case 'p': ans = powf(float1, float2);
    break;
  case 'l': ans = (logf(float1)/logf(float2));
    break;
  case 'r': ans = (float)sqrt(float1);
    break;
  default: chprintf(bss, "Not a valid operator\r\n");
    break;
  }
  return ans;
}
#endif   /*CORTEX_USE_FPU && DAS_USE_FPUTEST */
