add_library(graphics)                                 # Crée notre librairie. Elle sera ensuite linkée dans le CMakeLists.txt du projet principal avec target_link_libraries(${PROJECT_NAME} PRIVATE geometry)
#add_library(graphics::graphics ALIAS graphics)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*) # Récupère tous les .cpp qui sont dans src
target_sources(graphics PRIVATE ${MY_SOURCES})        # Et les passe à notre librairie "geometry"
target_include_directories(graphics PUBLIC include)   # Déclare que l'include directory de notre librairie s'appelle include