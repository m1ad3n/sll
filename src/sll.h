/*
 * Copyright (c) 2024 Mladen Stanimirovic
 */

#ifndef SLL_HEADER
#define SLL_HEADER

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SLL_CALL
#   undef SLL_CALL
#endif
#ifndef SLL_CALL
#   define SLL_CALL __attribute__((visibility("default")))
#endif

#ifdef SLL_DEPRECATED
#   undef SLL_DEPRECATED
#endif
#ifndef SLL_DEPRECATED
#   define SLL_DEPRECATED(func, alternative) __attribute__((deprecated("function " #func " is deprecated, please use " #alternative)))
#endif

/**
 * @brief Structure representing a node in a singly linked list.
 *
 * This structure contains a pointer to the data stored in the node
 * and a pointer to the next node in the list.
 */
typedef struct sll_s {
    void* data;             /**< Pointer to the data stored in the node. */
    struct sll_s* next;     /**< Pointer to the next node in the list. */
} sll_t;

/**
 * @brief Enum representing status codes for singly linked list operations.
 *
 * This enum provides various status codes to indicate the result of operations
 * performed on the singly linked list.
 */
typedef enum sll_status {
    SLL_FINE,                   /**< Operation completed successfully. 		*/
    SLL_NOT_FOUND,              /**< Specified node or data not found. 		*/
    SLL_PASSED_NULL,            /**< Null pointer was passed as an argument. 	*/
    SLL_MALLOC_RETURNED_NULL,   /**< Memory allocation failed (returned NULL). */
    SLL_INDEX_OUT_OF_RANGE      /**< Given index is smaller than sll_get_size */
} sll_status_t;

/**
 * @brief Create a new node.
 *
 * This function allocates memory for a new node and initializes it with the given data.
 * 
 * @param _new_data Pointer to the data to be stored in the new node.
 * @return Pointer to the newly created node.
 */
SLL_CALL sll_t* sll_new(void* _new_data);

/**
 * @brief Get the last node in the list.
 *
 * This function retrieves the last node of the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @return Pointer to the last node in the list, or NULL if the list is empty.
 */
SLL_CALL sll_t* sll_get_last(sll_t* _root);

/**
 * @brief Retrieve the node at a specified index in the list.
 *
 * This function returns the node located at the specified index in the singly linked list.
 * If the index is out of bounds (i.e., greater than or equal to the size of the list),
 * the function will return NULL.
 *
 * @param _root Pointer to the root of the list.
 * @param _index The index of the node to retrieve. The first node is at index 0.
 * @return Pointer to the node at the specified index, or NULL if the index is out of bounds.
 */
SLL_CALL sll_t* sll_at(sll_t* _root, size_t _index);

/**
 * @brief Insert a new node at the end of the list.
 *
 * This function inserts a new node with the given data at the end of the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @param _new_data Pointer to the data to be inserted into the new node.
 * @return Pointer to the updated root of the list.
 */
SLL_CALL sll_t* sll_insert(sll_t* _root, void* _new_data);

/**
 * @brief Insert a new node at a specified index in the list.
 *
 * This function inserts a new node with the given data at a specified index in the list.
 *
 * @param _root Pointer to a pointer to the root of the list.
 * @param _new_data Pointer to the data to be inserted into the new node.
 * @param _index The index at which to insert the new node.
 * @return Pointer to the updated root of the list.
 */
SLL_CALL sll_t* sll_insert_at(sll_t** _root, void* _new_data, size_t _index);

/**
 * @brief Insert a new node at the front of the list.
 *
 * This function inserts a new node with the given data at the front of the singly linked list.
 *
 * @param _root Pointer to a pointer to the root of the list.
 * @param _new_data Pointer to the data to be inserted into the new node.
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_insert_front(sll_t** _root, void* _new_data);

/**
 * @brief Add a new node at the end of the list.
 *
 * This function adds a new node with the given data at the end of the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @param _new_data Pointer to the data to be added.
 * @return Pointer to the updated root of the list.
 */
SLL_CALL sll_t* sll_insert_back(sll_t* _root, void* _new_data);

