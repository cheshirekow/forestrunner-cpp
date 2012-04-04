find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
find_package(CEGUI COMPONENTS OGRE REQUIRED)
#find_package(Boost COMPONENTS iostreams REQUIRED)
                                                                    
include_directories( 
    ${OGRE_INCLUDE_DIRS} 
    ${OGRE_RenderSystem_GL_INCLUDE_DIRS}
    ${CEGUI_INCLUDE_DIR}
    )


set(LIBS ${LIBS} 
    ${OGRE_LIBRARIES}
    ${OGRE_RenderSystem_GL__LIBRARIES}
    ${CEGUI_LIBRARY} 
    )
 
#add_executable( ${CMAKE_PROJECT_NAME} main.cpp Application.cpp)

#target_link_libraries( ${CMAKE_PROJECT_NAME} ${LIBS})

#configure_file( 
#    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.glade 
#    ${CMAKE_CURRENT_BINARY_DIR}/mainwindow.glade COPYONLY )
    
#configure_file( 
#    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.xml 
#    ${CMAKE_CURRENT_BINARY_DIR}/mainwindow.xml COPYONLY )
 

add_subdirectory(BasicTutorial7)