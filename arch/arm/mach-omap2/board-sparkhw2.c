/*
 * linux/arch/arm/mach-omap2/board-sparkhw2.c
 *
 * Copyright (C) 2010 PASCO scientific
 * Laine Walker-Avina <lwalkera@pasco.com>
 *
 * Modified from mach-omap2/board-omap3beagle.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "board_sparkhw2: " fmt

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>

#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <plat/board.h>
#include <plat/common.h>
#include <plat/gpmc.h>
#include <plat/nand.h>
#include <plat/usb.h>
#include <plat/timer-gp.h>
#include <plat/display.h>

#include "mux.h"
#include "hsmmc.h"

#include "sdram-micron-mt46h16m32lf-6.h"

static struct omap2_hsmmc_info mmc[] = {
	{
		.mmc		= 1,
		.wires		= 4,
		.gpio_cd	= -EINVAL,
		.gpio_wp	= -EINVAL,
		.nonremovable = true,
	},
	{}	/* Terminator */
};

static struct omap_dss_device spark_hw2_lcd_device = {
	.name				= "lcd",
	.driver_name		= "generic_panel",
	.type				= OMAP_DISPLAY_TYPE_DPI,
	.phy.dpi.data_lines	= 24,
	.reset_gpio			= -EINVAL,
};

static struct omap_dss_device *spark_hw2_dss_devices[] = {
	&spark_hw2_lcd_device,
};

static struct omap_dss_board_info spark_hw2_dss_data = {
	.num_devices	= ARRAY_SIZE(spark_hw2_dss_devices),
	.devices	= spark_hw2_dss_devices,
	.default_device	= &spark_hw2_lcd_device,
};

static struct platform_device spark_hw2_dss_device = {
	.name		= "omapdss",
	.id		= -1,
	.dev		= {
		.platform_data = &spark_hw2_dss_data,
	},
};

static struct omap_lcd_config spark_hw2_lcd_config __initdata = {
	.ctrl_name	= "internal",
};

static struct regulator_consumer_supply spark_hw2_vmmc_supply[] = {
	REGULATOR_SUPPLY("vmmc", "mmci-omap-hs.0"),
	REGULATOR_SUPPLY("vmmc_aux", "mmci-omap-hs.0"),
};

