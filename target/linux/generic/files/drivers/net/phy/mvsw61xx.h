/*
 * Marvell 88E61xx switch driver
 *
 * Copyright (c) 2014 Claudio Leite <leitec@staticky.com>
 * Copyright (c) 2014 Nikita Nazarenko <nnazarenko@radiofid.com>
 *
 * Based on code (c) 2008 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License v2 as published by the
 * Free Software Foundation
 */

#ifndef __MVSW61XX_H
#define __MVSW61XX_H

#define MV_PORTS			7
#define MV_PORTS_MASK			((1 << MV_PORTS) - 1)

#define MV_BASE				0x10

#define MV_SWITCHPORT_BASE		0x10
#define MV_SWITCHPORT(_n)		(MV_SWITCHPORT_BASE + (_n))
#define MV_SWITCHREGS			(MV_BASE + 0xb)

#define MV_VLANS			64
#define MV_MAX_VLAN			4096

enum {
	MVSW61XX_COUNTER_IN = 0x0,
	MVSW61XX_COUNTER_OUT = 0x1,
	MVSW61XX_COUNTER_HISTOGRAM = 0x2
};

struct mvsw61xx_counter {
	u8 type; // 1 - in, 2 - out, 3 - histogram
	u8 ptr; // number written to statsptr
	u8 len; // some counters may contain more than one field
	char* name; // counter name
};

struct mv_link_event {
	u8 port;
	u16 link;
	u16 duplex;
	u16 speed;
	struct sk_buff *skb;
	struct work_struct work;
};

enum {
	MV_PORT_STATUS			= 0x00,
	MV_PORT_PHYCTL			= 0x01,
	MV_PORT_JAMCTL			= 0x02,
	MV_PORT_IDENT			= 0x03,
	MV_PORT_CONTROL			= 0x04,
	MV_PORT_CONTROL1		= 0x05,
	MV_PORT_VLANMAP			= 0x06,
	MV_PORT_VLANID			= 0x07,
	MV_PORT_CONTROL2		= 0x08,
	MV_PORT_ASSOC			= 0x0b,
	MV_PORT_RX_DISCARD_LOW		= 0x10,
	MV_PORT_RX_DISCARD_HIGH		= 0x11,
	MV_PORT_IN_FILTERED		= 0x12,
	MV_PORT_OUT_ACCEPTED		= 0x13,
	MV_PORT_LED_CONTROL		= 0x16,
};
#define MV_PORTREG(_type, _port) MV_SWITCHPORT(_port), MV_PORT_##_type

enum {
	MV_PHY_CONTROL 				= 0x00,
	MV_PHY_STATUS				= 0x01,
	MV_PHY_ID_1				= 0x02,
	MV_PHY_ID_2				= 0x03,
	MV_PHY_AUTONEG_ADV			= 0x04,
	MV_PHY_LINK_PARTNER_ABILITY		= 0x05,
	MV_PHY_AUTONEG_EXPANSION		= 0x06,
	MV_PHY_NEXT_PAGE_TRANSMIT		= 0x07,
	MV_PHY_LINK_PARTNER_NEXT_PAGE		= 0x08,
	MV_PHY_MASTER_SLAVE_CONTROL		= 0x09,
	MV_PHY_MASTER_SLAVE_STATUS		= 0x0A,
	MV_PHY_EXTENDED_STATUS 			= 0x0F,
	MV_PHY_SPECIFIC_CONTROL_1		= 0x10,
	MV_PHY_SPECIFIC_STATUS_1		= 0x11,
	MV_PHY_INTERRUPT_ENABLE			= 0x12,
	MV_PHY_SPECIFIC_STATUS_2		= 0x13,
	MV_PHY_SPECIFIC_STATUS_3		= 0x14,
	MV_PHY_RECIEVE_ERROR_COUNTER		= 0x15,
	MV_PHY_PAGE_REGISTER			= 0x16,
	MV_PHY_INTERRUPT_STATUS			= 0x17,
	MV_PHY_PAGE_SPECIFIC_1			= 0x18,
	MV_PHY_PAGE_SPECIFIC_2			= 0x19,
	MV_PHY_PAGE_SPECIFIC_3			= 0x1A,
	MV_PHY_PAGE_SPECIFIC_4			= 0x1B,
	MV_PHY_PAGE_SPECIFIC_5			= 0x1C
};

#define MV_PHYREG(_type, _port) _port, MV_PHY_##_type

enum {
	MV_PORT_STATUS_FDX		= (1 << 10),
	MV_PORT_STATUS_LINK		= (1 << 11),
};

