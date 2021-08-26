#include <iostream>
#include <vector>
#include <algorithm>
// #include <priority_queue>
#include <queue>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

constexpr int mem_size = 10000000;
constexpr int file_size = 900000000;
constexpr int merge_way = 3;
constexpr int data_range = 1000000;

string inFile = "./unsorted_data";
string outFile = "./sorted_data";
const char* input_file_name = inFile.c_str();
const char* output_file_name = outFile.c_str();


typedef struct HeapNode {
    int index;
    int pos;
    string value;
    HeapNode(int i, int p, string v) {
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

template <typename T>
void print(vector<T>& nums)
{
    for (auto num : nums) cout << num << " ";
    cout << endl;
}
template <typename T>
void print(vector<vector<T>>& nums)
{
    for (auto num : nums) print(num);
}

template <typename T>
void print(vector<vector<vector<T>>>& nums)
{
    cout << " ------------------------------- "<< endl;
    for (int i = 0; i < nums.size(); ++i)
    {
        cout << i << ":" << endl;
        print(nums[i]);
    }
    cout << " ------------------------------- "<< endl << endl;
}

string get_file_name(int pass, int runs)
{
    stringstream ss;
    string name;
    ss << "data_" << pass << "_" << runs;
    ss >> name;
    return name;
}