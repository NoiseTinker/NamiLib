/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "ComplexNumber.h"
#include <math.h>

/* x + yi */
void initComplexNumber(ComplexNumber* n, double r, double i)
{
	n->r = r;
	n->i = i;
}

void setReal(ComplexNumber* n, double r)
{
	n->r = r;
}

void setImaginary(ComplexNumber* n, double i)
{
	n->i = i;
}

double getReal(ComplexNumber* n)
{
	return n->r;
}

double getImaginary(ComplexNumber* n)
{
	return n->i;
}

double getAbsolute(ComplexNumber* n)
{
	return sqrt((n->r * n->r) + (n->i * n->i));
}

/* (x + yi)(u + vi) = (xu – yv) + (xv + yu)i */
void mult(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result)
{
	double realProduct = (n1->r * n2->r) - (n1->i * n2->i);
	double imaginaryProduct = (n1->r * n2->i) + (n1->i * n2->r);

	result->r = realProduct;
	result->i = imaginaryProduct;
}

void add(ComplexNumber* n1, ComplexNumber* n2, ComplexNumber* result)
{
	double realSum = n1->r + n2->r;
	double imaginarySum = n1->i + n2->i;

	result->r = realSum;
	result->i = imaginarySum;
}
