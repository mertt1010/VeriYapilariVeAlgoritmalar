#include <stdio.h>
#include <stdlib.h>

struct Node {
   int data;
   struct Node *next;
};

struct Node* deleteNode(struct Node *head, int value) {
   struct Node *temp = head, *prev;

   // Eðer ilk düðüm silinecekse
   if (temp != NULL && temp->data == value) {
      head = temp->next;
      free(temp);
      return head;
   }

   // Silinecek düðümü bul
   while (temp != NULL && temp->data != value) {
      prev = temp;
      temp = temp->next;
   }

   // Eðer düðüm bulunamazsa
   if (temp == NULL) {
      printf("Girilen veri listede bulunamadý.\n");
      return head;
   }

   // Düðümü baðlantýdan ayýr
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

   printf("Liste uzunluðunu girin: ");
   scanf("%d", &n);

   // Liste oluþturma
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
