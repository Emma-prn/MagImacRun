add_library(geometry)                                 # Crée notre librairie. Elle sera ensuite linkée dans le CMakeLists.txt du projet principal avec target_link_libraries(${PROJECT_NAME} PRIVATE geometry)
#add_library(geometry::geometry ALIAS geometry)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*) # Récupère tous les .cpp qui sont dans src
target_sources(geometry PRIVATE ${MY_SOURCES})        # Et les passe à notre librairie "geometry"
target_include_directories(geometry PUBLIC include)   # Déclare que l'include directory de notre librairie s'appelle include