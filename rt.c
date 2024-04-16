20240416
handle_arch_irq
  gic_handle_irq  #irq-gic-v3.c
    generic_handle_domain_irq  #irqdesc.c
      handle_irq_desc
        generic_handle_irq_desc
        
        
        handle_fasteoi_irq
          handle_irq_event
            handle_irq_event_percpu
              __handle_irq_event_percpu
                action->handler
                __irq_wake_thread
                
gic-v3 init时设置 handle_arch_irq 函数指针值
