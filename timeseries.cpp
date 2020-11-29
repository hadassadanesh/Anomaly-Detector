/*
 * timeseries.cpp
 *
 * Author: 322567041 , Hadassa Danesh
 */

#include "timeseries.h"
#include <fstream>
#include <sstream>
#include <iostream>

list<string> TimeSeries::returnListOfFeatures() const
{
    list<string> listOfFeatures;
    for (auto i = m_dataMap.begin(); i != m_dataMap.end(); i++)
    {
        listOfFeatures.push_back(i->first);
    }
    return listOfFeatures;
}

vector<float> TimeSeries::getCol(string feature) const
{
    auto iter = m_dataMap.find(feature);
    return iter->second;
}

void TimeSeries::loadFromCsv()
{
    vector<float> vec;
    string line, word;
    float val;
    ifstream file;
    file.clear();

    file.open(m_CSVfileName);
    getline(file, line);
    stringstream ss(line);
    while (getline(ss, word, ','))
    {
        m_dataMap.insert({word, vec});
    }
    while (file.good())
    {
        getline(file, line);
        stringstream s(line);
        auto j = m_dataMap.begin();
        while (getline(s, word, ','))
        {
            j->second.push_back(std::stof(word));
            j++;
        }
    }
    file.close();
}