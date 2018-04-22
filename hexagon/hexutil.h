#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <unordered_map>
using std::unordered_map;
using std::max;
unordered_map<int,int> distance_map(int q, int r, int s) {

	if (q == 0 && r == 0 && s == 0) {
		// íÜâõ	
		return {
			{ 4,1 },
		{ 3,1 },{ 5,1 },
			{ 0,0 },
		{ 2,1 } ,{ 6,1 },
			{ 1,1 }
		};
	}

	if (q == 0)
	{
		if (r > 0)
		{
			//ñkÅ@äp
			return {
				{ 4,1 },
			{ 3,1 },{ 5,1 },
				{ 0,0 },
			{ 2,0 } ,{ 6,0 },
				{ 1,-1 }
			};
		}
		else
		{
			//ìÏÅ@äp
			return { 
				{ 4,-1 },
			{ 3,0 },{ 5,0 },
				{ 0,0 },
			{ 2,1 } ,{ 6,1 },
				{ 1,1 } 
			};
		}
	}
	else if (r == 0)
	{
		if (q > 0)
		{
			//ñkìåÅ@äp
			return {
				{ 4,1 },
			{ 3,0 },{ 5,1 },
				{ 0,0 },
			{ 2,-1 } ,{ 6,1 },
				{ 1,0 } 
			};
		}
		else
		{
			//ìÏêºÅ@äp
			return {
				{ 4,0 },
			{ 3,1 },{ 5,-1 },
				{ 0,0 },
			{ 2,1 },{ 6,0 },
				{ 1,1 } 
			};
		}
	}
	else if (s == 0)
	{
		if (r > 0) 
		{
			//ñkêºÅ@äp
			return { 
				{ 4,1 },
			{ 3,1 },{ 5,0 },
				{ 0,0 },
			{ 2,1 },{ 6,-1 },
				{ 1,0 } 
			};

		}
		else 
		{
			//ìÏìåÅ@äp
			return {
				{ 4,0 },
			{ 3,-1},{ 5,1 },
				{ 0,0 },
			{ 2,0 }, { 6,1 },
				{ 1,1 }
			};

		}
	}
	else
	{
		const int aq{ abs(q) };
		const int ar{ abs(r) };
		const int as{ abs(s) };

		if (aq > ar && aq> as)
		{
			if(q>0)
			{ 
				// ìåÅ@ï”
				return {
					{ 4,0 },
				{ 3,-1 },{ 5,1 },
					{ 0,0 },
				{ 2,-1 } ,{ 6,1 },
					{ 1,0 }
				};
			}
			else
			{
				// êºÅ@ï”
				return {
					{ 4,0 },
				{ 3,1 },{ 5,-1 },
					{ 0,0 },
				{ 2,1 } ,{ 6,-1 },
					{ 1,0 }
				};
			}
		}
		else
		{
			if (ar > as)
			{
				if (r > 0) 
				{
					//ñkêºÅ@ï”
					return {
						{ 4,1 },
					{ 3,1 },{ 5,0 },
						{ 0,0 },
					{ 2,0} ,{ 6,-1 },
						{ 1,-1}
					};
				}
				else
				{
					//ìÏìåÅ@ï”
					return {
						{ 4,-1 },
					{ 3,-1 },{ 5,0 },
						{ 0,0 },
					{ 2,0 } ,{ 6,1 },
						{ 1,1 }
					};

				}

			}
			else 
			{
				if (s > 0) 
				{
					//ìÏêºÅ@ï”
					return {
						{ 4,-1 },
					{ 3,0 },{ 5,-1 },
						{ 0,0 },
					{ 2,1 } ,{ 6,0 },
						{ 1,1 }
					};
				}
				else 
				{
					//ñkìåÅ@ï”
					return {
						{ 4,1 },
					{ 3,0 },{ 5,1 },
						{ 0,0 },
					{ 2,-1 } ,{ 6,0 },
						{ 1,-1 }
					};
				}

			}

		}
	}


}