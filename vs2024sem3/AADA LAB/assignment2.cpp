//Analysis and Design Of Algorithm

// List of students 
// marks out of hundred in arts , science - list is sorted wrt roll no.
// array stores list - 9
//You are forbidden to use any record or any of its components on the right side of assign
//you are allowed to use O(n) additional space in your functions, where n denotes the nu of stud
// part 1:
//specified subject provided that the marks are in the range [a,b]. The printing should be in the sorted
//order of the marks (higher to lower).
// Handle queries that filter and print student roll numbers and marks based on a subject (Arts/Science) and a marks range [a,b].
// Output should be sorted by marks in descending order.
// Aim for efficient query handling with a time complexity of O(t + log n).


//part 2:
//Determine whether a student joins the BA or BS program based on their ranks in Arts and Science.
// Print decisions (BA/BS/Student's Choice) in roll number order.
// Calculate the count of students for each decision in O(n) time.


#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char mis[10];
    int artsMarks;
    int scienceMarks;
    int rankArts;
    int rankScience;
} Student;

void calculateRanks(Student students[], int n, int isArts) {
    for (int i = 0; i < n; i++) {
        int currentMarks = isArts ? students[i].artsMarks : students[i].scienceMarks;
        int rank = 1;

        for (int j = 0; j < n; j++) {
            int compareMarks = isArts ? students[j].artsMarks : students[j].scienceMarks;
            if (compareMarks > currentMarks) {
                rank++;
            }
        }

        if (isArts) {
            students[i].rankArts = rank;
        } else {
            students[i].rankScience = rank;
        }
    }
}

void intervalSearch(Student students[], int n, int isArts, int a, int b) {
    printf("+++ %s: a = %d, b = %d\n--- List of students:\n", isArts ? "Arts" : "Science", a, b);
    printf("\n");
    for (int i = 0; i < n; i++) {
        int marks = isArts ? students[i].artsMarks : students[i].scienceMarks;
        if (marks >= a && marks <= b) {
            printf("%s, %d, %d\n", students[i].mis, students[i].artsMarks, students[i].scienceMarks);
        }
    }
}

void makeDecisions(Student students[], int n) {
    int baCount = 0, bsCount = 0, choiceCount = 0;

    printf(" Rank comparisons\n");
    for (int i = 0; i < n; i++) {
        printf("%s, %d, %d, Arts rank = %d, Science rank = %d, Decision: ", 
               students[i].mis, students[i].artsMarks, students[i].scienceMarks, 
               students[i].rankArts, students[i].rankScience);

        if (students[i].rankArts < students[i].rankScience) {
            printf("BA\n");
            baCount++;
        } else if (students[i].rankArts > students[i].rankScience) {
            printf("BS\n");
            bsCount++;
        } else {
            printf("SC\n");
            choiceCount++;
        }
    }

    printf("Number of BA = %d\nNumber of BS = %d\nNumber of SC = %d\n", baCount, bsCount, choiceCount);
}

int main() {
    int n;
    Student students[MAX_STUDENTS];

    // Input number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Input student details
    printf(" Initial list (sorted by roll numbers): roll no , marks in arts , marks in science :\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", students[i].mis, &students[i].artsMarks, &students[i].scienceMarks);
    }

    for (int i = 0; i < n; i++) {
        printf("%s, %d, %d\n", students[i].mis, students[i].artsMarks, students[i].scienceMarks);
    }

    // Perform interval search queries
    intervalSearch(students, n, 1, 53, 65); // Arts
    intervalSearch(students, n, 1, 13, 14); // Arts
    intervalSearch(students, n, 0, 69, 74); // Science
    intervalSearch(students, n, 0, 26, 41); // Science

    // Calculate ranks
    calculateRanks(students, n, 1);  // Calculate Arts ranks
    calculateRanks(students, n, 0);  // Calculate Science ranks

    // Make decisions based on ranks
    makeDecisions(students, n);

    return 0;
}
