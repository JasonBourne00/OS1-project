/*
 * PCB.h
 *
 *  Created on: Aug 10, 2021
 *      Author: OS1
 */

#ifndef pcb_h_
#define pcb_h_

#define lock
#ifndef BCC_BLOCK_IGNORE
asm { pushf
			cli;
		}
#endif
#define unlock
#ifndef BCC_BLOCK_IGNORE
asm popf
#endif
#include"thread.h"
#include"Uzalud.h"
enum Status{
	nova,aktivna,zavrsena,blokirana
};
class PCBList;

class PCB{
public:
	unsigned bp;
	unsigned sp;
	unsigned ss;
	unsigned *stack;
	StackSize size;
	Thread*myThread;
	Status myStatus;
	unsigned timeslice;
	unsigned neogranicen;
	PCBList*waitlist;
	unsigned force_wakeup;
	static unsigned volatile brojac_niti;
	PCB(Thread*mythr=0, StackSize sz=defaultStackSize, Time timeSlice=defaultTimeSlice);
	~PCB();
	static void wrapper();

	static volatile PCB*running;

	static Uzalud*holder;

	void wait_to_complete();
protected:

	friend class Thread;
	friend class PCBList;
	friend class Timer;
	friend class KernelSem;

};
void _dispatch();
#endif /* PCB_H_ */
