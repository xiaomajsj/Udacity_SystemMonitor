#include "processor.h"
#include "linux_parser.h"


template <class Type>

Type stringToNum(string &str){
std::istringstream iss(str);
Type num;
iss>>num;
return num;
}

using std::vector;
using std::string;


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

long TestDuration=1000; //every one second check

float Idle;
float PrevIdle;
float NonIdle;
float PrevNonIdle;
float Total;
float PrevTotal;
float totald;
float idled;

if(StateRefresh==true){
CpuState=TransEle(LinuxParser::CpuUtilization());
StateRefresh=false;
}

if(clock()-StartTime>TestDuration){
CpuStateNew=TransEle(LinuxParser::CpuUtilization());

PrevIdle=CpuState[LinuxParser::kIdle_]+CpuState[LinuxParser::kIOwait_];
PrevNonIdle=CpuState[LinuxParser::kUser_]+CpuState[LinuxParser::kNice_]+CpuState[LinuxParser::kSystem_]+CpuState[LinuxParser::kIRQ_]+CpuState[LinuxParser::kSoftIRQ_]+CpuState[LinuxParser::kSteal_];
PrevTotal=PrevIdle+PrevNonIdle;

Idle=CpuStateNew[LinuxParser::kIdle_]+CpuStateNew[LinuxParser::kIOwait_];
NonIdle=CpuStateNew[LinuxParser::kUser_]+CpuStateNew[LinuxParser::kNice_]+CpuStateNew[LinuxParser::kSystem_]+CpuStateNew[LinuxParser::kIRQ_]+CpuStateNew[LinuxParser::kSoftIRQ_]+CpuStateNew[LinuxParser::kSteal_];
Total=Idle+NonIdle;

totald=Total-PrevTotal;
idled=Idle-PrevIdle;

if(totald==0){
UtiliNew=(PrevTotal-PrevIdle)/PrevTotal;
}
else {UtiliNew=(totald-idled)/totald;}

StateRefresh=true;
StartTime=clock();
}

return UtiliNew;

}

vector<float> Processor::TransEle(vector<string> input){
vector<float> output;
float ele;
for(unsigned int i=0;i<(input.size()-1);i++){
ele=stringToNum<float>(input[i]);
output.push_back(ele);
}
return output;
}

