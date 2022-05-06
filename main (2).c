#include <kipr/wombat.h>
int forwardSpeed=100;		// speed moving forwards (mm/s)
int backSpeed=-100;				// speed moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int lightPort = 4;				// light port
int clawPort = 3;			 //claw port
int open = 1200;				// claw open position
int closed = 350;			//claw closed position
int clawWait = 1000; 	//wait 1 second for claw to change position

void Forward(float distance);										//move forward for certain distance (cm)
void Backwards(float distance);									//move backwards for certain distance (cm)
void Left(float angle);											//turn left at certain angle (degrees)
void Right(float angle);										//turn right at certain angle (degrees)
void Claw(int position);										//open claw 

int main()
{
	
    shut_down_in(115);																					//shut down robot 5 secs before game ends
    
    create_connect();																				//connect create
    
    create_drive_direct(200,200);																							//turn left 90 degrees
	msleep(10000);
    
    create_disconnect();																			//disconect create
    return 0;
}

void Forward(float distance) {																			//move forward x cm
    set_create_distance(0);																			
    while ((get_create_distance())<(distance*cm)) {
        create_drive_direct(forwardSpeed,forwardSpeed);
        msleep(interval);
    }}

void Backwards(float distance) {																//move backwards x cm
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