#include <dynlist.h>
#include <string.h>
#include <unity.h>

/*======= Фиксированные данные для тестирования (фиктуры) =========================*/
#define FIXTURE_SIZE 3
const int fixture_data_init[FIXTURE_SIZE] = {1, 2, 3};
int fixture_data[FIXTURE_SIZE];
Dynlist list;

void clean_func(void* val) {
    *(int*)val = 0; 
}

static void incrementor(void* val) {
    *(int*)val += 1;
}

/*===================================================================================*/
void setUp(void) {
    memcpy(fixture_data, fixture_data_init, sizeof(fixture_data));
    list = dynlist_new(clean_func);
}

void tearDown(void) {
    dynlist_free(list);
}

void test_dynlist_new_created_empty(void) {
    TEST_ASSERT_NULL(dynlist_begin(list));
}

void test_dynlist_free_called_clean_callback(void) {
    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    dynlist_free(list);
    list = NULL;  // предотвратить повторное удлание в tearDown()
    TEST_ASSERT_EACH_EQUAL_INT(0, fixture_data, FIXTURE_SIZE);
}

void test_dynlist_append_data_in_place(void) {
    // Помещаем данные в спиок
    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    // Выбираем данные из списка в массив actual_data
    int actual_data[FIXTURE_SIZE] = {0};
    DynlistNode* node = dynlist_begin(list);
    int index = 0;
    while (node != NULL) {
        TEST_ASSERT_TRUE_MESSAGE(index < FIXTURE_SIZE, "List has more elements, than expected");
        actual_data[index++] = *(int*)dynlist_value(node);
        node = dynlist_next(node);
    }
    // Сравниваем
    TEST_ASSERT_EQUAL_INT_ARRAY(fixture_data, actual_data, FIXTURE_SIZE);
}

void test_dynlist_foreach_called(void) {
    // Помещаем данные в спиок
    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    // Вызов
    dynlist_foreach(list, incrementor);
    // Проверка
    DynlistNode* node = dynlist_begin(list);
    for (int i = 0; i < FIXTURE_SIZE; i++) {
        TEST_ASSERT_NOT_NULL_MESSAGE(node, "List is shorter, than expected");
        incrementor(&fixture_data[i]);
        TEST_ASSERT_EQUAL_INT(fixture_data[i], *(int*)dynlist_value(node));
        node = dynlist_next(node);
    }
}

// My tests for dynlist_remove, dynlist_insert functions
void test_dynlist_remove_called(void) {
    DynlistNode* node_0;
    DynlistNode* node_1;
    DynlistNode* node_2;
    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    node_0 = dynlist_begin(list);
    node_1 = node_0->next;
    node_2 = node_1->next;

    dynlist_remove(list, node_1);
    TEST_ASSERT_NULL(node_1);
    TEST_ASSERT_EQUAL_PTR(node_2, node_0->next);
    dynlist_remove(list, node_0);
    TEST_ASSERT_EQUAL_PTR(node_2, list->head);
    dynlist_remove(list, node_2);
    TEST_ASSERT_NULL(node_2);
    TEST_ASSERT_NULL(list->head);

    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    node_0 = dynlist_begin(list);
    node_1 = node_0->next;
    node_2 = node_1->next;
    dynlist_remove(list, node_2);
    TEST_ASSERT_NULL(node_2);
    if(FIXTURE_SIZE == 3)
        TEST_ASSERT_NULL(node_1->next);
    else
        TEST_ASSERT_NOT_NULL(node_1->next)
}

void test_dynlist_insert(void) {
    DynlistNode* node_0;
    DynlistNode* node_1;
    DynlistNode* node_2;
    int val_3 = 4;
    int val_1_new = 5;
    int* val_3_ptr = &val_3_ptr;
    int* val_1_new_ptr = &val_1_new;

    for (int i = 0; i < FIXTURE_SIZE; i++) {
        dynlist_append(list, &fixture_data[i]);
    }
    node_0 = dynlist_begin(list);
    node_1 = node_0->next;
    node_2 = node_1->next;

    dynlist_insert(list, node_2, (void*)val_3_ptr);
    TEST_ASSERT_NOT_NULL(node_2->next);
    TEST_ASSERT_EQUAL_INT32(val_3, *((int*)(node_2->value)));

    DynlistNode* node_1_new;
    node_1_new = node_0->next;

    dynlist_insert(list, node_0, (void*)val_1_new_ptr);
    TEST_ASSERT_EQUAL_PTR(node_1, node_1_new->next);
    TEST_ASSERT_EQUAL_INT32(val_1_new, *((int*)(node_1_new->value)));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_dynlist_new_created_empty);
    RUN_TEST(test_dynlist_free_called_clean_callback);
    RUN_TEST(test_dynlist_append_data_in_place);
    RUN_TEST(test_dynlist_foreach_called);
    RUN_TEST(test_dynlist_remove_called);
    RUN_TEST(test_dynlist_insert);
    return UNITY_END();
}
