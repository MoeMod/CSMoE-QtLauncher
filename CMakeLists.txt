# QtGuiApplication1 CMakeLists.txt
# By MoeMod

cmake_minimum_required(VERSION 3.1.3)
set(APP_NAME CSMoE-QtLauncher)
project(${APP_NAME})
set(CMAKE_PROJECT_VERSION_MAJOR 20)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)

include_directories (

)

file(GLOB FILE_RES 
	./QtGuiApplication1.qrc
)
file(GLOB FILE_UI 
	./QtGuiApplication1.ui
)
file(GLOB FILE_MOC 
	./QtGuiApplication1.h
)
file(GLOB FILE_SRC 
	./QtGuiApplication1.cpp
	./main.cpp

	./Model/GameModeList.cpp
	./Model/GameSettings.cpp

	./Controller/GameDirController.cpp
	./Controller/MapListController.cpp
	./Controller/GameModeController.cpp
	./Controller/GameSettingsController.cpp
	./Controller/GameLaunchController.cpp
)
file(GLOB FILE_SRC_MACOS
	./Platform/TouchBar.mm
)

# Find Qt5
find_package(Qt5 REQUIRED Core Widgets)

# Moc settings
qt5_wrap_cpp( GEN_MOC ${FILE_MOC})
qt5_wrap_ui( GEN_UIC ${FILE_UI})
qt5_add_resources( GEN_RCC ${FILE_RES})

# output
if(APPLE)

	set(APP_ICNS ./Resources/Icon.icns)
	set_source_files_properties(${APP_ICNS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

	add_executable(${APP_NAME} MACOSX_BUNDLE ${FILE_SRC_MACOS} ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC} ${APP_ICNS})

	set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in")
	set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE "Icon.icns")

	qt5_use_modules(${APP_NAME} Core Widgets MacExtras)
	target_link_libraries(${APP_NAME} "-framework AppKit")

	set(CPACK_GENERATOR "DragNDrop")
	set(CPACK_PACKAGE_VENDOR "MoeMod")
	set(CPACK_PACKAGE_FILE_NAME "${APP_NAME}-v${CMAKE_PROJECT_VERSION_MAJOR}-macOS-${CMAKE_SYSTEM_PROCESSOR}")
	set(CPACK_DMG_VOLUME_NAME "${APP_NAME}")
	set(CPACK_DMG_FORMAT "UDRO") #UDRW
	set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/cmake/DragNDrop/background.png")
	set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/cmake/DragNDrop/DS_Store")

	if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
		add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND "${Qt5_DIR}/../../../bin/macdeployqt" ARGS "${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.app" "-always-overwrite")
		add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND "cpack")
	endif()

	include(CPack)
	include(CPackDMG)

	set(CMAKE_INSTALL_PREFIX "/Applications")
	install(TARGETS ${APP_NAME} BUNDLE DESTINATION ".")

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")

	add_executable(${APP_NAME} ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})
	qt5_use_modules(${APP_NAME} Core Widgets)

	set(CPACK_GENERATOR "DEB")
	set(CPACK_PACKAGE_VENDOR "MoeMod")
	set(CPACK_PACKAGE_CONTACT "https://github.com/MoeMod")
	set(CPACK_PACKAGE_FILE_NAME "${APP_NAME}-v${CMAKE_PROJECT_VERSION_MAJOR}-Linux-${CMAKE_SYSTEM_PROCESSOR}")
	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5ore5a (>=5.11.0), libqt5widgets5 (>=5.11.0)")
	set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "libsdl2-2.0-0 (>=2.0.8), libfontconfig1 (>=2.12.0)")
	set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
	set(CPACK_DEBIAN_PACKAGE_SECTION "games")

	if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
		add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND "cpack")
	endif()

	include(CPack)

	install(TARGETS ${APP_NAME} DESTINATION "bin")

else()
	add_executable(${APP_NAME} ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})
	target_link_libraries(${APP_NAME} Qt5::Core Qt5::Widgets)
endif()
