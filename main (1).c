#include <kipr/wombat.h>
int leftForwardSpeed=200;		// left motor speed moving forwards (mm/s)
int rightForwardSpeed=200;		// right motor speed moving forwards (mm/s)
int turnSpeed=150;		//turning speed (mm/s) 
int leftBackSpeed=-150;				// speed left moving backwards (mm/s)
int rightBackSpeed=-150;				// speed left moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int rightAngle = 90;				// right angle turn
int lightPort = 4;					// light port
int clawPort = 2;				 //claw port
int armPort = 1;      		       //arm port
int up = 1600;						//arm up position
int middle=1450;				//arm middle position
int down = 1100;					//arm down position	
int open = 700;					// claw open position
int closed = 1660;				//claw closed position
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

int main()
{
    
	Claw(open);													//open claw
    
    Arm(middle);
    
    create_connect();											//connect create
    
    //wait_for_light(lightPort);								//wait for light before starting
    
    shut_down_in(115);											//shut down robot 5 secs before game ends
    
    BackUntil(40);
    
    Forward(30);												// move forwards 30 cm
    
	Forward(35);												// move forwards 35 cm
    
    Left(rightAngle);											//turn left 90 degrees
    
    BackUntil(40);
    
    Claw(open);
    
    Forward(12);													//move forward 12 cm to middle
    
    Arm(down);															//put arm down
    
    Forward(33);													//forward 33cm more
    
    Claw(closed);
    
    Arm(middle);
    
	Right(rightAngle);											// turns right to face transporter
    
    Forward(6);														//move forward 6cm
    
    Claw(open);
    
    Arm(down);
    
    Forward(77);													//move forwards 77cm to transporter
    
   	Claw(closed);													//close claw
    
    Arm(middle);													//lift arm to middle level
    
    Forward(21);														//move forward 21cm so arm is above transporter
    
    Arm(down);															//drop arm to transporter
    
   Claw(open);																//release poms to transporter
    
    Arm(middle);														
    
    msleep(15000);														//wait 15sec for Legobot
    
    Left(rightAngle*2);
    
    Arm(down);
    
    Forward(70);
    
    Claw(closed);																						//grab botguy
    
    Left(rightAngle*2);
    
    BackUntil(70);
    
    Forward(5);
    
    Right(rightAngle);
    
    BackUntil(30);
    
    Forward(30);
    
    Claw(open);																			//drop botguy into starting box
    
    Arm(down);
    
    create_disconnect();														//disconnect create
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