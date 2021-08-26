#include "util.h"

void create_data(const char* input_file, int file_size)
{
    ofstream outFile;
    outFile.open(input_file);
    int file_current_size = 0;
    int wordSize = 0;
    char letter;
    while (file_current_size < file_size)
    {
        wordSize = rand()%10+1;
        if (file_current_size + wordSize <= file_size)
        {
            for (int i = 0; i < wordSize; ++i)
            {
                letter = 'a'+rand()%26;
                outFile << letter;
            }
            file_current_size += wordSize;
            // cout << file_current_size << " ";
            if (file_current_size < file_size)
            {
                outFile << '\n';
                ++file_current_size;
            }
        }
        if (file_current_size >= file_size) break;
    }
    outFile.close();
}



void get_file_content(ifstream& input_file, vector<string>& content, int size)
{
    content.clear();
    if (input_file.eof()) return;
    string line;
    int len = 0;
    while ( len <= size and !input_file.eof())
    {
        getline(input_file, line);
        len += line.length();
        content.push_back(line);
    }

    return;
}



void merge(int pass, int begin, int end)
{
    auto outFile_name = get_file_name(pass+1, begin/merge_way+1);
    ofstream output_file(outFile_name.c_str());
    vector<ifstream> input_files(merge_way);
    for (int i = 0; i < input_files.size(); ++i)
    {
        const char* file_name = get_file_name(pass, begin+i+1).c_str();
        input_files[i].open(file_name);
    }

    int mem_part_size = mem_size / (merge_way+1);

    vector<vector<string>> content_in_memory(merge_way, vector<string>{});
    vector<string> output_memory;
    vector<int> mem_size(merge_way+1, 0);
    for (int i = 0; i < merge_way; ++i)
    {
        get_file_content(input_files[i], content_in_memory[i], mem_part_size);
    }

    priority_queue<HeapNode, vector<HeapNode>, decltype(compare)> que(compare);
    for (int i = 0; i < content_in_memory.size(); ++i)
    {
        que.push(HeapNode(i, 0, content_in_memory[i][0]));
    }

    int counter = 0;

    while (!que.empty())
    {
        ++counter;
        auto node = que.top();
        int index = node.index;
        int pos = node.pos;
        string value = node.value;
        que.pop();
        output_memory.push_back(value);
        if (output_memory.size() == mem_part_size)
        {
            // write back to memory
            for (int i = 0; i < output_memory.size(); ++i)
            {
                if (output_file.tellp() != 0) output_file << '\n';
                output_file << output_memory[i];
            }
            // output_file << output_memory.back();
            output_memory.clear();
            // output_file.flush();
        }
        ++pos;
        if (pos == content_in_memory[index].size() ) {
            get_file_content(input_files[index], content_in_memory[index], mem_part_size);
            pos = 0;
        }
        if (content_in_memory[index].empty()) continue;
        que.push(HeapNode(index, pos, content_in_memory[index][pos]));
    }
    if (!output_memory.empty())
    {
        for (int i = 0; i < output_memory.size(); ++i)
        {
            if (output_file.tellp() != 0) output_file << '\n';
            output_file << output_memory[i];
        }
            // output_file << output_memory.back();
        output_memory.clear();
    }

    // cout << counter << endl;
    output_file.close();
    for (int i = 0; i < input_files.size(); ++i)
    {
        input_files[i].close();
    }
}



void external_sort(const char* file)
{
    int len = 0, runs = 0, pass = 0;
    ifstream input(file);
    vector<string> file_content;
    while (!input.eof())
    {
        // cout << runs << endl;
        string line;
        file_content.clear();
        getline(input, line);
        len = 0;
        while (len + line.length() <= mem_size)
        {
            file_content.push_back(line);
            len += line.length()+1;
            if (input.eof()) break;
            getline(input, line);
        }
        sort(file_content.begin(), file_content.end());
        
        auto file_name = get_file_name(pass, runs+1);
        ofstream output(file_name.c_str());
        for (int i = 0; i < file_content.size()-1; ++i)
        {
            output << file_content[i] << endl;
        }
        output << file_content.back();
        output.close();
        ++runs;
    }

    // cout << endl;
    // print(file_content);

    int new_runs = 0;
    while (runs > 1)
    {
        int begin = 0, end = merge_way < runs ? merge_way-1 : runs-1;
        new_runs = 0;
        while (end < runs)
        {
            merge(pass, begin, end);
            begin = end+1, end = end+merge_way;
            ++new_runs;
        }
        for (int i = 0; i < runs; ++i)
        {
            auto file_name = get_file_name(pass, i+1);
            remove(file_name.c_str());
        }
        ++pass;
        runs = new_runs;
    }

    return;
}


int main() {


    create_data(input_file_name, file_size);

    cout << "sort begin..." << endl;
    
    const clock_t begin_time = clock();

    external_sort(input_file_name);

    float time_cost = clock()-begin_time;
    cout << "Sort " << file_size << " B file took " << time_cost/CLOCKS_PER_SEC << " seconds" << endl; 

    return 0;
}