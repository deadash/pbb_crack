#include "stdafx.h"
#include "doEnc.h"
#include "doTab.h"
#include <boost/make_shared.hpp>

void doEnc(pvData src, pvKey key)
{
	pvTable vt = doBuild(key);
	doEnc(src->v, 0x10, vt);
}

void doEnc(void *src, pvTable vt)
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

void doEnc(void *src,int len, pvTable vt) 
{
	int ll = len / 0x10;
	for (int i = 0; i < ll; i++) {
		doEnc((unsigned char *)src + 0x10 * i, vt);
	}
}

void doTestEnc()
{
	pvKey key = boost::make_shared<vKey>();
	pvData data = boost::make_shared<vKey>();

	unsigned char hexData[16] = {
		0x00, 0x00, 0x00, 0x14, 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x01
	};
	memcpy(data->v, hexData, 0x10);

	unsigned char hexKey[16] = {
		0x81, 0xBD, 0x80, 0x89, 0x65, 0x1A, 0x8F, 0x1E, 0x9A, 0xDF, 0x55, 0xD6, 0x96, 0xBD, 0x84, 0x26
	};
	memcpy(key->v, hexKey, 0x10);

	doEnc(data, key);

/*
 *  70 da 08 00 4c 6d 8c 42 91 67 bc 41 94 fe cd cd
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
