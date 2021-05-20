set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

cmake_minimum_required(VERSION 3.5)

project(Guys VERSION 1.0) # Set variable PROJECT_NAME

add_executable(output) # Create a executable from main.cpp

target_include_directories(output 
		PUBLIC 
		./
		./Dependencies/SDL_FULL/include/
		./Dependencies/json/single_include/nlohmann
		./Dependencies/hopscotch-map/include/tsl
		)

link_directories(output
		PUBLIC
		./Dependencies/SDL_FULL/x86/
		)

target_sources(output 
		PUBLIC 
		main.cpp
		Entity.cpp
		Game.cpp
		Quadtree.cpp
		Setup.cpp
		Tools/DebugTools.cpp
		Tools/Font.cpp
		Tools/FRect.cpp
		Tools/InputSystem.cpp
		Tools/Rect.cpp
		Tools/Timer.cpp
		Tools/TM.cpp
		Tools/Menu/Dropdown.cpp
		Tools/Menu/Overlay/BoolButton.cpp
		Tools/Menu/Overlay/NumberButton.cpp
		Tools/Menu/Overlay/Overlay.cpp
		
		)

target_link_libraries(output 
		SDL2main
		SDL2_image
		SDL2
		SDL2_ttf
		)
