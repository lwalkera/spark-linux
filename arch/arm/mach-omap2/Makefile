#
# Makefile for the linux kernel.
#

# Common support
obj-y := id.o io.o control.o mux.o devices.o serial.o gpmc.o timer-gp.o pm.o \
	 common.o gpio.o dma.o wd_timer.o

omap-2-3-common				= irq.o sdrc.o
hwmod-common				= omap_hwmod.o \
					  omap_hwmod_common_data.o
clock-common				= clock.o clock_common_data.o \
					  clkt_dpll.o clkt_clksel.o

obj-$(CONFIG_ARCH_OMAP2) += $(omap-2-3-common) $(hwmod-common)
obj-$(CONFIG_ARCH_OMAP3) += $(omap-2-3-common) $(hwmod-common)
obj-$(CONFIG_ARCH_OMAP4) += prm44xx.o $(hwmod-common)
obj-$(CONFIG_ARCH_TI81XX) += $(omap-2-3-common) $(hwmod-common)

obj-$(CONFIG_OMAP_MCBSP) += mcbsp.o

obj-$(CONFIG_TWL4030_CORE)		+= omap_twl.o
obj-$(CONFIG_REGULATOR_TPS65023)	+= pmic_tps65023.o

# SMP support ONLY available for OMAP4
obj-$(CONFIG_SMP)			+= omap-smp.o omap-headsmp.o
obj-$(CONFIG_LOCAL_TIMERS)		+= timer-mpu.o
obj-$(CONFIG_HOTPLUG_CPU)		+= omap-hotplug.o
obj-$(CONFIG_ARCH_OMAP4)		+= omap44xx-smc.o omap4-common.o

plus_sec := $(call as-instr,.arch_extension sec,+sec)
AFLAGS_omap-headsmp.o			:=-Wa,-march=armv7-a$(plus_sec)
AFLAGS_omap44xx-smc.o			:=-Wa,-march=armv7-a$(plus_sec)

# Functions loaded to SRAM
obj-$(CONFIG_ARCH_OMAP2420)		+= sram242x.o
obj-$(CONFIG_ARCH_OMAP2430)		+= sram243x.o
obj-$(CONFIG_ARCH_OMAP3)		+= sram34xx.o

AFLAGS_sram242x.o			:=-Wa,-march=armv6
AFLAGS_sram243x.o			:=-Wa,-march=armv6
AFLAGS_sram34xx.o			:=-Wa,-march=armv7-a

# Pin multiplexing
obj-$(CONFIG_ARCH_OMAP2420)		+= mux2420.o
obj-$(CONFIG_ARCH_OMAP2430)		+= mux2430.o
obj-$(CONFIG_ARCH_OMAP3)		+= mux34xx.o
obj-$(CONFIG_ARCH_OMAP4)		+= mux44xx.o
obj-$(CONFIG_ARCH_TI81XX)		+= mux81xx.o

# SMS/SDRC
obj-$(CONFIG_ARCH_OMAP2)		+= sdrc2xxx.o
# obj-$(CONFIG_ARCH_OMAP3)		+= sdrc3xxx.o

# OPP table initialization
ifeq ($(CONFIG_PM_OPP),y)
obj-y					+= opp.o
obj-$(CONFIG_ARCH_OMAP3)		+= opp3xxx_data.o
obj-$(CONFIG_ARCH_OMAP4)		+= opp4xxx_data.o
endif

# Power Management
ifeq ($(CONFIG_PM),y)
obj-$(CONFIG_ARCH_OMAP2)		+= pm24xx.o
obj-$(CONFIG_ARCH_OMAP2)		+= sleep24xx.o pm_bus.o voltage.o
obj-$(CONFIG_ARCH_OMAP3)		+= pm34xx.o sleep34xx.o sleep3517.o voltage.o \
					   cpuidle34xx.o pm_bus.o
obj-$(CONFIG_ARCH_OMAP4)		+= pm44xx.o voltage.o pm_bus.o
obj-$(CONFIG_ARCH_TI81XX)		+= voltage.o pm_bus.o
obj-$(CONFIG_PM_DEBUG)			+= pm-debug.o
obj-$(CONFIG_OMAP_SMARTREFLEX)          += sr_device.o smartreflex.o
obj-$(CONFIG_OMAP_SMARTREFLEX_CLASS3)	+= smartreflex-class3.o
obj-$(CONFIG_SMARTREFLEX_CLASS2)	+= smartreflex-class2.o

AFLAGS_sleep24xx.o			:=-Wa,-march=armv6
AFLAGS_sleep34xx.o			:=-Wa,-march=armv7-a
AFLAGS_sleep3517.o			:=-Wa,-march=armv7-a

ifeq ($(CONFIG_PM_VERBOSE),y)
CFLAGS_pm_bus.o				+= -DDEBUG
endif

endif

