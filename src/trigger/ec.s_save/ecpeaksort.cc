
/* ecpeaksort.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <iostream>
using namespace std;

#include <ap_int.h>

#include "eclib.h"

#define MAX(a,b)    (a > b ? a : b)
#define MIN(a,b)    (a < b ? a : b)
#define ABS(x)      ((x) < 0 ? -(x) : (x))



#undef DEBUG

/*xc7vx550tffg1158-1*/

int
ecpeaksort(ECPeak0 peakin[NSTRIP], ECPeak0 peakout[NPEAK])
{
//#pragma HLS PIPELINE
#pragma HLS ARRAY_PARTITION variable=peakin complete dim=1
#pragma HLS ARRAY_PARTITION variable=peakout complete dim=1

  uint8_t i, j;

  ECPeak0 peakswap, peaktmp, peak0[NSTRIP];
#pragma HLS ARRAY_PARTITION variable=peak0 complete dim=1

  uint16_t enswap, enn, en[NSTRIP], en0[NPEAK], en1[NSTRIP];
#pragma HLS ARRAY_PARTITION variable=en complete dim=1

  ap_uint<6> indswap, ind[NSTRIP];
#pragma HLS ARRAY_PARTITION variable=ind complete dim=1


#ifdef DEBUG
  printf("\n\n++ ecpeaksort ++\n");
  printf("BEFOR:\n");
  for(i=0; i<NSTRIP; i++)
  {
    printf("peakin[%2d]: energy=%d, energysum4coord=%d, first strip=%d, number of strips=%d\n",
      i,peakin[i].energy,peakin[i].energysum4coord,peakin[i].strip1,peakin[i].stripn);
  }
#endif




/* 3.46/97/98/0%/0%/~0%/~0% - no pipeline, all complete */
/* 3.39/65/66/0%/0%/~0%/~0% - no pipeline, all complete, peaktmp in the beginning of the loop */
/* 3.39/143/33/0%/0%/4%/9% - pipeline, all complete, peaktmp in the beginning of the loop */
#if 1
  for(i=0; i<NPEAK; i++)
  {
#pragma HLS UNROLL
    peakout[i] = peakin[i];
    en0[i] = peakin[i].energy;
  }

  for(i=NPEAK; i<NSTRIP; i++)
  {
	peaktmp = peakin[i];
	if     ((en0[0]<=en0[1])&&(en0[0]<=en0[2])&&(en0[0]<=en0[3])) j=0;
	else if((en0[1]<=en0[0])&&(en0[1]<=en0[2])&&(en0[1]<=en0[3])) j=1;
	else if((en0[2]<=en0[0])&&(en0[2]<=en0[1])&&(en0[2]<=en0[3])) j=2;
	else if((en0[3]<=en0[0])&&(en0[3]<=en0[1])&&(en0[3]<=en0[2])) j=3;
	if(peakout[j].energy < peaktmp.energy)
    {
	  peakout[j] = peaktmp;
      en0[j] = peaktmp.energy;
    }
  }
#endif



/* 3.36/72/72/0%/0%/3%/8% - pipeline, complete peakout */
/* 3.36/69/ 1/0%/0%/4%/13% - pipeline, complete peakin and peakout */
#if 0
  for(i=0; i<NSTRIP; i++)
  {
    en[i]    = peakin[i].energy;
    ind[i]   = i;
  }

  /*bubble*/
  for(i=1; i<NSTRIP; i++)
  {
    for(j=0; j<(NSTRIP-i); j++)
    {
      if (en[j] < en[j+1])
      {
        enswap = en[j];
        en[j]    = en[j+1];
        en[j+1]  = enswap;

        indswap  = ind[j];
        ind[j]   = ind[j+1];
        ind[j+1] = indswap;
      }
    }
  }

  ecpeaksort_label0:for(i=0; i<NPEAK; i++) peakout[i] = peakin[ind[i]];
#endif



/* 2.39/71/18/0%/0%/11%/23% - bubble sort: pipeline, params not complete */
/* 2.31/68/1/0%/0%/11%/24% - bubble sort: pipeline, params complete */
#if 0
  /* bubble sort */
  for(i=0; i<NSTRIP; i++) peak0[i] = peakin[i];

  for(i=1; i<NSTRIP; i++)
  {
    for(j=0; j<(NSTRIP-i); j++)
    {
      if (peak0[j].energy < peak0[j+1].energy)
      {
        peakswap = peak0[j];
        peak0[j]    = peak0[j+1];
        peak0[j+1]  = peakswap;
      }
    }
  }
  for(i=0; i<NPEAK; i++) peakout[i] = peak0[i];
#endif




#ifdef DEBUG
  printf("AFTER:\n");
  for(i=0; i<NPEAK; i++)
  {
    printf("peakout[%2d]: energy=%d, energysum4coord=%d, first strip=%d, number of strips=%d\n",
      i,peakout[i].energy,peakout[i].energysum4coord,peakout[i].strip1,peakout[i].stripn);
  }
#endif

  return(0);
}