/*
static struct regulator_consumer_supply spark_hw2_vdds_supply[] = {
	{ .supply = "vddio" },
	{ .supply = "vsram" },
	{ .supply = "vmem" },
};

static struct regulator_consumer_supply spark_hw2_vcore_supply = {
	.supply = "vcore",
};

static struct regulator_consumer_supply spark_hw2_vmpu_supply = {
	.supply = "vmpu",
};

static struct regulator_consumer_supply spark_hw2_vdpll_supply[] = {
	{ .supply = "dpll1" },
	{ .supply = "dpll2" },
	{ .supply = "dpll3" },
	{ .supply = "dpll4" },
	{ .supply = "dpll5" },
};

static struct regulator_init_data spark_hw2_tps65023_data[] = {
	{
		.constraints = {
			.name			= "VDCDC1", //Vmpu 1.2v nom
			.min_uV			= 1060000,
			.max_uV			= 1350000,
			.valid_modes_mask	= REGULATOR_MODE_FAST,
			.valid_ops_mask		= REGULATOR_CHANGE_STATUS  |
			                      REGULATOR_CHANGE_VOLTAGE |
								  REGULATOR_CHANGE_MODE,
		},
		.num_consumer_supplies	= 1,
		.consumer_supplies		= &spark_hw2_vmpu_supply,
	},
	{
		.constraints = {
			.name			= "VDCDC2", //Vcore 1.15v nom
			.min_uV			= 1150000,
			.max_uV			= 1150000,
			.valid_modes_mask	= REGULATOR_MODE_NORMAL,
			.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies	= 1,
		.consumer_supplies		= &spark_hw2_vcore_supply,
	},
	{
		.constraints = {
			.name			= "VDCDC3", //1.8v sys
			.min_uV			= 1800000,
			.max_uV			= 1800000,
			.valid_modes_mask	= REGULATOR_MODE_NORMAL,
			.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies	= ARRAY_SIZE(spark_hw2_vdds_supply),
		.consumer_supplies		= spark_hw2_vdds_supply,
	},
	{
		.constraints = {
			.name			= "LDO1", //1.8v dpll
			.min_uV			= 1800000,
			.max_uV			= 1800000,
			.valid_modes_mask	= REGULATOR_MODE_NORMAL,
			.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies	= ARRAY_SIZE(spark_hw2_vdpll_supply),
		.consumer_supplies		= spark_hw2_vdpll_supply,
	},
	{
		.constraints = {
			.name			= "LDO2", //3.3v mmc1/mmc1a
			.min_uV			= 3300000,
			.max_uV			= 3300000,
			.valid_modes_mask	= REGULATOR_MODE_NORMAL,
			.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies	= ARRAY_SIZE(spark_hw2_vmmc_supply),
		.consumer_supplies	= spark_hw2_vmmc_supply,
	},

};

static struct i2c_board_info __initdata spark_hw2_i2c_boardinfo[] = {
	{
		I2C_BOARD_INFO("tps65023", 0x48),
		.flags = I2C_CLIENT_WAKE,
		.platform_data = &spark_hw2_tps65023_data,
	},
};

static int __init spark_hw2_i2c_init(void)
{
	omap_register_i2c_bus(1, 400, spark_hw2_i2c_boardinfo,
			ARRAY_SIZE(spark_hw2_i2c_boardinfo));
	return 0;
}
*/

static struct regulator_init_data spark_hw2_mmc_reg_initdata = {
	.constraints = {
		.name			= "vMMC", //3.3v mmc1/mmc1a
		.min_uV			= 3300000,
		.max_uV			= 3300000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL,
		.valid_ops_mask		= 0,
	},
	.num_consumer_supplies	= ARRAY_SIZE(spark_hw2_vmmc_supply),
	.consumer_supplies	= spark_hw2_vmmc_supply,
};

static struct fixed_voltage_config spark_hw2_fixed1 = {
	.supply_name = "3.3V",
	.microvolts = 3300000,
	.enabled_at_boot = true,
	.init_data = &spark_hw2_mmc_reg_initdata,
};

static struct platform_device regulator_devices[] = {
	{
		.name = "reg-fixed-voltage",
		.id = 1,
		.dev = {
			.platform_data = &spark_hw2_fixed1,
		},
	},
};


#if 0
static struct gpio_led gpio_leds[] = {
	{
		.name			= "beagleboard::usr0",
		.default_trigger	= "heartbeat",
		.gpio			= 150,
	},
	{
		.name			= "beagleboard::usr1",
		.default_trigger	= "mmc0",
		.gpio			= 149,
	},
	{
		.name			= "beagleboard::pmu_stat",
		.gpio			= -EINVAL,	/* gets replaced */
		.active_low		= true,
	},
};


static struct gpio_led_platform_data gpio_led_info = {
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
};

static struct platform_device leds_gpio = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &gpio_led_info,
	},
};

static struct gpio_keys_button gpio_buttons[] = {
	{
		.code			= BTN_EXTRA,
		.gpio			= 7,
		.desc			= "user",
		.wakeup			= 1,
	},
};

static struct gpio_keys_platform_data gpio_key_info = {
	.buttons	= gpio_buttons,
	.nbuttons	= ARRAY_SIZE(gpio_buttons),
};

static struct platform_device keys_gpio = {
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= {
		.platform_data	= &gpio_key_info,
	},
};
#endif

static struct platform_device spark_hw2_otg_ulpi_xceiv = {
	.name = "nop_usb_xceiv",
	.id = -1,
};

