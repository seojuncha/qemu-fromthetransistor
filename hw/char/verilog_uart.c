#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/char/verilog_uart.h"
#include "hw/sysbus.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "qemu/log.h"
#include "qemu/module.h"

static uint64_t verilog_uart_read(void *opaque, hwaddr addr, unsigned int size)
{
  return 0;
}

static void verilog_uart_write(void *opaque, hwaddr offset,
                              uint64_t value, unsigned size)
{
  
}


static const MemoryRegionOps verilog_uart_ops = {
    .read = verilog_uart_read,
    .write = verilog_uart_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .impl = {.min_access_size = 1, .max_access_size = 1}
};

static Property verilog_uart_properties[] = {
    DEFINE_PROP_CHR("chardev", VerilogUartState, chr),
    DEFINE_PROP_END_OF_LIST(),
};

static int verilog_uart_can_receive(void *opaque)
{
    // VerilogUartState *s = (VerilogUartState *)opaque;
    return 1;
}

static void verilog_uart_receive(void *opaque, const uint8_t *buf, int size)
{
  // VerilogUartState *s = (VerilogUartState *)opaque;
}

static void verilog_uart_realize(DeviceState *dev, Error **errp)
{
  VerilogUartState *s = VERILOG_UART(dev);
  
  qemu_chr_fe_set_handlers(&s->chr, verilog_uart_can_receive, verilog_uart_receive,
                            NULL, NULL, s, NULL, true);
}

static void verilog_uart_init(Object *obj)
{
  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
  VerilogUartState *s = VERILOG_UART(obj);

  memory_region_init_io(&s->mmio, OBJECT(s), &verilog_uart_ops, s, TYPE_VERILOG_UART, 0x1000);
  sysbus_init_mmio(sbd, &s->mmio);
}

static void verilog_uart_class_init(ObjectClass *oc, void *data)
{
  DeviceClass *dc = DEVICE_CLASS(oc);
  dc->realize = verilog_uart_realize;
  device_class_set_props(dc, verilog_uart_properties);
}

static const TypeInfo verilog_uart_info = {
    .name          = TYPE_VERILOG_UART,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(VerilogUartState),
    .instance_init = verilog_uart_init,
    .class_init    = verilog_uart_class_init,
};

static void verilog_uart_register_types(void)
{
    type_register_static(&verilog_uart_info);
}

type_init(verilog_uart_register_types)
