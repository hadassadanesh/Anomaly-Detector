#include <string>
#include <vector>
using std::string;
using std:: vector;

class TimeSeries{
public:
    void returnListOfFeatures();
    void supplyListOfFeatures();
    void addALine();
    void findValOfFeature();
    void loadFromCsv();
};
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
    description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
