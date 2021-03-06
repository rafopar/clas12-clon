//  epics_server.h

//  epics server class defs

//  E.Wolin, 3-Jul-03


#include <gddApps.h>
#include <gddAppFuncTable.h>
#include <casdef.h>


#define NDIM 100
#define STRLEN 256


//-------------------------------------------------------------------------


class myPV : public casPV {


private:

  static int ft_is_initialized;
  static gddAppFuncTable<myPV> ft;
  
  
public:

  char *myName;
  aitEnum myType;
  int myDimension;
  int myBound;

  char myCValue;
  char myCArray[NDIM];

  unsigned char myUCValue;
  unsigned char myUCArray[NDIM];

  short mySValue;
  short mySArray[NDIM];

  unsigned short myUSValue;
  unsigned short myUSArray[NDIM];

  int myIValue;
  int myIArray[NDIM];

  unsigned int myUIValue;
  unsigned int myUIArray[NDIM];

  float myFValue;
  float myFArray[NDIM];

  double myDValue;
  double myDArray[NDIM];

  char myString[STRLEN];

  time_t myTime;
  int myStat;
  int mySevr;
  int myMonitor;
  int myUpdate;

  myPV(const char *name, aitEnum type, int size);

  void fillPV(char);
  void fillPV(unsigned char);
  void fillPV(short);
  void fillPV(unsigned short);
  void fillPV(int);
  void fillPV(unsigned int);
  void fillPV(float);
  void fillPV(double);

  void fillPV(char *);
  void fillPV(unsigned char *);
  void fillPV(short *);
  void fillPV(unsigned short *);
  void fillPV(int *);
  void fillPV(unsigned int *);
  void fillPV(float *);
  void fillPV(double *);

  /*void fillPV(char *);  string */


  /*for array -  maxDimension() returns 1, maxBound(0) supplies number of elements in array*/
  unsigned maxDimension () const
  {
    //printf("maxDimension returns %d\n",myDimension);
	return myDimension;
  }

  aitIndex maxBound (unsigned /* dimension */) const
  {
    //printf("maxBound returns %d\n",myBound);
	return myBound;
  }



  caStatus read(const casCtx &ctx, gdd &prototype);

  static void initFT();
  aitEnum bestExternalType() const;

  gddAppFuncTableStatus getVAL(gdd &value);
  /*
  gddAppFuncTableStatus getUNITS(gdd &value);
  gddAppFuncTableStatus getSTAT(gdd &value);
  gddAppFuncTableStatus getSEVR(gdd &value);
  gddAppFuncTableStatus getHIHI(gdd &value);
  gddAppFuncTableStatus getLOLO(gdd &value);
  gddAppFuncTableStatus getHOPR(gdd &value);
  gddAppFuncTableStatus getLOPR(gdd &value);
  gddAppFuncTableStatus getDRVH(gdd &value);
  gddAppFuncTableStatus getDRVL(gdd &value);
  gddAppFuncTableStatus getHIGH(gdd &value);
  gddAppFuncTableStatus getLOW(gdd &value);
  gddAppFuncTableStatus getPREC(gdd &value);
  gddAppFuncTableStatus getENUM(gdd &value);
  */
  caStatus interestRegister();
  void interestDelete();
  epicsShareFunc const char *getName() const;
  void destroy();
  ~myPV();

};


