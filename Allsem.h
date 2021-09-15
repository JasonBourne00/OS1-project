/*
 * Allsem.h
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#ifndef ALLSEM_H_
#define ALLSEM_H_

class KernelSem;

class AllSem {
public:

	struct Elem{
		KernelSem* data;
		Elem* next;
		Elem(KernelSem*k,Elem*n){
			data=k; next=n;
		}
	};
	Elem* prvi;
	Elem* posl;

	AllSem();
	 ~AllSem();

	void addSem(KernelSem* newKer);
	void deleteSem(KernelSem* delKer);
	void tick_all();

};


#endif /* ALLSEM_H_ */
