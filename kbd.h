#ifndef KBD_H
#define KBD_H

typedef struct op_code_t{
  char char_;
  const char* literal;
  char code;
  char modifiers;
}op_code_t;

// called in the form  callback(date, op)
typedef struct KbdConsumer{
  void(*callback)(void*, op_code_t*);
  void* data;
}KbdConsumer;

typedef struct KbdContext{
  unsigned config_sleep_ms; // = 0;
  unsigned config_alt_sleep_ms; // = 10;
  unsigned config_op_sleep_ms; // = 10;
  KbdConsumer* consumers[16];
}KbdContext;

void kbd_parse(KbdContext* ctx, const char* seq);
int kdb_main(int argc, char* argv[]);

#endif /* KBD_H */
