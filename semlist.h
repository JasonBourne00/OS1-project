/*
 * semlist.h
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class PCB;

class SemList{

	struct Elem{
		PCB*pcb;
		Elem*next;
		unsigned int time;
		Elem(PCB*p, unsigned int t, Elem*n=0){
			pcb=p; next=n; time=t;
		}
	};
	Elem*prvi,*posl,*prev;
	unsigned int velicina;

public:

	SemList();
	~SemList();
	void put(PCB*info, unsigned int t);
	PCB*get();
	PCB*get_prinudno();

	void otkucaj();

	unsigned int get_size(){
		return this->velicina;
	}

};




#endif /* SEMLIST_H_ */
