#include <ctime>
#include <cstdlib>

// Nodeを操作するTreapのアルゴリズムを実装する
template<typename Node>
class Treap {
public:
    Treap() { srand(time(NULL)); }
 
    // Treapにキーがkey,値がvalueのエントリを追加する.
    // 既に同じキーのエントリが存在すれば値をvalueで更新する.
    void set_entry(int key, int value) {
        if (key <= 0 || value <= 0) return;
        if (Node::get_root_node().is_null()) {
            Node::set_root_node(create_node(key, value));
        } else {
            Node node = search(Node::get_root_node(), key);
            if (node.is_null())
                Node::set_root_node(insert(Node::get_root_node(), key, value));
            else
                node.set_val(value);
        }
    }
 
    // Treap内からキーがkeyであるエントリを探索し、その値を返す.
    // 存在しない場合は0を返す.
    int find_entry(int key) {
        Node node = search(Node::get_root_node(), key);
        return node.is_null() ? 0 : node.get_val();
    }
 
private:
    // nodeを根とした部分木からキーがkeyのノードを探して、そのノードのコピーを返す
    Node search(Node node, int key) {
        if (node.is_null() || key == node.get_key()) return node;
        if (key < node.get_key())
            return search(node.get_lch(), key);
        else
            return search(node.get_rch(), key);
    }
 
    // nodeを根として左回転し、新たな根を返す
    Node rotate_left(Node node) {
        Node right_child = node.get_rch();
        node.set_rch(right_child.get_lch());
        right_child.set_lch(node);
        return right_child;
    }
 
    // nodeを根として右回転し、新たな根を返す
    Node rotate_right(Node node) {
        Node left_child = node.get_lch();
        node.set_lch(left_child.get_rch());
        left_child.set_rch(node);
        return left_child;
    }
 
    // nodeを根とした部分木にキーがkey,値がvalueのノードを挿入し、
    // 挿入に伴って起こる回転操作が終わった後の新たな根を返す
    Node insert(Node node, int key, int value) {
        if (node.is_null()) return create_node(key, value);
        if (key < node.get_key()) {
            node.set_lch(insert(node.get_lch(), key, value));
            if (node.get_pri() > node.get_lch().get_pri())
                node = rotate_right(node);
        } else {
            node.set_rch(insert(node.get_rch(), key, value));
            if (node.get_pri() > node.get_rch().get_pri())
                node = rotate_left(node);
        }
        return node;
    }
 
    // キーがkey,値がvalueの新たなノードを作って返す
    Node create_node(int key, int value) {
        Node node = Node::new_node();
        node.set_key(key);
        node.set_val(value);
        node.set_pri(rand());
        return node;
    }
};
 
