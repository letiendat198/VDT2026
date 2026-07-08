cmake_minimum_required(VERSION 3.16)

# list(APPEND CMAKE_PREFIX_PATH "~/Applications/Qt/6.11.1/gcc_64")

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/package/")

project(VDT2026 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

add_subdirectory(src)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -fsanitize=undefined -fsanitize=address -fsanitize=memory -fsanitize=thread -fno-omit-frame-pointer -fast_unwind_on_malloc=0")
#     target_link_options(appVDT2026 BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address)
endif()

# Packaging stuffs

set(PACKAGE_INSTALL_PREFIX "/opt/${PROJECT_NAME}")
set(BINARY_NAME "appVDT2026")

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

# Configure the .desktop entry to the correct path
configure_file(${CMAKE_SOURCE_DIR}/src/resources/packaging/gisVDT.desktop ${CMAKE_INSTALL_PREFIX}configured/gisVDT.desktop)
# Configure the script, but no need to install them because the content are written into the final spec file
configure_file(${CMAKE_SOURCE_DIR}/src/resources/packaging/postin.sh ${CMAKE_INSTALL_PREFIX}scripts/postin.sh)
configure_file(${CMAKE_SOURCE_DIR}/src/resources/packaging/postun.sh ${CMAKE_INSTALL_PREFIX}scripts/postun.sh)

# If you want CPACK to install it correctly, use relative path only
# DON'T USE ABSOLUTE PATH OR CPACK WILL INSTALL IT ABSOLUTELY AND WILL FUCK UP YOUR FOLDER PERMISSION
# THERE IS CMAKE_INSTALL_PREFIX AND CPACK_PACKAGING_INSTALL_PREFIX FOR A REASON!
install(FILES ${CMAKE_INSTALL_PREFIX}configured/gisVDT.desktop DESTINATION ".")

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "gisVDT")
set(CPACK_RPM_PACKAGE_SUMMARY "gisVDT")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Package for VDT 2026 Mini Project")
# Use post install and post uninstall scripts feature of RPM to copy the .desktop file
# CMake install() will tries to copy it during packaging time, which is annoying. And then there's the whole permission fiasco
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE ${CMAKE_INSTALL_PREFIX}scripts/postin.sh)
set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE ${CMAKE_INSTALL_PREFIX}scripts/postun.sh)
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Le Tien Dat")
set(CPACK_PACKAGE_VENDOR "Le Tien Dat")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGING_INSTALL_PREFIX ${PACKAGE_INSTALL_PREFIX})
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)