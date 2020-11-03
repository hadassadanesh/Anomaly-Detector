/*
 * anomaly_detection_util.cpp
 *
 * Author: 322567041 , Hadassa Danesh
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
	float sum=0;
	for(int i=0; i<size; i++){
		sum+=x[i];
	}
	return sum/(float)size;
}


// returns the variance of X and Y
float var(float* x, int size){
	float sum=0;
	for(int i=0; i<size; i++){
		sum+=pow(x[i],2);
	}
	float divisionBySize= sum/size;
	float calculation=  divisionBySize-pow(avg(x, size),2);
	return calculation;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
   float sum = 0; 
   float avgX=avg(x, size);
   float avgY= avg(y, size);
    for(int i = 0; i < size; i++) 
        sum += (x[i] - avgX) *  (y[i] - avgY);  
    return sum / (float) size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	return cov(x,y,size)/(sqrt(var(x, size))*sqrt(var(y, size)));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float a=0;
	float sumOfX=0;
	float sumOfY=0;
	for(int k=0; k<size; k++){
		float x= points[k]->x;
		float y= points[k]->y;
		a+=cov(&x, &y, size)/var(&x, size);
		sumOfX+=x;
		sumOfY+=y;
	}
	float avgOfX= sumOfX/size;
	float avgOfY= sumOfY/size;
	float b=avgOfY-a*avgOfX;
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line line=linear_reg(points, size);
    return dev(p,line);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	float x= p.x;
	float yOnLine= l.f(x);
	float differenceOfYValues= yOnLine-p.y;
	if(differenceOfYValues>=0){
		return differenceOfYValues;
	}
	return -differenceOfYValues;
}
