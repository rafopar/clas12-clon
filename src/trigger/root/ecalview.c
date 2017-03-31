/*
   ecalview.c - draw ECAL geometry, hits and clusters

*/


#define NOFFSETS 16
#define NWIRES 112

#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <termios.h>
#include <unistd.h>

#include "prlib.h"

#include "evio.h"

#ifdef USE_PCAL
#include "pclib.h"
static uint8_t iview[3] = {84,77,77}; /* the number of strips in different views */
#else
#include "eclib.h"
static uint8_t iview[3] = {NSTRIP,NSTRIP,NSTRIP}; /* the number of strips in different views */
#endif

#define ABS(x) ((x) < 0 ? -(x) : (x))


TText t(0,0,"a");
static float ticksize = 0.0;
static int polyline_color_index = 0;
static int polymarker_color_index = 0;
static int marker_type = 0;

#define IGAXIS(x0,x1,y0,y1,wmin,wmax,ndiv,chopt) \
{ \
  TGaxis *fAxis = new TGaxis(x0,y0, x1,y1, wmin,wmax, ndiv, chopt); \
  if(ticksize>0.0) fAxis->SetTickSize(ticksize); /*set by IGSET*/ \
  fAxis->Draw();											  \
}

/*polyline color index*/
#define ISPLCI(icoli) \
{ \
  polyline_color_index = icoli; \
}

/*polymarker color index*/
#define ISPMCI(icoli) \
{ \
  polymarker_color_index = icoli; \
}

/*marker type*/
#define ISMK(mtype) \
{ \
  marker_type = mtype; \
}

#define IGBOX(x_min, x_max, y_min, y_max) \
{ \
  Float_t x1 = x_max; \
  Float_t y1 = y_min; \
  Float_t x2 = x_min; \
  Float_t y2 = y_max; \
  TBox* box = new TBox(x1,y1,x2,y2); \
  box->Draw();					 \
}

#define IGTEXT(x,y,chars,size,angle,chopt) \
{ \
  t.SetTextFont(62); \
  t.SetTextSize(size/10.); \
  t.SetTextAlign(12); \
  t.DrawText(x,y,chars);					\
}

#define IPL(n, x, y) \
{ \
  /*TPolyLine * */pl = new TPolyLine(n,x,y);	\
  pl->SetLineColor(polyline_color_index); \
  /*pl->SetFillColor(3);*/				  \
  /*pl->Draw("f");*/					  \
  pl->Draw(); \
}

/*draw polymarker*/
#define IPM(n, x, y) \
{ \
  TPolyMarker *pm = new TPolyMarker(n);	  \
  pm->SetMarkerColor(polymarker_color_index); \
  pm->SetMarkerStyle(marker_type); \
  for(Int_t i=0; i<n; i++) pm->SetPoint(i,x[i],y[i]); \
  pm->Draw();										  \
}

#define IPM_DC(n, x, y, t)			\
{ \
  /*TArc *circle = new TArc();*/				\
  circle->SetLineColor(polymarker_color_index); \
  for(Int_t i=0; i<n; i++) \
  { \
    circle->DrawArc(x[i],y[i],t[i]);		\
  } \
}

#define IPM_ELLIPSE(n, x, y, tlong, tshort) \
{ \
  TEllipse *ellipse = new TEllipse(); \
  ellipse->SetLineColor(polymarker_color_index); \
  for(Int_t i=0; i<n; i++) \
  { \
    ellipse->DrawEllipse(x[i],y[i],tlong[i],tshort[i],0.,360.,0.); \
  } \
}

/*set parameter (here always "TMSI" - Tick Marks Size for axis (in world coordinates))*/
#define IGSET(chname, val) \
{ \
  ticksize = val; \
}

#define REDRAW \
  if(fCanvas>0) \
  { \
    fCanvas->Modified(); \
    fCanvas->Update(); \
  }






int
mygetch (void) 
{
  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}




