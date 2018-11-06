cmake_minimum_required(VERSION 2.8)
project(frednator)

add_definitions(-DDEBUG_PERCEPTION)

#########################################################
# FINDING QIBUILD
#########################################################
find_package(qibuild)

#########################################################
# INCLUDE THE QIBUILD'S QT MODULES
#########################################################
include(qibuild/modules/qt-tools)
include(qibuild/modules/qt_qtcore-config)
include(qibuild/modules/qt_qtgui-config)

#########################################################
# SOURCES
#########################################################
set(_srcs
  mainwindow.cpp
  mainwindow.h
  videoThread.cpp
  videoThread.hpp
  controller.cpp
  controller.hpp
  main.cpp
  Arquivos-do-competionCode/unboard/unBoard.cpp
  Arquivos-do-competionCode/unboard/BehaviorRequest.hpp
  Arquivos-do-competionCode/thread/threadClass.cpp
  Arquivos-do-competionCode/module/basemodule.cpp
  Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/balldetectorrapha.cpp
  Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/balldetectorrapha.h
  Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/include/*.h
  Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/src/*.cpp
  Classes-Externas-Ao-CompetionCode/Raphael-NovoBallDetector/include/*.hpp
)

#Behaviour Sources
set(B_SRCS
    Arquivos-do-competionCode/behavior/src/behavior.cpp #PLAYING
    Arquivos-do-competionCode/behavior/src/BehaviorBase.cpp
    Arquivos-do-competionCode/behavior/src/Start.cpp
    Arquivos-do-competionCode/behavior/src/LookForBall.cpp
    Arquivos-do-competionCode/behavior/src/LookAround.cpp
    Arquivos-do-competionCode/behavior/src/Sonar.cpp
    Arquivos-do-competionCode/behavior/src/walkBall.cpp
    Arquivos-do-competionCode/behavior/src/Avoid.cpp
    Arquivos-do-competionCode/behavior/src/movingAverage.cpp
    Arquivos-do-competionCode/behavior/src/WalkInit.cpp
    Arquivos-do-competionCode/behavior/src/WalkRandom.cpp
    Arquivos-do-competionCode/behavior/src/turn.cpp
    Arquivos-do-competionCode/behavior/src/readyWalk.cpp #READY
    Arquivos-do-competionCode/behavior/src/readyTurn.cpp
    Arquivos-do-competionCode/behavior/src/readyWait.cpp
    Arquivos-do-competionCode/behavior/src/GmCtrlFinished.cpp #GAME CONTROL STATES
    Arquivos-do-competionCode/behavior/src/GmCtrlInitial.cpp
    Arquivos-do-competionCode/behavior/src/GmCtrlPenalized.cpp
    Arquivos-do-competionCode/behavior/src/GmCtrlPlaying.cpp
    Arquivos-do-competionCode/behavior/src/GmCtrlReady.cpp
    Arquivos-do-competionCode/behavior/src/GmCtrlSet.cpp
    Arquivos-do-competionCode/behavior/src/BallClose.cpp
    Arquivos-do-competionCode/behavior/src/Kick.cpp
    Arquivos-do-competionCode/behavior/src/postKick.cpp
    Arquivos-do-competionCode/behavior/src/approachBall.cpp
    Arquivos-do-competionCode/behavior/src/faceBall.cpp
    Arquivos-do-competionCode/behavior/src/faceBall.cpp
    Arquivos-do-competionCode/behavior/src/staticTest.cpp
    Arquivos-do-competionCode/behavior/src/roundBall.cpp
    Arquivos-do-competionCode/behavior/src/pickUp.cpp
    )
#Communication Sources
set(C_SRCS
    Arquivos-do-competionCode/communication/src/communication.cpp
    Arquivos-do-competionCode/communication/src/UdpInterface.cpp
    )

#Perception Sources
set(P_SRCS
    Arquivos-do-competionCode/perception/src/ballDetector.cpp
    Arquivos-do-competionCode/perception/src/ballDetector2.cpp
    Arquivos-do-competionCode/perception/src/ballCandidateANN.cpp
    Arquivos-do-competionCode/perception/src/perception.cpp
    Arquivos-do-competionCode/perception/src/fieldDetector.cpp
    Arquivos-do-competionCode/perception/src/fieldDetector2.cpp
    Arquivos-do-competionCode/perception/src/goalDetector.cpp
    Arquivos-do-competionCode/perception/src/lineDetector.cpp
    Arquivos-do-competionCode/perception/src/yellowDetector.cpp
    Arquivos-do-competionCode/perception/src/ellipseDetector.cpp
    Arquivos-do-competionCode/perception/include/*.hpp
    )

#Motion Sources
set(M_SRCS
    Arquivos-do-competionCode/motion/src/motion.cpp
    Arquivos-do-competionCode/motion/runswift/motion/MotionAdapter.cpp
    Arquivos-do-competionCode/motion/runswift/motion/MotionOdometry.cpp
    Arquivos-do-competionCode/motion/runswift/motion/SonarRecorder.cpp
    Arquivos-do-competionCode/motion/runswift/motion/effector/AgentEffector.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/ActionGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/BodyModel.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/ClippedGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/DeadGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/DistributedGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/HeadGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/NullGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/PendulumModel.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/RefPickupGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/StandGenerator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/Walk2014Generator.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/WalkCycle.cpp
    Arquivos-do-competionCode/motion/runswift/motion/generator/WalkEnginePreProcessor.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/AgentTouch.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/FeetState.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/FilteredTouch.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/NullTouch.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/SensorOutput.cpp
    Arquivos-do-competionCode/motion/runswift/motion/touch/TorsoStateFilter.cpp
    Arquivos-do-competionCode/motion/runswift/perception/kinematics/Kinematics.cpp
    Arquivos-do-competionCode/motion/runswift/perception/kinematics/Parameters.cpp
    Arquivos-do-competionCode/motion/runswift/perception/kinematics/Pose.cpp
    Arquivos-do-competionCode/motion/runswift/perception/kinematics/Kinematics.cpp
    Arquivos-do-competionCode/motion/runswift/perception/kinematics/SonarFilter.cpp
    Arquivos-do-competionCode/motion/runswift/perception/vision/Camera.cpp
    Arquivos-do-competionCode/motion/runswift/types/XYZ_Coord.hpp
    Arquivos-do-competionCode/motion/runswift/gamecontroller/RoboCupGameControlData.cpp
    Arquivos-do-competionCode/motion/runswift/utils/options.cpp
    Arquivos-do-competionCode/motion/runswift/utils/Timer.hpp
    )

#########################################################
# SETUP QT
#########################################################

# Qt headers that need be processed by 'uic' to generate 'moc' files
set(q_HEADERS mainwindow.h controller.hpp videoThread.hpp)

# Qt user interface files to be processed
set(q_UI ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

# Qt resources files
set(q_RCCS resources.qrc)

# Include files generated to be included in the compilation
#INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/motion/include
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/perception/include
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/communication/include
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/behavior/include
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/unboard
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/thread
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/common
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/module
${CMAKE_CURRENT_SOURCE_DIR}/Arquivos-do-competionCode/motion/runswift
${CMAKE_CURRENT_SOURCE_DIR}/Classes-Externas-Ao-competionCode/
)

# Wrap the files to generate all neccesary 'moc' and 'ui' files
QT4_ADD_RESOURCES(q_HEADERS_RCCS ${q_RCCS})
QT4_WRAP_CPP(q_HEADERS_MOC ${q_HEADERS})
QT4_WRAP_UI(q_HEADERS_UI ${q_UI})

#########################################################
# RUN BASH SCRIPT
#########################################################

#Make the script possible to be executed
FILE(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/copyIcon.sh
"mv ${PROJECT_NAME}.desktop ~/.local/share/applications/
chmod +x ~/.local/share/applications/${PROJECT_NAME}.desktop")

execute_process(COMMAND chmod +x copyIcon.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

FILE(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop
"[Desktop Entry]
Name=${PROJECT_NAME}
GenericName=${PROJECT_NAME}QT
Comment=QT Simulator for NAO robot.
Type=Application
Categories=Qt;NaoRobot;Simulation;VideoRecording;
Terminal=false
Icon=${CMAKE_CURRENT_SOURCE_DIR}/unbeatablesicon.png
Exec=${CMAKE_CURRENT_BINARY_DIR}/sdk/bin/${PROJECT_NAME}")

execute_process(COMMAND ./copyIcon.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

execute_process(COMMAND rm copyIcon.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})




#########################################################
# OTHER THINGS
#########################################################
#Disable BOOST Useless warning
add_definitions(-DBOOST_SIGNALS_NO_DEPRECATION_WARNING)
#add_definitions(-DCMAKE_TOOLCHAIN_FILE=/home/yuri/nao/devtools/naoqi-sdk-2.1.3.3-linux64/toolchain-pc.cmake)


#########################################################
# CREATE BINARY FILE AND ADD LIBRARIES
#########################################################
# Create a executable named video_recorder
qi_create_bin(${PROJECT_NAME} ${_srcs} ${q_HEADERS_MOC} ${q_HEADERS_UI} ${q_HEADERS_RCCS} ${P_SRCS})
qi_use_lib(${PROJECT_NAME} ALCOMMON ALPROXIES BOOST ALVISION OPENCV2_CORE OPENCV2_HIGHGUI OPENCV2_IMGPROC OPENCV2_OBJDETECT OPENCV2_ML OPENCV2_VIDEO QT_QTCORE QT_QTGUI)