/**
 * @brief Add a new node at the end of the list.
 *
 * This inline function adds a new node with the given data at the end of the singly linked list
 * by calling the `sll_insert_back` function.
 *
 * @param _root Pointer to the root of the list.
 * @param _new_data Pointer to the data to be added.
 * @return Pointer to the updated root of the list.
 *
 * @note This function is inline to optimize performance, as it directly calls another
 *       function responsible for the actual insertion.
 */
SLL_CALL sll_t* sll_push_back(sll_t* _root, void* _new_data);

/**
 * @brief Add an existing node at the end of the list.
 *
 * This function adds an existing node to the end of the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @param _node Pointer to the node to be added.
 * @return Status code indicating success or error.
 */
SLL_CALL SLL_DEPRECATED(sll_push_back_obj, sll_push_back) sll_status_t sll_push_back_obj(sll_t* _root, sll_t* _node);

/**
 * @brief Debug output of the list.
 *
 * This function runs _print_func for every _node->data element in the list, useful for debugging.
 *
 * @param _root Pointer to the root of the list.
 * @param _print_func Function for debugging data.
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_debug(sll_t* _root, void(*_print_func)(void*));

/**
 * @brief Remove a node from the list.
 *
 * This function removes a node with the specified data from the list.
 *
 * @param _root Pointer to the root of the list.
 * @param _data Pointer to the data of the node to be removed.
 * @param _data_len Length of the data to be removed.
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_remove(sll_t* _root, void* _data, size_t _data_len);

/**
 * @brief Remove a node from the list at given index.
 *
 * This function removes a node from the specified index.
 *
 * @param _root Pointer to the root of the list.
 * @param _index Index of the node to be removed
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_remove_at(sll_t** _root, size_t _index);

/**
 * @brief Remove the node at the front of the list.
 *
 * This function removes the first node from the singly linked list.
 *
 * @param _root Pointer to a pointer to the root of the list.
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_remove_front(sll_t** _root);

/**
 * @brief Remove the node at the end of the list.
 *
 * This function removes the last node from the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @return Status code indicating success or error.
 */
SLL_CALL sll_status_t sll_remove_back(sll_t* _root);

/**
 * @brief Get the size of the list.
 *
 * This function returns the number of nodes in the singly linked list.
 *
 * @param _root Pointer to the root of the list.
 * @return Number of nodes in the list.
 */
SLL_CALL size_t sll_get_size(sll_t* _root);

/**
 * @brief Set new data for a given node.
 *
 * This function updates the data stored in the specified node with new data.
 * It replaces the existing data, so it is important to ensure that the old data
 * is properly freed if it was dynamically allocated.
 *
 * @param _node Pointer to the node whose data is to be updated.
 * @param _new_data Pointer to the new data to be set in the node.
 * @return Status code indicating success or error.
 *         - SLL_FINE: Data was set successfully.
 *         - SLL_PASSED_NULL: The provided node pointer or new data pointer is NULL.
 */
SLL_CALL sll_status_t sll_set(sll_t* _node, void* _new_data);

/**
 * @brief Clear the list and free its nodes.
 *
 * This function iterates through the singly linked list and deallocates the memory
 * used by each node. It also calls the provided free function on each node's data
 * to ensure proper cleanup of any dynamically allocated data associated with the nodes.
 * After clearing, the list will be empty, but the root pointer will still point to a
 * valid `sll_t` object.
 *
 * @param _root Pointer to the root of the list. This pointer will point to an empty list after clearing, but will not be set to NULL.
 * @param _free_func Pointer to a function that will be called to free the data stored in each node. If no special handling for node data is needed, this can be set to NULL.
 * @return Status code indicating success or error.
 *         - SLL_FINE: List was cleared successfully.
 *         - SLL_PASSED_NULL: The provided root pointer is NULL.
 */
SLL_CALL sll_status_t sll_clear(sll_t* _root);

/**
 * @brief Free the memory allocated for the list.
 *
 * This function deallocates the memory used by the singly linked list and its nodes.
 * After freeing, the root pointer should be set to NULL to avoid dangling pointers.
 *
 * @param _root Pointer to the root of the list. This pointer will be set to NULL after freeing.
 * @return Status code indicating success or error.
 *         - SLL_FINE: Memory was freed successfully.
 *         - SLL_PASSED_NULL: The provided root pointer is NULL.
 */
SLL_CALL sll_status_t sll_free(sll_t* _root);


#ifdef __cplusplus
}
#endif

#endif // SLL_HEADER
