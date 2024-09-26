#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    string roll_number;
    int arts_marks;
    int science_marks;
};
void handle_query(const vector<Student>& students, 
                  int min_marks, int max_marks, 
                  bool is_arts) {
    vector<pair<int, string>> records;
    
    for (const auto& student : students) {
        int marks = is_arts ? student.arts_marks : student.science_marks;
        if (marks >= min_marks && marks <= max_marks) {
            records.emplace_back(marks, student.roll_number);
        }
    }

    sort(records.rbegin(), records.rend());

    for (const auto& record : records) {
        cout << "Roll Number: " << record.second << ", Marks: " << record.first << endl;
    }
}

void compute_ranks(const vector<Student>& students, 
                   map<string, int>& arts_rank, 
                   map<string, int>& science_rank) {
    vector<pair<int, string>> arts_records;
    vector<pair<int, string>> science_records;

    for (const auto& student : students) {
        arts_records.emplace_back(student.arts_marks, student.roll_number);
        science_records.emplace_back(student.science_marks, student.roll_number);
    }

    auto compute_rank = [](vector<pair<int, string>>& records) {
        sort(records.rbegin(), records.rend()); // Sort descending
        map<int, int> rank_map;
        int rank = 1;
        for (size_t i = 0; i < records.size(); ++i) {
            if (i > 0 && records[i].first < records[i - 1].first) {
                rank = i + 1;
            }
            rank_map[records[i].first] = rank;
        }
        return rank_map;
    };

    map<int, int> arts_rank_map = compute_rank(arts_records);
    map<int, int> science_rank_map = compute_rank(science_records);

    for (const auto& student : students) {
        arts_rank[student.roll_number] = arts_rank_map[student.arts_marks];
        science_rank[student.roll_number] = science_rank_map[student.science_marks];
    }
}

void decide_program(const vector<Student>& students, 
                    const map<string, int>& arts_rank, 
                    const map<string, int>& science_rank) {
    vector<tuple<string, string>> decisions;
    int count_ba = 0, count_bs = 0, count_choice = 0;

    for (const auto& student : students) {
        int ra = arts_rank.at(student.roll_number);
        int rs = science_rank.at(student.roll_number);

        if (ra < rs) {
            decisions.emplace_back(student.roll_number, "BA");
            ++count_ba;
        } else if (ra > rs) {
            decisions.emplace_back(student.roll_number, "BS");
            ++count_bs;
        } else {
            decisions.emplace_back(student.roll_number, "Choice");
            ++count_choice;
        }
    }

    sort(decisions.begin(), decisions.end());

    for (const auto& decision : decisions) {
        cout << "Roll Number: " << get<0>(decision) << ", Decision: " << get<1>(decision) << endl;
    }

    cout << "Number of students for BA: " << count_ba << endl;
    cout << "Number of students for BS: " << count_bs << endl;
    cout << "Number of students for Choice: " << count_choice << endl;
}
int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<Student> students(n);

    cout << "Enter roll number, arts marks, and science marks for each student:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> students[i].roll_number >> students[i].arts_marks >> students[i].science_marks;
    }

    map<string, int> arts_rank;
    map<string, int> science_rank;

    compute_ranks(students, arts_rank, science_rank);

    while (true) {
        int option;
        cout << "Enter option (0: Exit, 1: Arts Query, 2: Science Query): ";
        cin >> option;

        if (option == 0) break;

        int a, b;
        if (option == 1) {
            cout << "Enter arts marks interval (a b): ";
            cin >> a >> b;
            handle_query(students, a, b, true);
        } else if (option == 2) {
            cout << "Enter science marks interval (a b): ";
            cin >> a >> b;
            handle_query(students, a, b, false);
        }
    }

    decide_program(students, arts_rank, science_rank);

    return 0;
}