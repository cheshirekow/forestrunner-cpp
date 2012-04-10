find_package(OIS REQUIRED)
find_package(CEGUI COMPONENTS OGRE REQUIRED)
find_package(SigC++ REQUIRED)

if(FORESTRUNNER_DESKTOP)
    message(status "Configuring for DESKTOP build\n------------------------\n")
    find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
    include_directories( ${OGRE_RenderSystem_GL_INCLUDE_DIR} )
    set(LIBS ${LIBS} ${OGRE_RenderSystem_GL_LIBRARY} )
endif(FORESTRUNNER_DESKTOP)

if(FORESTRUNNER_IOS)
    message(status "Configuring for iOS build\n------------------------\n")
    find_package(OGRE COMPONENTS RenderSystem_GLES REQUIRED)
    include_directories( ${OGRE_RenderSystem_GLES_INCLUDE_DIR} )
    set(LIBS ${LIBS} ${OGRE_RenderSystem_GLES_LIBRARY} )
endif(FORESTRUNNER_IOS)
                                                                    
include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/TutorialFramework
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
                    IOSApplication.cpp
                    Application.cpp
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
                    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/plugins.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg )
                
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ogre.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg COPYONLY)
                
if(FORESTRUNNER_DESKTOP)
add_executable( forestrunner_exe
                    main.cpp )

target_link_libraries( forestrunner_exe forestrunner ${LIBS})
endif(FORESTRUNNER_DESKTOP)
