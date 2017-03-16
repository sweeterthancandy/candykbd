
static void kdb_test(){
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


void main(){
  KbdContext ctx = {0};
  KbdConsumer printConsumer = { KbdPrintOp, NULL };
  KbdConsumer executeConsumer = { KbdExecuteOp, &ctx };
  
  ctx.consumers[0] = &printConsumer;
  ctx.consumers[1] = &executeConsumer;

  Sleep(200);
  parse(&ctx, "hello");
  parse(&ctx, "world");
  parse(&ctx, "h{sleep(1000)}w");
  parse(&ctx, "<c-f>");
}

