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
        ui/AppDialog.qml
    SOURCES
        provider/ShipRadarInfoProvider.cpp provider/ShipRadarInfoProvider.h
        model/ShipRadarInfoModel.cpp model/ShipRadarInfoModel.h
        model/WatchPolygonModel.h model/WatchPolygonModel.cpp
        provider/WatchPolygonProvider.h provider/WatchPolygonProvider.cpp
        ui/model/ShipRadarInfoItemModel.h ui/model/ShipRadarInfoItemModel.cpp
        provider/DialogProvider.h provider/DialogProvider.cpp
)

qt_add_resources(appVDT2026 "images"
        PREFIX "/"
        FILES
             resources/marker.svg
             resources/marker_highlighted.svg
             resources/gisVDT.desktop
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
