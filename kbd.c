#define WINVER 0x0500
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
    


#define FOR_EACH_LITERAL(V)  \
     V('0' , 0x30         , 0)\
     V('1' , 0x31         , 0)\
     V('2' , 0x32         , 0)\
     V('3' , 0x33         , 0)\
     V('4' , 0x34         , 0)\
     V('5' , 0x35         , 0)\
     V('6' , 0x36         , 0)\
     V('7' , 0x37         , 0)\
     V('8' , 0x38         , 0)\
     V('9' , 0x39         , 0)\
     V('a' , 0x41         , 0)\
     V('b' , 0x42         , 0)\
     V('c' , 0x43         , 0)\
     V('d' , 0x44         , 0)\
     V('e' , 0x45         , 0)\
     V('f' , 0x46         , 0)\
     V('g' , 0x47         , 0)\
     V('h' , 0x48         , 0)\
     V('i' , 0x49         , 0)\
     V('j' , 0x4A         , 0)\
     V('k' , 0x4B         , 0)\
     V('l' , 0x4C         , 0)\
     V('m' , 0x4D         , 0)\
     V('n' , 0x4E         , 0)\
     V('o' , 0x4F         , 0)\
     V('p' , 0x50         , 0)\
     V('q' , 0x51         , 0)\
     V('r' , 0x52         , 0)\
     V('s' , 0x53         , 0)\
     V('t' , 0x54         , 0)\
     V('u' , 0x55         , 0)\
     V('v' , 0x56         , 0)\
     V('w' , 0x57         , 0)\
     V('x' , 0x58         , 0)\
     V('y' , 0x59         , 0)\
     V('z' , 0x5A         , 0)\
     V('A' , 0x41         , MOD_SHIFT)\
     V('B' , 0x42         , MOD_SHIFT)\
     V('C' , 0x43         , MOD_SHIFT)\
     V('D' , 0x44         , MOD_SHIFT)\
     V('E' , 0x45         , MOD_SHIFT)\
     V('F' , 0x46         , MOD_SHIFT)\
     V('G' , 0x47         , MOD_SHIFT)\
     V('H' , 0x48         , MOD_SHIFT)\
     V('I' , 0x49         , MOD_SHIFT)\
     V('J' , 0x4A         , MOD_SHIFT)\
     V('K' , 0x4B         , MOD_SHIFT)\
     V('L' , 0x4C         , MOD_SHIFT)\
     V('M' , 0x4D         , MOD_SHIFT)\
     V('N' , 0x4E         , MOD_SHIFT)\
     V('O' , 0x4F         , MOD_SHIFT)\
     V('P' , 0x50         , MOD_SHIFT)\
     V('Q' , 0x51         , MOD_SHIFT)\
     V('R' , 0x52         , MOD_SHIFT)\
     V('S' , 0x53         , MOD_SHIFT)\
     V('T' , 0x54         , MOD_SHIFT)\
     V('U' , 0x55         , MOD_SHIFT)\
     V('V' , 0x56         , MOD_SHIFT)\
     V('W' , 0x57         , MOD_SHIFT)\
     V('X' , 0x58         , MOD_SHIFT)\
     V('Y' , 0x59         , MOD_SHIFT)\
     V('Z' , 0x5A         , MOD_SHIFT)\
     V('\t', VK_TAB       , 0)\
     V(' ' , VK_SPACE     , 0)\
     V(';' , VK_OEM_1     , 0)\
     V(':' , VK_OEM_1     , MOD_SHIFT)\
     V('/' , VK_OEM_2     , 0)\
     V('?' , VK_OEM_2     , MOD_SHIFT)\
     V('\'', VK_OEM_3     , 0)\
     V('@' , VK_OEM_3     , MOD_SHIFT)\
     V('[' , VK_OEM_4     , 0)\
     V('{' , VK_OEM_4     , MOD_SHIFT)\
     V('\\', VK_OEM_5     , 0)\
     V('|' , VK_OEM_5     , MOD_SHIFT)\
     V(']' , VK_OEM_6     , 0)\
     V('}' , VK_OEM_6     , MOD_SHIFT)\
     V('#' , VK_OEM_7     , 0)\
     V('~' , VK_OEM_7     , MOD_SHIFT)\
     V('`' , VK_OEM_8     , 0)\
     V('.' , VK_OEM_PERIOD, 0)\
     V('>' , VK_OEM_PERIOD, MOD_SHIFT)\
 
 #define FOR_EACH_EXTENDED(V) \
    V("space" , VK_SPACE ,0)  \
    V("tab"   , VK_TAB   ,0)  \
    V("enter" , VK_RETURN,0)  \
    V("return", VK_RETURN,0)  \
    V("M-tab" , VK_TAB,   MOD_ALT) 




