

GCC_VERSION           := 4.2
IOS_DEPLOYMENT_TARGET := 5.1
OSX_DEPLOYMENT_TARGET := 10.7

PREFIX      := $(DEVROOT)/$(PLATFORM)/usr
BIN_DIR     := $(DEVELOP)/Platforms/$(PLATFORM).platform/Developer/usr/bin
SDKROOT     := $(DEVELOP)/Platforms/$(PLATFORM).platform/Developer/SDKs/$(PLATFORM)$(IOS_DEPLOYMENT_TARGET).sdk

CFLAGS      += -g
CFLAGS      += -O0
CFLAGS      += -Wall
CFLAGS      += -Wmissing-prototypes

CFLAGS      += -arch $(ARCH)
CFLAGS      += -isysroot $(SDKROOT)
CFLAGS      += -D__IPHONE_OS_VERSION_MIN_REQUIRED=40000

CFLAGS      += -I$(PREFIX)/include
CFLAGS      += -I$(SRCROOT)/src/

CXXFLAGS    += -I$(PREFIX)/include/sigc++-2.0
CXXFLAGS    += -I$(PREFIX)/lib/sigc++-2.0/include/
CXXFLAGS    += -I$(PREFIX)/include/OIS
CXXFLAGS    += -I$(PREFIX)/include/OGRE
CXXFLAGS    += -I$(PREFIX)/include/OGRE/RenderSystems/GLES
CXXFLAGS    += -I$(PREFIX)/include/OGRE/RenderSystems/GLES/APPLE


OBJCFLAGS   += -fobjc-abi-version=2
OBJCFLAGS   += -fobjc-legacy-dispatch

LDFLAGS     += -arch $(ARCH)
LDFLAGS     += -isysroot $(SDKROOT)
LDFLAGS     += -F$(SDKROOT)/System/Library/Frameworks
LDFLAGS     += -L$(PREFIX)/lib

CC          := $(BIN_DIR)/llvm-gcc-$(GCC_VERSION)
CXX         := $(BIN_DIR)/llvm-g++-$(GCC_VERSION)

APPNAME     := forestRunnerIOS
APP_TGT     := $(APPNAME).app/$(APPNAME)

DIRS := src/                          \
    src/ios                           \
    src/stategraph                    \
    src/stategraph/states             \
    src/gui                           \
    src/gui/screens                   \
    src/game                          \
    $(APPNAME).app                    \
    $(APPNAME).app/media              \
        

LIB_NAMES := \
    RenderSystem_GLESStatic            \
    OIS                                \
    OgreMainStatic                     \
    zzip                               \
    z                                  \
    freeimage                          \
    freetype                           \
    boost_thread                       \
    CEGUIBase_d                        \
    CEGUIOgreRenderer_d                \
    CEGUICommonDialogs_d               \
    CEGUICoreWindowRendererSet_d       \
    CEGUIFreeImageImageCodec_d         \
    CEGUINullRenderer_d                \
    CEGUITGAImageCodec_d               \
    CEGUITinyXMLParser_d               \
    sigc-2.0                           \
    tinyxml                            \
    
    
FMK_NAMES := \
    OpenGLES               \
    QuartzCore             \
    Foundation             \
    CoreGraphics           \
    UIKit                  \
    
LIBS := $(addprefix -l, $(LIB_NAMES) )
FMKS := $(addprefix -framework , $(FMK_NAMES) )




CXX_SOURCES := src/stategraph/Button.cpp             \
    src/stategraph/TextEntry.cpp                     \
    src/stategraph/states/PickNick.cpp               \
    src/stategraph/states/Agreement.cpp              \
    src/stategraph/states/Initialize.cpp             \
    src/stategraph/states/AnimatedPanel.cpp          \
    src/stategraph/Manager.cpp                       \
    src/stategraph/State.cpp                         \
    src/gui/Transition.cpp                           \
    src/gui/Screen.cpp                               \
    src/gui/GuiManager.cpp                           \
    src/gui/screens/CountdownScreen.cpp              \
    src/gui/screens/PauseScreen.cpp                  \
    src/gui/screens/RunningScreen.cpp                \
    src/gui/screens/CrashScreen.cpp                  \
    src/gui/screens/InitScreen.cpp                   \
    src/gui/screens/AgreementScreen.cpp              \
    src/gui/screens/HighScoreScreen.cpp              \
    src/gui/screens/AdvancedScreen.cpp               \
    src/game/ForestPatch.cpp                         \
    src/game/CEGUIDummyLogger.cpp                    \
    src/game/KeyboardGame.cpp                        \
    src/game/InitCycle.cpp                           \
    src/game/Game.cpp                                \
    src/Application.cpp                              \
    src/MeshBuilder.cpp                              \
    src/IOSApplication.cpp                           \

OBJCXX_SOURCES := src/ios/main.mm

CFG_FILES := \
	ogre.cfg             \
	plugins.cfg          \
	resources.cfg        \
	
COPY_TGT     := $(addprefix $(APPNAME).app/, $(CFG_FILES) )	

CXX_OBJECTS    := $(CXX_SOURCES:.cpp=.o)
OBJCXX_OBJECTS := $(OBJCXX_SOURCES:.mm=.o)

OBJECTS        := $(CXX_OBJECTS) $(OBJCXX_OBJECTS)


RESOURCES      := \
    fonts        \
    gui          \
    materials    \
    meshes       \
    overlays     \

RESOURCE_TGT   := $(addprefix $(APPNAME).app/media/, $(RESOURCES) )


all : $(DIRS) $(APP_TGT) copies $(RESOURCE_TGT)

$(DIRS) :
	mkdir -p $@

$(CXX_OBJECTS) : %.o : $(SRCROOT)/%.cpp
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $< -o $@

$(OBJCXX_OBJECTS) : %.o : $(SRCROOT)/%.mm
	$(CC) -c  $(CFLAGS) $(CXXFLAGS) $(OBJCFLAGS) $< -o $@

$(APP_TGT) : $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) $(FMKS)
	
$(RESOURCE_TGT) : $(APPNAME).app/media/% : $(SRCROOT)/%
	cp -r $< $(APPNAME).app/media

copies : $(COPY_TGT) $(APPNAME).app/Info.plist

$(COPY_TGT) : $(APPNAME).app/%.cfg : $(SRCROOT)/src/ios/config/%.cfg
	cp $< $@

$(APPNAME).app/Info.plist : $(SRCROOT)/src/ios/config/$(PLATFORM).plist
	cp $< $@
	plutil -convert binary1 $@

	
clean : FORCE
	rm -rf $(OBJECTS)
	rm -rf $(APP_TGT)
	rm -rf $(COPY_TGT)
	rm -rf $(APPNAME).app/Info.plist

FORCE :
	

	