static int iev = 0;
static int goodevent;

#define MAXBUF 1000000
unsigned int buf[MAXBUF];

static double xmin, ymin, xmax, ymax;
static double xdiff, ydiff, xdelta[3], xx1, xx2, yy1, yy2;
static double viewx0[3], viewy0[3], viewx1[3], viewy1[3], viewangle[3], viewcosa[3], viewsina[3];
static double dxy = 5.0;

/*ECAL*/
static ECStrip strip[2][3][NSTRIP];
static ECPeak peak[3][NPEAK];
static uint8_t nhits;
static ECHit hit[NHIT];

static int npeaks_trig[NLAYER]; 
static TrigECPeak peaks_trig[NLAYER][NPEAKMAX];
static int nhits_trig[2];
static TrigECHit hits_trig[2][NHITMAX];

typedef struct drawobject *DrawObjectPtr;
typedef struct drawobject
{
  TObject *obj;
  char name[128];
  double energy;

} DrawObject;


#define NDOBJ 500
static int ndobj = 0;
DrawObject dobj[NDOBJ];


void
place_pmt(int view, double x0pmt, double y0pmt, double h1, double h2, double angle, double xdelta,
          double x[5], double y[5], int level)
{
  int ii;
  double xx[5], yy[5], cosa, sina, delta;

#ifdef USE_PCAL
  /* 0 degree - vertical up, negative - rotate right, positive - rotate left */
  if(view==0)      angle = -(90.0+62.9)*M_PI/180.0;
  else if(view==1) angle = -(90.0-54.2)*M_PI/180.0;
  else if(view==2) angle = 90*M_PI/180.0;
#else
  angle = angle - 150.0*M_PI/180.0;
#endif
  cosa = cos(angle);
  sina = sin(angle);

  /*printf("ANGLE=%f COSA=%f\n",angle,cosa);*/

  delta = xdelta*(1.0-(double)level*(1./(NHIT+1)));

  xx[0] = x0pmt - delta*0.866/2.;
  xx[1] = xx[0] + delta*0.866;
  xx[2] = xx[1];
  xx[3] = xx[0];
  xx[4] = xx[0];

  yy[0] = y0pmt + h1;
  yy[1] = y0pmt + h1;
  yy[2] = y0pmt + h2;
  yy[3] = y0pmt + h2;
  yy[4] = yy[00];
  
  for(ii=0; ii<5; ii++)
  {
    x[ii] = ((xx[ii]-x0pmt) * cosa - (yy[ii]-y0pmt) * sina) + x0pmt;
    y[ii] = ((yy[ii]-y0pmt) * cosa + (xx[ii]-x0pmt) * sina) + y0pmt;
  }
  
}

void
place_line(int view, double x0pmt, double y0pmt, double angle, double xdelta, double x[2], double y[2])
{
  int ii;
  double xx[2], yy[2], cosa, sina;

#ifdef USE_PCAL
  if(view==0)      angle = (180.0-(90.0+62.9))*M_PI/180.0;
  else if(view==1) angle = (180.0-(90.0-54.2))*M_PI/180.0;
  else if(view==2) angle = (180.+90)*M_PI/180.0;
#else
  angle = angle + 30.0*M_PI/180.0;
#endif

  cosa = cos(angle);
  sina = sin(angle);

  xx[0] = x0pmt;
  xx[1] = xx[0];

  yy[0] = y0pmt;
  yy[1] = y0pmt + xdelta*((double)NSTRIP);
  
  for(ii=0; ii<2; ii++)
  {
    x[ii] = ((xx[ii]-x0pmt) * cosa - (yy[ii]-y0pmt) * sina) + x0pmt;
    y[ii] = ((yy[ii]-y0pmt) * cosa + (xx[ii]-x0pmt) * sina) + y0pmt;
  }

}



