cmake_minimum_required(VERSION 3.20)

# Définition du projet
project(MyTorch LANGUAGES CXX)

# Configuration du standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/headers)

# Ajouter les répertoires pour les fichiers d'en-tête
include_directories(${HEADERS_DIR})

# Désactiver pthreads pour GoogleTest sous Windows
if(WIN32)
    set(gtest_disable_pthreads ON)
endif()

# Ajouter GoogleTest comme sous-module
add_subdirectory(googletest)

# Récupérer tous les fichiers sources
set(SOURCE_FILES
        src/main.cpp
        src/tensorshape.cpp
        src/tensor.cpp
)

# Créer la bibliothèque principale du projet
add_library(mytorch_lib ${SOURCE_FILES})

# Inclure les répertoires d'en-tête dans la bibliothèque
target_include_directories(mytorch_lib PUBLIC ${HEADERS_DIR})

# Créer l'exécutable principal
add_executable(main_executable src/main.cpp)

# Lier la bibliothèque principale à l'exécutable
target_link_libraries(main_executable mytorch_lib)

# --- Tests ---

# Récupérer les fichiers sources de tests
set(TEST_FILES
        tests/test_main.cpp
        tests/test_shape.cpp
        tests/test_tensor.cpp
)

# Créer l'exécutable pour les tests
add_executable(tests ${TEST_FILES})

# Lier GoogleTest et la bibliothèque principale aux tests
target_link_libraries(tests PRIVATE gtest gtest_main mytorch_lib)

# Activer les tests dans CMake
enable_testing()

# Ajouter les tests au projet
add_test(NAME MyTorchTests COMMAND tests)
