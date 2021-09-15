/*
 * KernelSem.h
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include"PCBList.h"
#include"Allsem.h"
#include"semlist.h"

class KernelSem{

private:
	PCBList*sem_list;
	int value;

	public:
	KernelSem(int init=1);
	virtual ~KernelSem ();
	virtual int wait (Time maxTimeToWait);
	virtual void signal();
	int val () const;
	SemList*uspavani;
	static AllSem*svi_semafori;
	protected:
	 void block();
	 void unblock();

};




#endif /* KERSEM_H_ */