typedef struct op_code_t{
  char char_;
  const char* literal;
  char code;
  char modifiers;
}op_code_t;

typedef struct parser_context{
  const char* seq;
  const char* iter;
}parser_context;


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

void dispatch_consumers( KbdContext* ctx, op_code_t* op){
  size_t i=0;
  for(; i!= 16;++i){
    KbdConsumer* consumer = ctx->consumers[i];
    if( consumer ){
      consumer->callback(consumer->data, op);
    }
  }
}

op_code_t* map_literal(char c){
  #define V(char_, code, shift) \
    case char_:{                \
      static op_code_t op = {   \
        char_,                  \
        #char_,                 \
        code,                   \
        shift                   \
      };                        \
      return &op;               \
    }
  switch(c){
    FOR_EACH_LITERAL(V)
    default:
      return NULL;
  }
  #undef V
}
op_code_t* parse_literal(parser_context* ctx){
  op_code_t* op = map_literal(*ctx->iter);
  if( op ){
    ++ctx->iter;
  }
  return op;
}

void KbdPrintOp(void* self, op_code_t* op){
  printf("%s:->%x(%d)\n", op->literal, op->code, op->modifiers);
}

void KbdExecuteOp(KbdContext* ctx, op_code_t* op){
  INPUT ip = {0};

  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0; // hardware scan code for key
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;
  ip.ki.dwFlags = 0; // 0 for key press
  if(op->modifiers & MOD_SHIFT){
    ip.ki.wVk = VK_SHIFT; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
  }
  if(op->modifiers & MOD_CONTROL){
    ip.ki.wVk = VK_CONTROL; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
  }
  if(op->modifiers & MOD_ALT){
    ip.ki.wVk = VK_MENU;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));
  }
  ip.ki.wVk = op->code; // virtual-key code for the "a" key
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));
  ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
  SendInput(1, &ip, sizeof(INPUT));
  if(op->modifiers & MOD_ALT){
    Sleep(ctx->config_alt_sleep_ms);
    ip.ki.wVk = VK_MENU;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
  }
  if(op->modifiers & MOD_CONTROL){
    ip.ki.wVk = VK_CONTROL; // virtual-key code for the "a" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
  }
  if(op->modifiers & MOD_SHIFT){
    ip.ki.wVk = VK_SHIFT; // virtual-key code for the "a" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
  }
}



op_code_t* parse_meta(parser_context* psr){
  op_code_t* op;
  ++psr->iter;
  if( ! psr->iter ){
    fprintf(stderr,"unknownn meta");
    return NULL;
  }

  switch(*psr->iter){
  case 't': op = map_literal('\t'); break;
  case '<': op = map_literal('<'); break;
  default:
    fprintf(stderr,"unknownn meta \\%c", *psr->iter);
    return NULL;
  }
  ++psr->iter;
  return op;
}
// just need to find > but not \>
const char* find_extended_end(parser_context* psr){
  const char* iter = psr->iter;
  for(;*iter;){
    switch(*iter){
    case '\\':
      ++iter;
      if(!iter)
        return NULL;
      ++iter;
      break;
    case '>':
      return iter;
    default:
      ++iter;
      break;
    }
  }
  return NULL;
}
op_code_t* parse_extended(parser_context* psr){
  const char* end;
  size_t len;
  ++psr->iter;
  end = find_extended_end(psr);
  if( end == 0 ){
    fprintf(stderr,"bad extended");
  }
  len = end - psr->iter;

  // parser those of the form 
  //      M-a
  //      C-a
  if( len == 3 && _strnicmp( "c-", psr->iter,2) == 0 ){
    #define V(char_, code, shift) \
      case char_:{                \
        static op_code_t op = {   \
          char_,                  \
          "<C-" #char_ ">",       \
          code,                   \
          shift | MOD_CONTROL     \
        };                        \
        psr->iter = end + 1;      \
        return &op;               \
      }
    switch(*(psr->iter+2)){
      FOR_EACH_LITERAL(V)
      default:
        return NULL;
    }
    #undef V
  }


  #define V(str, code, shift) \
  if( _strnicmp(str, psr->iter, len) == 0){ \
    static op_code_t op = {\
      0, str, code, shift\
    };\
    psr->iter = end + 1;\
    return &op;\
  }

  FOR_EACH_EXTENDED(V)
  #undef V

  return 0;
}
void parse_next(KbdContext* ctx, parser_context* psr){
  op_code_t* op;
  switch(*psr->iter){
  case '\\':
    op = parse_meta(psr);
    break;
  case '<':
    op = parse_extended(psr);
    break;
  default:
    op = parse_literal(psr);
    break;
  }
  if( op == NULL){
    fprintf(stderr,"unable to parse %s\n", psr->iter);
    exit(EXIT_FAILURE);
  }
  dispatch_consumers(ctx, op);
}
void parse(KbdContext* ctx, const char* seq){
  parser_context psr = {seq, seq};

  for(;*psr.iter;){
    parse_next(ctx, &psr);
  }
}

