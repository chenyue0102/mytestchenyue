#ifndef BYTE_SWAP_H
#define BYTE_SWAP_H
#include <assert.h>
#include <stdint.h>

namespace ByteSwap {
enum {
	LITTLE_ENDIAN = 1234,
	BIG_ENDIAN = 4321,
};
union MyUnion
{
	char ch;
	int i;
};

inline int getByteOrder()
{
	MyUnion un;
	un.i = 0x12345678;
	if (un.ch == 0x12) {
		return BIG_ENDIAN;
	}
	else {
		return LITTLE_ENDIAN;
	}
}

inline uint16_t byteSwap(uint16_t n) {
	//ab ba
	return ((n & 0xff) << 8) | ((n >> 8) & 0xff);
}

inline uint32_t byteSwap(uint32_t n) {
	//abcd dcba
	return ((n & 0xff) << 24)
		| ((n & 0xff00) << 8)
		| ((n & 0xff0000) >> 8)
		| ((n & 0xff000000) >> 24);
}

#define letoh htole
#define betoh htobe

inline uint16_t htole(uint16_t n) {
	if (getByteOrder() == LITTLE_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}

inline uint32_t htole(uint32_t n) {
	if (getByteOrder() == LITTLE_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}

inline uint16_t htobe(uint16_t n) {
	if (getByteOrder() == BIG_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}

inline uint32_t htobe(uint32_t n) {
	if (getByteOrder() == BIG_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}

inline uint16_t htons(uint16_t n) {
	if (getByteOrder() == BIG_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}

inline uint32_t htonl(uint32_t n) {
	if (getByteOrder() == BIG_ENDIAN) {
		return n;
	}
	else {
		return byteSwap(n);
	}
}
}

#endif