int
draw_ecstrips(TCanvas *fCanvas, double energy[NHIT+1][3][NSTRIP], int maxen)
{
#if 1
  int ii, jj, kk, view, color;
  double emax;
  double x0pmt[3][NSTRIP], y0pmt[3][NSTRIP], x1pmt[3][NSTRIP], y1pmt[3][NSTRIP], x0, y0;
  double xx[NSTRIP][5], yy[NSTRIP][5];
  double x[NSTRIP][5], y[NSTRIP][5];
  double xl[2], yl[2];
  double endraw;
  TPolyLine *pl;
  char txt[128];
#endif

  /*
  printf("draw_ecstrips reached\n");fflush(stdout);
return(0);
  */

#if 1
  /* found max energy */
  emax = 0.;

  /* find maximum energy */
  for(kk=0; kk<maxen; kk++) for(jj=0; jj<3; jj++) for(ii=0; ii<NSTRIP; ii++) if(emax < energy[kk][jj][ii]) emax = energy[kk][jj][ii];
#endif

#if 1
  /* normalize energy (divide 'ydiff' as needed!) */
  for(kk=0; kk<maxen; kk++) for(jj=0; jj<3; jj++) for(ii=0; ii<NSTRIP; ii++) energy[kk][jj][ii] = ( energy[kk][jj][ii] * (ydiff/5.) )/ emax;
#endif

  if(fCanvas>0)
  {

#if 1

    for(view=0; view<3; view++) /* loop over views */
	{
      color = 1;


      for(ii=0; ii<iview[view]/*NSTRIP*/; ii++)
	  {

        x0pmt[view][ii] = xx1 + xdelta[view]/2. + xdelta[view]*ii;
        y0pmt[view][ii] = yy1;
		//printf("XY1: %f %f\n",x0pmt[view][ii],y0pmt[view][ii]);fflush(stdout);



        /* U-V-W adjustment */
        x0 = ((x0pmt[view][ii]-xx1) * viewcosa[view] - (y0pmt[view][ii]-yy1) * viewsina[view]) + viewx0[view];
        y0 = ((y0pmt[view][ii]-yy1) * viewcosa[view] + (x0pmt[view][ii]-xx1) * viewsina[view]) + viewy0[view];
		//printf("XY2: %f %f\n",x0,y0);fflush(stdout);



        /* draw original energy */
        place_pmt(view,x0,y0,0.0,energy[0][view][ii],viewangle[view],xdelta[view],x[ii],y[ii],0);
        ISPLCI(color);
        IPL(5,x[ii],y[ii]);
            dobj[ndobj].obj = pl;
            strncpy(txt,"initial energy",127);
            strncpy(dobj[ndobj].name,txt,strlen(txt));
            dobj[ndobj].energy = energy[0][view][ii];
            ndobj ++;
        /*endraw = energy[0][view][ii];*/


		/* draw corrected energies */
        for(kk=0; kk<maxen-1; kk++)
		{
          place_pmt(view,x0,y0,0.0/*endraw*/,energy[kk+1][view][ii],viewangle[view],xdelta[view],x[ii],y[ii],kk+1);
          ISPLCI(color+1+kk);
          if(energy[kk+1][view][ii]>0.)
		  {
            IPL(5,x[ii],y[ii]);

            dobj[ndobj].obj = pl;
            strncpy(txt,"corrected energy",127);
            strncpy(dobj[ndobj].name,txt,strlen(txt));
            dobj[ndobj].energy = energy[kk+1][view][ii];
            ndobj ++;
		  }
          /*endraw = energy[kk+1][view][ii];*/
		}

      }


	} /* loop over views */

#endif

  }

}










