# QtGuiApplication1 CMakeLists.txt
# By MoeMod

cmake_minimum_required(VERSION 3.1.3)
project(Launcher)
set(APP_NAME CSMoE-QtLauncher)

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

# Find Qt5
find_package(Qt5 REQUIRED Core Widgets)

# Moc settings
qt5_wrap_cpp( GEN_MOC ${FILE_MOC})
qt5_wrap_ui( GEN_UIC ${FILE_UI})
qt5_add_resources( GEN_RCC ${FILE_RES})

# output
if(APPLE)

	add_executable(${APP_NAME} MACOSX_BUNDLE ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})

	qt5_use_modules(${APP_NAME} Core Widgets MacExtras)

	# Note Mac specific extension .app
	set(APPS "\${CMAKE_INSTALL_PREFIX}/${APP_NAME}.app")

	# Directories to look for dependencies
	set(DIRS ${CMAKE_BINARY_DIR})

	install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

	set(CPACK_GENERATOR "DRAGNDROP")
	include(CPack)
else()
	add_executable(${APP_NAME} ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})
	target_link_libraries(${APP_NAME} Qt5::Core Qt5::Widgets)
endif()
