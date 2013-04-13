#include "tlli.h"

// Trianyへの各フィールドへのアクセス方法と生のidを隠蔽し、
// Treapアルゴリズムに渡すインタフェースを公開する
class TLLINode {
public:
    int get_key()   { return get_a(id); } // key
    int get_val()   { return get_b(id); } // value
    TLLINode get_lch()  { return TLLINode(get_a(get_c(id))); } // id of left child
    TLLINode get_rch()  { return TLLINode(get_b(get_c(id))); } // id of right child
    int get_pri()   { return get_c(get_c(id)); } // priority
 
    void set_key(int key)   { set_a(id, key); }
    void set_val(int val)   { set_b(id, val); }
    void set_lch(TLLINode lch)  { set_a(get_c(id), lch.id); }
    void set_rch(TLLINode rch)  { set_b(get_c(id), rch.id); }
    void set_pri(int pri)   { set_c(get_c(id), pri); }
 
    bool is_null() { return id == 0; }
 
    static TLLINode new_node() {
        int id = allocate_triany();
        int id_sub = allocate_triany();
        set_c(id, id_sub);
        return TLLINode(id);
    }
    static TLLINode get_root_node() { return TLLINode(get_a(root_triany())); }
    static void set_root_node(TLLINode node) { set_a(root_triany(), node.id); }
 
private:
    int id;
    TLLINode(int id): id(id) {};
    TLLINode();
};
