#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#define wsize   sizeof(unsigned)
#define wmask   (wsize - 1)

void
_libkernel_bzero(void *dst0, size_t length)
{
    extern void * _libkernel_memset(void *dst0, int c0, size_t length);
	return (void)_libkernel_memset(dst0, 0, length);
}

#define RETURN  return (dst0)
#define VAL     c0
#define WIDEVAL c

void *
_libkernel_memset(void *dst0, int c0, size_t length)
{
	size_t t;
	unsigned c;
	unsigned char *dst;

	dst = dst0;
	/*
	 * If not enough words, just fill bytes.  A length >= 2 words
	 * guarantees that at least one of them is `complete' after
	 * any necessary alignment.  For instance:
	 *
	 *	|-----------|-----------|-----------|
	 *	|00|01|02|03|04|05|06|07|08|09|0A|00|
	 *	          ^---------------------^
	 *		 dst		 dst+length-1
	 *
	 * but we use a minimum of 3 here since the overhead of the code
	 * to do word writes is substantial.
	 */
	if (length < 3 * wsize) {
		while (length != 0) {
			*dst++ = VAL;
			--length;
		}
		RETURN;
	}

	if ((c = (unsigned char)c0) != 0) {    /* Fill the word. */
		c = (c << 8) | c;       /* unsigned is 16 bits. */
#if UINT_MAX > 0xffff
		c = (c << 16) | c;      /* unsigned is 32 bits. */
#endif
#if UINT_MAX > 0xffffffff
		c = (c << 32) | c;      /* unsigned is 64 bits. */
#endif
	}
	/* Align destination by filling in bytes. */
	if ((t = (long)dst & wmask) != 0) {
		t = wsize - t;
		length -= t;
		do {
			*dst++ = VAL;
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / wsize;
	do {
		*(unsigned *)dst = WIDEVAL;
		dst += wsize;
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & wmask;
	if (t != 0) {
		do {
			*dst++ = VAL;
		} while (--t != 0);
	}
	RETURN;
}