#include "pwm.h"

char orders[] = {'f', 'r', 'l', 'f', 's', 'u', 'f', '5', '7', '1', 's'};
int current_speed = 5;

void stop(){
	motor_on(0);
	Delay(50);
	//terminate condition?
}

void turn(char direction){
	stop();
	if(direction == 'l'){
		motor_left(5);
	}else{
		motor_right(5);
	}
	Delay(100);
}

int main(int argc, char *argv[]) {
	CHIP_Init();
	init_motors();

	int i = 0;
	while (1) {
		// replace with actual received order
		if(i == sizeof(orders)-1){
			i = 0;
		}
		char order = orders[i++];
		//char order = 'f';

		switch(order){
		case 'f' :
			motor_forward(current_speed);
			break;
		case 's' :
			stop();
			break;
		case 'u' :
			turn('l');
			turn('l');
			break;
		case '5' :
		case '7' :
		case '1' :
			current_speed = (order - '0'); //translates speed to int
			break;
		case 'l' :
		case 'r' :
			turn(order);
		}
	}
}