static struct platform_device *spark_hw2_devices[] __initdata = {
	&spark_hw2_dss_device,
	&regulator_devices[0],
	&spark_hw2_otg_ulpi_xceiv,
#if 0
	&leds_gpio,
	&keys_gpio,
#endif
};

static struct omap_board_config_kernel spark_hw2_config[] __initdata = {
	{ OMAP_TAG_LCD,		&spark_hw2_lcd_config },
};

static void __init spark_hw2_init_irq(void)
{
	omap_board_config = spark_hw2_config;
	omap_board_config_size = ARRAY_SIZE(spark_hw2_config);
	omap2_init_common_hw(mt46h16m32lf6_sdrc_params,
			     mt46h16m32lf6_sdrc_params);
	omap_init_irq();
#ifdef CONFIG_OMAP_32K_TIMER
	omap2_gp_clockevent_set_gptimer(12);
#endif
	omap_gpio_init();
}

static void __init spark_hw2_init_extclks(void)
{
	struct clk * outclk;
	struct clk * outclk2;

	/* Reparent clkout2 to 96M_FCK */
	outclk = clk_get(NULL, "clkout2_src_ck");
	if(outclk < 0) {
		pr_err("couldn't get clkout2_src_ck\n");
		return;
	}
	outclk2 = clk_get(NULL, "cm_96m_fck");
	if(outclk2 < 0)	{
		pr_err("couldn't get cm_96m_fck\n");
		return;
	}
	if(clk_set_parent(outclk, outclk2) < 0) {
		pr_err("couldn't reparent clkout2_src_ck\n");
		return;
	}

	/* Set clkout2 to 24MHz for internal usb hub*/
	outclk = clk_get(NULL, "sys_clkout2");
	if(outclk < 0) {
		pr_err("couldn't get sys_clkout2\n");
		return;
	}
	if(clk_set_rate(outclk, 24000000) < 0) {
		pr_err("couldn't set sys_clkout2 rate\n");
		return;
	}
	if(clk_enable(outclk) < 0) {
		pr_err("couldn't enable sys_clkout2\n");
		return;
	}

	/* Enable clkout1, which should be sys_clk @ 12MHz */
	outclk = clk_get(NULL, "sys_clkout1");
	if(outclk < 0) {
		pr_err("couldn't get sys_clkout1\n");
		return;
	}
	if(clk_enable(outclk) < 0) {
		pr_err("couldn't enable sys_clkout1\n");
		return;
	}

	pr_debug("setup output clocks successfully\n");
}

static void __init spark_hw2_init_gpmc(void)
{
	unsigned long cs_mem_base;
	struct gpmc_timings timings = {
		.cs_on		= 50,
		.cs_rd_off	= 250,
		.cs_wr_off	= 250,

		.we_on		= 50,
		.we_off		= 250,

		.oe_on		= 50,
		.oe_off		= 250,

		.access		= 166,
		.wr_access	= 166,

		.rd_cycle	= 373,
		.wr_cycle	= 373,
	};

	/*Setup CONFIG1 as 16-bit, async, non-muxed, with all times x2*/
	gpmc_cs_write_reg(0, GPMC_CS_CONFIG1,
			GPMC_CONFIG1_DEVICESIZE_16 | GPMC_CONFIG1_TIME_PARA_GRAN);

	if(gpmc_cs_set_timings(0, &timings) < 0)
	{
		pr_err("Failed to set GPMC timings\n");
		return;
	}

	if (gpmc_cs_request(0, SZ_16M, &cs_mem_base) < 0) {
		pr_err("Failed to request GPMC mem\n");
		return;
	}
	/* Disable prefetch and disable cacheing*/
	gpmc_prefetch_reset();

	pr_debug("GPMC enabled, CS0 at 0x%08lx\n", cs_mem_base);
}

