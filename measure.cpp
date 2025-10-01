//============== measure.cpp ==================
#include "include.h"

void measure(){
  cout << E() << " " << M() << '\n';
}

int E(){
  int e,snn,i,nn;
  e=0;
  for(i=0;i<N;i++){
    //Sum of neighboring spins:
    //only forward nn necessary in the sum
    if((nn=i+XNN)>= N) nn -= N; snn  = s[nn];
    if((nn=i+YNN)>= N) nn -= N; snn += s[nn];
    e += snn*s[i];
  }
  return -e;
}

int M(){
  int i,m;
  m=0;
  for(i=0;i<N;i++) m+=s[i];
  return m;
}

