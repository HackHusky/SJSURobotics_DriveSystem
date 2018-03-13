
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern "C" {
	#ifndef DEBUG
		#include "Wifi.h"
	#endif
	#include "Structure.h"
}


#ifndef PROTOLOBE_H_
#define PROTOLOBE_H_

#ifdef _cplusplus
extern "C"{
#endif

extern "C" void Protolobe_Init();

#ifdef _cplusplus
}
#endif

#endif 
