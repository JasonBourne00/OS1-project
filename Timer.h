/*
 * Timer.h
 *
 *  Created on: Aug 8, 2021
 *      Author: OS1
 */

#ifndef timer_h_
#define timer_h_

typedef void interrupt (*pInterrupt)(...);

class Thread;
class PCB;
class PCBList;
class KernelSem;
class SemList;
class Timer{
public:
	static volatile int zahtev_za_promenu;
	static volatile unsigned brojac;
	static pInterrupt stara_rutina;
	static SemList* lista_cekajucih;

	static void interrupt timer(...);

	static void inicijalizuj();

	static void restore();
	static Thread*main;
protected:
	friend class Thread;
	friend class PCB;
	friend class PCBList;


};



#endif /* TIMER_H_ */
