#include <kipr/wombat.h>
int forwardSpeed=100;		// speed moving forwards (mm/s)
int backSpeed=-100;				// speed moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int lightPort = 4;					// light port
int clawPort = 3;				 //claw port
int armPort = 0;      		       //arm port
int up = 1900;						//arm up position
int down = 1300;					//arm down position	
int storage;
int open = 700;					// claw open position
int closed = 1500;				//claw closed position
int clawWait = 500; 			//wait half-second for claw to change position
int leftButton = 8;				//left button from back view
int rightButton = 1;			//right button from back view



void Forward(float distance);								//move forward for certain distance (cm)
void Backwards(float distance);							//move backwards for certain distance (cm)
void Left(float angle);											//turn left at certain angle (degrees)
void Right(float angle);										//turn right at certain angle (degrees)
void Claw(int position);										//set claw position 
void Arm(int position);											//set arm position
void BackUntil();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    wait_for_light(lightPort);													//wait for light before starting
    
    shut_down_in(115);																//shut down robot 5 secs before game ends
   
    create_connect();																//connect create
    
	Claw(open);																			//open claw
    
	Forward(50);																		// move forwards 50 cm
    
    Left(90);																				//turn left 90 degrees
    
    BackUntil();
    
    Forward(40);																		//move forward 40 cm
    
    Right(90);																				//turn right 90 degrees
    
    Forward(60);																		// move forwards 60 cm to transporter
    
   	Claw(closed);																		//close claw
    
    Arm(up);																			//lift arm
    
    Forward(5);																			//move forward 5cm so arm is above transporter
    
    Arm(down);																		//lower arm to drag transporter
    
    //--------------------------------------------------------------------------------------------------------------------------
    
    Left(5);																			//turn left 5 degrees to angle towards starting box
    
    Backwards(110);																	//move backwards 110cm to starting box
    
    Claw(open);																			//open claw to drop poms in transporter
    
    Arm(up);																			//lift arm up
    
    BackUntil();
    
    Forward(7);																			//move forward 7cm
    
    Left(90);																				//turn left 90 degrees
    
    Forward(70);																	//move forward 70cm to storage rack
    
    Right(90);																			//turn 90 degrees right
    
    //--------------------------------------------------------------------------------------------------------------------------
    
    Forward(80);																			//push all cubes to side
    
    Backwards(10);																		//move backwards 10cm
    
    Right(80);																					//turn right 80 degrees
    
    Forward(30);																			//move forward 30cm
    
    Left(160);																					//turn around to face track
    
    Arm(storage);																			//move arm to storage rack level
    
    Forward(30);																			//move forward 30cm to storage rack
    
    Claw(closed);																			//close arm to pick up cubes
    
    Backwards(50);																		//move cubes back to black line
    
    Claw(open);																				//drop cubes on line
    
    Backwards(30);																		//move back 30cm
    
    Right(80);																				//turn right to be 90 degrees along rack
    
    Forward(50);																		//move forward 50 degrees
    
    Right(90);																				//turn right 90 degrees
    
    Backwards(75);																		//move 75cm back to rack
    
    Left(90);																				//turn left 90 degrees
    
//				2nd cube collection
    
    Forward(80);																		//push all cubes to side
    
    Backwards(10);																		//move backwards 10cm
    
    Right(80);																					//turn right 80 degrees
    
    Forward(30);																			//move forward 30cm
    
    Left(160);																					//turn around to face track
    
    Arm(storage);																			//move arm to storage rack level
    
    Forward(30);																			//move forward 30cm to storage rack
    
    Claw(closed);																			//close arm to pick up cubes
    
    Backwards(50);																		//move cubes back to black line
    
    Claw(open);																				//drop cubes on line
    
    
    
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

void BackUntil()																			//back up until both buttons are pressed
{
    if (digital(leftButton) == 0 || digital(rightButton) == 0)
    {
        create_drive_direct(backSpeed,backSpeed);
    }
}



