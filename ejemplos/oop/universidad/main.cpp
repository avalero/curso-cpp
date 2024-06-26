#include <iostream>
#include <vector>
#include <memory>
#include "student.h"
#include "teacher.h"
#include "course.h"
#include "fstream"

using namespace std;

vector<shared_ptr<Student>> students;
vector<shared_ptr<Teacher>> teachers;
vector<shared_ptr<Course>> courses;

void saveToFile(string fileName, vector<shared_ptr<Student>> students, vector<shared_ptr<Teacher>> teachers, vector<shared_ptr<Course>> courses)
{
  fstream file;
  file.open(fileName, ios::out);
  if (file.is_open())
  {
    for (auto student : students)
      file << "(s " + student->getName() + ")\n";
    for (auto teacher : teachers)
      file << "(t " + teacher->getName() + ")\n";

    for (auto course : courses)
    {
      file << "(c " + course->getName() + ")\n";

      for (auto student : course->getStudents())
      {
        file << "(cs " + course->getName() + " " + student->getName() + ")\n";
      }
      if (auto teacher = course->getTeacher())
      {
        file << "(ct " + course->getName() + " " + teacher->getName() + ")\n";
      }
    }

    file.close();
  }
  else
  {
    cout << "Error opening file" << endl;
  }
}

void loadFromFile(string fileName, vector<shared_ptr<Student>> &students, vector<shared_ptr<Teacher>> &teachers, vector<shared_ptr<Course>> &courses)
{
  students.clear();
  teachers.clear();
  courses.clear();

  fstream file;
  file.open(fileName, ios::in);
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      // add studente
      if (line.starts_with("(s "))
      {
        string name = line.substr(3, line.size() - 4);
        students.push_back(make_shared<Student>(Student(name)));
      }
      // add teacher
      else if (line.starts_with("(t "))
      {
        string name = line.substr(3, line.size() - 4);
        teachers.push_back(make_shared<Teacher>(name));
      }
      // add course
      else if (line.starts_with("(c "))
      {
        string name = line.substr(3, line.size() - 4);
        courses.push_back(make_shared<Course>(name));
      }
      // add student to course
      else if (line.starts_with("(cs "))
      {
        string courseName = line.substr(4, line.find_last_of(' ') - 4);
        string studentName = line.substr(line.find_last_of(' ') + 1, line.size() - line.find_last_of(' ') - 2);
        for (auto course : courses)
        {
          if (course->getName() == courseName)
          {
            for (auto student : students)
            {
              if (student->getName() == studentName)
              {
                course->addStudent(student);
              }
            }
          }
        }
      }
      // add teacher to course
      else if (line.starts_with("(ct "))
      {
        string courseName = line.substr(4, line.find_last_of(' ') - 4);
        string teacherName = line.substr(line.find_last_of(' ') + 1, line.size() - line.find_last_of(' ') - 2);
        for (auto course : courses)
        {
          if (course->getName() == courseName)
          {
            for (auto teacher : teachers)
            {
              if (teacher->getName() == teacherName)
              {
                course->setTeacher(teacher);
              }
            }
          }
        }
      }
    }
    file.close();
  }
  else
  {
    cout << "Error opening file" << endl;
  }
}

void createStudent()
{
  string name;
  cout << "Enter student name: ";
  getline(cin, name);
  students.push_back(make_shared<Student>(Student(name)));
  cout << "Student created successfully.\n";
}

void createTeacher()
{
  string name;
  cout << "Enter teacher name: ";
  getline(cin, name);
  teachers.push_back(make_shared<Teacher>(name));
  cout << "Teacher created successfully.\n";
}

void createCourse()
{
  string title;
  cout << "Enter course title: ";
  getline(cin, title);
  courses.push_back(make_shared<Course>(title));
  cout << "Course created successfully.\n";
}

