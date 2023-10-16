#include "StdAfx.h"
#include "X86Optr.h"


pci_ops pci_direct_conf1 = { 
	pci_conf1_read_config_byte,
	pci_conf1_read_config_word,
	pci_conf1_read_config_dword,
	pci_conf1_write_config_byte,
	pci_conf1_write_config_word,
	pci_conf1_write_config_dword
};
   pci_ops pci_direct_conf2 = {
	pci_conf2_read_config_byte,
	pci_conf2_read_config_word,
	pci_conf2_read_config_dword,
	pci_conf2_write_config_byte,
	pci_conf2_write_config_word,
	pci_conf2_write_config_dword
};
pci_ops *CurrentPCI=NULL;
#if 1
#define CONFIG_CMD(dev, where)   (0x80000000 | (dev->bus << 16) | (dev->devfn << 8) | (where & ~3))

 int pci_conf1_read_config_byte( pci_dev *dev, int where, u8 *value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);
	*value = inb(0xCFC + (where&3));
	return 0;
}

 int pci_conf1_read_config_word( pci_dev *dev, int where, u16 *value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);    
	*value = inw(0xCFC + (where&2));
	return 0;    
}

 int pci_conf1_read_config_dword( pci_dev *dev, int where, u32 *value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);
	*value = inl(0xCFC);
	return 0;    
}

 int pci_conf1_write_config_byte( pci_dev *dev, int where, u8 value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);    
	outb(value, 0xCFC + (where&3));
	return 0;
}

 int pci_conf1_write_config_word( pci_dev *dev, int where, u16 value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);
	outw(value, 0xCFC + (where&2));
	return 0;
}

 int pci_conf1_write_config_dword( pci_dev *dev, int where, u32 value)
{
	outl(CONFIG_CMD(dev,where), 0xCF8);
	outl(value, 0xCFC);
	return 0;
}

#undef CONFIG_CMD



/*
 * Functions for accessing PCI configuration space with type 2 accesses
 */

#define IOADDR(devfn, where)	((0xC000 | ((devfn & 0x78) << 5)) + where)
#define FUNC(devfn)		(((devfn & 7) << 1) | 0xf0)
#define SET(dev)		if (dev->devfn & 0x80) return PCIBIOS_DEVICE_NOT_FOUND;		\
				outb((BYTE)FUNC(dev->devfn), 0xCF8);					\
				outb((BYTE)dev->bus, 0xCFA);

 int pci_conf2_read_config_byte( pci_dev *dev, int where, u8 *value)
{
	SET(dev);
	*value = inb(IOADDR(dev->devfn,where));
	outb (0, 0xCF8);
	return 0;
}

 int pci_conf2_read_config_word( pci_dev *dev, int where, u16 *value)
{
	SET(dev);
	*value = inw(IOADDR(dev->devfn,where));
	outb (0, 0xCF8);
	return 0;
}

 int pci_conf2_read_config_dword( pci_dev *dev, int where, u32 *value)
{
	SET(dev);
	*value = inl (IOADDR(dev->devfn,where));    
	outb (0, 0xCF8);    
	return 0;
}

 int pci_conf2_write_config_byte( pci_dev *dev, int where, u8 value)
{
	SET(dev);
	outb (value, IOADDR(dev->devfn,where));
	outb (0, 0xCF8);    
	return 0;
}

 int pci_conf2_write_config_word( pci_dev *dev, int where, u16 value)
{
	SET(dev);
	outw (value, IOADDR(dev->devfn,where));
	outb (0, 0xCF8);    
	return 0;
}

 int pci_conf2_write_config_dword( pci_dev *dev, int where, u32 value)
{
	SET(dev);
	outl (value, IOADDR(dev->devfn,where));    
	outb (0, 0xCF8);    
	return 0;
}

#undef SET
#undef IOADDR
#undef FUNC


/*
 * Before we decide to use direct hardware access mechanisms, we try to do some
 * trivial checks to ensure it at least _seems_ to be working -- we just test
 * whether bus 00 contains a host bridge (this is similar to checking
 * techniques used in XFree86, but ours should be more reliable since we
 * attempt to make use of direct access hints provided by the PCI BIOS).
 *
 * This should be close to trivial, but it isn't, because there are buggy
 * chipsets (yes, you guessed it, by Intel and Compaq) that have no class ID.
 */
 int  pci_sanity_check( pci_ops *ops)
{
	u16 x;
	 pci_dev dev;

	dev.bus = 0;
	for(dev.devfn=0; dev.devfn < 0x100; dev.devfn++)
	{
		if ((!ops->read_word(&dev, PCI_CLASS_DEVICE, &x) && (x == PCI_CLASS_BRIDGE_HOST || x == PCI_CLASS_DISPLAY_VGA)) || (!ops->read_word(&dev, PCI_VENDOR_ID, &x) && (x == PCI_VENDOR_ID_INTEL || x == PCI_VENDOR_ID_COMPAQ)))
			return 1;
	}
	return 0;
}

pci_ops *  pci_init(void)
{
	unsigned int tmp;
	ULONG_PTR	Flags;
	SyserSaveFlags(&Flags);
	SyserCloseInterrupt();
	
	/*
	 * Check if configuration type 1 works.
	 */

	outb (0x01, 0xCFB);
	tmp = inl (0xCF8);
	outl (0x80000000, 0xCF8);
	if (inl (0xCF8) == 0x80000000 &&
		pci_sanity_check(&pci_direct_conf1)) {
		outl (tmp, 0xCF8);
		SyserRestoreFlags(Flags);
		return &pci_direct_conf1;
	}
	outl (tmp, 0xCF8);


	/*
	 * Check if configuration type 2 works.
	 */

	outb (0x00, 0xCFB);
	outb (0x00, 0xCF8);
	outb (0x00, 0xCFA);
	if (inb (0xCF8) == 0x00 && inb (0xCFA) == 0x00 &&
		pci_sanity_check(&pci_direct_conf2)) {
		SyserRestoreFlags(Flags);
		return &pci_direct_conf2;
	}
	SyserRestoreFlags(Flags);
	return NULL;
}


#endif

