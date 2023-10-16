#ifndef _PCIDEF_H_
#define _PCIDEF_H_ 
#define outl(value,port)	SyserWritePortDword(port,value)
#define outw(value,port)	SyserWritePortWord(port,value)
#define outb(value,port)	SyserWritePortByte(port,value)
#define inl					SyserReadPortDword
#define inw					SyserReadPortWord
#define inb					SyserReadPortByte
#define u16					WORD
#define u32					DWORD
#define u8					BYTE
//#define PCIBIOS_DEVICE_NOT_FOUND 0
//#define PCI_CLASS_DEVICE 0

typedef struct pci_dev_t
{
	int bus;
	int devfn;
}pci_dev;
typedef struct st_pci_ops_t {
	int (*read_byte)( pci_dev *, int where, u8 *val);
	int (*read_word)( pci_dev *, int where, u16 *val);
	int (*read_dword)( pci_dev *, int where, u32 *val);
	int (*write_byte)( pci_dev *, int where, u8 val);
	int (*write_word)( pci_dev *, int where, u16 val);
	int (*write_dword)( pci_dev *, int where, u32 val);
}pci_ops;


pci_ops *  pci_init(void);
int  pci_sanity_check(pci_ops *ops);
int pci_conf2_write_config_dword( pci_dev *dev, int where, u32 value);
int pci_conf2_write_config_word( pci_dev *dev, int where, u16 value);
int pci_conf2_write_config_byte( pci_dev *dev, int where, u8 value);
int pci_conf2_read_config_dword( pci_dev *dev, int where, u32 *value);
int pci_conf2_read_config_word( pci_dev *dev, int where, u16 *value);
int pci_conf2_read_config_byte( pci_dev *dev, int where, u8 *value);
int pci_conf1_read_config_byte( pci_dev *dev, int where, u8 *value);
int pci_conf1_read_config_word( pci_dev *dev, int where, u16 *value);
int pci_conf1_read_config_dword( pci_dev *dev, int where, u32 *value); 
int pci_conf1_write_config_byte( pci_dev *dev, int where, u8 value);
int pci_conf1_write_config_word( pci_dev *dev, int where, u16 value);
int pci_conf1_write_config_dword( pci_dev *dev, int where, u32 value);
extern pci_ops pci_direct_conf2;
extern pci_ops pci_direct_conf1;
extern pci_ops *CurrentPCI;
#endif

