#pragma once
namespace Tmpl8
{
class MergeSort
{
  public:
    vector<Tank*> mergeSort(vector<Tank*>& original);

  private:
    vector<Tank*> merge(vector<Tank*>& tank_ptrs_a, vector<Tank*>& tank_ptrs_b);
	
     
};
}