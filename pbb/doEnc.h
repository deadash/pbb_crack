#pragma once
#include "doBuild.h"

typedef pvKey pvData;

// TODO * chang the name of key.
void doEnc(pvData src, pvKey key);
void doEnc(void *src, int len, pvTable vt);
