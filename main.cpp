#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

//расстояние Хэмминга
int hamingDist(string &vec1, string &vec2, int &index_word)
{
    int vec1_size = vec1.size();
    int vec2_size = vec2.size();
    int minCount = vec1.size();
    bool flag_find = false;

    //#pragma omp parallel for
    #pragma omp parallel for schedule(dynamic, 1000)
    for (int j = 0; j < vec2_size-vec1_size; ++j)
    {
        int hamingCount = 0;
        for (int i = 0; i < vec1_size; ++i)
        {
            if (vec1[i] != vec2[j+i])
            {
                hamingCount++;
            }
        }

        //Присваиваем минимальный путь
        if(hamingCount < minCount)
        {
            minCount = hamingCount;
        }

        if(minCount == 0 && flag_find == false)
        {
            flag_find = true;
            index_word = j;
        }
    }

    return minCount;
}

string readFile(const string& fileName) {
    ifstream f(fileName);
    f.seekg(0, ios::end);
    size_t size = f.tellg();
    string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size);
    return s;
}

int main()
{
    string word;
    string text;
    string word_find;
    int size = 0;
    int index_word = -1;

    string fileName = "C:\\Qt_Lab\\paralel_3\\text.txt";
    text = readFile(fileName);     //Открыли файл и записали text

    fileName = "C:\\Qt_Lab\\paralel_3\\word.txt";
    word = readFile(fileName);     //Открыли файл и записали word

    //Время начала работы
    clock_t tStart = clock();

    size = hamingDist(word,text,index_word);

    for (size_t i = index_word; i < word.size() + index_word; ++i)
    {
        word_find += text[i];
    }

    if(size == 0)
    {
        cout << "Find word - " << word_find <<endl;
    }

    if(index_word == -1)
    {
        cout << "Minimum path - " << size << endl;
    }

    //Время окончания работы
    printf_s("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
