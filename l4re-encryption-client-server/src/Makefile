PKGDIR          ?= .
L4DIR           ?= $(PKGDIR)/../..

TARGET                   = encryption-server encryption-client
REQUIRES_LIBS           := libstdc++
SRC_CC_encryption-server = server.cc
SRC_CC_encryption-client = client.cc

include $(L4DIR)/mk/prog.mk
