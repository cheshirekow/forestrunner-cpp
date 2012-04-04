find_package(OIS REQUIRED)
find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
find_package(CEGUI COMPONENTS OGRE REQUIRED)
find_package(SigC++ REQUIRED)
                                                                    
include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/../TutorialFramework
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
 
add_executable( tutorial7 
                    BasicTutorial7.cpp
                    ../TutorialFramework/BaseApplication.cpp
                    )
                    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/plugins.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg COPYONLY)
                
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ogre.cfg 
                ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg COPYONLY)

target_link_libraries( tutorial7 ${LIBS})

