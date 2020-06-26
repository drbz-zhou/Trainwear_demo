#include "lpfilter.h"

lpfilter::lpfilter()
{
    oldSample = 0;
    alpha = 1.0/3.0;
    firsttime = true;
}
double lpfilter::applyfilter(double newSample){
    if(firsttime){
        oldSample = newSample;
        firsttime=false;
    }else{
        oldSample = alpha * newSample + (1-alpha) * oldSample;
    }
    return oldSample;
}
void lpfilter::setOld(double input){
    oldSample=input;
}
void lpfilter::setAlpha(double input){
    alpha = input;
}
