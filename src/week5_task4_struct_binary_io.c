// week5_task4_struct_binary_io.c   (BONUS)
// Name: jishan  Surname: Kaliparamban didesh  Student ID: 251ADB016
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls
// them directly)
int save_student_binary(const Student* s,
                        const char* filename);  // 0 on success, -1 on error
int load_student_binary(const char* filename,
                        Student* out);  // 0 on success, -1 on error
long file_size(const char* filename);   // bytes, -1 on error

int main(void) {
  Student s1 = {
      0};  // zero-initialised so unused name bytes are not garbage on disk
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* bin_file = "student.bin";
  const char* txt_file = "student.txt";

  printf("Saving student in binary format...\n");

  if (save_student_binary(&s1, bin_file) != 0) {
    perror("Failed to save student to binary file");
    return EXIT_FAILURE;
  }

  FILE* txt_fp = fopen(txt_file, "w");
  if (txt_fp == NULL) {
    perror("Failed to open text file");
    return EXIT_FAILURE;
  }

  fprintf(txt_fp, "%s,%d,%.2f\n", s1.name, s1.age, s1.gpa);
  fclose(txt_fp);

  printf("Loading student from binary file...\n");
  if (load_student_binary(bin_file, &loaded) != 0) {
    perror("Failed to load student from binary file");
    return EXIT_FAILURE;
  }

  printf("Loaded student: Name: %s, Age: %d, GPA: %.2f\n", loaded.name,
         loaded.age, loaded.gpa);
  printf("Text file saved as: %ld bytes\n", file_size(txt_file));
  printf("Binary file saved as: %ld bytes\n", file_size(bin_file));

  return EXIT_SUCCESS;
}

// TODO: open with "wb", fwrite(s, sizeof(Student), 1, fp) must return 1, close,
// return 0/-1
int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) {
    return -1;
  }

  size_t written = fwrite(s, sizeof(Student), 1, fp);
  fclose(fp);

  if (written != 1) {
    return -1;
  }

  return 0;
}

// TODO: open with "rb", fread(out, sizeof(Student), 1, fp) must return 1,
// close, return 0/-1
int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    return -1;
  }

  size_t read = fread(out, sizeof(Student), 1, fp);
  fclose(fp);

  if (read != 1) {
    return -1;
  }

  return 0;
}

// TODO: open with "rb", fseek(fp, 0, SEEK_END), size = ftell(fp), close, return
// size (-1 on error)
long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");

  if (fp == NULL) {
    return -1;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
  }

  long size = ftell(fp);
  fclose(fp);
  return size;
}