enum {
	MV_PORT_STATUS_SPEED_10		= 0x00,
	MV_PORT_STATUS_SPEED_100	= 0x01,
	MV_PORT_STATUS_SPEED_1000	= 0x02,
	MV_PORT_STATUS_SPEED_AUTO	= 0x03,
};
#define MV_PORT_STATUS_SPEED_SHIFT	8
#define MV_PORT_STATUS_SPEED_MASK	(3 << 8)

enum {
	MV_PORTCTRL_DISABLED		= (0 << 0),
	MV_PORTCTRL_BLOCKING		= (1 << 0),
	MV_PORTCTRL_LEARNING		= (2 << 0),
	MV_PORTCTRL_FORWARDING		= (3 << 0),
	MV_PORTCTRL_VLANTUN		= (1 << 7),
	MV_PORTCTRL_EGRESS		= (1 << 12),
};

#define MV_PHYCTL_FC_MASK		(3 << 6)

enum {
	MV_PHYCTL_FC_ENABLE		= (3 << 6),
	MV_PHYCTL_FC_DISABLE		= (1 << 6),
};

enum {
	MV_8021Q_EGRESS_UNMODIFIED	= 0x00,
	MV_8021Q_EGRESS_UNTAGGED	= 0x01,
	MV_8021Q_EGRESS_TAGGED		= 0x02,
	MV_8021Q_EGRESS_ADDTAG		= 0x03,
};

#define MV_8021Q_MODE_SHIFT		10
#define MV_8021Q_MODE_MASK		(0x3 << MV_8021Q_MODE_SHIFT)

enum {
	MV_8021Q_MODE_DISABLE		= 0x00,
	MV_8021Q_MODE_FALLBACK		= 0x01,
	MV_8021Q_MODE_CHECK		= 0x02,
	MV_8021Q_MODE_SECURE		= 0x03,
};

enum {
	MV_8021Q_VLAN_ONLY		= (1 << 15),
};

#define MV_PORTASSOC_MONITOR		(1 << 15)

enum {
	MV_SWITCH_ATU_FID0		= 0x01,
	MV_SWITCH_ATU_FID1		= 0x02,
	MV_SWITCH_ATU_SID		= 0x03,
	MV_SWITCH_CTRL			= 0x04,
	MV_SWITCH_ATU_CTRL		= 0x0a,
	MV_SWITCH_ATU_OP		= 0x0b,
	MV_SWITCH_ATU_DATA		= 0x0c,
	MV_SWITCH_ATU_MAC0		= 0x0d,
	MV_SWITCH_ATU_MAC1		= 0x0e,
	MV_SWITCH_ATU_MAC2		= 0x0f,
	MV_SWITCH_GLOBAL		= 0x1b,
	MV_SWITCH_GLOBAL2		= 0x1c,
};
#define MV_SWITCHREG(_type) MV_SWITCHREGS, MV_SWITCH_##_type

enum {
	MV_SWITCHCTL_EEIE		= (1 << 0),
	MV_SWITCHCTL_PHYIE		= (1 << 1),
	MV_SWITCHCTL_ATUDONE		= (1 << 2),
	MV_SWITCHCTL_ATUIE		= (1 << 3),
	MV_SWITCHCTL_CTRMODE		= (1 << 8),
	MV_SWITCHCTL_RELOAD		= (1 << 9),
	MV_SWITCHCTL_MSIZE		= (1 << 10),
	MV_SWITCHCTL_DROP		= (1 << 13),
};

enum {
#define MV_ATUCTL_AGETIME_MIN		16
#define MV_ATUCTL_AGETIME_MAX		4080
#define MV_ATUCTL_AGETIME(_n)		((((_n) / 16) & 0xff) << 4)
	MV_ATUCTL_ATU_256		= (0 << 12),
	MV_ATUCTL_ATU_512		= (1 << 12),
	MV_ATUCTL_ATU_1K		= (2 << 12),
	MV_ATUCTL_ATUMASK		= (3 << 12),
	MV_ATUCTL_NO_LEARN		= (1 << 14),
	MV_ATUCTL_RESET			= (1 << 15),
};

enum {
#define MV_ATUOP_DBNUM(_n)		((_n) & 0x0f)
	MV_ATUOP_NOOP			= (0 << 12),
	MV_ATUOP_FLUSH_ALL		= (1 << 12),
	MV_ATUOP_FLUSH_U		= (2 << 12),
	MV_ATUOP_LOAD_DB		= (3 << 12),
	MV_ATUOP_GET_NEXT		= (4 << 12),
	MV_ATUOP_FLUSH_DB		= (5 << 12),
	MV_ATUOP_FLUSH_DB_UU		= (6 << 12),
	MV_ATUOP_INPROGRESS		= (1 << 15),
};

