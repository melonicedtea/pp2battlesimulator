#include "merge_sort.h"
#include "precomp.h"
namespace Tmpl8
{
vector<Tank*> MergeSort::mergeSort(vector<Tank*>& original)
{  

	if (original.size() <= 1)
    {
        return original;
    }
    int len = floor(original.size() / 2);
    vector<Tank*> left(original.begin(), original.begin() + len);
    vector<Tank*> right(original.begin() + len, original.end());

    return merge(mergeSort(left), mergeSort(right));
}
vector<Tank*> MergeSort::merge(vector<Tank*>& left, vector<Tank*>& right)
{
	int leftCount = 0;
    int rightCount = 0;
    
    vector<Tank*> results;
    results.reserve(1279 + 1279);
    bool useLeft;
    for (int i = 0; i < left.size() + right.size(); i++)
    {
        if (leftCount < left.size())
        {
            if (rightCount < right.size())
            {
                useLeft = (left[leftCount]->health < right[rightCount]->health);
            }
            else
            {
                useLeft = true;
            }
        }
        else
        {
            useLeft = false;
        }

        if (useLeft)
        {
            results.push_back(left[leftCount]);
            if (leftCount < left.size())
            {
                leftCount++;
            }
        }
        else
        {
            results.push_back(right[rightCount]);
            if (rightCount < right.size())
            {
                rightCount++;
            }
        }
    }
    return results;
}



} // namespace Tmpl8