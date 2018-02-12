#pragma once
#include "doEnc.h"

// TODO * chang the name of key.
void doDec(pvData src, pvKey key);
// 和 doEnc算法完全一样
void doDec(void *src, int len, pvTable vt);

