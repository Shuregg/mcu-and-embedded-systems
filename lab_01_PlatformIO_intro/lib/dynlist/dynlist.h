#pragma once
#ifdef __cplusplus
extern "C" {
#endif
    typedef struct DynlistDescriptor DynlistDescriptor;
    typedef struct DynlistNode DynlistNode;
    typedef struct DynlistDescriptor *Dynlist;
    typedef void (*dynlist_pval_func_t)(void *val);
    __attribute__((warn_unused_result)) Dynlist dynlist_new(dynlist_pval_func_t clean_val_func);
    void dynlist_free(Dynlist plist);
    void dynlist_append(Dynlist list, void *value);
    void dynlist_prepend(Dynlist list, void *value);
    void dynlist_foreach(Dynlist list, dynlist_pval_func_t do_func);
    struct DynlistNode *dynlist_begin(Dynlist list);
    struct DynlistNode *dynlist_next(struct DynlistNode *node);
    void *dynlist_value(struct DynlistNode *node);
    void dynlist_remove(Dynlist list, DynlistNode* node);
    void dynlist_insert(Dynlist list, DynlistNode* pos, void* value);
#ifdef __cplusplus
}
#endif