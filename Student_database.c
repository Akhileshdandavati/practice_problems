#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50

typedef struct Student
{
    int id;
    char name[MAX_NAME_LEN];
    char gender;
    int age;
    float gpa;
    float math_score;
    float physics_score;
    float chemistry_score;
    float average_score;
    char academic_score[20];
} Student;

struct Student students[MAX_STUDENTS];
int num_students = 0;
int load_students();
void save_students();
void add_student(int);
void update_student();
void delete_student(); //
void search_student(); //
void sort_by_gpa();
void sort_by_name();
void display_students();
void print_student(struct Student *student);

int main()
{
    int choice;
    // load_students();
    int last_id = load_students();
    do
    {
        printf("\nStudent Management Program\n");
        printf("1. Add student\n");
        printf("2. Update student information by ID\n");
        printf("3. Delete student by ID\n");
        printf("4. Search students by name\n");
        printf("5. Sort students by GPA\n");
        printf("6. Sort students by name\n");
        printf("7. Display students\n");
        printf("8. Save students to file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("Exiting program...\n");
            break;
        case 1:
            add_student(last_id);
            break;
        case 2:
            update_student();
            break;
        case 3:
            delete_student();
            break;
        case 4:
            search_student();
            break;
        case 5:
            sort_by_gpa();
            break;
        case 6:
            sort_by_name();
            break;
        case 7:
            display_students();
            break;
        case 8:
            save_students();
            break;
        case 9:
        default:
            printf("Invalid choice, try again.\n");
            break;
        }
    } while (choice != 0);
    return 0;
}

int load_students()
{
    FILE *fp = fopen("/home/user/MY_git/practice_problems/program.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%[^,],%c,%d,%f,%f,%f,%f,%s\n",
                      &students[num_students].id, students[num_students].name, &students[num_students].gender,
                      &students[num_students].age, &students[num_students].math_score,
                      &students[num_students].physics_score, &students[num_students].chemistry_score,
                      &students[num_students].average_score, students[num_students].academic_score) == 9)
        {
            num_students++;
            // last_id = students[num_students].id;
            if (num_students >= MAX_STUDENTS)
            {
                printf("Maximum number of students reached, can't load more.\n");
                break;
            }
        }
        fclose(fp);
        printf("%d students loaded from file.\n", num_students);
    }
    else
    {
        printf("File not found, starting with empty list of students.\n");
    }
    printf("last %d \n", num_students);
    return num_students;
}

void save_students()
{
    FILE *fp = fopen("/home/user/MY_git/practice_problems/program.txt", "w");
    if (fp != NULL)
    {
        for (int i = 0; i < num_students; i++)
        {
            fprintf(fp, "%d,%s,%c,%d,%.2f,%.2f,%.2f,%.2f,%s\n",
                    students[i].id, students[i].name, students[i].gender,
                    students[i].age, students[i].math_score, students[i].physics_score,
                    students[i].chemistry_score, students[i].average_score,
                    students[i].academic_score);
        }
        fclose(fp);
        printf("%d students saved to file.\n", num_students);
    }
    else
    {
        printf("Error saving students to file.\n");
    }
}

void add_student(int last_id)
{
    char name[MAX_NAME_LEN];
    char gender;
    int age;
    float math_score, physics_score, chemistry_score;

    printf("Enter student name: ");
    scanf("%s", name);

    printf("Enter student gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter student age: ");
    scanf("%d", &age);

    printf("Enter math score: ");
    scanf("%f", &math_score);

    printf("Enter physics score: ");
    scanf("%f", &physics_score);

    printf("Enter chemistry score: ");
    scanf("%f", &chemistry_score);

    float average_score = (math_score + physics_score + chemistry_score) / 3;
    char academic_score[20];
    if (average_score >= 8)
    {
        strcpy(academic_score, "Excellent");
    }
    else if (average_score >= 6.5)
    {
        strcpy(academic_score, "Likelihood");
    }
    else if (average_score >= 5)
    {
        strcpy(academic_score, "Average");
    }
    else
    {
        strcpy(academic_score, "Mild");
    }

    struct Student new_student;
    strcpy(new_student.name, name);
    new_student.gender = gender;
    new_student.age = age;
    new_student.math_score = math_score;
    new_student.physics_score = physics_score;
    new_student.chemistry_score = chemistry_score;
    new_student.average_score = average_score;
    strcpy(new_student.academic_score, academic_score);

    new_student.id = ++last_id;
    students[num_students++] = new_student;

    printf("Student added with ID %d.\n", new_student.id);
}