void
draw_init()
{
  int view;
  double angle, cosa, sina, xdelta0, x0, y0, x1, y1, h, len1;

  printf("draw_init reached, xmin=%f, xmax=%f, ymin=%f, ymax=%f\n",xmin,xmax,ymin,ymax);fflush(stdout);

#ifdef USE_PCAL

  /*

                          x
                         x62.9deg
                        x
                       x
                      x   |
                     x    |
                    x     |
           432.7cm x      |          394.2cm
                  x       |
                 x        |
                x      h=350.9473
               x          |
              x           |
             x            | 
            x             |
           x54.2deg       |              62.9deg
    beam  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    here      len1=cm      432.7cm

  */

  /*1/4 of drawing area*/
  dxy = FULLSIZE/4. /*432.7/2*/;

  /* staring point for drawing (left bottom corner */
  xx1 = xmin + dxy;
  yy1 = ymin + dxy;

  xx2 = xmax - dxy; /*not used*/
  yy2 = ymax - dxy; /*not used*/

  h = 432.7*sin(54.2*M_PI/180.0);
  len1 = sqrt( pow(432.7,2.) - pow(h,2.) );

  xdiff = 432.7;
  ydiff = 410.0 /* approximately */;

#else
  dxy = (xmax-xmin)/4.0;
  xx1 = xmin + dxy;
  xx2 = xmax - dxy;
  yy1 = ymin + dxy;
  yy2 = ymax - dxy;
  xdiff = xx2 - xx1;
  ydiff = yy2 - yy1;
#endif

  for(view=0; view<3; view++)
  {

#ifdef USE_PCAL
    if(view==0)
	{
      angle = 0.0 * M_PI / 180.0;
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = 432.7 / (double)iview[view];
      x0 = dxy;
      y0 = dxy;
      x1 = x0+432.7;
	  y1 = y0;
	}
    else if(view==1)
	{
	  /* rotation */
      angle = (180. - 62.9) * M_PI / 180.0;
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = 394.2 / (double)iview[view];
      x0 = x1; /* end of previous view */
      y0 = y1; /* end of previous view */
      x1 = dxy+len1;
      y1 = y0+h;
	  printf("++++++++++++++ h=%f len1=%f -> %f %f\n",h,len1,x1,y1);
	}
    else if(view==2)
	{
	  /* rotation */
      angle = -(180. - 54.2) * M_PI / 180.0;
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = 432.7 / (double)iview[view];
      x0 = x1;
      y0 = y1;
      x1 = viewx0[0]; /* returns to starting point */
      y1 = viewy0[0]; /* returns to starting point */
    }
#else
    if(view==0)
	{
      angle = 0.0 * M_PI / 180.0;
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = xdiff / (double)NSTRIP;
      x0 = dxy;
      y0 = dxy;
	}
    else if(view==1)
	{
	  /* rotation */
      angle = 120.0 * M_PI / 180.0; /* convert 120 degree to radians */
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = xdiff / (double)NSTRIP;
      x0 = xmax-dxy;
      y0 = dxy;
	}
    else if(view==2)
	{
	  /* rotation */
      angle = -120.0 * M_PI / 180.0; /* convert 120 degree to radians */
      cosa = cos(angle);
      sina = sin(angle);
      xdelta0 = xdiff / (double)NSTRIP;
      x0 = (xmax-xmin)/2.0;
      y0 = dxy + ydiff*ABS(sina);
    }
#endif

    xdelta[view] = xdelta0;
    viewangle[view] = angle;
    viewcosa[view] = cosa;
    viewsina[view] = sina;
    viewx0[view] = x0;
    viewy0[view] = y0;

#ifdef DEBUG
    printf("draw_init: view=%d cosa=%f sina=%f xdelta=%f xdiff=%f, y0=%f\n",view,cosa,sina,xdelta0,xdiff,y0);
#endif
  }

  printf("draw_init done\n");fflush(stdout);

  return;
}



