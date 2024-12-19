#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>
#include <clocale> 

using namespace std;

struct Student {
    string full_name;
    string group_number;
    vector<int> grades;

    double average_grade() const {
        double sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
};

vector<Student> read_students(int n) {
    vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        getline(cin >> ws, students[i].full_name);
        cin >> students[i].group_number;
        students[i].grades.resize(5);
        for (int j = 0; j < 5; ++j) {
            cin >> students[i].grades[j];
        }
    }
    return students;
}

bool compare_by_group(const Student& a, const Student& b) {
    return a.group_number < b.group_number;
}

vector<Student> filter_students_with_high_avg(const vector<Student>& students) {
    vector<Student> filtered_students;
    for (const auto& student : students) {
        if (student.average_grade() > 4.0) {
            filtered_students.push_back(student);
        }
    }
    sort(filtered_students.begin(), filtered_students.end(), [](const Student& a, const Student& b) {
        return a.average_grade() > b.average_grade();
        });
    return filtered_students;
}

map<string, pair<int, int>> group_students(const vector<Student>& students) {
    map<string, pair<int, int>> groups;

    for (const auto& student : students) {
        groups[student.group_number].first++;
        if (find(student.grades.begin(), student.grades.end(), 2) != student.grades.end()) {
            groups[student.group_number].second++;
        }
    }

    return groups;
}

void print_group_table(const map<string, pair<int, int>>& grouped_info) {
    cout << "\nГрупповая информация:\n";

    cout << "┌────────────┬───────────────┬─────────────┐\n";
    cout << "│ Номер группы│ Количество     │ Двоечники   │\n";
    cout << "├────────────┼───────────────┼─────────────┤\n";

    for (const auto& group : grouped_info) {
        cout << "│ " << setw(11) << group.first
            << " │ " << setw(13) << group.second.first
            << " │ " << setw(11) << group.second.second
            << " │\n";
    }

    cout << "└────────────┴───────────────┴─────────────┘\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;

    cout << "Введите количество студентов: ";
    cin >> n;

    vector<Student> students = read_students(n);

    sort(students.begin(), students.end(), compare_by_group);

    cout << "\nИнформация о студентах:\n";

    cout << "┌────────────┬───────────────────────────┬───────────────────────────┐\n";
    cout << "│ Номер группы│ ФИО                       │ Оценки                   │\n";
    cout << "├────────────┼───────────────────────────┼───────────────────────────┤\n";

    for (const auto& student : students) {
        cout << "│ " << setw(11) << student.group_number
            << " │ " << setw(25) << student.full_name
            << " │ ";

        for (size_t j = 0; j < student.grades.size(); ++j) {
            cout << student.grades[j];
            if (j < student.grades.size() - 1)
                cout << ", ";
        }

        cout << setw(25 - (student.grades.size() * 3)) << " │\n";
    }

    cout << "└────────────┴───────────────────────────┴───────────────────────────┘\n";

    vector<Student> high_avg_students = filter_students_with_high_avg(students);

    if (!high_avg_students.empty()) {
        cout << "\nСтуденты с высоким средним баллом:\n";

        cout << "┌────────────┬───────────────────────────┬───────────────┐\n";
        cout << "│ Номер группы│ ФИО                       │ Средний балл  │\n";
        cout << "├────────────┼───────────────────────────┼───────────────┤\n";

        for (const auto& student : high_avg_students) {
            cout << "│ " << setw(11) << student.group_number
                << " │ " << setw(25) << student.full_name
                << " │ " << fixed << setprecision(2)
                << setw(13) << student.average_grade()
                << " │\n";
        }

        cout << "└────────────┴───────────────────────────┴───────────────┘\n";

    }
    else {
        cout << "\nNO\n";
    }

    auto grouped_info = group_students(students);

    print_group_table(grouped_info);

    return 0;
}
//