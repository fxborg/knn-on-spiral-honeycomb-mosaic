#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
using std::max;
int is_direction(int q, int r, int s) {

	if (q == 0 && r == 0 && s == 0) return 0;

	if (q == 0)
	{
		if (r > 0)
		{
			//�k�@�p
		}
		else
		{
			//��@�p
		}
	}
	else if (r == 0)
	{
		if (q > 0)
		{
			//�k���@�p
		}
		else
		{
			//�쐼�@�p
		}
	}
	else if (s == 0)
	{
		if (r > 0) 
		{
			//�k���@�p

		}
		else 
		{
			//�쓌�@�p
		}
	}
	else
	{
		int aq = abs(q);
		int ar = abs(r);
		int as = abs(s);

		if (aq > ar && aq> as)
		{
			if(q>0)
			{ 
				// ���@��
			}
			else
			{
				// ���@��
			}
		}
		else
		{
			if (ar > as)
			{
				if (r > 0) 
				{
					//�k���@��
				}
				else
				{
					//�쓌�@��

				}

			}
			else 
			{
				if (s > 0)
				{
					//�쐼�@��
				}
				else 
				{
					//�k���@��
				}

			}

		}
	}


}