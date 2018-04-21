#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 32

typedef struct {
    int id;
    char* name;
    int mark;
} student;

student* get_students(int n) {
    student* students = (student*) malloc(sizeof(student) * n);
    int i;
    for (i = 0; i < n; i++) {
        students[i].name = (char*) malloc(sizeof(char) * NAME_LENGTH);
        scanf("%d %s %d", &students[i].id, students[i].name, &students[i].mark);
    }
    return students;
}

void print_students_with_mark(student* students, int n, int mark) {
    int i;
    for (i = 0; i < n; i++) {
        if (students[i].mark == mark) {
            printf("%d %s %d \n", students[i].id, students[i].name, students[i].mark);
        }
    }
}

int main() {
    printf("Enter the number of students:\n");
    int n;
    scanf("%d", &n);
    printf("Enter info about %d students: id, name and mark\n", n);
    student* students = get_students(n);
    printf("Here is a list of students, sorted by mark:\n");
    int i;
    for (i = 2; i < 6; i++) {
        print_students_with_mark(students, n, i);
    }
    return 0;
}
