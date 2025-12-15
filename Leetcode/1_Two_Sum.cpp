// Two pointers

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> imap;

        for (int i = 0;; ++i) {
            auto it = imap.find(target - nums[i]);

            if (it != imap.end())
                return vector<int>{i, it->second};

            imap[nums[i]] = i;
        }
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target){
        for(int i = 0; i < nums.size(); i++){
            for(int j = i + 1; j < nums.size(); j++){
                if(nums[i] + nums[j] == target){
                    return {i, j};
                }
            }
        }
        return {};
    }
};

int main(){
    int size{0}, target;
    vector<int> nums{0};
    cin >> size;
    for(auto i = 0; i < size; i++){
        cin >> i;
        nums.push_back(i);
    }

    cin >> target;

    Solution s1;

    vector<int> res = s1.twoSum(nums, target);

    cout << res;

    return 0;
}