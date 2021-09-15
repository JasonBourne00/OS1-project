/*
 * KernelEv.h
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include"Event.h"
#include"PCB.h"

class KernelEv{
	void wait();
	KernelEv(IVTNo ivtNo);
	~KernelEv();

protected:
	PCB*creator;
	PCB*blocked;
	//varijanta je bez blocked
	friend class Event;
	friend class IVTEntry;
	IVTNo broj_ulaza;
	int value;
	void signal();

};


#endif /* KERNELEV_H_ */
