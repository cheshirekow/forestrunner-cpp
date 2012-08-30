find_package(OIS REQUIRED)
find_package(SigC++ REQUIRED)

if(FORESTRUNNER_LINUX)
    add_definitions( -DFORESTRUNNER_LINUX )
elseif(FORESTRUNNER_WINDOWS)
    add_definitions( -DFORESTRUNNER_WINDOWS )
elseif(FORESTRUNNER_OSX)
    add_definitions( -DFORESTRUNNER_OSX )
elseif(FORESTRUNNER_IOS)
    add_definitions( -DFORESTRUNNER_IOS )
elseif(FORESTRUNNER_ANDROID)
    add_definitions( -DFORESTRUNNER_ANDROID )
endif()
      


if(FORESTRUNNER_DESKTOP)
    message(status "Configuring for DESKTOP build\n------------------------\n")
    find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
    find_package(CEGUI COMPONENTS OGRE  REQUIRED)
    include_directories( ${OGRE_RenderSystem_GL_INCLUDE_DIR} )
    set(LIBS ${LIBS} ${OGRE_RenderSystem_GL_LIBRARY} )
endif(FORESTRUNNER_DESKTOP)

if(FORESTRUNNER_IOS)
    message(status "Configuring for iOS build\n------------------------\n")
    find_package(OGRE COMPONENTS RenderSystem_GLES REQUIRED)
    find_package(CEGUI COMPONENTS OGRE REQUIRED)
    include_directories( ${OGRE_RenderSystem_GLES_INCLUDE_DIR} )
    set(LIBS ${LIBS} ${OGRE_RenderSystem_GLES_LIBRARY} )
endif(FORESTRUNNER_IOS)
                                                                    
include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS} 
    ${CEGUI_INCLUDE_DIR}
    ${SigC++_INCLUDE_DIRS}
    )


set(LIBS ${LIBS} 
    ${OIS_LIBRARIES}
    ${OGRE_LIBRARIES}
    ${CEGUI_LIBRARY}
    ${SigC++_LIBRARIES} 
    )
 
add_library( forestrunner 
                    forestrunner/Application.cpp
                    forestrunner/DesktopApplication.cpp
                    forestrunner/ios/Application.cpp
                    forestrunner/ios/AppInterface.cpp
                    ${CMAKE_CURRENT_BINARY_DIR}/app/linux.cpp
                    MeshBuilder.cpp
                    game/Game.cpp
                    game/KeyboardGame.cpp
                    game/ForestPatch.cpp
                    game/InitCycle.cpp
                    game/CEGUIDummyLogger.cpp
                    gui/GuiManager.cpp
                    gui/Screen.cpp
                    gui/Transition.cpp
                    gui/screens/AgreementScreen.cpp
                    gui/screens/InitScreen.cpp
                    gui/screens/PauseScreen.cpp
                    gui/screens/AdvancedScreen.cpp
                    gui/screens/CountdownScreen.cpp
                    gui/screens/RunningScreen.cpp
                    gui/screens/CrashScreen.cpp
                    gui/screens/HighScoreScreen.cpp
                    )
                    
install(TARGETS forestrunner
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/app/linux.cpp
                ${CMAKE_CURRENT_BINARY_DIR}/app/linux.cpp )
                    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/plugins.cfg.in 
                ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg.in 
                ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg )
                
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ogre.cfg.in 
                ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg COPYONLY)
                
if(FORESTRUNNER_DESKTOP)
add_executable( forestrunner_exe
                    main.cpp )

target_link_libraries( forestrunner_exe forestrunner ${LIBS})
install(TARGETS forestrunner_exe
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(DIRECTORY ../ceed         DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
install(DIRECTORY ../materials    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
install(DIRECTORY ../meshes       DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
install(FILES   ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg
                ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg
                ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg
         DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)

endif(FORESTRUNNER_DESKTOP)
