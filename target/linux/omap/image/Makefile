#
# Copyright (C) 2012-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

UBIFS_OPTS = -F -m 2048 -e 124KiB -c 4096 -U
UBI_OPTS = -m 2048 -p 128KiB -s 512 -O 2048

define Image/Prepare/Template
	$(CC) -E -nostdinc -I$(DTS_DIR) -I$(DTS_DIR)/include -I$(LINUX_DIR)/drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o /dev/stdout "../dts/$(1).dts" | \
	$(LINUX_DIR)/scripts/dtc/dtc -O dtb -i "$(DTS_DIR)" -o "$(DTS_DIR)/$(1).dtb"
endef

define Image/BuildKernel
	$(CP) $(KDIR)/zImage $(BIN_DIR)/$(IMG_PREFIX)-zImage
 ifneq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),)
	$(CP) $(KDIR)/zImage-initramfs $(BIN_DIR)/$(IMG_PREFIX)-zImage-initramfs
 endif

 ifneq ($(CONFIG_TARGET_ROOTFS_INCLUDE_KERNEL),)
	$(INSTALL_DIR) $(TARGET_DIR)/boot
	$(CP) $(BIN_DIR)/$(IMG_PREFIX)-zImage $(TARGET_DIR)/boot/zImage
 endif
 ifneq ($(CONFIG_TARGET_ROOTFS_INCLUDE_DTB),)
	$(INSTALL_DIR) $(TARGET_DIR)/boot
	$(CP) $(DTS_DIR)/am335x*.dtb $(TARGET_DIR)/boot/
	$(CP) $(DTS_DIR)/omap3*.dtb $(TARGET_DIR)/boot/
	$(CP) $(DTS_DIR)/omap4*.dtb $(TARGET_DIR)/boot/
 endif
	-mkdir $(BIN_DIR)/dtbs
	-$(CP) $(DTS_DIR)/am335x*.dtb $(BIN_DIR)/dtbs/
	-$(CP) $(DTS_DIR)/omap3*.dtb $(BIN_DIR)/dtbs/
	-$(CP) $(DTS_DIR)/omap4*.dtb $(BIN_DIR)/dtbs/
endef

define Image/Prepare
       $(call Image/Prepare/Template/$(PROFILE))
endef

define Image/Build
	$(call Image/Build/$(1),$(1))
endef

define Image/Build/jffs2-64k
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-$(1).img bs=65536 conv=sync
endef

define Image/Build/jffs2-128k
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-$(1).img bs=131072 conv=sync
endef

define Image/Build/squashfs
	$(call prepare_generic_squashfs,$(KDIR)/root.squashfs)
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-$(1).img bs=131072 conv=sync
endef

$(eval $(call BuildImage))
