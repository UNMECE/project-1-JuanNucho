#ifndef CAPACITOR_H
#define CAPACITOR_H

// Capacitor structure
struct Capacitor {
    double *time;
    double *voltage;
    double *current;
    double capacitance;
}; 
// Functions
void constantCurrent(Capacitor cap, double initialCurrent, double dt, int numSteps);
void constantVoltage(Capacitor cap, double initialVoltage, double resistance, double dt, int numSteps);

#endif