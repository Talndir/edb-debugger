cmake_minimum_required (VERSION 3.1)
include("GNUInstallDirs")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.0.0 REQUIRED Widgets Xml XmlPatterns Svg LinguistTools)

qt5_add_translation(QM_FILES
	# add translation files in /src/res/translations here
	res/translations/edb_zh_CN.ts
)

# Create translations QRC file - translations.qrc
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/translations.qrc")

file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/translations\">")
foreach(QM_FILE ${QM_FILES})
	get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
	file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file>${QM_FILE_NAME}</file>")
endforeach()

file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND QRC_FILES ${TRANSLATIONS_QRC})

qt5_add_resources(QRC_SOURCES
	res/debugger.qrc
	res/themes.qrc
	res/breeze-edb.qrc
	res/breeze-dark-edb.qrc
	${TRANSLATIONS_QRC}
)

foreach(FILE IN LISTS QRC_SOURCES)
	set_property(SOURCE ${FILE} PROPERTY SKIP_UNITY_BUILD_INCLUSION ON)
endforeach()

set(edb_SRCS
	${QRC_SOURCES}

	BasicBlock.cpp
	BinaryString.cpp
	BinaryString.ui
	ByteShiftArray.cpp
	CommentServer.cpp
	CommentServer.h
	Configuration.cpp
	DataViewInfo.cpp
	DataViewInfo.h
	DebugEventHandlers.cpp
	DebugEventHandlers.h
	Debugger.cpp
	Debugger.h
	Debugger.ui
	DebuggerInternal.h
	DialogAbout.cpp
	DialogAbout.h
	DialogAbout.ui
	DialogArguments.cpp
	DialogArguments.h
	DialogArguments.ui
	DialogBreakpoints.cpp
	DialogBreakpoints.h
	DialogBreakpoints.ui
	DialogAttach.cpp
	DialogAttach.h
	DialogAttach.ui
	DialogInputBinaryString.cpp
	DialogInputBinaryString.h
	DialogInputBinaryString.ui
	DialogInputValue.cpp
	DialogInputValue.h
	DialogInputValue.ui
	DialogMemoryRegions.cpp
	DialogMemoryRegions.h
	DialogMemoryRegions.ui
	DialogOpenProgram.cpp
	DialogOpenProgram.h
	DialogOptions.cpp
	DialogOptions.h
	DialogOptions.ui
	DialogPlugins.cpp
	DialogPlugins.h
	DialogPlugins.ui
	DialogThreads.cpp
	DialogThreads.h
	DialogThreads.ui
	ExpressionDialog.cpp
	ExpressionDialog.h
	FixedFontSelector.cpp
	FixedFontSelector.h
	FixedFontSelector.ui
	FloatX.cpp
	Font.cpp
	Function.cpp
	HexStringValidator.cpp
	MemoryRegions.cpp
	PluginModel.cpp
	PluginModel.h
	ProcessModel.cpp
	ProcessModel.h
	QLongValidator.cpp
	QULongValidator.cpp
	RecentFileManager.cpp
	RecentFileManager.h
	RegionBuffer.cpp
	RegionBuffer.h
	Register.cpp
	RegisterViewModelBase.cpp
	State.cpp
	SymbolManager.cpp
	SymbolManager.h
	Theme.cpp
	ThreadsModel.cpp
	capstone-edb/Inspection.cpp
	capstone-edb/Instruction.cpp
	capstone-edb/include/Formatter.h
	capstone-edb/include/Inspection.h
	capstone-edb/include/Instruction.h
	capstone-edb/include/Operand.h
	edb.cpp
	main.cpp
	qhexview/QHexView
	qhexview/qhexview.cpp
	qhexview/qhexview.h
	session/SessionError.cpp
	session/SessionError.h
	session/SessionManager.cpp
	session/SessionManager.h
	widgets/NavigationHistory.cpp
	widgets/NavigationHistory.h
	widgets/QDisassemblyView.cpp
	widgets/QDisassemblyView.h
	widgets/RegisterViewDelegate.cpp
	widgets/RegisterViewDelegate.h
	widgets/SyntaxHighlighter.cpp
	widgets/SyntaxHighlighter.h
	widgets/TabWidget.cpp
	widgets/TabWidget.h

	${PROJECT_SOURCE_DIR}/include/API.h
	${PROJECT_SOURCE_DIR}/include/ArchProcessor.h
	${PROJECT_SOURCE_DIR}/include/BasicBlock.h
	${PROJECT_SOURCE_DIR}/include/BinaryString.h
	${PROJECT_SOURCE_DIR}/include/ByteShiftArray.h
	${PROJECT_SOURCE_DIR}/include/Configuration.h
	${PROJECT_SOURCE_DIR}/include/Expression.h
	${PROJECT_SOURCE_DIR}/include/FloatX.h
	${PROJECT_SOURCE_DIR}/include/Function.h
	${PROJECT_SOURCE_DIR}/include/HexStringValidator.h
	${PROJECT_SOURCE_DIR}/include/IAnalyzer.h
	${PROJECT_SOURCE_DIR}/include/IBinary.h
	${PROJECT_SOURCE_DIR}/include/IBreakpoint.h
	${PROJECT_SOURCE_DIR}/include/IDebugEvent.h
	${PROJECT_SOURCE_DIR}/include/IDebugEventHandler.h
	${PROJECT_SOURCE_DIR}/include/IDebugger.h
	${PROJECT_SOURCE_DIR}/include/IPlugin.h
	${PROJECT_SOURCE_DIR}/include/IProcess.h
	${PROJECT_SOURCE_DIR}/include/IRegion.h
	${PROJECT_SOURCE_DIR}/include/IState.h
	${PROJECT_SOURCE_DIR}/include/ISymbolGenerator.h
	${PROJECT_SOURCE_DIR}/include/ISymbolManager.h
	${PROJECT_SOURCE_DIR}/include/IThread.h
	${PROJECT_SOURCE_DIR}/include/Instruction.h
	${PROJECT_SOURCE_DIR}/include/MemoryRegions.h
	${PROJECT_SOURCE_DIR}/include/Module.h
	${PROJECT_SOURCE_DIR}/include/Patch.h
	${PROJECT_SOURCE_DIR}/include/Prototype.h
	${PROJECT_SOURCE_DIR}/include/QLongValidator.h
	${PROJECT_SOURCE_DIR}/include/QULongValidator.h
	${PROJECT_SOURCE_DIR}/include/QtHelper.h
	${PROJECT_SOURCE_DIR}/include/Register.h
	${PROJECT_SOURCE_DIR}/include/RegisterRef.h
	${PROJECT_SOURCE_DIR}/include/RegisterViewModelBase.h
	${PROJECT_SOURCE_DIR}/include/State.h
	${PROJECT_SOURCE_DIR}/include/Status.h
	${PROJECT_SOURCE_DIR}/include/Symbol.h
	${PROJECT_SOURCE_DIR}/include/Theme.h
	${PROJECT_SOURCE_DIR}/include/ThreadsModel.h
	${PROJECT_SOURCE_DIR}/include/Types.h
	${PROJECT_SOURCE_DIR}/include/Util.h
	${PROJECT_SOURCE_DIR}/include/Value.h
	${PROJECT_SOURCE_DIR}/include/edb.h
	${PROJECT_SOURCE_DIR}/include/string_hash.h
	${PROJECT_SOURCE_DIR}/include/util/Container.h
	${PROJECT_SOURCE_DIR}/include/util/Float.h
	${PROJECT_SOURCE_DIR}/include/util/Font.h
	${PROJECT_SOURCE_DIR}/include/util/Integer.h
	${PROJECT_SOURCE_DIR}/include/util/Math.h
	${PROJECT_SOURCE_DIR}/include/util/String.h
	${PROJECT_SOURCE_DIR}/include/util/Error.h
	${PROJECT_SOURCE_DIR}/include/version.h.in
)

