#include <string.h>
#include <stdio.h>

/**
 * BEE 2693
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 06/11/2024
 */

struct Student {
    char name[20];
    char region;
    int distance;
} typedef Student;

void swap(Student studentsArray[], int i, int j) {
    Student temp = studentsArray[i];
    studentsArray[i] = studentsArray[j];
    studentsArray[j] = temp;
}

void bubbleSort(Student studentsArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (
                (studentsArray[j].distance > studentsArray[j + 1].distance) ||
                (studentsArray[j].distance == studentsArray[j + 1].distance && studentsArray[j].region > studentsArray[j + 1].region) ||
                (studentsArray[j].distance == studentsArray[j + 1].distance && studentsArray[j].region == studentsArray[j + 1].region &&
                 strcmp(studentsArray[j].name, studentsArray[j + 1].name) > 0)
            ) {
                swap(studentsArray, j, j + 1);
            }
        }
    }
}

int main() {
    int studentsNumber;
    scanf("%d", &studentsNumber);

    Student students[studentsNumber];

    for (int i = 0; i < studentsNumber; i++) {
        Student student;

        scanf("%s %c %d", student.name, &student.region, &student.distance);

        students[i] = student;
    }

    bubbleSort(students, studentsNumber);

    for (int i = 0; i < studentsNumber; i++) {
        printf("%s\n", students[i].name);
    }

    return 0;
}