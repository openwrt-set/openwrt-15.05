#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/RX15
	NAME:=RX15 board
endef

$(eval $(call Profile,RX15))

define Profile/R0
	NAME:=R0 board
endef


$(eval $(call Profile,R0))