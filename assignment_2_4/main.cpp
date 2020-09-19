/*

Shows how to store a map container inside a map container
Shows how to set values on the innermost value in such a container
Shows how to iterate a container and then iterate the container it contains

*/

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// Create an alias type for a map with string to int lookup.
// The key represents a course name and the int the course grade.
typedef map<string, string> Grades;

// Create an alias type for a map with string to map with string to int lookup.
// The key represents a student name, and the value a list of grades for that student.
// todo Students [name] [course name] = grade
typedef map<string, Grades> Students;

int main()
{
    // Create container for students
    Students students;
    string student_name_user;
    string course_name_user;
    string grade_user;
    string Stop = "stop";

    cout << "Enter student name:  " << endl;
    getline(cin, student_name_user);

    while (true){

        cout << "Enter course name:  " << endl;
        getline(cin, course_name_user);
        if (course_name_user == Stop){
            break;
        }else{
        cout << "Enter grade:  " << endl;
        getline(cin, grade_user);
        students[student_name_user][course_name_user] = grade_user;
        }
    }


//        // Use find_if and erase the result, if any. Works!
//        auto it = std::find_if(students.begin(), students.end(), [student_name_user](auto& students) { return students.second == student_name_user; });
//        if (it != students.end())
//            students.erase(it);


    string  student_name_user_check;

    cout << "Enter new student name:  " << endl;
    getline(cin, student_name_user);

    while (student_name_user != Stop){

        cout << "Enter course name:  " << endl;
        getline(cin, course_name_user);
        if (course_name_user != Stop){

            cout << "Enter grade:  " << endl;
            getline(cin, grade_user);
            students[student_name_user][course_name_user] = grade_user;
        }else{
            getline(cin, student_name_user);
            if (student_name_user == Stop){break;}
        }
    }

    // Iterate all students
    for(const auto& student: students)
    {
        // Iterate and print all grades of this student
        for(const auto& grade: student.second)
            std::cout << student.first << " - " << grade.first << " - " << grade.second << std::endl;
    }

    return 0;
}