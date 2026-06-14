qt_add_executable(appVDT2026
        main.cpp
        socket/Server.cpp
        socket/ClientHandler.h socket/ClientHandler.cpp
        socket/runnable/ReadHandler.h socket/runnable/ReadHandler.cpp


        dao/BaseDAO.h dao/BaseDAO.cpp
        model/ShipRadarInfoModel.h
        dao/ShipRadarInfoDAO.h dao/ShipRadarInfoDAO.cpp
        utils/WKBConverter.h utils/WKBConverter.cpp
        service/ShipService.h service/ShipService.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVDT2026 PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVDT2026
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

# Qt stuffs
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Sql)

target_link_libraries(appVDT2026
        PRIVATE Qt6::Quick Qt6::Network Qt6::Sql
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS appVDT2026
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)