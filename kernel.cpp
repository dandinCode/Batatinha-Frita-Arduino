#include "kernel.h"

#define POOL_SIZE 10
#define MIN_INT -30000

//armazena as refer�ncias dos processos
volatile static process* pool[POOL_SIZE];

//primeiro elemento do buffer
volatile int start;

//�ltimo elemento do buffer
volatile int end;

//adiciona os processos no pool
char kernelAddProc(process* newProc){
//adiciona os processos somente se houver espa�o livre
//o fim nunca pode coincidir com o in�cio
	if(((end+1)%POOL_SIZE) != start){//sempre proteje o espa�o depois do �ltimo
		//protege acesso a pool
				
		//adiciona o novo processo e agenda para executar imediatamente
		newProc->deadline += newProc->periodo;
		pool[end] = newProc;
		end = (end+1)%POOL_SIZE;
		//libera pool de processos
				
		return SUCCESS;			
	}
	return FAIL;
}

//inicializa o kernel
char kernelInit(void){
	start=0;
	end=0;
	return SUCCESS;
}

//executa os processos do 'pool'
void kernelLoop(void){
	unsigned int count;
	unsigned int next;
	process * tempProc;
	for(;;){    	
		if(start != end){						
			//procura a pr�xima fun��o a ser executada com base no tempo
			count = (start+1)%POOL_SIZE;
			next =  start;
			while(count!=end){
				if((pool[count]->deadline)<(pool[next]->deadline)){
					next = count;
				}
				count = (count + 1) % POOL_SIZE; //pr�ximo processo
			}						
			//troca processo de menor tempo como o primeiro
			tempProc = pool[next];
			pool[next] = pool[start];
			pool[start] = tempProc;						
			while((pool[start]->deadline) > 0){
				//coloca a CPU em modo de economia de energia
			}						
			switch(pool[start]->func()){
				case REPEAT:
					kernelAddProc(pool[start]);
					break;
				case FAIL:
					break;
				default:
					break;						
			}
			start = (start+1)%POOL_SIZE;			
		}					
	}	
}

void kernelTick(void){
	int proc;	
	proc = start;	
	while(proc!=end){
		if((pool[proc]->deadline) > (MIN_INT)){
			pool[proc]->deadline--;
		}
		proc = (proc + 1)%POOL_SIZE;		
	}
}