# PRCM
obj-$(CONFIG_ARCH_OMAP2)		+= prcm.o cm2xxx_3xxx.o prm2xxx_3xxx.o
obj-$(CONFIG_ARCH_OMAP3)		+= prcm.o cm2xxx_3xxx.o prm2xxx_3xxx.o
# XXX The presence of cm2xxx_3xxx.o on the line below is temporary and
# will be removed once the OMAP4 part of the codebase is converted to
# use OMAP4-specific PRCM functions.
obj-$(CONFIG_ARCH_OMAP4)		+= prcm.o cm2xxx_3xxx.o cminst44xx.o \
					   cm44xx.o prcm_mpu44xx.o \
					   prminst44xx.o
obj-$(CONFIG_ARCH_TI81XX)		+= prcm.o cm2xxx_3xxx.o prm2xxx_3xxx.o \
					   cm81xx.o

# OMAP powerdomain framework
powerdomain-common			+= powerdomain.o powerdomain-common.o
obj-$(CONFIG_ARCH_OMAP2)		+= $(powerdomain-common) \
					   powerdomain2xxx_3xxx.o \
					   powerdomains2xxx_data.o \
					   powerdomains2xxx_3xxx_data.o
obj-$(CONFIG_ARCH_OMAP3)		+= $(powerdomain-common) \
					   powerdomain2xxx_3xxx.o \
					   powerdomains3xxx_data.o \
					   powerdomains2xxx_3xxx_data.o
obj-$(CONFIG_ARCH_OMAP4)		+= $(powerdomain-common) \
					   powerdomain44xx.o \
					   powerdomains44xx_data.o
obj-$(CONFIG_ARCH_TI81XX)		+= $(powerdomain-common) \
					   powerdomain2xxx_3xxx.o \
					   powerdomains3xxx_data.o \
					   powerdomains2xxx_3xxx_data.o

# PRCM clockdomain control
obj-$(CONFIG_ARCH_OMAP2)		+= clockdomain.o \
					   clockdomains2xxx_3xxx_data.o
obj-$(CONFIG_ARCH_OMAP3)		+= clockdomain.o \
					   clockdomains2xxx_3xxx_data.o
obj-$(CONFIG_ARCH_OMAP4)		+= clockdomain.o \
					   clockdomains44xx_data.o
obj-$(CONFIG_ARCH_TI81XX)		+= clockdomain.o \
					   clockdomains2xxx_3xxx_data.o
# Clock framework
obj-$(CONFIG_ARCH_OMAP2)		+= $(clock-common) clock2xxx.o \
					   clkt2xxx_sys.o \
					   clkt2xxx_dpllcore.o \
					   clkt2xxx_virt_prcm_set.o \
					   clkt2xxx_apll.o clkt2xxx_osc.o
obj-$(CONFIG_ARCH_OMAP2420)		+= clock2420_data.o
obj-$(CONFIG_ARCH_OMAP2430)		+= clock2430.o clock2430_data.o
obj-$(CONFIG_ARCH_OMAP3)		+= $(clock-common) clock3xxx.o \
					   clock34xx.o clkt34xx_dpll3m2.o \
					   clock3517.o clock36xx.o \
					   dpll3xxx.o clock3xxx_data.o
obj-$(CONFIG_ARCH_OMAP4)		+= $(clock-common) clock44xx_data.o \
					   dpll3xxx.o
obj-$(CONFIG_ARCH_TI81XX)		+= $(clock-common) clock816x_data.o \
					   clock814x_data.o clock81xx.o ti81xx_fb.o

# OMAP2 clock rate set data (old "OPP" data)
obj-$(CONFIG_ARCH_OMAP2420)		+= opp2420_data.o
obj-$(CONFIG_ARCH_OMAP2430)		+= opp2430_data.o

# hwmod data
obj-$(CONFIG_ARCH_OMAP2420)		+= omap_hwmod_2420_data.o
obj-$(CONFIG_ARCH_OMAP2430)		+= omap_hwmod_2430_data.o
obj-$(CONFIG_ARCH_OMAP3)		+= omap_hwmod_3xxx_data.o
obj-$(CONFIG_ARCH_OMAP4)		+= omap_hwmod_44xx_data.o
obj-$(CONFIG_ARCH_TI81XX)		+= omap_hwmod_81xx_data.o

# EMU peripherals
obj-$(CONFIG_OMAP3_EMU)			+= emu.o

obj-$(CONFIG_OMAP_MBOX_FWK)		+= mailbox_mach.o
mailbox_mach-objs			:= mailbox.o

obj-$(CONFIG_OMAP_IOMMU)		+= iommu2.o

iommu-$(CONFIG_OMAP_IOMMU)		:= omap-iommu.o
obj-y					+= $(iommu-m) $(iommu-y)

i2c-omap-$(CONFIG_I2C_OMAP)		:= i2c.o
obj-y					+= $(i2c-omap-m) $(i2c-omap-y)

ifneq ($(CONFIG_TIDSPBRIDGE),)
obj-y					+= dsp.o
endif

obj-$(CONFIG_PCI)                       += pcie-ti816x.o

ifeq ($(CONFIG_PCI_DEBUG),y)
CFLAGS_pcie-ti816x.o += -DDEBUG
endif

