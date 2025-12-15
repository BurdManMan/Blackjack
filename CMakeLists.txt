cmake_minimum_required(VERSION 3.16)

project(BlackJack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appBlackJack
    main.cpp
)

qt_add_qml_module(appBlackJack
    URI BlackJack
    QML_FILES
        Main.qml
        SOURCES random.h
        SOURCES blackjackcontroller.h blackjackcontroller.cpp
        QML_FILES Blackjack.qml
        QML_FILES MainMenu.qml
        SOURCES card.h card.cpp
        SOURCES deck.h deck.cpp
        SOURCES handmodel.h handmodel.cpp
)

file(GLOB_RECURSE CARD_IMAGES RELATIVE ${CMAKE_SOURCE_DIR} "assets/cards/*.png")

qt_add_resources(appBlackJack "card_assets"
    FILES ${CARD_IMAGES}
    assets/sounds/wasted.mp3
    assets/sounds/yay.mp3
    assets/sounds/boom.mp3
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBlackJack PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBlackJack
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBlackJack
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Multimedia
)
target_link_libraries(appBlackJack PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appBlackJack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
