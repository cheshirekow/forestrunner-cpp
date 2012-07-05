HOME    :=/Users/josh
DEVROOT :=$(HOME)/dev/root
SRCROOT :=$(HOME)/Documents/dev/forestrunner
DEVELOP :=/Applications/Xcode.app/Contents/Developer

PLATFORM    := iPhoneSimulator
ARCH        := i686

CFLAGS      += -mmacosx-version-min=$(OSX_DEPLOYMENT_TARGET)
LDFLAGS     += -mmacosx-version-min=$(OSX_DEPLOYMENT_TARGET)

include $(SRCROOT)/common.mk
