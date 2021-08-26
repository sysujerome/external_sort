#include <iostream>
#include <vector>
#include <algorithm>
// #include <priority_queue>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

constexpr int mem_size = 1000;
constexpr int file_size = 9000;
constexpr int merge_way = 3;
constexpr int data_range = 1000000;

char* input_file_name = "./unsorted_data";
char* output_file_name = "./sorted_data";



typedef struct HeapNode {
    int index;
    int pos;
    int value;
    HeapNode(int i, int p, int v) {
        index = i;
        pos = p;
        value = v;
    }
} HeapNode;

struct comp {
    bool operator() (HeapNode p1, HeapNode p2)
    {
        return p1.value > p2.value;
    }
};
static bool cmp(HeapNode p1, HeapNode p2)
{
    return p1.value > p2.value;
}

auto compare = [](HeapNode p1, HeapNode p2) { return p1.value > p2.value ; };

void print(vector<int>& nums)
{
    for (auto num : nums) cout << num << " ";
    cout << endl;
}


void print(vector<vector<int>>& nums)
{
    for (auto num : nums) print(num);
}


void print(vector<vector<vector<int>>>& nums)
{
    cout << " ------------------------------- "<< endl;
    for (int i = 0; i < nums.size(); ++i)
    {
        cout << i << ":" << endl;
        print(nums[i]);
    }
    cout << " ------------------------------- "<< endl << endl;
}

