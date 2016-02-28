#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Ultrasonic.h" 

Ultrasonic::Ultrasonic(int tp, int ep) // This class define the pins and the constants to convert the units
    {
    pinMode(tp, OUTPUT);
    pinMode(ep, INPUT);
    _trigPin = tp;
    _echoPin = ep;
    _cmDivisor = 27.6233;
    _inDivisor = 70.1633;
    }

long Ultrasonic::timing(){
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    double a= pulseIn(_echoPin, HIGH, 4350); // Standard function on Arduino (pulseIn(pin, value, timeout), where timeout is the time used to stop the reading. The chosen value is equivalent to the time that a sound takes to go through 150 cm  )
    return a; 

}

float Ultrasonic::convert(long microsec, int metric){
    // microsec / 29 / 2;
    if(metric){
        double cm;
    cm =  microsec / _cmDivisor / 2.0;  // CM
        return cm;
    }
    // microsec / 74 / 2;
    else return microsec / _inDivisor / 2.0;  // IN
    }

void Ultrasonic::setDivisor(float value, int metric)
    {
    if(metric) _cmDivisor = value;
    else _inDivisor = value;
    }

class With_Filter :: public Ultrasonic {        
public:
    double filter(double alpha, timing);// turn the result more reliable, depending on the alpha value to be set. If alpha = 1, the filter is off 
    double after_filter_cm(convert(filter, 1));  
    double after_filter_in(convert(filter, 0));
    bool digital_result(filter){
      if (With_Filter:filter()  >= 4350) return false;
      else return true // if the enemy is not in the range, return false
    };
}


With_Filter :filter(double alpha, double timing){
    // Y[n] = a * X[n] + (1-a) * Y[N-1]
    {
        // Y[n] = a * X[n] + (1-a) * Y[N-1]
    long previous_reading;
   double result_function;
    long y;
    for (int i=0;i>=0;i++) {
        if (i=0){
            y= Ultrasonic::timing();
            previous_reading = result_function;
            return result_function;
        } 
        else {
            y = (alpha*Ultrasonic::timing()) + ((1- alpha)*previous_reading);
            previous_reading = result_function;
            return result_function;
        }
    }    
        
}
    

  With_Filter : digital_result(With_Filter:filter(double alpha, Ultrasonic:timing())){
      if (With_Filter:filter()  >= 4350) return false;
      else return true 
  }