void
ecaldrawevent(TCanvas *fCanvas)
{
  int io=0;
  int ii, jj, kk, nn;
  double energy[NHIT+1][3][NSTRIP];
  double corenergy[NSTRIP];
  double coord[3];
  TPolyLine *pl;
  TArc *circle;
  char txt[128];

  ndobj = 0;
  double A[3], B[3], C[3], DET, X[3], Y[3], XX, YY, ENERGY;

  fCanvas->GetRange(xmin,ymin,xmax,ymax);
#ifdef DEBUG
  printf("ecaldrawevent: xmin=%f xmax=%f ymin=%f ymax=%f\n",xmin,xmax,ymin,ymax);
#endif

  fCanvas->Clear();

#ifdef DEBUG
  printf("- ecaldrawevent: xx1=%f xx2=%f yy1=%f yy2=%f dxy=%f -> xdiff=%f ydiff=%f\n",xx1,xx2,yy1,yy2,dxy,xdiff,ydiff);fflush(stdout);
#endif

  draw_init();

  /* copy initial energies for drawing */
  for(ii=0; ii<3; ii++) for(jj=0; jj<NSTRIP; jj++) energy[0][ii][jj] = strip[io][ii][jj].energy;

  cout<<"11: nhits="<<+nhits<<endl;fflush(stdout);


  for(kk=0; kk<nhits; kk++)
  {
    int color = kk+2;
    double x0pmt, y0pmt, x0, y0, xl[2], yl[2];

    printf("22\n");fflush(stdout);
#ifdef USE_PCAL	
    for(ii=0; ii<3; ii++) coord[ii] = (double)hit[kk].coord[ii]/(double)fview[ii];
#else
    for(ii=0; ii<3; ii++) coord[ii] = (double)hit[kk].coord[ii]/8.0;
#endif
    cout<<"ecaldrawevent: hit["<<+kk<<"]: energy="<<+hit[kk].energy<<" coord="<<+coord[0]<<" "<<+coord[1]<<" "<<+coord[2]<<endl;

    printf("33\n");fflush(stdout);

    /* loop over 3 views calculating correction for every strip*/
    ENERGY = 0.0;
    for(jj=0; jj<3; jj++)
	{
      int energy0, energy1, strip1, stripn; /* peak values */


#if 0
	  /*HAVE TO REDO, NO SUCH ELEMENTS IN STRUCTURE !!!*/
      energy0 = peak[jj][hit[kk].peak1[jj]].energy;
      strip1  = peak[jj][hit[kk].peak1[jj]].strip1;
      stripn  = peak[jj][hit[kk].peak1[jj]].stripn;
      energy1 = hit[kk].corren[jj];
      cout<<"  ecaldrawevent: hit["<<+kk<<"] strips["<<+jj<<"]: strip1="<<+strip1<<", stripn="<<+stripn<<", energy0="<<+energy0<<", energy1="<<+energy1<<endl;
	  for(nn=0; nn<NSTRIP; nn++) corenergy[nn] = 0.0;
      for(nn=strip1; nn<strip1+stripn; nn++)
	  {
        corenergy[nn] = (double)strip[io][jj][nn].energy * ((double)energy1) / ((double)energy0); /* for drawing */
        cout<<"    ecaldrawevent: strip["<<+jj<<"]["<<+nn<<"] energy = "<<+strip[io][jj][nn].energy<<" -> corrected strip energy = "<<+corenergy[nn]<<endl;
	  }
#endif





#if 1

      x0pmt = xx1 + xdelta[jj]*coord[jj];
      cout << "++++++++++++++++++++ " << +hit[kk].coord[jj] << endl;
      y0pmt = yy1;
	  //printf("XY3: %f %f\n",x0pmt,y0pmt);

      x0pmt += kk*(xdelta[jj]/5.); /*???????????????*/

      /* U-V-W adjustment */
      x0 = ((x0pmt-xx1) * viewcosa[jj] - (y0pmt-yy1) * viewsina[jj]) + viewx0[jj];
      y0 = ((y0pmt-yy1) * viewcosa[jj] + (x0pmt-xx1) * viewsina[jj]) + viewy0[jj];
	  //printf("XY4: %f %f\n",x0,y0);

      place_line(jj, x0, y0, viewangle[jj], xdelta[jj], xl, yl);
      ISPLCI(color);
      IPL(2,xl,yl);
            dobj[ndobj].obj = pl;
            sprintf(txt,"hit %d, view %d\0",kk,jj);
            strcpy(dobj[ndobj].name,txt);
            dobj[ndobj].energy = energy0;
            ndobj ++;

      /* copy corrected energies for drawing */
      for(nn=0; nn<NSTRIP; nn++)
	  {
        energy[kk+1][jj][nn] = corenergy[nn]; /* kk+1 - ERRORRRRRRRRRRRRRR ???*/
        //printf("HIT %d: coping energy energy[%d][%d][%d]=%f\n",kk,kk+1,jj,nn,energy[kk+1][jj][nn]);
	  }

      /* calculate some values for the following line-line crossing */
      A[jj] = yl[1] - yl[0];
      B[jj] = xl[0] - xl[1];
      C[jj] = A[jj] * xl[0] + B[jj] * yl[0];
      ENERGY += energy0;

#endif

	}

	/* line-line cross
    A = y2-y1
    B = x1-x2
    C = A*x1+B*y1

    A1*x + B1*y = C1
    A2*x + B2*y = C2

    double det = A1*B2 - A2*B1
    if(det == 0){
        //Lines are parallel
    }else{
        double x = (B2*C1 - B1*C2)/det
        double y = (A1*C2 - A2*C1)/det
	*/

#if 1

    /* draw circle here */
    DET = A[0] * B[1] - A[1] * B[0];
    X[0] = (B[1]*C[0] - B[0]*C[1]) / DET;
    Y[0] = (A[0]*C[1] - A[1]*C[0]) / DET;

    DET = A[1] * B[2] - A[2] * B[1];
    X[1] = (B[2]*C[1] - B[1]*C[2]) / DET;
    Y[1] = (A[1]*C[2] - A[2]*C[1]) / DET;

    DET = A[0] * B[2] - A[2] * B[0];
    X[2] = (B[2]*C[0] - B[0]*C[2]) / DET;
    Y[2] = (A[0]*C[2] - A[2]*C[0]) / DET;

    XX = (X[0]+X[1]+X[2])/3.;
	YY = (Y[0]+Y[1]+Y[2])/3.;

    circle = new TArc(XX,YY,0.1);
	printf("OBJ circle=0x%08x\n",circle);
    circle->SetLineColor(color);
    circle->Draw();
            dobj[ndobj].obj = circle;
            sprintf(txt,"hit %d\0",kk);
            strcpy(dobj[ndobj].name,txt);
            dobj[ndobj].energy = ENERGY;
            ndobj ++;

#endif

  }



  printf("44\n");fflush(stdout);

  /* draw */
  draw_ecstrips(fCanvas, energy, nhits+1 /* +1 ?????????*/);
  
  printf("55\n");fflush(stdout);

  return;
}




