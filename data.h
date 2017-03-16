#ifndef KBD_DATA_H
#define KBD_DATA_H

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

#endif /* KBD_DATA_H */
