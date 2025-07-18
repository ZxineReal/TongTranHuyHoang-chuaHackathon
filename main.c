#include <ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Task{
    int id;
    char title[50];
    int priority;
    char deadline[50];
} Task;

typedef struct Node {
    Task task;
    struct Node* next;
} Node;

typedef struct DNode {
    Task task;
    struct Node* next;
    struct Node* prev;
} DNode;

Node* createNode(Task task) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Khong the cap phat bo nho dong!\n");
        return NULL;
    }
    newNode->task = task;
    newNode->next = NULL;
    return newNode;
}

int isDuplicate(Node* head, int id) {
    Node* current = head;
    while (current != NULL) {
        if (current->task.id == id) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node* createTask(Node* head, int id, char title[],int priority, char deadline[]) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Khong the cap phat bo nho dong!\n");
        return head;
    }
    node->task.id = id;
    strcpy(node->task.title, title);
    node->task.priority = priority;
    strcpy(node->task.deadline, deadline);
    node->next = NULL;

    if (head == NULL) {
        printf("Them nhiem vu thanh cong!\n");
        return node;
    }
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    printf("Them nhiem vu thanh cong!\n");
    return head;
}

void printTask(Node* head) {
    if (head == NULL) {
        printf("Danh sach nhiem vu rong!\n");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        printf("ID: %d \n", current->task.id);
        printf("Title: %s \n", current->task.title);
        printf("Priority: %d \n", current->task.priority);
        printf("Deadline: %s \n", current->task.deadline);
        printf("\n");
        current = current->next;
    }
    printf("\n");
}

Node* deleteTask(Node* head, int id) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong!\n");
        return NULL;
    }
    Node* current = head;
    Node* prev = NULL;

    if (current->task.id == id) {
        head = current->next;
        free(current);
        printf("Xoa khoa hoc thanh cong!\n");
        return head;
    }

    while (current != NULL && current->task.id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Khong tim thay khoa hoc!\n");
        return head;
    }
    prev->next = current->next;
    free(current);
    printf("Xoa khoa hoc thanh cong!\n");
    return head;
}

void updateTask(Node* head, int id) {
    Node* current = head;
    if (current == NULL) {
        printf("Danh sach khoa hoc rong!\n");
        return;
    }
    while (current != NULL) {
        if (current->task.id == id) {
            printf("Moi ban nhap tieu de nhiem vu moi:\n");
            getchar();
            fgets(current->task.title, sizeof(current->task.title), stdin);
            current->task.title[strcspn(current->task.title, "\n")] = '\0';

            printf("Moi ban nhap do uu tien moi:\n");
            scanf("%d", &current->task.priority);
            getchar();

            printf("Moi ban nhap thoi gian hoan thanh nhiem vu moi:\n");
            fgets(current->task.deadline, sizeof(current->task.deadline), stdin);
            current->task.deadline[strcspn(current->task.deadline, "\n")] = '\0';
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay nhiem vu!\n");
}


void findTask(Node* head, char key[]) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong!\n");
        return;
    }
    int flag = 0;
    Node* current = head;
    while (current != NULL) {
        if (strstr(current->task.title,key) != NULL) {
            printf("ID: %d\n", current->task.id);
            printf("Title: %s\n", current->task.title);
            printf("Priority: %d\n", current->task.priority);
            printf("Deadline: %s\n", current->task.deadline);
            printf("\n");
            flag = 1;
        }
        current = current->next;
    }
    if (flag == 0) {
        printf("Khong tim thay nhiem vu!\n");
    }
}

int getLength(Node* head) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong!\n");
        return 0;
    }
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int main() {
    Task task;
    Node* head = NULL;
    int choice;

    do {
        printf("TAK MANAGER\n");
        printf("1. Them nhiem vu\n");
        printf("2. Hien thi danh sach nhiem vu\n");
        printf("3. Xoa nhiem vu\n");
        printf("4. Cap nhat thong tin nhiem vu\n");
        printf("5. Danh dau nhiem vu hoan thanh\n");
        printf("6. Sap xep nhiem vu\n");
        printf("7. Tim kiem nhiem vu\n");
        printf("8. Thoat chuong trinh\n");
        printf("Lua chon cua ban: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int id;
                char title[50];
                int priority;
                char deadline[50];
                printf("Moi ban nhap ID nhiem vu:\n");
                scanf("%d", &id);
                getchar();
                if (isDuplicate(head, id)) {
                    printf("ID da ton tai!\n");
                    break;
                }

                printf("Moi ban nhap tieu de nhiem vu:\n");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("Moi ban nhap muc do uu tien:\n");
                scanf("%d", &priority);
                getchar();

                printf("Moi ban nhap thoi gian hoan thanh nhiem vu\n");
                fgets(deadline, sizeof(deadline), stdin);
                deadline[strcspn(deadline, "\n")] = '\0';

                head = createTask(head, id, title, priority, deadline);
                break;
            case 2:
                printTask(head);
                break;
            case 3:
                int deletaID;
                printf("Moi ban nhap ID nhiem vu can xoa:\n");
                scanf("%d", &deletaID);
                head = deleteTask(head, deletaID);
                break;
            case 4:
                int updateID;
                printf("Moi ban nhap vao id nhiem vu can cap nhat:\n");
                scanf("%d", &updateID);
                updateTask(head, updateID);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                char key[50];
                printf("Moi ban nhap tieu de can tim kiem:\n");
                getchar();
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';
                findTask(head, key);
                break;
            case 8:
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 8);
}