# Specific board support
obj-$(CONFIG_MACH_OMAP_GENERIC)		+= board-generic.o
obj-$(CONFIG_MACH_OMAP_H4)		+= board-h4.o
obj-$(CONFIG_MACH_OMAP_2430SDP)		+= board-2430sdp.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP_APOLLON)		+= board-apollon.o
obj-$(CONFIG_MACH_OMAP3_BEAGLE)		+= board-omap3beagle.o \
					   board-flash.o \
					   hsmmc.o
obj-$(CONFIG_MACH_SPARK_SLS_HW2)	+= board-sparkhw2.o \
					   hsmmc.o
obj-$(CONFIG_MACH_DEVKIT8000)     	+= board-devkit8000.o \
                                           hsmmc.o
obj-$(CONFIG_MACH_OMAP_LDP)		+= board-ldp.o \
					   board-flash.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP3530_LV_SOM)      += board-omap3logic.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP3_TORPEDO)        += board-omap3logic.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OVERO)		+= board-overo.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP3EVM)		+= board-omap3evm.o \
					   hsmmc.o \
					   board-flash.o
obj-$(CONFIG_MACH_OMAP3_PANDORA)	+= board-omap3pandora.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP_3430SDP)		+= board-3430sdp.o \
					   hsmmc.o \
					   board-flash.o
obj-$(CONFIG_MACH_NOKIA_N8X0)		+= board-n8x0.o
obj-$(CONFIG_MACH_NOKIA_RM680)		+= board-rm680.o \
					   sdram-nokia.o \
					   hsmmc.o
obj-$(CONFIG_MACH_NOKIA_RX51)		+= board-rx51.o \
					   sdram-nokia.o \
					   board-rx51-peripherals.o \
					   board-rx51-video.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP_ZOOM2)		+= board-zoom.o \
					   board-zoom-peripherals.o \
					   board-flash.o \
					   hsmmc.o \
					   board-zoom-debugboard.o
obj-$(CONFIG_MACH_OMAP_ZOOM3)		+= board-zoom.o \
					   board-zoom-peripherals.o \
					   board-flash.o \
					   hsmmc.o \
					   board-zoom-debugboard.o
obj-$(CONFIG_MACH_OMAP_3630SDP)		+= board-3630sdp.o \
					   board-zoom-peripherals.o \
					   board-flash.o \
					   hsmmc.o
obj-$(CONFIG_MACH_CM_T35)		+= board-cm-t35.o \
					   hsmmc.o
obj-$(CONFIG_MACH_CM_T3517)		+= board-cm-t3517.o
obj-$(CONFIG_MACH_IGEP0020)		+= board-igep0020.o \
					   hsmmc.o
obj-$(CONFIG_MACH_IGEP0030)		+= board-igep0030.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP3_TOUCHBOOK)	+= board-omap3touchbook.o \
					   hsmmc.o
obj-$(CONFIG_MACH_OMAP_4430SDP)		+= board-4430sdp.o \
					   hsmmc.o \
					   omap_phy_internal.o
obj-$(CONFIG_MACH_OMAP4_PANDA)		+= board-omap4panda.o \
					   hsmmc.o \
					   omap_phy_internal.o

obj-$(CONFIG_MACH_OMAP3517EVM)		+= board-am3517evm.o \
					   board-flash.o \
					   hsmmc.o

obj-$(CONFIG_MACH_CRANEBOARD)		+= board-am3517crane.o

obj-$(CONFIG_MACH_SBC3530)		+= board-omap3stalker.o \
					   hsmmc.o
obj-$(CONFIG_MACH_TI8148EVM)		+= board-ti8148evm.o \
					   hsmmc.o \
					   board-flash.o
obj-$(CONFIG_MACH_TI8168EVM)		+= board-ti8168evm.o \
					   hsmmc.o \
					   board-flash.o
# Platform specific device init code
usbfs-$(CONFIG_ARCH_OMAP_OTG)		:= usb-fs.o
obj-y					+= $(usbfs-m) $(usbfs-y)
obj-y					+= usb-musb.o
obj-$(CONFIG_MACH_OMAP2_TUSB6010)	+= usb-tusb6010.o
obj-y					+= usb-ehci.o

onenand-$(CONFIG_MTD_ONENAND_OMAP2)	:= gpmc-onenand.o
obj-y					+= $(onenand-m) $(onenand-y)

nand-$(CONFIG_MTD_NAND_OMAP2)		:= gpmc-nand.o
obj-y					+= $(nand-m) $(nand-y)

smc91x-$(CONFIG_SMC91X)			:= gpmc-smc91x.o
obj-y					+= $(smc91x-m) $(smc91x-y)

smsc911x-$(CONFIG_SMSC911X)		:= gpmc-smsc911x.o
obj-y					+= $(smsc911x-m) $(smsc911x-y)

ifeq ($(CONFIG_MACH_OMAP3_BEAGLE),y)
beagle-camera-$(CONFIG_VIDEO_OMAP3)	:= board-omap3beagle-camera.o
obj-y					+= $(beagle-camera-m) $(beagle-camera-y)
endif

ifeq ($(CONFIG_MACH_OMAP3EVM),y)
evm-camera-$(CONFIG_VIDEO_OMAP3)	:= board-omap3evm-camera.o
obj-y					+= $(evm-camera-m) $(evm-camera-y)
endif
