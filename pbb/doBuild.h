#pragma once
#include <boost/enable_shared_from_this.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/locale.hpp>

struct vTable
	: public boost::enable_shared_from_this<vTable>
{
	unsigned int v[32];
};

struct vKey
	:public boost::enable_shared_from_this<vKey>
{
	unsigned char v[16];
public:
	std::string toString() {
		return boost::algorithm::hex(std::string(v, v + sizeof(v)));
	}
	std::wstring toWString() {
		return boost::locale::conv::utf_to_utf<wchar_t>(toString());
	}
	bool fromString(std::string key) {
		boost::algorithm::unhex(key, v);
	}
};

typedef boost::shared_ptr<vTable> pvTable;
typedef boost::shared_ptr<vKey> pvKey;

// 生成key
pvTable doBuild(pvKey key, bool enc = true);
pvKey buildKey(const char *mem = 
               "PYCAdminabcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345!@#$%^&");