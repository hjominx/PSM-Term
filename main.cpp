/*
 * Member Management System
 * This program manages member data, including attributes like tag, date, fee payment status,
 * name, age, organizational affiliation, and job. The data is handled using both arrays and linked lists.
 *
 * Key Features:
 * P1 (김현태). Data Sorting and Saving: Sorts member data by age in ascending order and saves the sorted data to a file.
 * P2 (김현태). Linked List Creation: Creates a linked list from the sorted data for further manipulation and display.
 * P3 (배혜림). Fee Payment Search: Searches for members who have paid their fees, using both array and linked list data structures.
 * P4 (최경민). Organization Affiliation Search: Searches for members affiliated with a specific institution (Gachon University), again in both array and linked list formats.
 * P5 (김현태). Member Cancellation: Cancels the registration of a specific member ('Choi') and reflects this change in both the array and linked list.
 * P6 (이우정). Late Registration: Handles late registration by adding a new member ('Paik') to both the array and linked list, maintaining the sorted order.
 * P1~P6 (황정민). Modification of all other codes and functions, production of submission files. Project Management: Oversees the entire project, including integration, testing, and finalization.And finalized the raw codes sent by the team members.
 *
 *
 * File Path (registraion_data.txt) : /Users/arthurk./Desktop/registraion_data.txt
 *
 * The program uses file I/O operations and dynamic memory management to implement these functionalities.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 데이터 구조체 정의
struct regi {
    int tag;
    char date[11];
    char fee_paid[4];
    char name[50];
    int age;
    char orga[50];
    char job[20];
};

// 연결 리스트 노드 구조체 정의
struct NODE {
    int tag;
    char* date;
    char* fee;
    char* name;
    int age;
    char* orga;
    char* job;
    struct NODE* next;
};

// 함수 선언
int Insertdata(struct NODE* head, struct regi data);
void printlist(struct NODE* head);
void sortData(struct regi data[], int size);
void writeDataToFile(struct regi data[], int dataSize, const char* filename);
struct NODE* createLinkedList(struct regi data[], int size);
void printLinkedListToFile(struct NODE* head, const char* filename);
void searchFeePaid(struct regi data[], int size);
void searchFeePaidLinkedList(struct NODE* head);
void searchGachonUniversityInArray(struct regi data[], int size);
void searchGachonUniversityInLinkedList(struct NODE* head);
void cancelChoi(struct regi data[], int* size);
void cancelChoiLinkedList(struct NODE** head);
void registerLatePaik(struct regi data[], int* size, struct NODE** head);

// 데이터 삽입
int Insertdata(struct NODE* head, struct regi data) {
    struct NODE* p = head, * prev = NULL;
    struct NODE* new_node = (struct NODE*)malloc(sizeof(struct NODE));

    if (!new_node) {
        perror("메모리 할당 실패");
        return -1;
    }
// 데이터 삽입
    new_node->tag = data.tag;
    new_node->date = strdup(data.date);
    new_node->fee = strdup(data.fee_paid);
    new_node->name = strdup(data.name);
    new_node->age = data.age;
    new_node->orga = strdup(data.orga);
    new_node->job = strdup(data.job);
    new_node->next = NULL;

    while (p->next) {
        prev = p;
        p = p->next;
    }

    p->next = new_node;
    return 0;
}

// Linked List 출력
void printlist(struct NODE* head) {
    struct NODE* p = head->next;
    while (p) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee, p->name, p->age, p->orga, p->job);
        p = p->next;
    }
}

// 데이터 정렬
void sortData(struct regi data[], int size) {
    struct regi temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (data[i].age > data[j].age) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

// P1: 데이터를 나이 오름차순으로 정렬하고 파일에 저장
void saveSortedDataToFile(struct regi data[], int size) {
    sortData(data, size); // 데이터를 나이 오름차순으로 정렬

    // 파일에 정렬된 데이터 저장
    FILE* outputFile = fopen("/Users/arthurk./Desktop/P1.txt ", "w");
    if (outputFile == NULL) {
        perror("파일 쓰기 오류");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(outputFile, "%d/%s/%s/%s/%d/%s/%s\n",
                data[i].tag, data[i].date, data[i].fee_paid,
                data[i].name, data[i].age, data[i].orga, data[i].job);
    }

    fclose(outputFile);
}

// P2: 정렬된 데이터를 사용하여 연결 리스트 생성
struct NODE* createLinkedList(struct regi data[], int size) {
    struct NODE* head = (struct NODE*)malloc(sizeof(struct NODE)); // 연결 리스트의 헤드 노드 동적 할당

    if (head == NULL) {
        perror("메모리 할당 실패");
        return NULL;
    }

    head->next = NULL; // 헤드 노드 초기화

    // 데이터를 연결 리스트에 추가
    for (int i = 0; i < size; i++) {
        Insertdata(head, data[i]);
    }

    return head;
}

// P3-1: 수수료 지불 여부로 검색 (배열)
void searchFeePaid(struct regi data[], int size) {
    printf("P3-1 / 배열에서 수수료 지불한 회원:\n");
    for (int i = 0; i < size; i++) {
        if (strcmp(data[i].fee_paid, "yes") == 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n",
                   data[i].tag, data[i].date, data[i].fee_paid,
                   data[i].name, data[i].age, data[i].orga, data[i].job);
        }
    }
}

// P3-2: 수수료 지불 여부로 검색 (연결 리스트)
void searchFeePaidLinkedList(struct NODE* head) {
    printf("P3-2 / 연결 리스트에서 수수료 지불한 회원:\n");
    struct NODE* p = head->next;
    while (p != NULL) {
        if (p->fee != NULL && strcmp(p->fee, "yes") == 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n",
                   p->tag, p->date, p->fee,
                   p->name, p->age, p->orga, p->job);
        }
        p = p->next;
    }
}

// P4-1: 가천대학교 소속 검색 (배열)
void searchGachonUniversityInArray(struct regi data[], int size) {
    printf(" P4-1 / 배열에서 가천대학교 소속 회원:\n");
    for (int i = 0; i < size; i++) {
        if (strcmp(data[i].orga, "Gachon University") == 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n",
                   data[i].tag, data[i].date, data[i].fee_paid,
                   data[i].name, data[i].age, data[i].orga, data[i].job);
        }
    }
}

// P4-2: 가천대학교 소속 검색 (연결 리스트)
void searchGachonUniversityInLinkedList(struct NODE* head) {
    printf("P4-2 / 연결 리스트에서 가천대학교 소속 회원:\n");
    struct NODE* p = head->next;
    while (p != NULL) {
        if (p->orga != NULL && strcmp(p->orga, "Gachon University") == 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n",
                   p->tag, p->date, p->fee,
                   p->name, p->age, p->orga, p->job);
        }
        p = p->next;
    }
}

// P5-1: "Choi"의 등록 취소 (배열)
void cancelChoi(struct regi data[], int* size) {
    printf("P5-1 / 배열에서 Choi의 등록을 취소합니다:\n");
    int i = 0;
    while (i < *size) {
        if (strcmp(data[i].name, "Choi") == 0) {
            // 데이터를 빈 값으로 초기화
            data[i].tag = 0;
            strcpy(data[i].date, "");
            strcpy(data[i].fee_paid, "");
            strcpy(data[i].name, "");
            data[i].age = 0;
            strcpy(data[i].orga, "");
            strcpy(data[i].job, "");

            (*size)--;
        } else {
            i++;
        }
    }
}

// P5-2: "Choi"의 등록 취소 (연결 리스트)
void cancelChoiLinkedList(struct NODE** head) {
    printf("P5-2 / 연결 리스트에서 Choi의 등록을 취소합니다:\n");
    struct NODE* p = (*head)->next;
    struct NODE* prev = *head;
    while (p != NULL) {
        if (p->name != NULL && strcmp(p->name, "Choi") == 0) {
            prev->next = p->next;
            free(p->date);
            free(p->fee);
            free(p->name);
            free(p->orga);
            free(p->job);
            free(p);
            p = prev->next;
        } else {
            prev = p;
            p = p->next;
        }
    }
}



// P6-1: "Paik"의 지각 등록 (배열)
void registerLatePaik(struct regi data[], int* size, struct NODE** head) {
    struct regi newMember = {35, "2023-08-26", "yes", "Paik", 40, "Gachon University", "Student"};

    printf("Paik을 배열에 지각으로 등록합니다:\n");
    if (*size < 31) {
        // "Choi"가 삭제되기 전의 나이 순으로 정렬된 배열에서 Paik의 위치를 찾습니다.
        int insertIndex = 0;
        while (insertIndex < *size && data[insertIndex].age <= newMember.age) {
            insertIndex++;
        }

        // Paik을 배열에 추가하고 이동한 데이터를 뒤로 밀어냅니다.
        for (int i = *size; i > insertIndex; i--) {
            data[i] = data[i - 1];
        }

        data[insertIndex] = newMember;
        (*size)++;
    }

    printf("Paik을 연결 리스트에 지각으로 등록합니다:\n");
    // "Paik"의 데이터를 연결 리스트에 추가
    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode != NULL) {
        newNode->tag = newMember.tag;
        newNode->date = strdup(newMember.date);
        newNode->fee = strdup(newMember.fee_paid);
        newNode->name = strdup(newMember.name);
        newNode->age = newMember.age;
        newNode->orga = strdup(newMember.orga);
        newNode->job = strdup(newMember.job);
        newNode->next = NULL;

        // 연결 리스트가 비어있을 때
        if (*head == NULL) {
            *head = newNode;
        } else {
            struct NODE* p = *head, * prev = NULL;
            while (p != NULL && p->age < newMember.age) {
                prev = p;
                p = p->next;
            }
            if (prev == NULL) {
                newNode->next = *head;
                *head = newNode;
            } else {
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
    }
}

// P6-2: "Paik"의 지각 등록 (연결 리스트)
void registerLatePaikLinkedList(struct NODE** head) {
    struct regi newMember = {35, "2023-08-26", "yes", "Paik", 40, "Gachon University", "Student"};

    printf("연결 리스트에서 Paik을 지각으로 등록합니다:\n");
    // "Paik"의 데이터를 연결 리스트에 추가
    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode != NULL) {
        newNode->tag = newMember.tag;
        newNode->date = strdup(newMember.date);
        newNode->fee = strdup(newMember.fee_paid);
        newNode->name = strdup(newMember.name);
        newNode->age = newMember.age;
        newNode->orga = strdup(newMember.orga);
        newNode->job = strdup(newMember.job);
        newNode->next = NULL;

        // 연결 리스트가 비어있을 때
        if (*head == NULL) {
            *head = newNode;
        } else {
            struct NODE* p = *head, * prev = NULL;
            while (p != NULL && p->age < newMember.age) {
                prev = p;
                p = p->next;
            }
            if (prev == NULL) {
                newNode->next = *head;
                *head = newNode;
            } else {
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
    }
}

void writeDataToFile(struct regi data[], int dataSize, const char* filename) {
    // 파일을 열고 데이터를 파일에 쓰는 코드를 작성하세요.
    // 이 함수는 data 배열의 내용을 지정된 파일에 쓰는 역할
}
void printLinkedListToFile(struct NODE* head, const char* filename) {
    // 파일을 열고 연결 리스트를 파일에 쓰는 코드를 작성하세요.
    // 이 함수는 연결 리스트의 내용을 지정된 파일에 쓰는 역할
}


int main(void) {
    struct regi data[31];
    int dataSize = 0;

    sortData(data, dataSize);

    printf("데이터 정렬 및 연결 리스트 생성 완료.\n");

    struct NODE* head = (struct NODE*)malloc(sizeof(struct NODE));
    if (head == NULL) {
        perror("메모리 할당 실패");
        return -1;
    }

    head->next = NULL;

    char file_path[100];
    printf("파일 경로를 입력하세요: ");
    scanf("%s", file_path);

    FILE* myFile = fopen(file_path, "r");
    if (myFile == NULL) {
        printf("파일 열기 오류.\n");
        return -1;
    }

    while (fscanf(myFile, "%d/%10[^/]/%3[^/]/%49[^/]/%d/%49[^/]/%19s",
                  &data[dataSize].tag, data[dataSize].date, data[dataSize].fee_paid,
                  data[dataSize].name, &data[dataSize].age, data[dataSize].orga, data[dataSize].job) == 7) {
        dataSize++;
    }
    fclose(myFile);

    sortData(data, dataSize);
    for (int j = 0; j < dataSize; j++) {
        Insertdata(head, data[j]);
    }
    printf("데이터 정렬 및 연결 리스트 생성 완료.\n");

    printf("--- P1: 배열 데이터를 파일에 쓰기 (P1.txt) ---\n");
    writeDataToFile(data, dataSize, "P1.txt");

// P2: 정렬된 데이터를 사용하여 연결 리스트 생성 및 출력
    struct NODE* sortedLinkedList = createLinkedList(data, dataSize); // 정렬된 데이터를 사용하여 연결 리스트 생성

    printf("\n--- P2: 연결 리스트 출력 ---\n");
    printlist(sortedLinkedList); // 연결 리스트의 내용을 출력

// P2: 연결 리스트를 이미지로 출력 (P2.png)
    printLinkedListToFile(sortedLinkedList, "P2.png"); // 연결 리스트의 내용을 이미지 파일로 출력


    printf("\n--- P3: 수수료 지불 여부로 검색 ---\n");
    searchFeePaid(data, dataSize);
    searchFeePaidLinkedList(head);

    printf("\n--- P4: 가천대학교 소속 검색 ---\n");
    searchGachonUniversityInArray(data, dataSize);
    searchGachonUniversityInLinkedList(head);

    printf("--- P5: Choi의 등록 취소 (배열) ---\n");
    cancelChoi(data, &dataSize); // Choi의 등록 취소

// "Choi"의 등록 취소 결과를 출력
    for (int i = 0; i < dataSize; i++) {
        if (data[i].tag != 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n",
                   data[i].tag, data[i].date, data[i].fee_paid,
                   data[i].name, data[i].age, data[i].orga, data[i].job);
        }
    }
    printf("--- P5: Choi의 등록 취소 (연결 리스트) ---\n");
    cancelChoiLinkedList(&head); // Choi의 등록 취소

// 연결 리스트의 내용을 출력
    printlist(head);



    printf("\n--- P6: Paik의 지각 등록 ---\n");
    struct regi paik = {35, "2023-08-26", "yes", "Paik", 40, "Gachon University", "Student"};
    registerLatePaik(data, &dataSize, &head); // 배열과 연결 리스트에 Paik 등록

// 배열의 최종 상태 출력
    printf("\n--- 최종 배열 데이터 (P6-1 완료) ---\n");
    for (int j = 0; j < dataSize; j++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n",
               data[j].tag, data[j].date, data[j].fee_paid,
               data[j].name, data[j].age, data[j].orga, data[j].job);
    }

// 연결 리스트의 최종 상태 출력
    printf("\n--- 최종 연결 리스트 데이터 (P6-2 완료) ---\n");
    printlist(head);

// 메모리 해제
    struct NODE* current = head->next; // 'current' 변수 선언.
    while (current != NULL) {
        struct NODE* temp = current;
        current = current->next;
        free(temp->date);
        free(temp->fee);
        free(temp->name);
        free(temp->orga);
        free(temp->job);
        free(temp);
    }

    free(head); // head 노드의 메모리 해제.

    return 0;// 프로그램 종료
}