/*
 * IVTEntry.h
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Event.h"
#include "Timer.h"
#define PREPAREENTRY(numEntry, callOld)\
		void interrupt inter##numEntry(...); \
		IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
		void interrupt inter##numEntry(...) {\
			newEntry##numEntry.signal();\
			if (callOld == 1)\
			newEntry##numEntry.callOldRoutine();\
	}
	//IVTEntry entry##brul(brul,pozvatiStaru,&rutina##brul);

class IVTEntry{
private:
	pInterrupt oldRoutine;
	//newRoutine; //definisano u timer prek rutini
	IVTNo entry;
	KernelEv*kernel_dogadjaj;
	//static IVTEntry* getIVT(IVTNo i);
	//static IVTEntry* ulazi[256];
	static KernelEv** ulazi;

public:
	IVTEntry(IVTNo entry, pInterrupt newRoutine);
	~IVTEntry();//virtual?
	void callOldRoutine();
	void signal();
protected:
	friend class KernelEv;
};

#endif /* IVTENTRY_H_ */