if(TARGET_ARCH_FAMILY_X86)
	set(edb_SRCS
		${edb_SRCS}
		arch/x86-generic/ArchProcessor.cpp
		arch/x86-generic/RegisterViewModel.cpp
		arch/x86-generic/RegisterViewModel.h
		${PROJECT_SOURCE_DIR}/include/arch/x86-generic/ArchTypes.h
	)
elseif(TARGET_ARCH_FAMILY_ARM)
	set(edb_SRCS
		${edb_SRCS}
		arch/arm-generic/ArchProcessor.cpp
		arch/arm-generic/RegisterViewModel.cpp
		arch/arm-generic/RegisterViewModel.h
		${PROJECT_SOURCE_DIR}/include/arch/arm-generic/ArchTypes.h
	)
endif()

if(TARGET_PLATFORM_WINDOWS)
	enable_language(ASM_MASM)
	set(CMAKE_ASM_MASM_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /safeseh")

	set(edb_SRCS
		${edb_SRCS}
		LongDoubleX86.asm
		${PROJECT_SOURCE_DIR}/include/os/win32/OSTypes.h
	)
elseif(TARGET_PLATFORM_LINUX)
    set(edb_SRCS
        ${edb_SRCS}
		${PROJECT_SOURCE_DIR}/include/os/unix/OSTypes.h
        ${PROJECT_SOURCE_DIR}/include/os/unix/linux/linker.h
    )
endif()

if(GRAPHVIZ_FOUND)
	set(edb_SRCS
		${edb_SRCS}
		graph/GraphEdge.cpp
		graph/GraphicsScene.cpp
		graph/GraphicsScene.h
		graph/GraphNode.cpp
		graph/GraphWidget.cpp
		graph/GraphvizHelper.cpp
		graph/GraphvizHelper.h
		${PROJECT_SOURCE_DIR}/include/GraphWidget.h
		${PROJECT_SOURCE_DIR}/include/GraphEdge.h
		${PROJECT_SOURCE_DIR}/include/GraphNode.h
	)
endif()

add_executable(edb ${edb_SRCS})

if(GRAPHVIZ_FOUND)
	target_include_directories (edb
	PUBLIC
		${GRAPHVIZ_INCLUDE_DIRS}
	)

	target_link_libraries(edb
		${GRAPHVIZ_LIBRARIES}
	)
endif()

if(UNIX AND TARGET_ARCH_FAMILY_X86)
	# now we always have it :-)
	add_definitions("-DHAVE_GDTOA")
	if(GDTOA_FOUND)
		target_include_directories (edb
		PUBLIC
			${GDTOA_INCLUDE_DIRS}
		)

		target_link_libraries(edb
			${GDTOA_LIBRARIES}
		)
	else()
		target_link_libraries(edb
			gdtoa-desktop
		)

		add_dependencies(edb gdtoa_h)
	endif()
endif()

if (NOT DEFINED DEFAULT_PLUGIN_DIR)
	message(STATUS "Using default value of EDB Plugin directory")
	set(DEFAULT_PLUGIN_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/edb")
endif()
target_compile_definitions(edb PRIVATE -DDEFAULT_PLUGIN_PATH="${DEFAULT_PLUGIN_DIR}")

target_link_libraries(edb
	${CAPSTONE_LIBRARIES}
	Qt5::Widgets
	Qt5::Xml
	Qt5::XmlPatterns
	Qt5::Svg
	${DOUBLE_CONVERSION_LIBRARIES}
)

target_include_directories (edb PRIVATE
	"capstone-edb"
	"qhexview"
	"widgets"
	"session"
)


target_add_warnings(edb)

install (TARGETS edb DESTINATION ${CMAKE_INSTALL_BINDIR})

set_property(TARGET edb PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET edb PROPERTY CXX_STANDARD 17)
set_property(TARGET edb PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET edb PROPERTY ENABLE_EXPORTS TRUE)
set_property(TARGET edb PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test")
