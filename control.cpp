#include "mtl.h"

#include <iostream>

using std::cout;
using std::endl;

MTL::MainWorker* MW;

void MTL::DO_test(void)
{
	cout << "Test MTL." << endl;
}

void MTL::DO_init()
{
    MW = new MainWorker();
}

void MTL::DO_load_substances()
{
    MW->DO_load_substances();
}