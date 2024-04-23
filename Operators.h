/*
 * IncFile1.h
 *
 * Created: 16.03.2017 15:26:41
 *  Author: a16007
 */


#ifndef OPERATORS_H_
#define OPERATORS_H_

#include <stdlib.h>
#include <stddef.h>

void * operator new(size_t size);
void operator delete(void * ptr);


#endif /* OPERATORS_H_ */
