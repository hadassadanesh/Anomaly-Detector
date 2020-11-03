#include <string>
#include <vector>
using std::vector;
using std:: string;
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"

struct correlatedFeatures{
    string feature1,feature2;
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
public:
      SimpleAnomalyDetector();
      virtual ~SimpleAnomalyDetector();
      virtual void learnNormal(const TimeSeries& ts);
      virtual vector<AnomalyReport> detect(const TimeSeries& ts);
      vector<correlatedFeatures> getNormalModel();
};
