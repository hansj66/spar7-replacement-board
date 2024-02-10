/*
 * Spar7.h
 *
 * Created: 3/12/2013 2:25:31 PM
 *  Author: Hans Jørgen Grimstad
 *  Homepage: http://www.timeexpander.com/wordpress/spar7
 */ 


#ifndef SPAR7_H_
#define SPAR7_H_

#define bool int
#define true 1
#define false 0

void InitPorts();
void StartMotor();
void StopMotor();
void Payout(int credit);
void DisplayCredit(uint8_t value);


#endif /* SPAR7_H_ */