#ifndef TIMESERIES_H_
#define TIMESERIES_H_

/*
 * timeseries.h
 *
 * Author: 322567041 , Hadassa Danesh
 */

using namespace std;
#include <map>
#include <vector>
#include <list>

class TimeSeries
{
private:
  const char *m_CSVfileName;
  map<string, vector<float>> m_dataMap;

public:
  //constructor
  TimeSeries(const char *CSVfileName)
  {
    m_CSVfileName = CSVfileName;
    m_dataMap;
    loadFromCsv();
  }
  list<string> returnListOfFeatures() const;
  vector<float> getCol(string feature) const;
  void loadFromCsv();
};

#endif /* TIMESERIES_H_ */