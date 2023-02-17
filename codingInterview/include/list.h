#pragma once
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void connectListNodes(ListNode* pCurrent, ListNode* pNext) {
    if (pCurrent == nullptr) {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->next = pNext;
}

ListNode* createLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curNode = head;
    for (int i = 1; i < arr.size(); ++i) {
        curNode->next = new ListNode(arr[i]);
        curNode = curNode->next;
    }
    return head;
}

void printLinkedList(ListNode* head) {
    ListNode* curNode = head;
    while (curNode) {
        cout << curNode->val << " -> ";
        curNode = curNode->next;
    }
    cout << "NULL" << endl;
}

void destroyLinkedList(ListNode* head) {
    ListNode* curNode = head;
    while (curNode) {
        ListNode* delNode = curNode;
        curNode = curNode->next;
        delete delNode;
    }
    return;
}

template <class Container>
void display(const Container& c) {
    typename Container::const_iterator cit = c.begin();
    while (cit != c.end()) {
        cout << *cit << " ";
        ++cit;
    }
    cout << endl;
}