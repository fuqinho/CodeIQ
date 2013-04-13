int root_triany(void);
int allocate_triany(void);
void set_a(int id, int value);
void set_b(int id, int value);
void set_c(int id, int value);
int get_a(int id);
int get_b(int id);
int get_c(int id);
 
/////////////////////////////////////////////////
// TLLIインターフェースをシミュレータに繋ぐ
#include "tlli_simulator.h"
TLLISimulator simulator;
int root_triany(void) { return simulator.root_triany(); }
int allocate_triany(void) { return simulator.allocate_triany(); }
void set_a(int id, int value) { simulator.set_value(id, 0, value); }
void set_b(int id, int value) { simulator.set_value(id, 1, value); }
void set_c(int id, int value) { simulator.set_value(id, 2, value); }
int get_a(int id) { return simulator.get_value(id, 0); }
int get_b(int id) { return simulator.get_value(id, 1); }
int get_c(int id) { return simulator.get_value(id, 2); }
