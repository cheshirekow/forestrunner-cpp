find_package(OIS )
find_package(SigC++ )
find_package(Soci COMPONENTS sqlite3)
find_package(Boost COMPONENTS filesystem system)


set( FORESTRUNNER_LIB_SOURCES

)


if(FORESTRUNNER_LINUX)
    add_definitions( -DFORESTRUNNER_LINUX )
    set( FORESTRUNNER_DESKTOP "TRUE" )
elseif(FORESTRUNNER_WINDOWS)
    add_definitions( -DFORESTRUNNER_WINDOWS )
    set( FORESTRUNNER_DESKTOP "TRUE" )
elseif(FORESTRUNNER_OSX)
    add_definitions( -DFORESTRUNNER_OSX )
    set( FORESTRUNNER_DESKTOP "TRUE" )
elseif(FORESTRUNNER_IOS)
    add_definitions( -DFORESTRUNNER_IOS )
elseif(FORESTRUNNER_ANDROID)
    add_definitions( -DFORESTRUNNER_ANDROID )
endif()
      
     
set(FORESTRUNNER_BUILD_OK "FALSE")


if(FORESTRUNNER_DESKTOP)
    message(status "Configuring for DESKTOP build\n------------------------\n")
    find_package(OGRE COMPONENTS RenderSystem_GL REQUIRED)
    find_package(CEGUI COMPONENTS OGRE  REQUIRED)

    include_directories( 
        ${OGRE_RenderSystem_GL_INCLUDE_DIR} 
        ${SOCI_INCLUDE_DIRS}
    )
    
    set(LIBS ${LIBS} 
        ${OGRE_RenderSystem_GL_LIBRARY}
        ${SOCI_LIBRARY}
        ${SOCI_sqlite3_PLUGIN}  )
        
    if( (OIS_FOUND) 
            AND (SigC++_FOUND) 
            AND (OGRE_FOUND) 
            AND (OGRE_RenderSystem_GL_FOUND)
            AND (CEGUI_FOUND)
            AND (SOCI_FOUND) 
            AND (SOCI_sqlite3_FOUND) 
            AND (Boost_FOUND)
        )
        set(FORESTRUNNER_BUILD_OK "TRUE") 
    else()
        message( WARNING 
            "One or more packages missing, "
            "disabling build of forestrunner DESKTOP" )
    endif()
        
endif(FORESTRUNNER_DESKTOP)


if(FORESTRUNNER_IOS)
    message(status "Configuring for iOS build\n------------------------\n")
    
    find_package(OGRE COMPONENTS RenderSystem_GLES2 REQUIRED)
    include_directories( 
	${OGRE_RenderSystem_GLES2_INCLUDE_DIR}
        ${OGRE_RenderSystem_GLES_INCLUDE_DIR} )
    set(LIBS ${LIBS} 
	${OGRE_RenderSystem_GLES_LIBRARY}
        ${OGRE_RenderSystem_GLES2_LIBRARY} )
    
    if( (OIS_FOUND) 
            AND (SigC++_FOUND) 
            AND (OGRE_FOUND) 
            AND (OGRE_RenderSystem_GLES_FOUND) 
            AND (SOCI_FOUND) 
            AND (SOCI_sqlite3_FOUND) 
            AND (Boost_FOUND)
        )
        set(FORESTRUNNER_BUILD_OK "TRUE") 
    else()
	set(MISSING, "")
        if( NOT (OIS_FOUND) )
            set(MISSING ${MISSING} "ois, ")
        endif()
        if( NOT (SigC++_FOUND) )
            set(MISSING ${MISSING} "sigc++, ")
        endif()
        if( NOT (OGRE_FOUND) )
            set(MISSING ${MISSING} "ogre, ")
        endif()
        if( NOT (OGRE_RenderSystem_GLES_FOUND) )
            set(MISSING ${MISSING} "ogre_GLES, ")
        endif()
        if( NOT (SOCI_FOUND) )
            set(MISSING ${MISSING} "soci, ")
        endif()
        if( NOT (SOCI_sqlite3_FOUND) )
            set(MISSING ${MISSING} "soci_sqlite3, ")
        endif()
        if( NOT (Boost_FOUND) )
            set(MISSING ${MISSING} "boost, ")
        endif()


        message( WARNING 
            "One or more packages missing: ${MISSING}, "
            "disabling build of forestrunner IOS" )
    endif()

endif(FORESTRUNNER_IOS)


if(FORESTRUNNER_BUILD_OK)
                                                                    
    include_directories( 
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${OIS_INCLUDE_DIRS}
        ${OGRE_INCLUDE_DIRS} 
        ${CEGUI_INCLUDE_DIR}
        ${SigC++_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${SOCI_INCLUDE_DIRS}
        ${SOCI_sqlite3_INCLUDE_DIRS}
        )
    
    set(LIBS ${LIBS} 
        ${OIS_LIBRARIES}
        ${OGRE_LIBRARIES}
        ${CEGUI_LIBRARY}
        ${SigC++_LIBRARIES} 
        ${Boost_LIBRARIES}
        ${SOCI_LIBRARIES}
        ${SOCI_sqlite3_LIBRARIES}
        )
     
    add_library( forestrunner 
        forestrunner/desktop/DataStore.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/app/linux.cpp
        forestrunner/Application.cpp
        forestrunner/ios/Application.cpp
        forestrunner/ios/AppInterface.cpp
        forestrunner/datastore/DataStore.cpp
        forestrunner/datastore/Map.cpp
        forestrunner/datastore/UserHighScoreRow.cpp
        forestrunner/datastore/GlobalHighScoreRow.cpp
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
                        forestrunner/desktop/Application.cpp
                        main.cpp )
    
        target_link_libraries( forestrunner_exe forestrunner ${LIBS})
        install(TARGETS forestrunner_exe
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
        )
    
        install(DIRECTORY ../resources/ceed         DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
        install(DIRECTORY ../resources/materials    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
        install(DIRECTORY ../resources/meshes       DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
        install(FILES   ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg
                        ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg
                        ${CMAKE_CURRENT_BINARY_DIR}/ogre.cfg
                        ../resources/Initialize.sql
                 DESTINATION ${CMAKE_INSTALL_PREFIX}/share/forestrunner)
    endif(FORESTRUNNER_DESKTOP)

    if(FORESTRUNNER_IOS)
        
    endif()

endif(FORESTRUNNER_BUILD_OK)
