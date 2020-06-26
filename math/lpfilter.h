#ifndef LPFILTER_H
#define LPFILTER_H


class lpfilter
{
public:
    lpfilter();
    double applyfilter(double newSample);
    void setOld(double input);
    void setAlpha(double input);
private:
    double oldSample;
    double alpha;
    bool firsttime;
};

#endif // LPFILTER_H
