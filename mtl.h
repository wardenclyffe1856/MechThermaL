#ifndef _MTL_H_
#define _MTL_H_
#include "constant.h"
#include "main.h"

namespace MTL
{
    #define DO_LoadSubstances DO_load_substances 
    #define DO_Test DO_test
    #define DO_Init DO_init
    ///
    void DO_Init(void);
	void DO_LoadSubstances(void);
	void DO_Test(void);
}

#endif