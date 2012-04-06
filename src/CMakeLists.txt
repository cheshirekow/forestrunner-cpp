add_subdirectory(BasicTutorial7)

find_package(OIS REQUIRED)
find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
find_package(CEGUI COMPONENTS OGRE REQUIRED)
find_package(SigC++ REQUIRED)
                                                                    
include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/TutorialFramework
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS} 
    ${OGRE_RenderSystem_GL_INCLUDE_DIRS}
    ${CEGUI_INCLUDE_DIR}
    ${SigC++_INCLUDE_DIRS}
    )


set(LIBS ${LIBS} 
    ${OIS_LIBRARIES}
    ${OGRE_LIBRARIES}
    ${OGRE_RenderSystem_GL__LIBRARIES}
    ${CEGUI_LIBRARY}
    ${SigC++_LIBRARIES} 
    )
 
add_executable( forestrunner 
                    Application.cpp
                    MeshBuilder.cpp
                    TutorialFramework/BaseApplication.cpp
                    game/Game.cpp
                    game/KeyboardGame.cpp
                    game/ForestPatch.cpp
                    game/InitCycle.cpp
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
                    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/plugins.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg COPYONLY)
                
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ogre.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg COPYONLY)

target_link_libraries( forestrunner ${LIBS})

