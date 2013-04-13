void set_entry(int key, int value);
int find_entry(int key);

/////////////////////////////////////////////////////////
// DICTIインタフェースをTreapの実装に繋ぐ
#include "treap.h"
#include "tlli_node.h"
Treap<TLLINode> dict;
void set_entry(int key, int value) { dict.set_entry(key, value); }
int find_entry(int key)  { return dict.find_entry(key); }
