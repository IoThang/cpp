#include <iostream>
using namespace std;


//  Binary search technique
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        vector<int> res{-1,-1};

        while(low <= high){
            int mid = low + (high - low) / 2;
            
            if(nums[mid] < target){
                low = mid + 1;
            }
            else if(nums[mid] > target){
                high = mid - 1;
            }
            else{
                if(mid == 0 || nums[mid - 1] != target){
                    res[0] = nums[mid];
                    break;
                }
                else{
                    high = mid - 1;
                }
            }
        }

        low = 0;
        high = nums.size() - 1;
        while(low <= high){
            int mid = low + (high - low) / 2;
            
            if(nums[mid] < target){
                low = mid + 1;
            }
            else if(nums[mid] > target){
                high = mid - 1;
            }
            else{
                if(mid == 0 || nums[mid + 1] != target){
                    res[0] = nums[mid];
                    break;
                }
                else{
                    low = mid + 1;
                }
            }
        }
    }
};