//============== end.cpp      ==================
#include "include.h"
#include <cstdio>
void endsim(){
  rename("conf","conf.old");
  ofstream conf("conf");
  conf << "# Configuration of 2d Ising model on square lattice. Parameters (N=Lx*Ly) and s[N]\n";
  conf << "Lx= "<<L<<" Ly= "<< L << " beta= " << beta
       << " seed= " << int(100000*drandom(mxmx)) << "\n"; //only for compatibility with old "conf" format
  for(int i=0;i<N;i++) conf << s[i] << '\n';
  conf << mxmx << endl;
  conf.close();
}//endsim()
