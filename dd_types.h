#ifndef DD_TYPES_H
#define DD_TYPES_H
		
	//Ponteiro de fun��o para driver
	typedef char(*ptrFuncDrv)(void * parameters);
	
	
	//estrutura do driver
	typedef struct{
		char id;
		ptrFuncDrv *funcoes;
		ptrFuncDrv initFunc;		
	}driver;
	
	//fun��o de retorno do driver
	
	typedef driver*(ptrGetDrv)(void);
	
#endif
