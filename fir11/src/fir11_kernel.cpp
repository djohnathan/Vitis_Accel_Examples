/*
        Filename: fir.cpp
                FIR lab wirtten for WES/CSE237C class at UCSD.

        INPUT:
                x: signal (chirp)

        OUTPUT:
                y: filtered output

*/

#include "fir11_kernel.h"

extern "C" {
  void fir(data_t *y, data_t x) {
  #pragma HLS pipeline II = 1
    coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};

    static data_t shift_reg[N];
    #pragma HLS ARRAY_PARTITION variable = shift_reg complete dim = 0
    acc_t acc;
    int i;

    acc = 0;
    TDL:
      for(i = N - 1; i > 0; i--)
      {
        #pragma HLS PIPELINE II = 1
        shift_reg[i] = shift_reg[i-1];
      }
      shift_reg[0] = x;
    MAC:
      for(i = N - 1; i >= 0; i--) {
        #pragma HLS PIPELINE II = 1
        acc += shift_reg[i] * c[i];
      }
    *y = acc;
  }
}
