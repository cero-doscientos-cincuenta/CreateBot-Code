#include <kipr/wombat.h>
int forwardSpeed=200;		// speed moving forwards (mm/s) 
int backSpeed=-200;				// speed moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int lightPort = 2;				// light port
int clawPort = 3;			 //claw port
int armPort = 0;             //arm port
int up;
int down;
int storage;
int open = 400;				// claw open position
int closed = 1350;			//claw closed position
int clawWait = 1000; 	//wait 1 second for claw to change position

void Forward(float distance);								//move forward for certain distance (cm)
void Backwards(float distance);							//move backwards for certain distance (cm)
void Left(float angle);											//turn left at certain angle (degrees)
void Right(float angle);										//turn right at certain angle (degrees)
void Claw(int position);										//set claw position 
void Arm(int position);											//set arm position

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    
    wait_for_light(lightPort);													//wait for light before starting
    
    shut_down_in(115);					
   
    create_connect();																//connect create
    
	Claw(open);																			//open claw
    
    
	Forward(50);																		// move forwards 50 cm
	
    Left(90);																			//turn left 90 degrees
    
    Forward(35);																	//move forwards 35cm
    
    Right(90);																		//turn right 90 degrees
    
    msleep(20);		//wait 2 millisec
    
    Forward(65);																	//move forwards 65cm to transporter
    
    Claw(closed);																	//close claw
    
    Right(175);																		//turn around 170 degrees, angled 5 degrees to starting box
    
    Forward(110);																	//move forward 110cm to start box
    
    Claw(open);																				//drop poms in starting box
    
    Backwards(20);																	//back up 20cm
    
    create_disconnect();														//disconnect create
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Forward(float distance) {																			//move forward x cm
    set_create_distance(0);																			
    while ((get_create_distance())<(distance*cm)) {
        create_drive_direct(forwardSpeed,forwardSpeed);
        msleep(interval);
    }}

void Backwards(float distance) {																			//move backwards x cm
	set_create_distance(0);
    while ((abs((get_create_total_angle())))<(distance*cm)) {
        create_drive_direct(backSpeed,backSpeed);
        msleep(interval);
    }}

void Left(float angle) {																			//turn left x degrees
    set_create_total_angle(0);
    while ((get_create_total_angle())<angle) {
        create_drive_direct(backSpeed,forwardSpeed);
        msleep(interval);
    }}

void Right(float angle) {																			//turn right x degrees
    set_create_total_angle(0);
    while ((abs((get_create_total_angle())))<angle) {
        create_drive_direct(forwardSpeed,backSpeed);
        msleep(interval);
    }}

void Claw(int position) {																			//change claw's position (open/closed)
    set_servo_position(clawPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
   
}

void Arm(int position) {																			//change claw's position (open/closed)
    set_servo_position(armPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
}