void kdb_test(){
  int idx=0;
  static op_code_t ops[]={
    {0, 0, VK_OEM_1, 0},
    {0, 0, VK_OEM_1, 1},
    {0, 0, VK_OEM_2, 0},
    {0, 0, VK_OEM_2, 1},
    {0, 0, VK_OEM_3, 0},
    {0, 0, VK_OEM_3, 1},
    {0, 0, VK_OEM_4, 0},
    {0, 0, VK_OEM_4, 1},
    {0, 0, VK_OEM_5, 0},
    {0, 0, VK_OEM_5, 1},
    {0, 0, VK_OEM_6, 0},
    {0, 0, VK_OEM_6, 1},
    {0, 0, VK_OEM_7, 0},
    {0, 0, VK_OEM_7, 1},
    {0, 0, VK_OEM_8, 0},
    {0, 0, VK_OEM_8, 1},
    {0, 0, VK_OEM_PERIOD,0 },
    {0, 0, VK_OEM_PERIOD,1 }
  };
  #if 0
  for(idx=0;idx!=sizeof(ops)/sizeof(*ops);++idx){
    execute_op(&ops[idx]);
    if( config_op_sleep_ms >= 0 )
      Sleep( config_op_sleep_ms );
  }
  #endif
}

#if 0
int kdb_main(int argc, char* argv[]){
  int i;
  KbdContext ctx = {0};
  KbdConsumer printConsumer = { KbdPrintOp, NULL };
  ctx.consumers[0] = &printConsumer;

  for(i=1;i!=argc;++i){
    if(strcmp(argv[i],"--sleep")==0){
      ++i;
      config_sleep_ms = atoi(argv[i]);
      continue;
    }
    if(strcmp(argv[i],"--alt-sleep")==0){
      ++i;
      config_alt_sleep_ms = atoi(argv[i]);
      continue;
    }
    break;
  }
  // Sleep(0) rescheduales the process, don't want this
  if( config_sleep_ms ){
    Sleep(config_sleep_ms);
  }
  for(;i!=argc;++i){
    parse(argv[i]);
  }
  return 0;
}
#endif 

void test_main(){
  KbdContext ctx = {0};
  KbdConsumer printConsumer = { KbdPrintOp, NULL };
  KbdConsumer executeConsumer = { KbdExecuteOp, &ctx };
  
  ctx.consumers[0] = &printConsumer;
  ctx.consumers[1] = &executeConsumer;

  Sleep(200);
  parse(&ctx, "hello");
  parse(&ctx, "world");
  parse(&ctx, "<c-f>");
}


#if 0
int main(int argc, char** argv){
  return kdb_main(argc, argv);
}
#endif

int main(){
  test_main();
}

#if 0
int main(){
   const char* args[] = {
    "dummy",
    #if 0
    "--sleep",
    "1000",
    #endif
    "--alt-sleep", 
    "25",
    "<m-tab>Mr Gerry K Candy<TAB>g3rc4n@gmail.com<TAB>07445615041<TAB>4 Lydd Road<Tab>Bexleyheath<TAB><TAB>Kent<TAB>Da7 5PB<TAB><TAB><TAB>visa<TAB>4921816436289950<TAB>08<TAB>2019<TAB>029<TAB><space><return>"
  };
  return kdb_main(sizeof(args)/sizeof(*args), args);
}
#endif
