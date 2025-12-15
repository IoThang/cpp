#include <set>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int idx{0};
        set<int> sett;
        vector<int> res;

        for(auto val:nums){
            auto it = sett.find(val);
            if(it == sett.end()){
                sett.insert(val);
                res.push_back(val);
                idx++;
            }
        }
        nums = res;
        return idx;
    }
};

class Solution2 {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0; // Handle empty array case
        int j = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1]) {
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }
};