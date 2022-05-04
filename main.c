#include <kipr/wombat.h>
int leftForwardSpeed=210;		// left motor speed moving forwards (mm/s)
int rightForwardSpeed=200;		// right motor speed moving forwards (mm/s)
int forwardTurnSpeed=200;		//turning speed (mm/s) 
int leftBackSpeed=-210;				// speed left moving backwards (mm/s)
int rightBackSpeed=-200;				// speed left moving backwards (mm/s)
int backTurnSpeed=-200;
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int lightPort = 4;					// light port
int clawPort = 2;				 //claw port
int armPort = 1;      		       //arm port
int up = 1700;						//arm up position
int middle=1300;				//arm middle position
int down = 1050;					//arm down position	
int open = 700;					// claw open position
int closed = 1650;				//claw closed position
int clawWait = 1000; 			//wait 1 second for claw to change position
int leftButton = 8;				//left button from back view
int rightButton = 1;			//right button from back view


int main()
{
    create_connect();
   	Claw(open);
    Arm(down);
    create_disconnect();
    return(0);
}


void Forward(float distance) {																			//move forward x cm
    set_create_distance(0);																			
    while ((get_create_distance())<(distance*cm)) {
        create_drive_direct(leftForwardSpeed,rightForwardSpeed);
        msleep(interval);
    }}

void Backwards(float distance) {																			//move backwards x cm
	set_create_distance(0);
    while ((abs((get_create_total_angle())))<(distance*cm)) {
        create_drive_direct(leftBackSpeed,rightBackSpeed);
        msleep(interval);
    }}

void Left(float angle) {																			//turn left x degrees
    set_create_total_angle(0);
    while ((get_create_total_angle())<angle) {
        create_drive_direct(backTurnSpeed,forwardTurnSpeed);
        msleep(interval);
    }}

void Right(float angle) {																			//turn right x degrees
    set_create_total_angle(0);
    while ((abs((get_create_total_angle())))<angle) {
        create_drive_direct(forwardTurnSpeed,backTurnSpeed);
        msleep(interval);
    }}

void Claw(int position) {																			//change claw's position (open/closed)
    set_servo_position(clawPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
   
}

void Arm(int position) {																			//change claw's position (open/storage/closed)
    set_servo_position(armPort,middle);
    enable_servos();
    msleep(clawWait);
    set_servo_position(armPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
}

void BackUntil() {																					//back up until both buttons are pressed
    while (digital(leftButton) == 0 || digital(rightButton) == 0)
    {
        create_drive_direct(leftBackSpeed, rightBackSpeed);
        msleep(10);
    }
}