enum {
	MV_GLOBAL_STATUS		= 0x00,
	MV_GLOBAL_ATU_FID		= 0x01,
	MV_GLOBAL_VTU_FID		= 0x02,
	MV_GLOBAL_VTU_SID		= 0x03,
	MV_GLOBAL_CONTROL		= 0x04,
	MV_GLOBAL_VTU_OP		= 0x05,
	MV_GLOBAL_VTU_VID		= 0x06,
	MV_GLOBAL_VTU_DATA1		= 0x07,
	MV_GLOBAL_VTU_DATA2		= 0x08,
	MV_GLOBAL_VTU_DATA3		= 0x09,
	MV_GLOBAL_CONTROL2		= 0x1c,
	MV_GLOBAL_STAT_CONTROL		= 0x1D,
	MV_GLOBAL_STATHI		= 0x1E,
	MV_GLOBAL_STATLO		= 0x1F,
};
#define MV_GLOBALREG(_type) MV_SWITCH_GLOBAL, MV_GLOBAL_##_type

enum {
	MV_GLOBAL2_INT_SRC		= 0x00,
	MV_GLOBAL2_INT_MASK		= 0x01,
	MV_GLOBAL2_SDET_POLARITY	= 0x1d,
	MV_GLOBAL2_SMI_PHY_CMD		= 0x18,
	MV_GLOBAL2_SMI_PHY_DATA		= 0x19,
};
#define MV_GLOBAL2REG(_type) MV_SWITCH_GLOBAL2, MV_GLOBAL2_##_type

enum {
	MV_VTU_VID_VALID		= (1 << 12),
};

enum {
	MV_VTUOP_PURGE			= (1 << 12),
	MV_VTUOP_LOAD			= (3 << 12),
	MV_VTUOP_INPROGRESS		= (1 << 15),
	MV_VTUOP_STULOAD		= (5 << 12),
	MV_VTUOP_VTU_GET_NEXT		= (4 << 12),
	MV_VTUOP_STU_GET_NEXT		= (6 << 12),
	MV_VTUOP_GET_VIOLATION		= (7 << 12),
};

enum {
	MV_CONTROL_RESET		= (1 << 15),
	MV_CONTROL_PPU_ENABLE		= (1 << 14),
};

enum {
	MV_VTUCTL_EGRESS_UNMODIFIED	= (0 << 0),
	MV_VTUCTL_EGRESS_UNTAGGED	= (1 << 0),
	MV_VTUCTL_EGRESS_TAGGED		= (2 << 0),
	MV_VTUCTL_DISCARD		= (3 << 0),
};

enum {
	MV_STUCTL_STATE_DISABLED	= (0 << 0),
	MV_STUCTL_STATE_BLOCKING	= (1 << 0),
	MV_STUCTL_STATE_LEARNING	= (2 << 0),
	MV_STUCTL_STATE_FORWARDING	= (3 << 0),
};

enum {
	MV_INDIRECT_REG_CMD		= 0,
	MV_INDIRECT_REG_DATA		= 1,
};

enum {
	MV_INDIRECT_INPROGRESS		= 0x8000,
	MV_INDIRECT_WRITE		= 0x9400,
	MV_INDIRECT_READ		= 0x9800,
};
#define MV_INDIRECT_ADDR_S		5

#define MV_IDENT_MASK			0xfff0

#define MV_IDENT_VALUE_6171		0x1710
#define MV_IDENT_STR_6171		"MV88E6171"

#define MV_IDENT_VALUE_6172		0x1720
#define MV_IDENT_STR_6172		"MV88E6172"

#define MV_IDENT_VALUE_6176		0x1760
#define MV_IDENT_STR_6176		"MV88E6176"

#define MV_PVID_MASK			0x0fff

#define MV_FDB_HI_MASK			0x00ff
#define MV_FDB_LO_MASK			0xf000
#define MV_FDB_HI_SHIFT			4
#define MV_FDB_LO_SHIFT			12

struct mvsw61xx_state {
	struct switch_dev dev;
	struct mii_bus *bus;
	int base_addr;
	u16 model;
	u16 last_vlan;

	bool registered;
	bool is_indirect;

	int cpu_port0;
	int cpu_port1;

	int vlan_enabled;
	struct port_state {
		u16 fdb;
		u16 pvid;
		u16 mask;
		u8 qmode;
		u16 link_status;
		u8 reg;
	} ports[MV_PORTS];

	struct vlan_state {
		bool port_based;

		u16 mask;
		u16 vid;
		u32 port_mode;
		u32 port_sstate;
	} vlans[MV_VLANS];

	struct mutex irq_lock;
	int irq;
	int int_gpio;
	struct timer_list link_poll_timer;
	struct work_struct link_poll_work;

	char *buf;
	unsigned int buf_size;
};

#define get_state(_dev) container_of((_dev), struct mvsw61xx_state, dev)

#endif
