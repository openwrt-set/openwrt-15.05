include $(TOPDIR)/rules.mk

PKG_NAME:=usbmode
PKG_VERSION:=2014-08-26
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/openwrt-set/usbmode.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=993a9a542791953c4804f7ddbb3a07756738e37a
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
CMAKE_INSTALL:=1

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

PKG_DATA_VERSION:=20150115
PKG_DATA_URL:=http://www.draisberghof.de/usb_modeswitch
PKG_DATA_PATH:=usb-modeswitch-data-$(PKG_DATA_VERSION)
PKG_DATA_FILENAME:=$(PKG_DATA_PATH).tar.bz2

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Download/data
  FILE:=$(PKG_DATA_FILENAME)
  URL:=$(PKG_DATA_URL)
  MD5SUM:=662bcd56a97e560ea974bc710822de51
endef
$(eval $(call Download,data))

define Package/usb-modeswitch
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libubox +libblobmsg-json +libusb-1.0
  TITLE:=USB mode switching utility
endef

define Build/Prepare
	$(Build/Prepare/Default)
	tar xvfj $(DL_DIR)/$(PKG_DATA_FILENAME) -C $(PKG_BUILD_DIR)
	rm -f \
		$(PKG_BUILD_DIR)/$(PKG_DATA_PATH)/usb_modeswitch.d/05c6:1000:sVe=GT
	cp ./data/* $(PKG_BUILD_DIR)/$(PKG_DATA_PATH)/usb_modeswitch.d/
endef

define Package/usb-modeswitch/install
	$(INSTALL_DIR) $(1)/etc/hotplug.d/usb $(1)/etc/init.d $(1)/sbin
	perl $(PKG_BUILD_DIR)/convert-modeswitch.pl \
		$(PKG_BUILD_DIR)/$(PKG_DATA_PATH)/usb_modeswitch.d/* \
		> $(1)/etc/usb-mode.json
	$(INSTALL_DATA) ./files/usbmode.hotplug $(1)/etc/hotplug.d/usb/20-usb_mode
	$(INSTALL_BIN) ./files/usbmode.init $(1)/etc/init.d/usbmode
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/usbmode $(1)/sbin/
endef

$(eval $(call BuildPackage,usb-modeswitch))