void update_student()
{
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    int found_index = -1;
    for (int i = 0; i < num_students; i++)
    {
        if (students[i].id == id)
        {
            found_index = i;
            break;
        }
    }

    if (found_index == -1)
    {
        printf("No student with ID %d found.\n", id);
        return;
    }

    char name[MAX_NAME_LEN];
    char gender;
    int age;
    float math_score, physics_score, chemistry_score;

    printf("Enter new student name: ");
    scanf("%s", name);

    printf("Enter new student gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter new student age: ");
    scanf("%d", &age);

    printf("Enter new math score: ");
    scanf("%f", &math_score);

    printf("Enter new physics score: ");
    scanf("%f", &physics_score);

    printf("Enter new chemistry score: ");
    scanf("%f", &chemistry_score);

    float average_score = (math_score + physics_score + chemistry_score) / 3;
    char academic_score[MAX_NAME_LEN];
    if (average_score >= 8)
    {
        strcpy(academic_score, "Excellent");
    }
    else if (average_score >= 6.5)
    {
        strcpy(academic_score, "Likelihood");
    }
    else if (average_score >= 5)
    {
        strcpy(academic_score, "Average");
    }
    else
    {
        strcpy(academic_score, "Mild");
    }
    // try useing pointer
    struct Student updated_student = students[found_index];
    strcpy(updated_student.name, name);
    updated_student.gender = gender;
    updated_student.age = age;
    updated_student.math_score = math_score;
    updated_student.physics_score = physics_score;
    updated_student.chemistry_score = chemistry_score;
    updated_student.average_score = average_score;
    strcpy(updated_student.academic_score, academic_score);

    students[found_index] = updated_student;
    printf("Student with ID %d updated.\n", id);
}

void delete_student()
{
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    int found_index = -1;
    for (int i = 0; i < num_students; i++)
    {
        if (students[i].id == id)
        {
            found_index = i;
            break;
        }
    }

    if (found_index == -1)
    {
        printf("No student with ID %d found.\n", id);
        return;
    }
    for (int i = found_index; i < num_students - 1; i++)
    {
        students[i] = students[i + 1];
    }

    num_students--;
    printf("Student with ID %d deleted.\n", id);
}

void search_student()
{
    char name[MAX_NAME_LEN];
    printf("\nSearching for Student\n");
    printf("---------------------\n");
    printf("Enter name of student to search: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("\nID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Gender: %c\n", students[i].gender);
            printf("Age: %d\n", students[i].age);
            printf("Math score: %.2f\n", students[i].math_score);
            printf("Physics score: %.2f\n", students[i].physics_score);
            printf("Chemistry score: %.2f\n", students[i].chemistry_score);
            printf("Average score: %.2f\n", students[i].average_score);
            printf("Academic score: %s\n", students[i].academic_score);
            printf("---------------------\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nStudent with name %s not found.\n", name);
    }
}

void sort_by_gpa()
{
    printf("\nSorting by GPA\n");
    printf("\n");
    for (int i = 0; i < num_students - 1; i++)
    {
        for (int j = 0; j < num_students - i - 1; j++)
        {
            if (students[j].average_score < students[j + 1].average_score)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < num_students; i++)
    {
        printf("\nID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Average score: %.2f\n", students[i].average_score);
        printf("\n");
    }
    printf("\nSorted successfully.\n");
}

void sort_by_name()
{
    printf("\nSorting by Name\n");
    printf("-----------------\n");

    for (int i = 0; i < num_students - 1; i++)
    {
        for (int j = 0; j < num_students - i - 1; j++)
        {
            if (strcmp(students[j].name, students[j + 1].name) > 0)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < num_students; i++)
    {
        printf("\nID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
    }
    printf("\nSorted successfully.\n");
}

void display_students()
{
    printf("\nDisplaying Students\n");
    printf("\n");

    for (int i = 0; i < num_students; i++)
    {
        printf("\nID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Gender: %c\n", students[i].gender);
        printf("Age: %d\n", students[i].age);
        printf("Math score: %.2f\n", students[i].math_score);
        printf("Physics score: %.2f\n", students[i].physics_score);
        printf("Chemistry score: %.2f\n", students[i].chemistry_score);
        printf("Average score: %.2f\n", students[i].average_score);
        printf("Academic score: %s\n", students[i].academic_score);
        printf("\n");
    }

    printf("\nDisplayed all students successfully.\n");
}
