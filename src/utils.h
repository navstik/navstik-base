/*Created By - Rohit Rangan
 *Created On - 06-07-2012
 *
 *Contains important conversion functions.
 */

#ifndef UTILS_H_
#define UTILS_H_

/*This function converts the halCounter ticks to milliseconds. Call
 *halGetCounterValue() before starting any operation. Assign the value
 *returned to start, the first parameter of this function. After the
 *operation has concluded, the end parameter will be halGetCounterValue().
 */
inline float convertCounterToMilliseconds(uint32_t start, uint32_t end) ;

/*My atan2f function.
 */
inline float my_atan2f(float y, float x) ;

/*Function to calculate regression coefficients for the equation y = a + bx.
 *coeff[0] = a, and coeff[1] = b.
 */
void regressionCoeffs(float *x, float *y, float coeff[2], uint8_t N) ;

/*Function to find the average of the elements in the array x.
 */
float average(float *x, uint8_t N) ;
#endif	/*UTILS_H_ */
