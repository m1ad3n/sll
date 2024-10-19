Singly Linked List (SLL) Project

Description: This project implements a singly linked list (SLL) data structure in the C programming language. This SLL allows for dynamic memory management for adding, removing, and searching elements.

Features:

    Creating a new node.
    Inserting nodes at various positions (at the end, at the front, at a specific index).
    Removing nodes based on value or position.
    Debugging output to print nodes.
    Memory deallocation.

API Reference:

    sll_t* sll_new(void* _new_data) - Creates a new node with the given data.
    sll_t* sll_get_last(sll_t* _root) - Returns the last node in the list.
    sll_t* sll_at(sll_t* _root, size_t _index) - Returns the node at given index
    sll_t* sll_insert(sll_t* _root, void* _new_data) - Inserts a new node at the end of the list.
    sll_status_t sll_insert_front(sll_t** _root, void* _new_data) - Inserts a new node at the front of the list.
    sll_t* sll_insert_at(sll_t* _root, void* _new_data, size_t _index) - Inserts a new node at the given index
    sll_status_t sll_remove(sll_t* _root, void* _data, size_t _data_len) - Removes a node with the specified data.
    sll_status_t sll_remove_back(sll_t* _root) - Removes the last node
    sll_status_t sll_remove_front(sll_t* _root) - Removes the first node
    size_t sll_get_size(sll_t* _root) - Returns the number of nodes in the list.
    sll_status_t sll_clear(sll_t* _root) - Removes all the nodes but not _root
    sll_sttaus_t sll_set(sll_t* _node, void* _new_data) - Sets the new data for the node
    sll_status_t sll_free(sll_t* _root) - Frees the memory occupied by the list.

Installation:

```bash
git clone https://github.com/m1ad3n/sll.git
cd sll
make
make install
```

Usage:

    Include sll.h in your C file: #include <sll.h>
    Link libsll.so or libsll.a: gcc ... -lsll ...

    Example usage:

```c
#include <stdio.h>
#include <sll.h>

void print_int(void* data) {
    printf("%d\n", *(int*)data);
}

int main() {
    sll_t* list = NULL;

    // Adding elements
    int a = 10, b = 20, c = 30;
    sll_insert_front(&list, &a);
    sll_insert_back(list, &b);
    sll_insert_at(&list, &c, 1);

    // Printing elements
    sll_debug(list, print_int);

    // Removing an element
    sll_remove(list, &b, sizeof(int));

    // Printing elements after removal
    sll_debug(list, print_int);

    // Freeing memory
    sll_free(list);
    
    return 0;
}
```

License: This project is licensed under the MIT License.

Author: Mladen Stanimirović - mstanimirovic@proton.me

Feel free to adjust any information to better fit your project!