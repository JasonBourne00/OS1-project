/*
 * Timer.cpp
 *
 *  Created on: Aug 11, 2021
 *      Author: OS1
 */
#include"thread.h"
#include"PCB.h"
#include"SCHEDULE.H"
#include"PCBList.h"
#include"Timer.h"
#include<dos.h>
#include<iostream.h>
#include"Uzalud.h"
#include"semlist.h"
#include"semaphor.h"
#include"kersem.h"
#include"Allsem.h"
unsigned tsp,tss,tbp;
extern void tick();
volatile int Timer::zahtev_za_promenu=0;
volatile unsigned Timer::brojac=0;
pInterrupt Timer::stara_rutina=0;
Thread* Timer::main=0;

void interrupt Timer::timer(...){
	if (!zahtev_za_promenu){
	brojac--;
	tick();
	asm int 60h;
	KernelSem::svi_semafori->tick_all();
	}
	if ((PCB::running->timeslice!=0 && brojac==0)|| zahtev_za_promenu) {
		//if(Timer::lockFlag==1){
		zahtev_za_promenu = 0;
#ifndef BCC_BLOCK_IGNORE
	asm {
	mov tsp, sp
	mov tss, ss
	mov tbp, bp
	}
#endif
	((PCB*)PCB::running)->sp = tsp;
	((PCB*)PCB::running)->ss = tss;
	((PCB*)PCB::running)->bp = tbp;
	if(PCB::running->myStatus==aktivna && PCB::running->myThread!=PCB::holder){
		Scheduler::put((PCB*)PCB::running);
	}
	PCB::running= Scheduler::get();


	if(PCB::running==0) {
		PCB::running=PCB::holder->myPCB;
		//asm cli;
		//cout<<"IDLE DOBIO"<<endl;
		//asm sti;
		//if(Timer::main->myPCB->myStatus!=aktivna) PCB::running =PCB::holder->myPCB;
		//  else PCB::running = Timer::main->myPCB;

	}


	PCB::running->myStatus=aktivna;

	tsp = ((PCB*)PCB::running)->sp;
	tss = ((PCB*)PCB::running)->ss;
	tbp = ((PCB*)PCB::running)->bp;
	brojac = ((PCB*)PCB::running)->timeslice;


#ifndef BCC_BLOCK_IGNORE
	asm {
	mov sp, tsp
	mov ss, tss
	mov bp, tbp
	}
#endif
	 }
}
void Timer::inicijalizuj(){
	//asm cli;
	/*Timer::main=new Thread(0,2);
    PCB::holder= new Uzalud();
    Timer::main->myPCB->myStatus=aktivna;
    PCB::running=Timer::main->myPCB;
	PCB::holder->myPCB->myStatus=aktivna;*/
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	stara_rutina = getvect(0x08);
	setvect(0x08, timer);
	setvect(0x60,stara_rutina);
	asm sti;
#endif
	//asm sti;
	Timer::main=new Thread(0,2);
	    PCB::holder= new Uzalud();
	    Timer::main->myPCB->myStatus=aktivna;
	    PCB::running=Timer::main->myPCB;
		PCB::holder->myPCB->myStatus=aktivna;

}
void Timer::restore(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(0x08, stara_rutina);
	asm sti;
#endif
	delete Timer::main;
	delete PCB::holder;
	//asm sti;
}

