#define WINVER 0x0500

#include <windows.h>
#include <WinUser.h>
#include <stdio.h>

#include "kbd.h"

#include "data.h"

typedef struct parser_context{
  const char* seq;
  const char* iter;
}parser_context;


static void dispatch_consumers( KbdContext* ctx, op_code_t* op){
  size_t i=0;
  if( ctx->config_op_sleep_ms ){
    Sleep(ctx->config_op_sleep_ms);
  }
  for(; i!= 16;++i){
    KbdConsumer* consumer = ctx->consumers[i];
    if( consumer ){
      consumer->callback(consumer->data, op);
    }
  }
}

static op_code_t* map_literal(char c){
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
static op_code_t* parse_literal(parser_context* ctx){
  op_code_t* op = map_literal(*ctx->iter);
  if( op ){
    ++ctx->iter;
  }
  return op;
}

static void KbdPrintOp(void* self, op_code_t* op){
  printf("%s:->%x(%d)\n", op->literal, op->code, op->modifiers);
}

static void KbdExecuteOp(KbdContext* ctx, op_code_t* op){
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



static op_code_t* parse_meta(parser_context* psr){
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
static const char* find_token_end(parser_context* psr, char token){
  const char* iter = psr->iter;
  for(;*iter;){
    switch(*iter){
    case '\\':
      ++iter;
      if(!iter)
        return NULL;
      ++iter;
      break;
    default:
      if( *iter == token)
        return iter;
      ++iter;
      break;
    }
  }
  return NULL;
}
static op_code_t* parse_extended(parser_context* psr){
  const char* end;
  size_t len;
  ++psr->iter;
  end = find_token_end(psr, '>');
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

static void apply_ctrl(parser_context* psr){
  const char* end;
  size_t len;
  ++psr->iter;
  end = find_token_end(psr, '}');
  if( end == 0 ){
    fprintf(stderr,"bad extended");
  }
  len = end - psr->iter;

  if( _strnicmp( "sleep(", psr->iter +1, 6) ){
    char sbuf[64];
    const char* from = psr->iter + 6;
    char* to = sbuf;
    int to_sleep;
    for(; *from != '\0' && isdigit(*from); ++from, ++to){
      *to = *from;
    }
    *to = '\0';
    to_sleep = atoi(sbuf);
    printf("sleeping for %i ms\n", to_sleep);
    Sleep(to_sleep);
    psr->iter = end + 1;
  } else{
    fprintf(stderr,"unable to parse ctrl %s\n", psr->iter );
    exit(EXIT_FAILURE);
  }
}
static void parse_next(KbdContext* ctx, parser_context* psr){
  op_code_t* op;
  switch(*psr->iter){
  case '\\':
    op = parse_meta(psr);
    break;
  case '<':
    op = parse_extended(psr);
    break;
  case '{':
    apply_ctrl(psr);
    return;
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
void kbd_parse(KbdContext* ctx, const char* seq){
  parser_context psr = {seq, seq};

  for(;*psr.iter;){
    parse_next(ctx, &psr);
  }
}


int kdb_main(int argc, char* argv[]){
  int i;
  KbdContext ctx = {0};
  KbdConsumer printConsumer = { KbdPrintOp, NULL };
  KbdConsumer executeConsumer = { KbdExecuteOp, &ctx };
  
  ctx.consumers[0] = &printConsumer;
  ctx.consumers[1] = &executeConsumer;

  for(i=1;i!=argc;++i){
    if(strcmp(argv[i],"--sleep")==0){
      ++i;
      ctx.config_sleep_ms = atoi(argv[i]);
      continue;
    }
    if(strcmp(argv[i],"--alt-sleep")==0){
      ++i;
      ctx.config_alt_sleep_ms = atoi(argv[i]);
      continue;
    }
    if(strcmp(argv[i],"--op-sleep")==0){
      ++i;
      ctx.config_op_sleep_ms = atoi(argv[i]);
      continue;
    }
    break;
  }
  // Sleep(0) rescheduales the process, don't want this
  if( ctx.config_sleep_ms ){
    Sleep(ctx.config_sleep_ms);
  }
  for(;i!=argc;++i){
    kbd_parse(&ctx,argv[i]);
  }
  return 0;
}


