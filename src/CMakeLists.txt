# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

add_executable(systemtransfer
    main.cpp
    about.cpp
    app.cpp
    resources.qrc)

target_link_libraries(systemtransfer
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Svg
    KF5::I18n
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::ConfigGui)

kconfig_add_kcfg_files(systemtransfer GENERATE_MOC systemtransferconfig.kcfgc)
install(TARGETS systemtransfer ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})