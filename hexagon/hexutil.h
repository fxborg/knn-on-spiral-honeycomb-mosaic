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
			//北　角
		}
		else
		{
			//南　角
		}
	}
	else if (r == 0)
	{
		if (q > 0)
		{
			//北東　角
		}
		else
		{
			//南西　角
		}
	}
	else if (s == 0)
	{
		if (r > 0) 
		{
			//北西　角

		}
		else 
		{
			//南東　角
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
				// 東　辺
			}
			else
			{
				// 西　辺
			}
		}
		else
		{
			if (ar > as)
			{
				if (r > 0) 
				{
					//北西　辺
				}
				else
				{
					//南東　辺

				}

			}
			else 
			{
				if (s > 0)
				{
					//南西　辺
				}
				else 
				{
					//北東　辺
				}

			}

		}
	}


}