#ifdef USE_PCAL
#define ecstrips pcstrips
#define ecstrip pcstrip
#define ecpeak pcpeak
#define ecpeaksort pcpeaksort
#define ecpeakcoord pcpeakcoord
#define echit pchit
#define ecfrac pcfrac
#define eccorr pccorr
#endif


#define THRESHOLD1 ((uint16_t)1)
#define THRESHOLD2 ((uint16_t)1)
#define THRESHOLD3 ((uint16_t)3)

int
ecalgetevent(int handler, TCanvas *fCanvas, int sec)
{
  int status, nogoodevents;
  unsigned int *bufptr;
  const unsigned short threshold[3] = {1,1,3};

  ECStrip strip[3][NSTRIP];

  int i, ii, jj, kk, io, ret;

#ifdef DEBUG
   printf("ecalgetevent reached\n");
#endif

  nogoodevents = 1;
  while(nogoodevents)
  {
    status = evRead(handler, buf, MAXBUF);
    if(status < 0)
    {
      if(status==EOF)
	  {
        printf("end of file after %d events - exit\n",iev);
        return(EOF);
	  }
      else
	  {
        printf("evRead error=%d after %d events - exit\n",status,iev);
	  }
      return(-1);
    }

    iev ++;
    bufptr = (unsigned int *) buf;


	
    ectrig(bufptr, sec, npeaks_trig, peaks_trig, nhits_trig, hits_trig);
    for(ii=0; ii<3/*NLAYER*/; ii++)
	{
      for(jj=0; jj<npeaks_trig[ii]; jj++)
	  {
        cout<<"TRIG PEAK ["<<+ii<<"]["<<+jj<<"]:  coord="<<peaks_trig[ii][jj].coord<<"   energy="<<peaks_trig[ii][jj].energy<<"   time="<<peaks_trig[ii][jj].time<<endl;
	  }
	}
    for(ii=0; ii<1/*2*/; ii++)
	{
      for(jj=0; jj<nhits_trig[ii]; jj++)
	  {
        cout<<"TRIG HIT ["<<+ii<<"]["<<+jj<<"]:  coord="<<hits_trig[ii][jj].coord[0]<<" "<<hits_trig[ii][jj].coord[1]<<" "<<hits_trig[ii][jj].coord[2]<<"   energy="<<hits_trig[ii][jj].energy<<"   time="<<hits_trig[ii][jj].time<<endl;
	  }
	}
	


	//#ifdef USE_PCAL
	//#else
    /*ECAL*/
    io = 0;
    if(ecstrips(bufptr, threshold[0], sec, io, strip) > 0)
    {

#ifdef USE_PCAL
      nhits = pcal(strip, hit);
#else
      nhits = ecal(strip, hit);
#endif


	  /*
	  if(io==0) printf("INNER\n");
      else if(io==1) printf("OUTER\n");
  	  */
#ifdef DEBUG
	  cout<<"ecalgetevent: sec=" << +sec << " nhits=" << +nhits << endl;
#endif
#ifdef DEBUG	  
	  if(io==0) printf("INNER\n");
	  else if(io==1) printf("OUTER\n");
	  cout<<"ecl3: nhits="<<+nhits<<endl;
      for(ii=0; ii<nhits; ii++)
	  {
        cout<<"ecl3: hit["<<+ii<<"]: energy="<<+hit[ii].energy<<" coordU="<<+hit[ii].coord[0]<<" coordV="<<+hit[ii].coord[1]<<" coordW="<<+hit[ii].coord[2]<<endl;
	  }
#endif
    }
	//#endif



    goodevent=1;
    nogoodevents=0;


  } /*while(nogoodevents)*/

#ifdef DEBUG
  printf("ecalgetevent done, iev=%d\n",iev);
#endif

  return(nhits);
}






static int ifirst = 1;

#define STRLEN 128


int
ecalview(int handler, TCanvas *fCanvas, int redraw)
{
  int sec = 0; /* 1 for sector 2  (all simulation is sector 2) */
  TArc *circle = new TArc();

  int ret;

#ifdef DEBUG
  printf("ecalview reached\n");fflush(stdout);
#endif

  /*should do it once*/
  /* if(first) */
  {
    ifirst = 0;
  }


  if(handler > 0)
  {
readnext:
    ret = ecalgetevent(handler, fCanvas, sec);
    /*if(ret==0) goto readnext;*//*return(0);*/ /* no hits */
    if(ret==EOF) return(EOF);
  }

  if(redraw) ecaldrawevent(fCanvas);
  printf("65\n");fflush(stdout);
  /*sleep(3);*/
  printf("66\n");fflush(stdout);


#ifdef DEBUG
  printf("ecalview done, iev=%d\n",iev);fflush(stdout);
#endif

  return(0);
}
