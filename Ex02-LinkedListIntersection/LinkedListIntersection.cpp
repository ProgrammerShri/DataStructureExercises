#include <unordered_set>
#include "../Common/LinkedList.hpp"

using Node = ds::Node<int>;
using LinkedList = ds::LinkedList<int>;

LinkedList getIntersection(LinkedList& list1, LinkedList& list2)
{
    std::unordered_set<int> hashset;
    LinkedList result;
    Node* node1 = list1.begin();
    Node* node2 = list2.begin();

    while (node1 != nullptr) {
        hashset.insert(node1->data);
        node1 = node1->next;
    }

    while (node2 != nullptr) {
        if (hashset.count(node2->data)) {
            result.push_back(node2->data);
        }
        node2 = node2->next;
    }

    return result;
}

void printLinkedList(LinkedList list)
{
    if (list.size() == 0) {
        std::cout << "NULL" << std::endl;
    }
    else {
        Node* current = list.begin();
        while (current != nullptr) {
            if (current->next != nullptr) {
                std::cout << current->data << " ";
            }
            else {
                std::cout << current->data;
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int main()
{
    LinkedList list1, list2;
    int num;
    while (std::cin >> num) {
        if (num == -1) {
            break;
        }
        else {
            list1.push_back(num);
        }
    }
    while (std::cin >> num) {
        if (num == -1) {
            break;
        }
        else {
            list2.push_back(num);
        }
    }

    printLinkedList(getIntersection(list1, list2));

    return 0;
}