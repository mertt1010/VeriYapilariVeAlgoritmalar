#include <stdio.h>
#include <stdlib.h>

struct Node {
   int data;
   struct Node *next;
};

struct Node* deleteNode(struct Node *head, int value) {
   struct Node *temp = head, *prev;

   // E�er ilk d���m silinecekse
   if (temp != NULL && temp->data == value) {
      head = temp->next;
      free(temp);
      return head;
   }

   // Silinecek d���m� bul
   while (temp != NULL && temp->data != value) {
      prev = temp;
      temp = temp->next;
   }

   // E�er d���m bulunamazsa
   if (temp == NULL) {
      printf("Girilen veri listede bulunamad�.\n");
      return head;
   }

   // D���m� ba�lant�dan ay�r
   prev->next = temp->next;
   free(temp);
   return head;
}

void printList(struct Node *node) {
   while (node != NULL) {
      printf("%d ", node->data);
      node = node->next;
   }
}

int main() {
   struct Node *head = NULL, *temp;
   int n, i, value;

   printf("Liste uzunlu�unu girin: ");
   scanf("%d", &n);

   // Liste olu�turma
   for (i = 0; i < n; i++) {
      temp = (struct Node *)malloc(sizeof(struct Node));
      printf("Veri %d girin: ", i+1);
      scanf("%d", &temp->data);
      temp->next = head;
      head = temp;
   }

   printf("Liste: ");
   printList(head);

   printf("\nSilinecek veri: ");
   scanf("%d", &value);
   head = deleteNode(head, value);

   printf("Yeni Liste: ");
   printList(head);

   return 0;
}
