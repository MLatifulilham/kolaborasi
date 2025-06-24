// Pembukaan
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Course
{
    string package_name;
    string type;
    int meetings;
    int session_duration;
    double price_per_meeting;
    int registered_students;
    string payment_status;
};

vector<Course> courses;

// Fungsi-fungsi
void addCourse();
void displayCourses();
void registerStudent();
void updatePaymentStatus();
void editCourse();
void deleteCourse();
void displayCourseSummary();
double calculateTotal();
