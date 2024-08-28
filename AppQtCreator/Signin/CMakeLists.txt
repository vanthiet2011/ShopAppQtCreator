cmake_minimum_required(VERSION 3.5)

project(Signin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)




set(TS_FILES Signin_vi_VN.ts)

set(PROJECT_SOURCES
        main.cpp
        signin.cpp
        signin.h
        signin.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Signin
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Image.qrc
        register.h register.cpp register.ui

        mydb.h
        mydb.cpp
        ShoppingData.db
        addproduct.h detailproduct.h shop_display.h shop_display_admin.h addproduct.cpp detailproduct.cpp shop_display.cpp shop_display_admin.cpp addproduct.ui detailproduct.ui shop_display.ui shop_display_admin.ui
        Global.h
        Global.cpp
        help_gift.h help_method.h help_shippingadd.h shoppingcart.h thanh_toan.h
        help_gift.cpp help_method.cpp help_shippingadd.cpp shoppingcart.cpp thanh_toan.cpp
        help_1.ui help_gift.ui help_method.ui help_shippingadd.ui shoppingcart.ui thanh_toan.ui
        User.h
        User.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Signin APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Signin SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Signin
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Signin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Signin PRIVATE Qt${QT_VERSION_MAJOR}::Sql)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Signin)
endif()
set_target_properties(Signin PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Signin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Signin)
endif()
