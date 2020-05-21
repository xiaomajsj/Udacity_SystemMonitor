#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<string>
#include<time.h>
#include <vector>


using std::string;
using std::vector;

class Processor {

 public:
  float Utilization();  // TODO: See src/processor.cpp
// TODO: Declare any necessary private members

 private:
 float Utili;
 float UtiliNew;
 vector<float> CpuState;
 vector<float> CpuStateNew;
 bool StateRefresh=true;
 long StartTime=clock();
 vector<float> TransEle(vector<string> input);
};

#endif