#ifndef KERNEL_H_
#define KERNEL_H_

// c�digos de retorno
#define SUCCESS	0
#define FAIL	1
#define REPEAT	2

// declara��o de ponteiro de fun��o
typedef char (*ptrFunc)(void);

//defini��o da estrutura de um processo
typedef struct {
	//ponteiro para fun��o a ser executada
	ptrFunc func;
	//per�odo de reexecu��o da fun��o
	int periodo;
	//contador de tempo de cada processo
	int deadline;	
}process;

//prot�tipos das fun��es do kernel
char kernelInit(void);
char kernelAddProc(process* newProc);
void kernelLoop(void);// declara��o de ponteiro de fun��o
void kernelTick(void);

#endif
