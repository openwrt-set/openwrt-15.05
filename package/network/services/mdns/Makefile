#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mdns
PKG_VERSION:=2016-12-19
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=git://github.com/openwrt-set/mdnsd.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=258039240037c81a77cf92517f5ba22fd0a2601d

PKG_MAINTAINER:=John Crispin <blogic@openwrt.org>
PKG_LICENSE:=LGPL-2.1

include $(INCLUDE_DIR)/package-seccomp.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/mdns
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenWrt Multicast DNS Daemon
  DEPENDS:=+libubox +libubus +libblobmsg-json
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include

define Package/mdns/conffiles
/etc/config/mdns
endef

define Package/mdns/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mdns $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/mdns.init $(1)/etc/init.d/mdns
	$(INSTALL_CONF) ./files/mdns.config $(1)/etc/config/mdns
	$(call InstallSeccomp,$(1),./files/mdns.json)
endef

$(eval $(call BuildPackage,mdns))
