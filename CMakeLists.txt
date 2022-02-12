# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("babel")
project (babel_client)
project (babel_server)

if (WIN32)
	find_program(conan_path conan)
	message(${conan_path})
	execute_process(COMMAND ${conan_path} "install" "${PROJECT_SOURCE_DIR}" "-s" "compiler=Visual Studio" "-s" "compiler.version=16" "-s" "build_type=Debug" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else()
	add_definitions("-fPIC")
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Babel Client

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
set(CMAKE_AUTOMOC ON)
Set(Boost_INSTALL_DIR ${CONAN_BOOST_ROOT})
find_package(Boost REQUIRED)
include_directories(${CMAKE_INCLUDE_PATH} Client/Includes/ ${CONAN_INCLUDE_DIRS_BOOST})
set(CLIENT_BUILD_DIR "${CMAKE_BINARY_DIR}/bin/")

add_executable (babel_client "Client/Sources/main.cpp" "Client/Sources/MainWindow.cpp" "Client/Includes/MainWindow.hpp"  "Client/Includes/Client.hpp" "Client/Sources/Client.cpp" "Client/Sources/ConnexionUdp.cpp" "Client/Includes/ConnexionUdp.hpp" "Client/Sources/Audio.cpp" "Client/Includes/Audio.hpp" "Client/Sources/Encoding.cpp" "Client/Includes/Encoding.hpp")
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CLIENT_BUILD_DIR}")
set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CLIENT_BUILD_DIR}")
set_target_properties(babel_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CLIENT_BUILD_DIR}")

if (MSVC) #Because Windows require to install a .dll or having it near the executable for dynamic linking, we need to copy it
	file(GLOB QT_DLL CONFIGURE_DEPENDS "${CONAN_BIN_DIRS_QT}/Qt5*.dll")
	foreach(dll ${QT_DLL})
		configure_file("${dll}" "${CLIENT_BUILD_DIR}" COPYONLY)
	endforeach()
	file(GLOB GLIB_DLL CONFIGURE_DEPENDS "${CONAN_BIN_DIRS_GLIB}/*.dll")
	foreach(dll ${GLIB_DLL})
		configure_file("${dll}" "${CLIENT_BUILD_DIR}" COPYONLY)
	endforeach()
    set_target_properties(babel_client PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")
endif (MSVC)

add_custom_command(TARGET babel_client POST_BUILD #We also QT Plugins
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${CONAN_QT_ROOT}/plugins ${CMAKE_BINARY_DIR}/bin/plugins/)

# Babel Server
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_INCLUDE_PATH} Server/Network/Includes/ Server/Queries/Includes/ Server/User/)
set(SERVER_BUILD_DIR "${CMAKE_BINARY_DIR}/bin/")
include_directories("Interfaces")
include_directories("Server/Network/Includes")
include_directories("Server/Queries/Includes")
include_directories("Server/Database/Includes")
include_directories("Server/User")
include_directories(${SQLite3_INCLUDE_DIRS})

add_executable (babel_server "Server/main.cpp"  "Server/Network/Includes/ServerNetworkManager.hpp" "Server/Network/Sources/ServerNetworkManager.cpp" "Server/Network/Includes/ConnectionHandler.hpp" "Server/Network/Sources/ConnectionHandler.cpp" "Server/Queries/Includes/Queries.hpp" "Server/Queries/Includes/QueryHandlers.hpp" "Server/Queries/Sources/QueryHandlers.cpp" "Server/User/ServerUser.hpp" "Server/Database/Includes/DatabaseController.hpp" "Server/Database/Sources/DatabaseController.cpp" )
target_link_libraries(babel_server ${CONAN_LIBS} ${CONAN_LIB_DIRS_BOOST})
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SERVER_BUILD_DIR}")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SERVER_BUILD_DIR}")
set_target_properties(babel_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SERVER_BUILD_DIR}")

if (MSVC) #Because Windows require to install a .dll or having it near the executable for dynamic linking, we need to copy it
	file(GLOB QT_DLL CONFIGURE_DEPENDS "${CONAN_BIN_DIRS_QT}/Qt5*.dll")
	foreach(dll ${QT_DLL})
		configure_file("${dll}" "${CLIENT_BUILD_DIR}" COPYONLY)
	endforeach()
	file(GLOB GLIB_DLL CONFIGURE_DEPENDS "${CONAN_BIN_DIRS_GLIB}/*.dll")
	foreach(dll ${GLIB_DLL})
		configure_file("${dll}" "${CLIENT_BUILD_DIR}" COPYONLY)
	endforeach()
    set_target_properties(babel_server PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")
endif (MSVC)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
