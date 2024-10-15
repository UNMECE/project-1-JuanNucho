#include <iostream>
#include "capacitor.h"

// Function for constant current
void constantCurrent(Capacitor cap, double initialCurrent, double dt, int numSteps) {
    cap.voltage[0] = 0;  //initial voltage is 0
    cap.current[0] = initialCurrent;  // Set initial current
    cap.time[0] = 0;  // Initial time is 0

    // Loop through each step
    for (int i = 1; i < numSteps; ++i) {
        cap.voltage[i] = cap.voltage[i-1]  + cap.current[i-1] * dt / cap.capacitance; // Update the voltage with V(t+1) = V(t) + I(t) * dt / C
        cap.time[i] = i * dt; // Update the time for the current step
        if (i % 200 == 0) { // Print every 200 steps
            std::cout << "Step: " << i << ", Time: " << cap.time[i]
                      << " s, Voltage: " << cap.voltage[i] << " V\n";
        }
    }
}

// Function for constant voltage
void constantVoltage(Capacitor cap, double initialVoltage, double resistance, double dt, int numSteps) {
    cap.current[0] = initialVoltage / resistance;  // Set the initial current
    cap.time[0] = 0;  // Initial time is 0
    for (int i = 1; i < numSteps; ++i) { // Loop through each step
        cap.current[i] = cap.current[i-1] - (cap.current[i-1] / (resistance * cap.capacitance)) * dt; // Update the current with I(t+1) = I(t) - I(t) / (R * C) * dt
        cap.time[i] = i * dt; // Update the time for the current step
        if (i % 200 == 0) {  // Printevery 200 steps
            std::cout << "Step: " << i << ", Time: " << cap.time[i]
                      << " s, Current: " << cap.current[i] << " A\n";
        }
    }
}

int main()  {
    // Constants
    double dt = 1e-10;
    int numSteps = 50000;
    double capacitance = 100e-12;
    double initialCurrent = 1e-2;
    double resistance = 1e3;
    double initialVoltage = 10.0;

    // Check for zero division errors
    if (capacitance == 0) 
    {
        std::cerr << "Error: Capacitance cannot be zero.\n";
        return 1;
    }
    if (resistance == 0) {
        std::cerr << "Error: Resistance cannot be zero.\n";
        return 1;
    }

    // Capacitor object
    Capacitor cap;
    cap.capacitance = capacitance;

    // Dynamically allocate memory for time, voltage, current arrays
    cap.time = new double[numSteps];
    cap.voltage = new double[numSteps];
    cap.current = new double[numSteps];

    // constant current simulation
    std::cout << "Running constant current simulation:\n";
    constantCurrent(cap, initialCurrent, dt, numSteps);

    // Constant voltage simulation
    std::cout << "\nRunning constant voltage simulation:\n";
    constantVoltage(cap, initialVoltage, resistance, dt, numSteps);

    // Free memory
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}