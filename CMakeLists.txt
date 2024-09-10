# Versão mínima requerida do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(game)

# Definir a versão do C++ utilizada
set(CMAKE_CXX_STANDARD 17)

# Incluir diretórios de inclusão
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/include)

# Definir o diretório onde o SFML está instalado
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/lib/cmake/SFML")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/lib/cmake/SFML")

# Encontrar e carregar o pacote SFML
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

# Adicionar arquivos de origem e cabeçalhos
file(GLOB_RECURSE SOURCES "src/*.cpp")  # Use o padrão '**/*.cpp' para capturar recursivamente
file(GLOB_RECURSE HEADERS "include/*.h") # Use o padrão '**/*.h' para capturar recursivamente

# Nome e origem do executável
add_executable(game ${SOURCES} ${HEADERS})

# Definir o tipo de aplicativo como console
set_target_properties(game PROPERTIES 
    WIN32_EXECUTABLE OFF  # Garante que seja um aplicativo de console
)

# Vincula as bibliotecas SFML estaticamente
target_link_libraries(game 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)


# Copiar as DLLs para o diretório de saída
if (MSYS)
    message(STATUS "Detectado Sistema Windows. Copiando DLLs")
    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
           "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/openal32.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-audio-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-audio-d-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-graphics-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-graphics-d-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-network-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-network-d-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-system-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-system-d-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-window-2.dll"
            "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.1/bin/sfml-window-d-2.dll"
            $<TARGET_FILE_DIR:game>
        COMMENT "Copying SFML DLLs to the output directory"
    )
endif()