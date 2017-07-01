#ifndef Stepper_h
#define Stepper_h

/*
Current : 160 mA per winding (320 mA in 4-step mode)
Voltage : 5V DC
Step Angle (8-Step sequence: Internal Motor alone): 5.625° (64 steps per revolution)
Step Angle (4-Step sequence: Internal Motor alone): 11.25° (32 steps per revolution) 
*/
class StepperMotor {
public:
    StepperMotor(int In1, int In2, int In3, int In4);    // Constructor that will set the inputs
    void setStepDuration(int duration);    // Function used to set the step duration in ms
    void step(int noOfSteps);    // Step a certain number of steps. + for one way and - for the other

    int duration;    // Step duration in ms
    int inputPins[4];    // The input pin numbers
};

#endif
