//============== options.cpp ==================
#include "include.h"
#include <unistd.h>
#include <libgen.h>
//Get the options function: See "man 3 getopt" for usage
//getopt   requires  <unistd.h>
//basename requires  <libgen.h> (see "man 3 basename")
//-------------------------------------------------------
//Set options: Option letters are defined with this string
#define OPTARGS  "hL:b:s:S:n:u"
//-------------------------------------------------------
string prog;
int seedby_urandom();
void get_the_options(int argc,char **argv){
  int c,errflg = 0;
  //prog is the name of executable file
  prog.assign((char *)basename(argv[0]));
  while (!errflg && (c = getopt(argc, argv, OPTARGS)) != -1){
    switch(c){
    case 'L':
      L      = atoi(optarg);
      break;
    case 'b':
      beta   = atof(optarg);
      break;
    case 's':
      start  = atoi(optarg);
      break;
    case 'S':
      seed   = atoi(optarg);
      break;
    case 'n':
      nsweep = atoi(optarg);
      break;
    case 'u':
      seed   = seedby_urandom();
      break;
    case 'h':
      errflg++;/*call usage*/
      break;
    default:
      errflg++;
    }/*switch*/
    if(errflg) usage(argv);
  }/*while...*/
  
}//get_the_options()
//=============================================
// Use /dev/urandom for more randomness.
#include <fcntl.h>
int seedby_urandom(){
  int ur,fd,ir;
  fd = open("/dev/urandom", O_RDONLY);
  ir = read (fd,&ur,sizeof(int));
  close(fd);
  return (ur>0)?ur:-ur;
}
//=============================================
void usage(char **argv){
  /*Careful: New lines end with \n\ : No space after last backslacsh
    indicates line is broken....*/
  cerr << "\
Usage: " << prog << "  [options]                                    \n\
       -L: Lattice length (N=L*L)                                   \n\
       -b: beta  (options beta overrides the one in config)         \n\
       -s: start (0 cold, 1 hot, 2 old config.)                     \n\
       -S: seed  (options seed overrides the one in config)         \n\
       -n: number of sweeps and measurements of E and M             \n\
       -u: seed  from /dev/urandom                                  \n\
Monte Carlo simulation of 2d Ising Model. Metropolis is used by     \n\
default. Using the options, the parameters of the simulations       \n\
must be set for a new run (start=0,1). If start=2, a configuration  \n\
is read from the file conf.\n";
  exit(1);
}//usage()
//=============================================
void locerr( string errmes ){
  cerr << prog << ": " << errmes << " Exiting....\n";
  exit(1); 
}
//=============================================
#include <string.h>
void simmessage(ostream& ostr){
  string notset = "NOTSET";
  char   NOTSET[100];strcpy(NOTSET,notset.c_str());
  time_t t;
  time(&t);/* store time in seconds, see: "man 2 time"  */
  char* TIME = ctime (&t        );if(!TIME) TIME = NOTSET;
  char* USER = getenv("USER"    );if(!USER) USER = NOTSET;
  char* MACH = getenv("HOSTTYPE");if(!MACH) MACH = NOTSET;
  char* HOST = getenv("HOST"    );if(!HOST) HOST = NOTSET;

  ostr << "\
# ###################################################################\n\
#      2d Ising Model with Metropolis algorithm on square lattice    \n\
# Run on "   <<HOST  <<" ( "<<MACH<<" ) by "<<USER<<" on "<<TIME  <<"\
# L       = "<<L     <<" (Lattice linear dimension, N=L*L)           \n\
# seed    = "<<seed  <<" (random number gener. seed)                 \n\
# nsweeps = "<<nsweep<<" (No. of sweeps)                             \n\
# beta    = "<<beta  <<"                                             \n\
# start   = "<<start <<" (0 cold, 1 hot, 2 old config)"<<endl;
}//simmessage()
