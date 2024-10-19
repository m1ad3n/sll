#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SLL_CALL sll_t* sll_new(void* _new_data) {
	if (_new_data == NULL) return NULL;
	sll_t* tmp = (sll_t*)malloc(sizeof(sll_t));
	if (tmp == NULL) return NULL;
	tmp->data = _new_data;
	tmp->next = NULL;
	return tmp;
}

SLL_CALL sll_t* sll_get_last(sll_t* _root) {
	if (_root)
		while (_root->next != NULL) _root = _root->next;
	return _root;
}

SLL_CALL sll_t* sll_at(sll_t* _root, size_t _index) {
	if (_index == 0 || _root == NULL) return _root;
	size_t count = 0;
	while (count != _index && _root) {
		count++;
		_root = _root->next;
	}
	return _root;
}

SLL_CALL sll_t* sll_insert_back(sll_t* _root, void* _new_data) {
	sll_t* last = sll_get_last(_root);
	last->next = sll_new(_new_data);
	return last->next;
}

SLL_CALL SLL_DEPRECATED(sll_push_back_obj, sll_push_back) sll_status_t sll_push_back_obj(sll_t* _root, sll_t* _node) {
	if (_root == NULL || _node == NULL) return SLL_PASSED_NULL;
	sll_t* last = sll_get_last(_root);
	last->next = _node;
	return SLL_FINE;
}

SLL_CALL sll_t* sll_push_back(sll_t* _root, void* _new_data) {
	return sll_insert_back(_root, _new_data);
} 

SLL_CALL sll_status_t sll_insert_front(sll_t** _root, void* _new_data) {
	if (_root == NULL || _new_data == NULL) return SLL_PASSED_NULL;
	sll_t* new_node = sll_new(_new_data);
	if (new_node == NULL) return SLL_MALLOC_RETURNED_NULL;
	new_node->next = *_root;
	*_root = new_node;
	return SLL_FINE;
}

SLL_CALL sll_t* sll_insert(sll_t* _root, void* _new_data) {
	if (_root == NULL || _new_data == NULL) return NULL;
	sll_t* new_node = sll_new(_new_data);
	new_node->next = _root->next;
	_root->next = new_node;
	return new_node;
}

SLL_CALL sll_t* sll_insert_at(sll_t** _root, void* _new_data, size_t _index) {
	if (_root == NULL || _new_data == NULL) return NULL;
	if (_index == 0) {
		sll_insert_front(_root, _new_data);
		return *_root;
	}
	size_t count = 0;
	sll_t* tmp = *_root;
	sll_t* new_node = sll_new(_new_data);
	while (count != _index - 1 && tmp->next != NULL) {
		count++;
		tmp = tmp->next;
	}
	new_node->next = tmp->next;
	tmp->next = new_node;
	return new_node;
}

SLL_CALL sll_status_t sll_remove(sll_t* _root, void* _data, size_t _data_len) {
	if (_root == NULL || _data == NULL) return SLL_PASSED_NULL;
	sll_t* last = _root;
	while (_root) {
		if (memcmp(_root->data, _data, _data_len) == 0) {
			if (_root->next) last->next = _root->next;
			else last->next = NULL;
			free(_root);
			return SLL_FINE;
		}
		last = _root;
		_root = _root->next;
	}
	return SLL_NOT_FOUND;
}

SLL_CALL sll_status_t sll_remove_at(sll_t** _root, size_t _index) {
	if (_root == NULL) return SLL_PASSED_NULL;
	if (_index == 0) {
		sll_remove_front(_root);
		return SLL_FINE;
	}

	size_t count = 0;
	sll_t* tmp = *_root;
	while (count != (_index - 1) && tmp) {
		count++;
		tmp = tmp->next;
	}

	if (tmp == NULL) return SLL_INDEX_OUT_OF_RANGE;
	sll_t* next_node = tmp->next->next;
	tmp->next = NULL;
	sll_free(tmp->next);
	tmp->next = next_node;
	return SLL_FINE;
}

SLL_CALL sll_status_t sll_remove_front(sll_t** _root) {
	if (_root == NULL) return SLL_PASSED_NULL;
	sll_t* tmp = *_root;
	*_root = tmp->next;
	tmp->next = NULL;
	sll_free(tmp);
	return SLL_FINE;
}

SLL_CALL sll_status_t sll_remove_back(sll_t* _root) {
	if (_root == NULL) return SLL_PASSED_NULL;
	while (_root->next->next != NULL)
		_root = _root->next;
	sll_free(_root->next);
	_root->next = NULL;
	return SLL_FINE;
}

SLL_CALL size_t sll_get_size(sll_t* _root) {
	size_t count = 0;
	sll_t* tmp = _root;
	while (tmp) {
		tmp = tmp->next;
		count++;
	}
	return count;
}

SLL_CALL sll_status_t sll_set(sll_t* _node, void* _new_data) {
	if (_node == NULL || _new_data == NULL) return SLL_PASSED_NULL;
	_node->data = _new_data;
	return SLL_FINE;
}

SLL_CALL sll_status_t sll_clear(sll_t* _root) {
	if (_root == NULL) return SLL_PASSED_NULL;
	sll_free(_root->next);
	_root->data = NULL;
	return SLL_FINE;
}

SLL_CALL sll_status_t sll_debug(sll_t* _root, void(*_print_func)(void*)) {
	if (_root == NULL || _print_func == NULL) return SLL_PASSED_NULL;
	while (_root) {
		_print_func(_root->data);
		_root = _root->next;
	}
	return SLL_FINE;
}

SLL_CALL sll_status_t sll_free(sll_t* _root) {
	if (_root == NULL) return SLL_PASSED_NULL;
	sll_free(_root->next);
	free(_root);
	_root = NULL;
	return SLL_FINE;
}
