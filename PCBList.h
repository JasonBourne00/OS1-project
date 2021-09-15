/*
 * PCBList.h
 *
 *  Created on: Aug 10, 2021
 *      Author: OS1
 */

#ifndef pcblist_h_
#define pcblist_h_
#include"thread.h"
class PCB;

class PCBList {

private:

	struct Elem {
	public:
		PCB* info;
		Elem* next;
		Elem(PCB* inf, Elem* n = 0) {
			info = inf;
			next = n;
		}
	};

public:
	Elem *first, *last,*pomocni;
	PCBList();
	~PCBList();
	void put(PCB* info);
	PCB* get();
	int isEmpty();
	PCB* get_byID(unsigned id);
};



#endif /* PCBLIST_H_ */
