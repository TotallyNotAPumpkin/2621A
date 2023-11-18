using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor_group RightMotorGroup;
extern motor_group LeftMotorGroup;
extern motor MotorRf;
extern motor MotorLf;
extern motor MotorRb;
extern motor MotorLb;
extern motor pMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );