#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"

#define psize (200)

struct poly_t
{
	int coef[psize], pwr[psize], cused;
};

void sortp(poly_t* p)
{
	for (int i = 0; i < p->cused; i++)
	{
		for (int j = 0; j < p->cused - 1; j++)
		{
			if (p->pwr[j] < p->pwr[j+1])
			{
				int tmp = p->coef[j],
				tmp2 = p->pwr[j];

				p->coef[j] = p->coef[j+1];
				p->coef[j+1] = tmp;

				p->pwr[j] = p->pwr[j+1];
				p->pwr[j+1] = tmp2;
			}
		}
	}
}

poly_t* new_poly_from_string(const char* t)
{
	poly_t *v;
	v = (poly_t*)calloc(1, sizeof(struct poly_t));

	v->cused = 0;


	//v->coef[0] = 0;
	//printf("SIZE %lu VAL %d", sizeof(v->coef), v->coef[0]);

	int c = 0, passedx = 0, sign = 1; // 0 = -, 1 = +


	for (int i = 0; i < strlen(t); i++)
	{
		//printf(" %c ", t[i]);
		if (t[i] == '^') // efterföljer alltid x
		{
			//passedpwr = 1;
			sign = 1; //positiv exponent antas
			v->pwr[c] = 0;
		}
		if (t[i] == 'x')
		{
			if (sign == 0 && v->coef[c] == 0)
				v->coef[c] = -1;
			passedx = 1;
			v->pwr[c] = 1;
			sign = 1;
		}
		if (isdigit(t[i]))
		{
			if (!passedx)
			{
				v->coef[c] *= 10;
				v->coef[c] += sign ? t[i] - '0' : -((int)(t[i] - '0'));
			}
			else
			{
				if (v->coef[c] == 0)
					v->coef[c] = sign ? 1 : -1;
				v->pwr[c] *= 10;
				v->pwr[c] += sign ? t[i] - '0' : -(int)((t[i] - '0'));
			}
		}
		if (t[i] == '-')
		{
			sign = 0;
			//passedpwr = 0;
			passedx = 0;

			if (i != 0)
				c++;
		}
		if (t[i] == '+')
		{
			sign = 1;
			//passedpwr = 0;
			passedx = 0;
			c++;
		}

		if (c > psize / 2)
		{
			exit(0);
		}
	}
	v->cused = c + 1;

	sortp(v);

	/*for (int i = 0; i < v->cused; i++)
	{
		printf("VAL %d VAL %d\n", v->coef[i], v->pwr[i]);
	}*/
	return v;
}


void free_poly(poly_t* p)
{
	free(p);
}

poly_t* mul(poly_t* p, poly_t* r)
{
	poly_t *v;
	v = (poly_t*)calloc(1, sizeof(struct poly_t));

	v->cused = 0;

	for (int i = 0; i < p->cused; i++)
	{
		for (int j = 0; j < r->cused; j++)
		{
			int co = p->coef[i] * r->coef[j],
			pw = p->pwr[i] + r->pwr[j], match = 0;


			for (int k = 0; k < v->cused; k++)
			{
				if (v->pwr[k] == pw)
				{
					v->coef[k] += co;
					match = 1;
				}
			}

			if (!match)
			{
				v->coef[v->cused] = co;
				v->pwr[v->cused] = pw;

				(v->cused)++;
			}
		}
	}
	sortp(v);

	return v;
}

void print_poly(poly_t* p)
{

	//for (int i = 0; i < p->cused; i++)
	//{
		//printf("##VAL %d VAL %d\n", p->coef[i], p->pwr[i]);
	//}

	if (p->coef[0] < 0)
		printf("-");

	for (int i = 0; i < p->cused; i++)
	{

		if (!(p->coef[i] == 1 && p->pwr[i] >= 2))
		{
			printf("%d", abs(p->coef[i]));
		}
		if (p->pwr[i] != 0)
		{
			printf("x");
		}
		if (p->pwr[i] >= 2)
		{
			printf("^%d", p->pwr[i]);
		}
		if (i != p->cused - 1)
		{
			printf(" ");

			if (p->coef[i+1] > 0)
			{
				printf("+ ");
			}
			else if (p->coef[i+1] < 0)
			{
				printf("- ");
			}
		}
	}
	printf("\n");
}

