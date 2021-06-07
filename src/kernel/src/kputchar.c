//
// Created by john on 6/7/21.
//

#include "../include/kstdio.h"

#if defined(__is_libk)
#include "../include/kterminal.h"
#endif

int kputchar(int ic) {

#if defined(__is_libk)
		char c = (char) ic;
		kterminal_write(&c,sizeof(c));
	#else
	#endif
		return ic;
}