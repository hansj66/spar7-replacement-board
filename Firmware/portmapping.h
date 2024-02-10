/*
 * portmapping.h
 *
 * Created: 3/9/2013 4:32:22 PM
 *	Author: Hans Jørgen Grimstad
 *  Homepage: http://www.timeexpander.com/wordpress/spar7
 */ 

#ifndef PORTMAPPING_H_
#define PORTMAPPING_H_

/*	Comment regarding the physical wiring of "Spar7" 
	(and probably the "Redningsselskapet" and "Capri" models, 
	since they have interchangeable CPU boards):

	Because of the switch wiring, pulling PB2,PB3, PB4 to ground 
	will register correctly at the edge connector, but they will also open the 
	normally closed PB5. 
	
	There is also some risk that PB5 will activate before PB2,PB3 or PB4
*/

#define HOPPER(s)	 ( s & (1 << PB0))	/* NC */
#define COIN_EXIT(s) (~s & (1 << PB1))	/* NO */
#define PAY2(s)		 (~s & (1 << PB2))	/* NO */
#define PAY3(s)		 (~s & (1 << PB3))	/* NO */
#define PAY4(s)		 (~s & (1 << PB4))	/* NO */
#define PAYOUT(s)    ( s & (1 << PB5))	/* NC */ 

#define RELAY PC0

#endif /* PORTMAPPING_H_ */