#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void readFile(const string filename, vector<string>& lines) {
    string line;
    int task_num = 0;
    
    // Open file
    ifstream fin;
    fin.open(filename.c_str());
    if (!fin.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }

    // Read & push to string vector
    while (getline(fin, line)) {
        if (line.substr(0, 6).compare("[Task ") == 0) {
            // The first line of a new task 
            task_num++;
            lines.push_back(line);
        } else if (task_num >= 1) {
            // Answer of the task
            lines[task_num-1] = lines[task_num-1] + "\n" + line;
        } else {
            cerr << "Unexpected file format: " << filename << endl;
            exit(-1);
        }
    }

    fin.close();
    return;
}


int main(int argc, char **argv) {
    vector<int> scores;
    int total_score = 0;
    vector<string> submit;
    vector<string> answer;

    // Scores
    if (argc == 1) {
        int sample[6] = {1, 2, 3, 3, 3, 3};
        scores.insert(scores.end(), sample, sample+6);
    } else {
        for (int i=1; i<argc; i++) {
            int score = atoi(argv[i]);
            scores.push_back(score);
        }
    }

    // Read submit.txt & answer.txt
    readFile("submit.txt", submit);
    readFile("answer.txt", answer);
    
    // Add score if submit and answer are the same
    for (int i=0; i < min(submit.size(), answer.size()); i++)
        if (submit[i].compare(answer[i]) == 0)
            total_score += scores[i];

    cout << "Your score is " << total_score << endl;

    return 0;
}