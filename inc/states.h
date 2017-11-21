/*
 * states.h
 *
 *  Created on: Nov 15, 2017
 *      Author: haavahe
 */

#ifndef STATES_H_
#define STATES_H_

enum STATES {
  ST_WAIT_FOR_GO,
  ST_FORWARD,
  ST_STEP_FORWARD,
  ST_CROSSROAD,
  ST_TURN_LEFT,
  ST_TURN_RIGHT,
  ST_U_TURN,
  ST_STOP
};

#endif /* STATES_H_ */