void setTeacherToCourse()
{
  int teacherIndex, courseIndex;
  cout << "Enter teacher index: ";
  cin >> teacherIndex;
  cout << "Enter course index: ";
  cin >> courseIndex;
  cin.ignore();

  if (teacherIndex >= teachers.size() || courseIndex >= courses.size())
  {
    cout << "Invalid teacher or course index.\n";
    return;
  }

  courses[courseIndex]->setTeacher(teachers[teacherIndex]);
  cout << "Teacher set to course successfully.\n";
}

void addStudentToCourse()
{
  int studentIndex, courseIndex;
  cout << "Enter student index: ";
  cin >> studentIndex;
  cout << "Enter course index: ";
  cin >> courseIndex;
  cin.ignore();

  if (studentIndex >= students.size() || courseIndex >= courses.size())
  {
    cout << "Invalid student or course index.\n";
    return;
  }

  courses[courseIndex]->addStudent(students[studentIndex]);
  cout << "Student added to course successfully.\n";
}

void addCourseToStudent()
{
  int studentIndex, courseIndex;
  cout << "Enter student index: ";
  cin >> studentIndex;
  cout << "Enter course index: ";
  cin >> courseIndex;
  cin.ignore();
  if (studentIndex >= students.size() || courseIndex >= courses.size())
  {
    cout << "Invalid student or course index.\n";
    return;
  }
  students[studentIndex]->addCourse(courses[courseIndex]);
  cout << "Course added to student successfully.\n";
}

void addCourseToTeacher()
{
  int teacherIndex, courseIndex;
  cout << "Enter teacher index: ";
  cin >> teacherIndex;
  cout << "Enter course index: ";
  cin >> courseIndex;
  cin.ignore();

  if (teacherIndex >= teachers.size() || courseIndex >= courses.size())
  {
    cout << "Invalid teacher or course index.\n";
    return;
  }

  teachers[teacherIndex]->addCourse(courses[courseIndex]);
  cout << "Course added to teacher successfully.\n";
}

void listStudents()
{
  for (int i = 0; i < students.size(); i++)
  {
    cout << i << ". " << *(students[i]) << endl;
  }
}

void listTeachers()
{
  for (int i = 0; i < teachers.size(); i++)
  {
    cout << i << ". " << *(teachers[i]) << endl;
  }
}

void listCourses()
{
  for (int i = 0; i < courses.size(); i++)
  {
    cout << i << ". " << *(courses[i]) << endl;
  }
}

int main()
{
  int choice = 0;

  while (true)
  {
    cout << "\nMenu:\n";
    cout << "1. Create Student\n";
    cout << "2. Create Teacher\n";
    cout << "3. Create Course\n";
    cout << "4. Set Teacher to Course\n";
    cout << "5. Add Student to Course\n";
    cout << "6. Add Course to Student\n";
    cout << "7. Add Course to Teacher\n";
    cout << "8. List all Students\n";
    cout << "9. List all Courses\n";
    cout << "10. List all Teachers\n";
    cout << "11. Save to file\n";
    cout << "12. Load from file\n";
    cout << "13. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
      createStudent();
      break;
    case 2:
      createTeacher();
      break;
    case 3:
      createCourse();
      break;
    case 4:
      setTeacherToCourse();
      break;
    case 5:
      addStudentToCourse();
      break;
    case 6:
      addCourseToStudent();
      break;
    case 7:
      addCourseToTeacher();
      break;
    case 8:
      listStudents();
      break;
    case 9:
      listCourses();
      break;
    case 10:
      listTeachers();
      break;
    case 11:
    {
      string fileName;
      cout << "Enter file name: ";
      getline(cin, fileName);
      saveToFile(fileName, students, teachers, courses);
      break;
    }
    case 12:
    {
      string loadFileName;
      cout << "Enter file name: ";
      getline(cin, loadFileName);
      loadFromFile(loadFileName, students, teachers, courses);
      break;
    }
    case 13:
      return 0;
    default:
      cout << "Invalid choice, please try again.\n";
    }
    // wait for input to continue
    cout << "Press enter to continue...";
    cin.get();
  }
}
