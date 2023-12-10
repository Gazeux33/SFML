cmake_minimum_required(VERSION 3.27)
project(SFML)

set(CMAKE_CXX_STANDARD 17)

# Créer un exécutable pour le projet
add_executable(SFML main.cpp)

# Définir le chemin vers les modules CMake de SFML
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

# Trouver les paquets SFML nécessaires
find_package(SFML 2.6.1 COMPONENTS graphics audio network system window REQUIRED)

# Inclure les répertoires d'en-tête SFML
include_directories(${SFML_INCLUDE_DIR})

# Lier les bibliothèques SFML à l'exécutable de votre projet
target_link_libraries(SFML sfml-graphics sfml-audio sfml-network sfml-system sfml-window)
