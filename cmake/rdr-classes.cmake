include(FetchContent)

message(STATUS "RDR-Classes")

FetchContent_Declare(
    RDR-Classes
    GIT_REPOSITORY https://github.com/xesdoog/RDR-Classes.git
    GIT_TAG        3f297052ab325d99b9c8e419d4576bdcfb3e4438
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(RDR-Classes)
set_property(TARGET RDR-Classes PROPERTY CXX_STANDARD 23)