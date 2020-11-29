#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

/*
 * SimpleAnomalyDetector.h
 *
 * Author: 322567041 , Hadassa Danesh
 */

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;

struct correlatedFeatures
{
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector
{
    vector<correlatedFeatures> cf;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    string *findMostCorrelatedFeature(string feature, const TimeSeries &ts);
    void getLinearReg(correlatedFeatures &correlatedStruct, const TimeSeries &ts);

    virtual void learnNormal(const TimeSeries &ts);
    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel()
    {
        return cf;
    }
    vector<correlatedFeatures> *getCf()
    {
        return &cf;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
