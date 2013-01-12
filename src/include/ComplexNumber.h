/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* C99 has a _Complex keyword but it might not be supported by 
* for instance avr-libc.
*
* Also various libraries like Ooura represent arrays of complex numbers as
* arrays of double numbers with the real component on odd indices and
* imaginary component on even indicies. This is equivalent to an array of
* ComplexNumber structs.
*
*/

#ifndef __COMPLEXNUMBER_H__
#define __COMPLEXNUMBER_H__

typedef struct {
   double   r;
   double   i;
} ComplexNumber;

/* x + yi */
void nami_init_complexnumber(ComplexNumber* n, double r, double i);

void nami_set_real(ComplexNumber* n, double r);

void nami_set_imaginary(ComplexNumber* n, double i);

double nami_get_real(ComplexNumber* n);

double nami_get_imaginary(ComplexNumber* n);

double nami_get_absolute(ComplexNumber* n);

/* (x + yi)(u + vi) = (xu – yv) + (xv + yu)i */
void nami_mult(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result);

void nami_add(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result);

#endif
