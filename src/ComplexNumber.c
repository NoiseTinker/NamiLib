/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "ComplexNumber.h"
#include <math.h>

/* x + yi */
void nami_init_complexnumber(ComplexNumber* n, double r, double i)
{
	n->r = r;
	n->i = i;
}

void nami_set_real(ComplexNumber* n, double r)
{
	n->r = r;
}

void nami_set_imaginary(ComplexNumber* n, double i)
{
	n->i = i;
}

double nami_get_real(ComplexNumber* n)
{
	return n->r;
}

double nami_get_imaginary(ComplexNumber* n)
{
	return n->i;
}

double nami_get_absolute(ComplexNumber* n)
{
	return sqrt((n->r * n->r) + (n->i * n->i));
}

/* (x + yi)(u + vi) = (xu – yv) + (xv + yu)i */
void nami_mult(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result)
{
	double realProduct = (n1->r * n2->r) - (n1->i * n2->i);
	double imaginaryProduct = (n1->r * n2->i) + (n1->i * n2->r);

	result->r = realProduct;
	result->i = imaginaryProduct;
}

void nami_add(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result)
{
	double realSum = n1->r + n2->r;
	double imaginarySum = n1->i + n2->i;

	result->r = realSum;
	result->i = imaginarySum;
}
