#define WINVER 0x0500
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>

#if 0
#define _VK_CHAR 0
static struct{
  int code;
  const char* code_literal;
  int literal;
  char ansi;
  const char* desc;
} key_map[] = {
#define DECL_VK( VK     , LIT, DESC ) {       VK, #VK, LIT,     0, DESC }
#define DECL_CHAR( char_, LIT, DESC ) { _VK_CHAR, "" , LIT, char_, DESC }
DECL_VK( VK_LBUTTON            , 0x01 , "Left mouse button"),
DECL_VK( VK_RBUTTON            , 0x02 , "Right mouse button"),
DECL_VK( VK_CANCEL             , 0x03 , "Control-break processing"),
DECL_VK( VK_MBUTTON            , 0x04 , "Middle mouse button (three-button mouse)"),
DECL_VK( VK_XBUTTON1           , 0x05 , "X1 mouse button"),
DECL_VK( VK_XBUTTON2           , 0x06 , "X2 mouse button"),
DECL_VK( VK_BACK               , 0x08 , "BACKSPACE key"),
DECL_VK( VK_TAB                , 0x09 , "TAB key"),
DECL_VK( VK_CLEAR              , 0x0C , "CLEAR key"),
DECL_VK( VK_RETURN             , 0x0D , "ENTER key"),
DECL_VK( VK_SHIFT              , 0x10 , "SHIFT key"),
DECL_VK( VK_CONTROL            , 0x11 , "CTRL key"),
DECL_VK( VK_MENU               , 0x12 , "ALT key"),
DECL_VK( VK_PAUSE              , 0x13 , "PAUSE key"),
DECL_VK( VK_CAPITAL            , 0x14 , "CAPS LOCK key"),
DECL_VK( VK_KANA               , 0x15 , "IME Kana mode"),
/*DECL_VK( VK_HANGUEL            , 0x15 , "IME Hanguel mode (maintained for compatibility; use VK_HANGUL)"),*/
DECL_VK( VK_HANGUL             , 0x15 , "IME Hangul mode"),
DECL_VK( VK_JUNJA              , 0x17 , "IME Junja mode"),
DECL_VK( VK_FINAL              , 0x18 , "IME final mode"),
DECL_VK( VK_HANJA              , 0x19 , "IME Hanja mode"),
DECL_VK( VK_KANJI              , 0x19 , "IME Kanji mode"),
DECL_VK( VK_ESCAPE             , 0x1B , "ESC key"),
DECL_VK( VK_CONVERT            , 0x1C , "IME convert"),
DECL_VK( VK_NONCONVERT         , 0x1D , "IME nonconvert"),
DECL_VK( VK_ACCEPT             , 0x1E , "IME accept"),
DECL_VK( VK_MODECHANGE         , 0x1F , "IME mode change request"),
DECL_VK( VK_SPACE              , 0x20 , "SPACEBAR"),
DECL_VK( VK_PRIOR              , 0x21 , "PAGE UP key"),
DECL_VK( VK_NEXT               , 0x22 , "PAGE DOWN key"),
DECL_VK( VK_END                , 0x23 , "END key"),
DECL_VK( VK_HOME               , 0x24 , "HOME key"),
DECL_VK( VK_LEFT               , 0x25 , "LEFT ARROW key"),
DECL_VK( VK_UP                 , 0x26 , "UP ARROW key"),
DECL_VK( VK_RIGHT              , 0x27 , "RIGHT ARROW key"),
DECL_VK( VK_DOWN               , 0x28 , "DOWN ARROW key"),
DECL_VK( VK_SELECT             , 0x29 , "SELECT key"),
DECL_VK( VK_PRINT              , 0x2A , "PRINT key"),
DECL_VK( VK_EXECUTE            , 0x2B , "EXECUTE key"),
DECL_VK( VK_SNAPSHOT           , 0x2C , "PRINT SCREEN key"),
DECL_VK( VK_INSERT             , 0x2D , "INS key"),
DECL_VK( VK_DELETE             , 0x2E , "DEL key"),
DECL_VK( VK_HELP               , 0x2F , "HELP key"),
DECL_CHAR('0'                  , 0x30 , "0 key"),
DECL_CHAR('1'                  , 0x31 , "1 key"),
DECL_CHAR('2'                  , 0x32 , "2 key"),
DECL_CHAR('3'                  , 0x33 , "3 key"),
DECL_CHAR('4'                  , 0x34 , "4 key"),
DECL_CHAR('5'                  , 0x35 , "5 key"),
DECL_CHAR('6'                  , 0x36 , "6 key"),
DECL_CHAR('7'                  , 0x37 , "7 key"),
DECL_CHAR('8'                  , 0x38 , "8 key"),
DECL_CHAR('9'                  , 0x39 , "9 key"),
DECL_CHAR('a'                  , 0x41 , "A key"),
DECL_CHAR('b'                  , 0x42 , "B key"),
DECL_CHAR('c'                  , 0x43 , "C key"),
DECL_CHAR('d'                  , 0x44 , "D key"),
DECL_CHAR('e'                  , 0x45 , "E key"),
DECL_CHAR('f'                  , 0x46 , "F key"),
DECL_CHAR('g'                  , 0x47 , "G key"),
DECL_CHAR('h'                  , 0x48 , "H key"),
DECL_CHAR('i'                  , 0x49 , "I key"),
DECL_CHAR('j'                  , 0x4A , "J key"),
DECL_CHAR('k'                  , 0x4B , "K key"),
DECL_CHAR('l'                  , 0x4C , "L key"),
DECL_CHAR('m'                  , 0x4D , "M key"),
DECL_CHAR('n'                  , 0x4E , "N key"),
DECL_CHAR('o'                  , 0x4F , "O key"),
DECL_CHAR('p'                  , 0x50 , "P key"),
DECL_CHAR('q'                  , 0x51 , "Q key"),
DECL_CHAR('r'                  , 0x52 , "R key"),
DECL_CHAR('s'                  , 0x53 , "S key"),
DECL_CHAR('t'                  , 0x54 , "T key"),
DECL_CHAR('u'                  , 0x55 , "U key"),
DECL_CHAR('v'                  , 0x56 , "V key"),
DECL_CHAR('w'                  , 0x57 , "W key"),
DECL_CHAR('x'                  , 0x58 , "X key"),
DECL_CHAR('y'                  , 0x59 , "Y key"),
DECL_CHAR('z'                  , 0x5A , "Z key"),
DECL_VK( VK_LWIN               , 0x5B , "Left Windows key (Natural keyboard) "),
DECL_VK( VK_RWIN               , 0x5C , "Right Windows key (Natural keyboard)"),
DECL_VK( VK_APPS               , 0x5D , "Applications key (Natural keyboard)"),
DECL_VK( VK_SLEEP              , 0x5F , "Computer Sleep key"),
DECL_VK( VK_NUMPAD0            , 0x60 , "Numeric keypad 0 key"),
DECL_VK( VK_NUMPAD1            , 0x61 , "Numeric keypad 1 key"),
DECL_VK( VK_NUMPAD2            , 0x62 , "Numeric keypad 2 key"),
DECL_VK( VK_NUMPAD3            , 0x63 , "Numeric keypad 3 key"),
DECL_VK( VK_NUMPAD4            , 0x64 , "Numeric keypad 4 key"),
DECL_VK( VK_NUMPAD5            , 0x65 , "Numeric keypad 5 key"),
DECL_VK( VK_NUMPAD6            , 0x66 , "Numeric keypad 6 key"),
DECL_VK( VK_NUMPAD7            , 0x67 , "Numeric keypad 7 key"),
DECL_VK( VK_NUMPAD8            , 0x68 , "Numeric keypad 8 key"),
DECL_VK( VK_NUMPAD9            , 0x69 , "Numeric keypad 9 key"),
DECL_VK( VK_MULTIPLY           , 0x6A , "Multiply key"),
DECL_VK( VK_ADD                , 0x6B , "Add key"),
DECL_VK( VK_SEPARATOR          , 0x6C , "Separator key"),
DECL_VK( VK_SUBTRACT           , 0x6D , "Subtract key"),
DECL_VK( VK_DECIMAL            , 0x6E , "Decimal key"),
DECL_VK( VK_DIVIDE             , 0x6F , "Divide key"),
DECL_VK( VK_F1                 , 0x70 , "F1 key"),
DECL_VK( VK_F2                 , 0x71 , "F2 key"),
DECL_VK( VK_F3                 , 0x72 , "F3 key"),
DECL_VK( VK_F4                 , 0x73 , "F4 key"),
DECL_VK( VK_F5                 , 0x74 , "F5 key"),
DECL_VK( VK_F6                 , 0x75 , "F6 key"),
DECL_VK( VK_F7                 , 0x76 , "F7 key"),
DECL_VK( VK_F8                 , 0x77 , "F8 key"),
DECL_VK( VK_F9                 , 0x78 , "F9 key"),
DECL_VK( VK_F10                , 0x79 , "F10 key"),
DECL_VK( VK_F11                , 0x7A , "F11 key"),
DECL_VK( VK_F12                , 0x7B , "F12 key"),
DECL_VK( VK_F13                , 0x7C , "F13 key"),
DECL_VK( VK_F14                , 0x7D , "F14 key"),
DECL_VK( VK_F15                , 0x7E , "F15 key"),
DECL_VK( VK_F16                , 0x7F , "F16 key"),
DECL_VK( VK_F17                , 0x80 , "F17 key"),
DECL_VK( VK_F18                , 0x81 , "F18 key"),
DECL_VK( VK_F19                , 0x82 , "F19 key"),
DECL_VK( VK_F20                , 0x83 , "F20 key"),
DECL_VK( VK_F21                , 0x84 , "F21 key"),
DECL_VK( VK_F22                , 0x85 , "F22 key"),
DECL_VK( VK_F23                , 0x86 , "F23 key"),
DECL_VK( VK_F24                , 0x87 , "F24 key"),
DECL_VK( VK_NUMLOCK            , 0x90 , "NUM LOCK key"),
DECL_VK( VK_SCROLL             , 0x91 , "SCROLL LOCK key"),
DECL_VK( VK_LSHIFT             , 0xA0 , "Left SHIFT key"),
DECL_VK( VK_RSHIFT             , 0xA1 , "Right SHIFT key"),
DECL_VK( VK_LCONTROL           , 0xA2 , "Left CONTROL key"),
DECL_VK( VK_RCONTROL           , 0xA3 , "Right CONTROL key"),
DECL_VK( VK_LMENU              , 0xA4 , "Left MENU key"),
DECL_VK( VK_RMENU              , 0xA5 , "Right MENU key"),
DECL_VK( VK_BROWSER_BACK       , 0xA6 , "Browser Back key"),
DECL_VK( VK_BROWSER_FORWARD    , 0xA7 , "Browser Forward key"),
DECL_VK( VK_BROWSER_REFRESH    , 0xA8 , "Browser Refresh key"),
DECL_VK( VK_BROWSER_STOP       , 0xA9 , "Browser Stop key"),
DECL_VK( VK_BROWSER_SEARCH     , 0xAA , "Browser Search key "),
DECL_VK( VK_BROWSER_FAVORITES  , 0xAB , "Browser Favorites key"),
DECL_VK( VK_BROWSER_HOME       , 0xAC , "Browser Start and Home key"),
DECL_VK( VK_VOLUME_MUTE        , 0xAD , "Volume Mute key"),
DECL_VK( VK_VOLUME_DOWN        , 0xAE , "Volume Down key"),
DECL_VK( VK_VOLUME_UP          , 0xAF , "Volume Up key"),
DECL_VK( VK_MEDIA_NEXT_TRACK   , 0xB0 , "Next Track key"),
DECL_VK( VK_MEDIA_PREV_TRACK   , 0xB1 , "Previous Track key"),
DECL_VK( VK_MEDIA_STOP         , 0xB2 , "Stop Media key"),
DECL_VK( VK_MEDIA_PLAY_PAUSE   , 0xB3 , "Play/Pause Media key"),
DECL_VK( VK_LAUNCH_MAIL        , 0xB4 , "Start Mail key"),
DECL_VK( VK_LAUNCH_MEDIA_SELECT, 0xB5 , "Select Media key"),
DECL_VK( VK_LAUNCH_APP1        , 0xB6 , "Start Application 1 key"),
DECL_VK( VK_LAUNCH_APP2        , 0xB7 , "Start Application 2 key"),
DECL_VK( VK_OEM_1              , 0xBA , "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard"),
DECL_VK( VK_OEM_PLUS           , 0xBB , "For any country/region the '+' key"),
DECL_VK( VK_OEM_COMMA          , 0xBC , "For any country/region the comma key"),
DECL_VK( VK_OEM_MINUS          , 0xBD , "For any country/region the '-' key"),
DECL_VK( VK_OEM_PERIOD         , 0xBE , "For any country/region the '.' key"),
DECL_VK( VK_OEM_2              , 0xBF , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the '/?' key "),
DECL_VK( VK_OEM_3              , 0xC0 , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the '`~' key "),
DECL_VK( VK_OEM_4              , 0xDB , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the '[{' key"),
DECL_VK( VK_OEM_5              , 0xDC , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the '|' key"),
DECL_VK( VK_OEM_6              , 0xDD , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the ']}' key"),
DECL_VK( VK_OEM_7              , 0xDE , "Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard the 'single-quote/double-quote' key"),
DECL_VK( VK_OEM_8              , 0xDF , "Used for miscellaneous characters; it can vary by keyboard."),
DECL_VK( VK_OEM_102            , 0xE2 , "Either the angle bracket key or the backslash key on the RT 102-key keyboard"),
DECL_VK( VK_PROCESSKEY         , 0xE5 , "IME PROCESS key"),
DECL_VK( VK_PACKET             , 0xE7 , "Used to pass Unicode characters as if they were keystrokes"),
DECL_VK( VK_ATTN               , 0xF6 , "Attn key"),
DECL_VK( VK_CRSEL              , 0xF7 , "CrSel key"),
DECL_VK( VK_EXSEL              , 0xF8 , "ExSel key"),
DECL_VK( VK_EREOF              , 0xF9 , "Erase EOF key"),
DECL_VK( VK_PLAY               , 0xFA , "Play key"),
DECL_VK( VK_ZOOM               , 0xFB , "Zoom key"),
DECL_VK( VK_NONAME             , 0xFC , "Reserved "),
DECL_VK( VK_PA1                , 0xFD , "PA1 key"),
DECL_VK( VK_OEM_CLEAR          , 0xFE , "Clear key")
};
#endif

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

void execute_op(op_code_t* op){
  INPUT ip = {0};
  printf("execuintg %s:->%x(%d)\n", op->literal, op->code, op->modifiers);

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
    Sleep(100);
    ip.ki.wVk = VK_MENU;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
  }
  if(op->modifiers & MOD_SHIFT){
    ip.ki.wVk = VK_SHIFT; // virtual-key code for the "a" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
  }
}



op_code_t* parse_meta(parser_context* ctx){
  op_code_t* op;
  ++ctx->iter;
  if( ! ctx->iter ){
    fprintf(stderr,"unknownn meta");
    return NULL;
  }

  switch(*ctx->iter){
  case 't': op = map_literal('\t'); break;
  case '<': op = map_literal('<'); break;
  default:
    fprintf(stderr,"unknownn meta \\%c", *ctx->iter);
    return NULL;
  }
  ++ctx->iter;
  return op;
}
// just need to find > but not \>
const char* find_extended_end(parser_context* ctx){
  const char* iter = ctx->iter;
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
op_code_t* parse_extended(parser_context* ctx){
  const char* end;
  size_t len;
  ++ctx->iter;
  end = find_extended_end(ctx);
  if( end == 0 ){
    fprintf(stderr,"bad extended");
  }
  len = end - ctx->iter;

  #define V(str, code, shift) \
  if( _strnicmp(str, ctx->iter, len) == 0){ \
    static op_code_t op = {\
      0, str, code, shift\
    };\
    ctx->iter = end + 1;\
    return &op;\
  }

  FOR_EACH_EXTENDED(V)
  #undef V

  return 0;
}
void parse_next(parser_context* ctx){
  op_code_t* op;
  switch(*ctx->iter){
  case '\\':
    op = parse_meta(ctx);
    break;
  case '<':
    op = parse_extended(ctx);
    break;
  default:
    op = parse_literal(ctx);
    break;
  }
  if( op == NULL){
    fprintf(stderr,"unable to parse %s\n", ctx->iter);
    exit(EXIT_FAILURE);
  }
  execute_op(op);
}
void parse(const char* seq){
  parser_context ctx = {seq, seq};

  for(;*ctx.iter;){
    parse_next(&ctx);
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
  for(idx=0;idx!=sizeof(ops)/sizeof(*ops);++idx){
    execute_op(&ops[idx]);
  }
}

int main(int argc, char* argv[]){
  int i;
  int to_sleep = 0;
  for(i=1;i!=argc;++i){
    if(strcmp(argv[i],"--sleep")==0){
      ++i;
      to_sleep = atoi(argv[i]);
      continue;
    }
    break;
  }
  Sleep(to_sleep);
  for(;i!=argc;++i){
    parse(argv[i]);
  }
}
