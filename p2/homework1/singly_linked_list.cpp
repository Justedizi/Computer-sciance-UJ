#include <iostream>

struct Node {
  int info;
  struct Node *next;
};

void AddFirst(struct Node **head, int val) {
  Node *newNode = new Node;
  newNode->info = val;
  newNode->next = *head;
  *head = newNode;
}

void InsertBefore(Node **head, Node *target, int val) {
  if (*head == nullptr || target == nullptr)
    return;
  if (*head == target) {
    AddFirst(head, val);
    return;
  }
  Node *temp = *head;
  while (temp->next != nullptr && temp->next != target) {
    temp = temp->next;
  }
  if (temp->next == target) {
    Node *newNode = new Node;
    newNode->info = val;
    newNode->next = target;
    temp->next = newNode;
  }
}

void RemoveFirst(Node **head) {
  if (*head == nullptr)
    return;
  Node *temp = *head;
  *head = (*head)->next;
  delete (temp);
}

void RemoveCurrent(Node **head, Node *target) {
  if (*head == nullptr || target == nullptr)
    return;
  if (*head == target) {
    RemoveFirst(head);
    return;
  }
  Node *temp = *head;
  while (temp->next != nullptr && temp->next != target) {
    temp = temp->next;
  }
  if (temp->next == target) {
    temp->next = target->next;
    delete (target);
  }
}

void RemoveBefore(Node **head, Node *target) {
  if (*head == nullptr || *head == target || target == nullptr)
    return;
  if ((*head)->next == target) {
    RemoveFirst(head);
    return;
  }
  Node *temp = *head;
  while (temp->next != nullptr && temp->next->next != target) {
    temp = temp->next;
  }
  if (temp->next != nullptr && temp->next->next == target) {
    Node *toDelete = temp->next;
    temp->next = target;
    delete (toDelete);
  }
}

void printList(Node *head) {
  while (head != NULL) {
    std::cout << head->info << " ";
    head = head->next;
  }
  std::cout << '\n';
}

int main() {
  Node *list = nullptr;
  AddFirst(&list, 10);
  AddFirst(&list, 5);
  InsertBefore(&list, list->next, 12);
  RemoveFirst(&list);
  InsertBefore(&list, list->next, 11);
  InsertBefore(&list, list->next, 9);
  RemoveCurrent(&list, list->next->next);
  RemoveBefore(&list, list->next);
  printList(list);
}
