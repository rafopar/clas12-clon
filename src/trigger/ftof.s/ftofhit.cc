
/* ftofhit.c - 

  input:  

  output: 

*/

	
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <iostream>
using namespace std;



#include "ftoflib.h"



#define DEBUG


#define MAX(a,b)    (a > b ? a : b)
#define MIN(a,b)    (a < b ? a : b)
#define ABS(x)      ((x) < 0 ? -(x) : (x))

#define NPIPE 24 /* the number on 4ns slices to keep and use in ftofhit logic; will be shifted 8 elements right on every call */

/*xc7vx550tffg1158-1*/


/* 1.96/46/8/0%/0%/(10270)1%/(5734)1% II=8 */

void
ftofhit(nframe_t nframes, FTOFStrip_s s_strip[NH_READS], FTOFHit s_hit[NH_READS])
{
//#pragma HLS INTERFACE ap_stable port=nframes
#pragma HLS PIPELINE II=1

  static ap_uint<NSTRIP> outL[NPIPE], outR[NPIPE];

  ap_uint<NSTRIP> output[NH_READS];

#ifdef DEBUG
  for(int j=0; j<NH_READS; j++)
  {
    cout<<"ftofhit: s_strip["<<j<<"].outL="<<hex<<s_strip[j].outL<<dec<<endl;
    cout<<"ftofhit: s_strip["<<j<<"].outR="<<hex<<s_strip[j].outR<<dec<<endl;
  }
#endif

  /* shift old data 8 elements to the right */
  for(int i=15; i>=0; i--)
  {
	outL[i+8] = outL[i];
	outR[i+8] = outR[i];
  }


  /* get new data */
  for(int j=0; j<NH_READS; j++)
  {
    outL[j]  = s_strip[j].outL;
    outR[j]  = s_strip[j].outR;
  }


#ifdef DEBUG
  for(int i=NPIPE; i>=0; i--)
  {
    cout<<"ftofhit: outL[pipe="<<i<<"]="<<hex<<outL[i]<<dec<<endl;
    cout<<"ftofhit: outR[pipe="<<i<<"]="<<hex<<outR[i]<<dec<<endl;
  }
#endif



  /* check for left-right coincidence withing 'nframes' interval */

  for(int i=8; i<16; i++) /* take middle interval left PMTs, and compare with +-(NPER/2) right PMTs */
  {
    output[i-8] = 0;
    for(int j=i-(NPER/2); j<=i+(NPER/2); j++) output[i-8] |= outL[i] & outR[j];
  }


  /* send trigger solution */
  for(int j=0; j<NH_READS; j++)
  {
#ifdef DEBUG
    cout<<"ftofhit: output["<<j<<"]="<<hex<<output[j]<<dec<<endl;
#endif
    s_hit[j].output = output[j];
  }
}
