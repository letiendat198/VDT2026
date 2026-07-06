qt_add_executable(appVDT2026
        main.cpp
        socket/Server.cpp
        socket/ClientHandler.cpp
        socket/runnable/ReadHandler.cpp
        utils/WKBConverter.cpp
        model/ShipRadarInfoModel.cpp
        dao/BaseDAO.h dao/BaseDAO.cpp
        dao/ShipRadarInfoDAO.cpp
        provider/ShipRadarInfoProvider.cpp
        model/WatchPolygonModel.cpp
        dao/WatchPolygonDAO.cpp
        provider/WatchPolygonProvider.cpp
)

qt_add_qml_module(appVDT2026
    URI VDT2026
    QML_FILES
        ui/Main.qml
        ui/AppStatusBar.qml
        ui/AppToolBar.qml
        ui/map/MainMap.qml
        ui/map/MapShipView.qml
        ui/map/MapInfoPopup.qml
        ui/map/MapShipIndicator.qml
        ui/map/MapSelectionHandler.qml
        ui/map/MapWatchView.qml
        ui/map/MapNotification.qml
        ui/Preferences.qml
        ui/NoticeDialog.qml
    SOURCES
        provider/ShipRadarInfoProvider.cpp provider/ShipRadarInfoProvider.h
        model/ShipRadarInfoModel.cpp model/ShipRadarInfoModel.h
        model/WatchPolygonModel.h model/WatchPolygonModel.cpp
        provider/WatchPolygonProvider.h provider/WatchPolygonProvider.cpp
        ui/model/ShipRadarInfoItemModel.h ui/model/ShipRadarInfoItemModel.cpp
        RESOURCES resources/gisVDT.desktop
)

qt_add_resources(appVDT2026 "images"
        PREFIX "/"
        FILES
             resources/marker.svg
             resources/marker_highlighted.svg
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
find_package(Qt6 REQUIRED COMPONENTS Positioning)
find_package(Qt6 REQUIRED COMPONENTS Concurrent)

target_link_libraries(appVDT2026
        PRIVATE Qt6::Quick Qt6::Network Qt6::Sql Qt6::Positioning Qt6::Concurrent
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
# QML expects to find C++ elements headers in project root(?), so we include these to satisfy the QML overlord
# TODO: Split this CMake files so it look less ugly
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/model")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/provider")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ui/model")

# Packaging stuffs

set(PACKAGE_INSTALL_PREFIX "/opt/${PROJECT_NAME}")

install(TARGETS appVDT2026
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_qml_app_script(TARGET appVDT2026
        OUTPUT_SCRIPT QT_INSTALL_SCRIPT
        EXCLUDE_PLUGINS qsqlmimer qsqlite qsqlmysql qsqloci # Qt tries to include all the sqldriver libs, whose depends on non-free libs we don't have
)

install(SCRIPT "${QT_INSTALL_SCRIPT}")

# Install the symlink to /usr/bin so desktop entry command works
# execute_process(COMMAND ln -s ${PACKAGE_INSTALL_PREFIX}/bin/appVDT2026 appVDT2026)

# install(FILES ${CMAKE_INSTALL_BINDIR}/appVDT2026 DESTINATION /usr/bin/appVDT2026 COMPONENT appVDT2026)

# # Install the .desktop entry
# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/gisVDT.desktop DESTINATION ~/.local/share/applications)

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "gisVDT")
set(CPACK_DEVEL_PACKAGE_DESCRIPTION "Package for VDT 2026 Mini Project")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Le Tien Dat")
set(CPACK_PACKAGE_VENDOR "Le Tien Dat")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGING_INSTALL_PREFIX ${PACKAGE_INSTALL_PREFIX})
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)