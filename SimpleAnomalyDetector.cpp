/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 322567041 , Hadassa Danesh
 */
#include "SimpleAnomalyDetector.h"

using namespace std;

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
  // TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
  // TODO Auto-generated constructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
  vector<AnomalyReport> vectorOfReports;
  vector<correlatedFeatures> cf = getNormalModel();
  //for every correlatedFeatures in the vector
  for (auto it = cf.begin(); it != cf.end(); it++)
  {
    string feature1 = (*it).feature1;
    string feature2 = (*it).feature2;
    vector<float> vec1 = ts.getCol(feature1);
    vector<float> vec2 = ts.getCol(feature2);
    int i = 0;
    for (auto iter = vec1.begin(); iter != vec1.end(); iter++)
    {
      //create a point wuth the values of the correlated features at a specific line
      Point point = Point(vec1[i], vec2[i]);
      //check the distance of the point from the linear regression line
      float theDistance = dev(point, (*it).lin_reg);
      // if the distance is more than the threshold, then report it
      if (theDistance > (*it).threshold)
      {
        AnomalyReport report = AnomalyReport(feature1 + "-" + feature2, i + 1);
        vectorOfReports.push_back(report);
      }
      i++;
    }
  }
  return vectorOfReports;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{
  list<string> listOfFeatures = ts.returnListOfFeatures();
  //for every feature in the table
  for (string feature : listOfFeatures)
  {
    bool alreadyExist = 0;
    //find the info about the correlated feature- the name and the correlation
    string *info = findMostCorrelatedFeature(feature, ts);
    correlatedFeatures correlatedStruct = correlatedFeatures();
    correlatedStruct.feature1 = feature;
    correlatedStruct.feature2 = info[0];
    correlatedStruct.corrlation = stof(info[1]);
    getLinearReg(correlatedStruct, ts);
    vector<correlatedFeatures> *cf = getCf();

    //if the cf is empty
    if (feature.compare(listOfFeatures.front()) == 0)
    {
      (*cf).push_back(correlatedStruct);
      continue;
    }
    //if there are correlatedFeatures obgects in the cf, go over them
    for (auto it = (*cf).begin(); it != (*cf).end(); it++)
    {
      string firstFeatureOfit = (*it).feature1;
      string secondFeatureOfit = (*it).feature2;
      string firstFeatureOfIter = correlatedStruct.feature1;
      string secondFeatureOfIter = correlatedStruct.feature2;

      //if the symetrical correlatedFeatures is in the cf
      if (firstFeatureOfit.compare(secondFeatureOfIter) == 0 &&
          secondFeatureOfit.compare(firstFeatureOfIter) == 0)
      {
        alreadyExist = 1;
        break;
      }
    }
    // if the symetrical correlatedFeatures is not in the cf
    if (alreadyExist == 0)
    {
      (*cf).push_back(correlatedStruct);
    }
  }
}

string *SimpleAnomalyDetector::findMostCorrelatedFeature(string feature, const TimeSeries &ts)
{
  list<string> listOfFeatures = ts.returnListOfFeatures();
  string maxPearsonAtAbs = "0.9";
  string nameOfCorrelated;
  for (string anotherFeature : listOfFeatures)
  {
    // go over all the features in the table except for the same feature that is checked
    if (feature != anotherFeature)
    {
      vector<float> values = ts.getCol(feature);
      vector<float> anotherValues = ts.getCol(anotherFeature);
      float arrayOfValue[values.size()];
      float arrayOfAnotherVal[values.size()];
      int i = 0;
      int j = 0;
      for (auto it = values.begin(); it != values.end(); it++)
      {
        arrayOfValue[i] = *it;
        i++;
      }
      for (auto iter = anotherValues.begin(); iter != anotherValues.end(); iter++)
      {
        arrayOfAnotherVal[j] = *iter;
        j++;
      }
      float thisPearson = pearson(arrayOfValue, arrayOfAnotherVal, values.size());
      //if the pearson that is found now is bigger than the max pearson that the function had,
      //then this is the max pearson.
      if (abs(thisPearson) > std::stof(maxPearsonAtAbs))
      {
        maxPearsonAtAbs = to_string(thisPearson);
        nameOfCorrelated = anotherFeature;
      }
    }
  }
  string *info = new string[2];
  info[0] = nameOfCorrelated;
  info[1] = maxPearsonAtAbs;
  return info;
}

void SimpleAnomalyDetector::getLinearReg(correlatedFeatures &correlatedStruct, const TimeSeries &ts)
{
  float maxLength = 0;
  string feature1 = correlatedStruct.feature1;
  string feature2 = correlatedStruct.feature2;
  vector<float> vec1 = ts.getCol(feature1);
  vector<float> vec2 = ts.getCol(feature2);

  Point *arrayOfPoints[vec1.size()];
  int i = 0;
  for (auto iter = vec1.begin(); iter != vec1.end(); iter++)
  {
    Point *point = new Point(vec1[i], vec2[i]);
    arrayOfPoints[i] = point;
    i++;
  }
  correlatedStruct.lin_reg = linear_reg(arrayOfPoints, sizeof(arrayOfPoints) / sizeof(arrayOfPoints[0]));
  for (int k = 0; k < sizeof(arrayOfPoints) / sizeof(arrayOfPoints[0]); k++)
  {
    float length = dev(*arrayOfPoints[k], correlatedStruct.lin_reg);
    if (abs(length) > maxLength)
    {
      maxLength = abs(length);
    }
  }
  correlatedStruct.threshold = 1.2 * maxLength;
}
