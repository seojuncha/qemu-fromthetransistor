#ifndef HW_VERILOG_UART_H
#define HW_VERILOG_UART_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"

#define TYPE_VERILOG_UART "verilog-uart"
OBJECT_DECLARE_SIMPLE_TYPE(VerilogUartState, VERILOG_UART)

struct VerilogUartState {
  SysBusDevice parent_obj;
  MemoryRegion mmio;
  CharBackend chr;
};

#endif