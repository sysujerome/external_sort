#include "util.h"

void get_file_content(vector<vector<vector<int>>>& files, vector<int>& content, int pass, int runs, int begin, int size)
{
    content.clear();
    int pos = begin, len = 0;

    while (pos < files[pass][runs].size() and len < size)
    {
        content.push_back(files[pass][runs][pos]);
        ++len;
        ++pos;
    }
    return;
}

void merge(vector<vector<vector<int>>>& files, int pass, int begin, int end)

    vector<int> output;

    int size_merge = end-begin+1;
    int mem_part_size = mem_size / (merge_way+1);
    files[pass+1].push_back({});

    vector<vector<int>> content_in_memory(size_merge, vector<int>{});
    for (int i = 0; i < merge_way; ++i)
    {
        get_file_content(files, content_in_memory[i], pass, begin+i, 0, mem_part_size);
    }

    priority_queue<HeapNode, vector<HeapNode>, decltype(compare)> que(compare);
    for (int i = 0; i < content_in_memory.size(); ++i)
    {
        que.push(HeapNode(i, 0, content_in_memory[i][0]));
    }

    while (!que.empty())
    {
        auto node = que.top();
        int index = node.index;
        int pos = node.pos;
        int value = node.value;
        que.pop();
        output.push_back(value);
        if (output.size() == mem_part_size)
        {
            // write back to memory
            for (int i = 0; i < output.size(); ++i)
                files[pass+1].back().push_back(output[i]);
            output.clear();
        }
        ++pos;
        if (pos % mem_part_size == 0) {
            get_file_content(files, content_in_memory[index], pass, index, pos, mem_part_size);
        }
        if (content_in_memory[index].empty()) continue;
        int content_in_memory_pos = pos%mem_part_size;
        que.push(HeapNode(index, pos, content_in_memory[index][content_in_memory_pos]));
    }
}

void external_sort(vector<int>& unsorted)
{
    vector<vector<vector<int>>> files;
    vector<vector<int>> tow_vector;
    vector<int> single_vector;
    files.push_back(tow_vector);
    for (int i = 0; i < unsorted.size(); ++i)
    {
        single_vector.push_back(unsorted[i]);
        if ((i+1) % mem_size == 0)
        {
            sort(single_vector.begin(), single_vector.end());
            files[0].push_back(single_vector);
            single_vector.clear();
        }
    }
    if (!single_vector.empty())
    {
        sort(single_vector.begin(), single_vector.end());
        files[0].push_back(single_vector);
    }
    int pass = 0;


    while (files.back().size() != 1)
    {
        files.push_back(tow_vector);
        int begin = 0, end = merge_way-1;
        while (end < files[pass].size())
        {
            merge(files, pass, begin, end);
            begin = end+1, end = end + merge_way;
        }
        ++ pass;
    }
    print(files.back()[0]);
    return;
}


int main() {
    vector<int> input(file_size, 0);
    for (int i = 0; i < file_size; ++i)
    {
        input[i] = rand()%data_range+1;
    }

    external_sort(input);


    return 0;
}