static const struct ehci_hcd_omap_platform_data ehci_pdata __initconst = {
	.port_mode[0] = EHCI_HCD_OMAP_MODE_UNKNOWN,
	.port_mode[1] = EHCI_HCD_OMAP_MODE_UNKNOWN,
	.port_mode[2] = EHCI_HCD_OMAP_MODE_UNKNOWN,

	.phy_reset  = false,
};

#ifdef CONFIG_OMAP_MUX
static struct omap_board_mux board_mux[] __initdata = {
/* HSUSB2 */
	OMAP3_MUX(ETK_D10,     OMAP_MUX_MODE3 | OMAP_PIN_OUTPUT),
	/*HSUSB2_CLK*/
	OMAP3_MUX(ETK_D11,     OMAP_MUX_MODE3 | OMAP_PIN_OUTPUT),
	/*HSUSB2_STP*/
	OMAP3_MUX(ETK_D12,     OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_DIR*/
	OMAP3_MUX(ETK_D13,     OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_NXT*/
	OMAP3_MUX(ETK_D14,     OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D0*/
	OMAP3_MUX(ETK_D15,     OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D1*/
	OMAP3_MUX(MCSPI1_CS3,  OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D2*/
	OMAP3_MUX(MCSPI2_CS1,  OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D3*/
	OMAP3_MUX(MCSPI2_SIMO, OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D4*/
	OMAP3_MUX(MCSPI2_SOMI, OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D5*/
	OMAP3_MUX(MCSPI2_CS0,  OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D6*/
	OMAP3_MUX(MCSPI2_CLK,  OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	/*HSUSB2_D7*/
	{ .reg_offset = OMAP_MUX_TERMINATOR },
};
#else
#define board_mux	NULL
#endif

static struct omap_musb_board_data musb_board_data = {
	.interface_type		= MUSB_INTERFACE_ULPI,
	.mode				= MUSB_PERIPHERAL,
	.power				= 100,
};

static void __init spark_hw2_init(void)
{
	omap3_mux_init(board_mux, OMAP_PACKAGE_CUS);
	//spark_hw2_i2c_init();
	platform_add_devices(spark_hw2_devices,
			ARRAY_SIZE(spark_hw2_devices));
	omap_serial_init();

	spark_hw2_init_extclks();
	spark_hw2_init_gpmc();

	usb_musb_init(&musb_board_data);
	usb_ehci_init(&ehci_pdata);
	omap2_hsmmc_init(mmc);

	/* Ensure SDRC pins are mux'd for self-refresh */
	omap_mux_init_signal("sdrc_cke0", OMAP_PIN_OUTPUT);

	// Init Spark FPGA IRQ and FPGA JTAG I/O
	omap_mux_init_gpio( 55, OMAP_PIN_INPUT_PULLUP );
	gpio_request( 55, "pasport-irq" );
	gpio_direction_input( 55 );

	omap_mux_init_gpio( 106, OMAP_PIN_INPUT_PULLUP );
	omap_mux_init_gpio( 107, OMAP_PIN_INPUT_PULLUP );
	omap_mux_init_gpio( 108, OMAP_PIN_INPUT_PULLUP );
	omap_mux_init_gpio( 109, OMAP_PIN_INPUT_PULLUP );
	omap_mux_init_gpio( 110, OMAP_PIN_INPUT_PULLUP );
}


static void __init spark_hw2_map_io(void)
{
	omap2_set_globals_343x();
	omap34xx_map_common_io();
}

MACHINE_START(SPARK_SLS_HW2, "PASCO scientific SPARKsls HW2")
	/* Maintainer: Laine Walker-Avina <lwalkera@pasco.com> */
	.phys_io		= 0x48000000,
	.io_pg_offst	= ((0xfa000000) >> 18) & 0xfffc,
	.boot_params	= 0x80000100,
	.map_io			= spark_hw2_map_io,
	.init_irq		= spark_hw2_init_irq,
	.init_machine	= spark_hw2_init,
	.timer			= &omap_timer,
MACHINE_END
