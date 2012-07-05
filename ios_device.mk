HOME    :=/Users/josh
DEVROOT :=$(HOME)/dev/root
SRCROOT :=$(HOME)/Documents/dev/forestrunner
DEVELOP :=/Applications/Xcode.app/Contents/Developer

PROVISION	:= $(HOME)/Library/MobileDevice/Provisioning\ Profiles/C28EF32D-3526-4696-B24C-C921EF979B3C.mobileprovision
SIGNER      := 5f2d149ed7cf48f45633ca440e51d9e9dc88a046 
KEYCHAIN    := $(HOME)/Library/Keychains/login.keychain

PLATFORM    := iPhoneOS
ARCH        := armv7

CFLAGS      += -miphoneos-version-min=$(IOS_DEPLOYMENT_TARGET)
LDFLAGS     += -miphoneos-version-min=$(IOS_DEPLOYMENT_TARGET)

default: all codesign

include $(SRCROOT)/common.mk

Entitlements.xcent : $(SRCROOT)/src/ios/config/Entitlements.xcent
	cp $< $@

codesign: Entitlements.xcent
	security unlock-keychain $(KEYCHAIN)
	codesign --force --sign $(SIGNER) --entitlements Entitlements.xcent $(APPNAME).app
	