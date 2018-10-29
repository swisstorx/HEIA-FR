/*
 * wheel.h
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified : Marc
 *
 */
#pragma once
#ifndef WHEEL_H_
#define WHEEL_H_



#endif /* WHEEL_H_ */

enum wheel_direction {
	WHEEL_STILL, WHEEL_RIGHT, WHEEL_LEFT
};

void wheel_init();

enum wheel_direction get_wheel_direction();
