/*
 *  Test out dbrt_VaPackSql
 *
 * JAM - 8/29/96 - init version
 *
 */
#include <rtworks/ipc.h>
#include <stdlib.h>
#include <sys/wait.h>


#define NUMBER_TO_FORK 1
/* -------------------------------- */
void parse_it (msg)
T_IPC_MSG msg;
{
  T_IPC_FT  ft;
  T_STR     str_val;
  T_REAL4   r4;
  T_INT4    i4;
  T_REAL8   r8;

  if (!TipcMsgSetCurrent (msg, 0))
    error_out ("set current failed\n");
  while (1) {
    if (!TipcMsgNextType (msg, &ft))
      return;

    printf ("t ipc ft = %d\n", ft);
    
    switch (ft) {
    case T_IPC_FT_STR:
      if (!TipcMsgNextStr (msg, &str_val))
	error_out ("could not get next string\n");
      printf ("--> %s\n\n", str_val);
      break;
    case T_IPC_FT_INT4:
      if (!TipcMsgNextInt4 (msg, &i4))
	error_out ("could not get next int4\n");
      printf ("--> %d\n", i4);
      break;
    case T_IPC_FT_REAL4:
      if (!TipcMsgNextReal4 (msg, &r4))
	error_out ("could not get next float4\n");
      printf ("--> %f\n", r4);
      break;
    case T_IPC_FT_REAL8:
      if (!TipcMsgNextReal8 (msg, &r8))
	error_out ("could not get next float8\n");
      printf ("--> %f\n", r8);
      break;
    }
  }
}

/* -------------------------------- */
main ()
{
  T_IPC_MSG msg;
  T_OPTION  option;
  int       r, stat_location, mp, j, cnt;
  float     aFloat[5]; 
  pid_t     pids[512];
  char      id_str[20];


  strcpy (id_str, "stupid");
  r = ipc_init (id_str, "MrMagoo") ;
  dbrt_SetDest ("james");
  if (r != 0) {
    printf ("ipc_init failed with: %d\n", r);
    exit (0);
  }
  
  for (r = 0; r<5; r++)
    aFloat[r] = drand48();
      
  r = dbrt_VaSendSql (1234, "Hello Elliott", 
		      4321, "Hello James", 
		      987,"killer dude", NULL);

  if (r <= 0)
    ipc_PackError ();

  r = dbrt_VaSendRow ("XYZ_TABLE",
			
			"XYZ_comment", 
			"str", 
			"A stupid comment", 
			
			"XYZ_col1",
			"flt8",
			aFloat[0],
			
			"XYZ_col2",
			"flt4",
			aFloat[1],
			
			"XYZ_col3",
			"flt4",
			aFloat[2],
			
			"XYZ_col4",
			"flt4",
			aFloat[3],
			
			"XYZ_col5",
			"flt4",
			aFloat[4],
			
			NULL) ;
  
  if (r <= 0)
    ipc_PackError () ;

  printf ("done ...\n");
}