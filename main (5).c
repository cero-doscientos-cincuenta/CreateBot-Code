#include <kipr/wombat.h>
float leftForwardSpeed=205.5;		// left motor speed moving forwards (mm/s)
int rightForwardSpeed=200;		// right motor speed moving forwards (mm/s)
int turnSpeed=150;		//turning speed (mm/s) 
int leftBackSpeed=-150;				// speed left moving backwards (mm/s)
int rightBackSpeed=-150;				// speed left moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int leftAngle = 93;					//left angle turn
int rightAngle = 95;				// right angle turn
int lightPort = 4;					// light port
int clawPort = 2;				 //claw port
int armPort = 1;      		       //arm port
int up = 1600;						//arm up position
int middle=1450;				//arm middle position
int almostDown=1300;			//arm almost down position
int down = 1150;					//arm down position	
int open = 1200;					// claw open position
int closed = 200;				//claw closed position
int clawWait = 500; 			//wait half-second for claw to change position
int leftButton = 8;				//left button from back view
int rightButton = 1;			//right button from back view



void Forward(float distance);								//move forward for certain distance (cm)
void Backwards(float distance);							//move backwards for certain distance (cm)
void Left(float angle);											//turn left at certain angle (degrees)
void Right(float angle);										//turn right at certain angle (degrees)
void Claw(int position);										//set claw position 
void Arm(int position);											//set arm position
void BackUntil(float maxDistance);						//back up until both buttons pressed or past max distance

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// -position Create in starting box
// -facing air lock
// -slightly to the right of ring stand
// -parallel/perpendicular to board edges

int main()
{
    
	Claw(open);													//open claw
    
    Arm(middle);
    
    create_connect();											//connect create
    
    wait_for_light(lightPort);								//wait for light before starting
    
    shut_down_in(115);											//shut down robot 5 secs before game ends
    
    BackUntil(40);
    
    Forward(65);												// move forwards 65 cm
    
    Left(leftAngle);											//turn left 90 degrees
    
    BackUntil(40);
    
    Claw(open);
    
    Forward(13);													//move forward 13 cm to middle
    
    Arm(down);															//put arm down
    
    Forward(34);													//forward 34cm more
    
    Claw(closed);
    
    Arm(middle);
    
	Right(rightAngle);    												// turns right to face transporter
    
    Forward(10);														//move forward 10cm
    
    Claw(open);
    
    Arm(down);
    
    Forward(73);													//move forwards 73cm to transporter
    
   	Claw(closed);													//close claw
    
    Arm(middle);													//lift arm to middle level
    
    Forward(23);														//move forward 23cm so arm is above transporter
    
    Arm(down);															//drop arm to transporter
    
   Claw(open);																//release poms to transporter
    
    Claw(closed);
    
    Claw(open);
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    Arm(middle);									//put arm in middle position to avoid getting caught on transporter	
    
    Right(rightAngle);							//turn right to face away from other board side
    
    BackUntil(60);									//back up to storage rack											
    
    Forward(5);										//move away from edge to prepare for turn
    
    Right(rightAngle);							//face botguy
    
    Arm(almostDown);
        
    BackUntil(60);									//back up for alignment				
    
    msleep(13000);									//wait 13sec for Legobot
    
    Forward(50);									//move forward 50cm to botguy
    
    Left(leftAngle);								//turn left 90 degrees, sweep botguy
    
    BackUntil(30);
    
    Forward(35);									//move forward 35cm to middle of board
    
    Right(rightAngle);								// turn right 90 degrees
    
    Forward(50);
    
    Arm(down);
    
    Forward(50);										//move almost to starting edge
    
   Claw(closed);
    
    Arm(almostDown);
    
    Left(200);								//turn around
    
    BackUntil(100);									//back up to near starting box
    
    Forward(5);										//move away from edge to prepare for turn
    
    Right(rightAngle);								//face starting box
    
    Forward(5);									//go to starting box
    
    Claw(open);										//drop botguy into starting box
    
    BackUntil(70);								//back up
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    Arm(up);
    
    Forward(5);
    
    Left(leftAngle);
    
    BackUntil(30);
    
    Forward(50);
    
    Right(rightAngle);
    
    BackUntil(30);
    
    Forward(80);
    
    Right(30);										//move rings slightly
    
    Left(30);
    
    Right(30);										
    
    Left(30);
    
    create_disconnect();						//disconnect create
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Forward(float distance) 
{																			//move forward x cm
    set_create_distance(0);																			
    while ((get_create_distance())<(distance*cm))
    {
        create_drive_direct(leftForwardSpeed,rightForwardSpeed);
        msleep(interval);
    }
    create_drive_direct(0,0);
}

void Backwards(float distance)
{																			//move backwards x cm
	set_create_distance(0);
    while ((abs((get_create_total_angle())))<(distance*cm)) 
    {
        create_drive_direct(leftBackSpeed,rightBackSpeed);
        msleep(interval);
    }
}

void Left(float angle)
{																			//turn left x degrees
    set_create_total_angle(0);
    while ((get_create_total_angle())<angle) 
    {
        create_drive_direct(-turnSpeed,turnSpeed);
        msleep(interval);
    }
    create_drive_direct(0,0);
}

void Right(float angle)
{																			//turn right x degrees
    set_create_total_angle(0);
    while ((abs((get_create_total_angle())))<angle) 
    {
        create_drive_direct(turnSpeed,-turnSpeed);
        msleep(interval);
    }
    create_drive_direct(0,0);
}

void Claw(int position) {																			//change claw's position (open/closed)
    set_servo_position(clawPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
   
}

void Arm(int position) 
{																			//change claw's position (open/middle/closed)
    set_servo_position(armPort,middle);
    enable_servos();
    msleep(clawWait);
    set_servo_position(armPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
}

void BackUntil(float maxDistance)											//back up until both buttons are pressed or max distance is overcome
{		
    set_create_distance(0);
    while ((digital(leftButton) == 0 || digital(rightButton) == 0)&&(abs((get_create_distance())))<(maxDistance*cm)) 
    {
        create_drive_direct(leftBackSpeed,rightBackSpeed);
        msleep(interval);
    }
    create_drive_direct(0,0);
    set_create_distance(0);
}