/*
 * SDRC register values for the Numonyx M65KXXXXAM
 *
 * Copyright (C) 2009 Integration Software and Electronic Engineering.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ARCH_ARM_MACH_OMAP2_SDRAM_NUMONYX_M65KXXXXAM
#define __ARCH_ARM_MACH_OMAP2_SDRAM_NUMONYX_M65KXXXXAM

#include <plat/sdrc.h>

/* Numonyx  M65KXXXXAM */
static struct omap_sdrc_params m65kxxxxam_sdrc_params[] = {
	[0] = {
		.rate        = 200000000,
		.actim_ctrla = ACTIM_TRFC(28) | ACTIM_TRC(12) | ACTIM_TRAS(8) |
			ACTIM_TRP(3) | ACTIM_TRCD(1) | ACTIM_TRRD(2) | ACTIM_TDPL(3) |
			ACTIM_TDAL(6),
		.actim_ctrlb = ACTIM_TWTR(2) | ACTIM_TCKE(2) | ACTIM_TXP(3) |
			ACTIM_TXSR(40),
		.rfr_ctrl    = RFR_CTRL_ARCV(1510) | RFR_CTRL_ARE(1),
		.mr          = MR_WBST(0) | MR_CASL(3) | MR_BL(2),
	},
	[1] = {
		.rate        = 166000000,
		.actim_ctrla = ACTIM_TRFC(23) | ACTIM_TRC(10) | ACTIM_TRAS(7) |
			ACTIM_TRP(3) | ACTIM_TRCD(0) | ACTIM_TRRD(2) | ACTIM_TDPL(2) |
			ACTIM_TDAL(5),
		.actim_ctrlb = ACTIM_TWTR(2) | ACTIM_TCKE(2) | ACTIM_TXP(3) |
			ACTIM_TXSR(33),
		.rfr_ctrl    = RFR_CTRL_ARCV(1244) | RFR_CTRL_ARE(1),
		.mr          = MR_WBST(0) | MR_CASL(3) | MR_BL(2),
	},
	[2] = {
		.rate        = 133000000,
		.actim_ctrla = ACTIM_TRFC(19) | ACTIM_TRC(8) | ACTIM_TRAS(6) |
			ACTIM_TRP(3) | ACTIM_TRCD(3) | ACTIM_TRRD(2) | ACTIM_TDPL(2) |
			ACTIM_TDAL(5),
		.actim_ctrlb = ACTIM_TWTR(2) | ACTIM_TCKE(2) | ACTIM_TXP(3) |
			ACTIM_TXSR(27),
		.rfr_ctrl    = RFR_CTRL_ARCV(990) | RFR_CTRL_ARE(1),
		.mr          = MR_WBST(0) | MR_CASL(3) | MR_BL(2),
	},
	[3] = {
		.rate        = 83000000,
		.actim_ctrla = ACTIM_TRFC(11) | ACTIM_TRC(5) | ACTIM_TRAS(3) |
			ACTIM_TRP(1) | ACTIM_TRCD(2) | ACTIM_TRRD(1) | ACTIM_TDPL(1) |
			ACTIM_TDAL(2),
		.actim_ctrlb = ACTIM_TWTR(2) | ACTIM_TCKE(2) | ACTIM_TXP(3) |
			ACTIM_TXSR(16),
		.rfr_ctrl    = RFR_CTRL_ARCV(597) | RFR_CTRL_ARE(1),
		.mr          = MR_WBST(0) | MR_CASL(3) | MR_BL(2),
	},
	[4] = {
		.rate			= 0
	},
};

#endif
