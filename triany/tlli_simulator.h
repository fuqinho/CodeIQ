#include <cstring>
#include <cassert>

// TLLI simulatorの実装
class TLLISimulator {
  public:
    TLLISimulator(): num_allocated(1) {
        std::memset(blocks, 0, sizeof(blocks));
        // [1,MOD)の整数に対して, MODを法とする逆元を計算しておく. 
        // この逆元を, idとスタック内indexの相互変換に利用する
        inv[1] = 1;
        for (int i = 2; i < MOD; i++) {
            inv[i] = static_cast<long long>(inv[MOD%i]) * (MOD - MOD/i) % MOD;
        }
    }
 
    int root_triany(void) { return 1; }
 
    int allocate_triany(void) {
        // 仕様上はallocate_triany()は失敗しないが、
        // simulatorでは確保済みブロックを超える場合0を返す
        assert(num_allocated < MAX_BLOCKS);
        if (num_allocated >= MAX_BLOCKS) return 0;
 
        return inv[++num_allocated];
    }
 
    void set_value(int id, int col, int value) {
        if (is_valid_id(id) && is_valid_value(value))
            blocks[inv[id]][col] = value;
    }
 
    int get_value(int id, int col) {
        return is_valid_id(id) ? blocks[inv[id]][col] : 0;
    }
 
 private:
    // MODを法とするkの逆元をinv[k]に保存する. id <-> idxの相互変換テーブルになる. 
    // 逆元が必ず存在するよう、MODは素数である必要がある
    static const int MOD = 1000003;
    int inv[MOD]; 
 
    // MOD-1個までTriany blockを確保できる
    static const int MAX_BLOCKS = MOD - 1;
    int blocks[MAX_BLOCKS+1][3];
    int num_allocated;
 
    bool is_valid_id(int id) {
        if (id <= 0) return false; // there's no triany with id<=0
        if (id >= MOD) return false; // the id can't be generated
        if (inv[id] > num_allocated) return false; // not allocated yet
        return true;
    }
 
    bool is_valid_value(int value) {
        if (value < 0) return false; // value must be non-negative
        return true;
    }
};
