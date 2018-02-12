#include "stdafx.h"
#include "doDec.h"
#include "doTab.h"
#include <boost/make_shared.hpp>

void doDec(pvData src, pvKey key)
{
	pvTable vt = doBuild(key, false);
	doDec(src->v, 0x10, vt);
}

void doDec(void *src, pvTable vt)
{
	unsigned int tTab[0x24] = { 0 };

	memcpy(tTab, src, 0x10);

	for (int i = 0; i < 0x20; i++) {
		tTab[i + 4] = tTab[i] ^ doYTab(tTab[i + 1] ^ tTab[i + 2] ^ tTab[i + 3] ^ vt->v[i]);
	}

	unsigned int *value = (unsigned int *)src;

	for (int i = 0; i < 4; i++) {
		value[i] = tTab[0x23 - i];
	}
}

void doDec(void *src, int len, pvTable vt)
{
	int ll = len / 0x10;
	for (int i = 0; i < ll; i++) {
		doDec((unsigned char *)src + 0x10 * i, vt);
	}
}

void doTestDec()
{
	pvKey key = boost::make_shared<vKey>();
	pvData data = boost::make_shared<vKey>();

	unsigned char hexData[16] = {
		0x70, 0xDA, 0x08, 0x00, 0x4C, 0x6D, 0x8C, 0x42, 0x91, 0x67, 0xBC, 0x41, 0x94, 0xFE, 0xCD, 0xCD
	};
	memcpy(data->v, hexData, 0x10);

	unsigned char hexKey[16] = {
		0x81, 0xBD, 0x80, 0x89, 0x65, 0x1A, 0x8F, 0x1E, 0x9A, 0xDF, 0x55, 0xD6, 0x96, 0xBD, 0x84, 0x26
	};
	memcpy(key->v, hexKey, 0x10);

	doDec(data, key);

	/*
	*  00 00 00 14 66 74 79 70 69 73 6F 6D 00 00 00 01
	*
	*/
#if 1
	unsigned char *p = (unsigned char *)data->v;
	for (int i = 0; i < 16; i++) {
		printf("%.2x ", p[i]);

		if ((i + 1) % 0x10 == 0)
			printf("\r\n");
	}
#endif
}