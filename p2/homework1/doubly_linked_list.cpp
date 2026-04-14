#include <iostream>

struct Node {
  int info;
  Node *next;
  Node *prev;
};

void AddLast(Node **head, int val) {
  Node *newNode = new Node;
  newNode->info = val;
  newNode->next = NULL;
  if (*head == nullptr) {
    newNode->prev = nullptr;
    *head = newNode;
    return;
  }
  Node *temp = *head;
  while (temp->next != nullptr)
    temp = temp->next;
  temp->next = newNode;
  newNode->prev = temp;
}

void InsertAfter(Node *target, int val) {
  if (target == nullptr)
    return;
  Node *newNode = new Node;
  newNode->info = val;
  newNode->next = target->next;
  newNode->prev = target;
  if (target->next != nullptr) {
    target->next->prev = newNode;
  }
  target->next = newNode;
}

void RemoveLast(Node **head) {
  if (*head == nullptr)
    return;
  Node *temp = *head;
  if (temp->next == nullptr) {
    delete (temp);
    *head = nullptr;
    return;
  }
  while (temp->next != nullptr)
    temp = temp->next;
  temp->prev->next = nullptr;
  delete (temp);
}

void RemoveAfter(Node *target) {
  if (target == nullptr || target->next == nullptr)
    return;
  Node *toDelete = target->next;
  target->next = toDelete->next;
  if (toDelete->next != nullptr) {
    toDelete->next->prev = target;
  }
  delete (toDelete);
}

void printList(Node *head) {
  while (head != NULL) {
    std::cout << head->info << " ";
    head = head->next;
  }
  std::cout << '\n';
}

int main() {
  Node *list;
  AddLast(&list, 9);
  AddLast(&list, 14);
  AddLast(&list, 1);
  InsertAfter(list->next, 10);
  RemoveAfter(list->next);
  RemoveLast(&list);
  printList(list);
}
