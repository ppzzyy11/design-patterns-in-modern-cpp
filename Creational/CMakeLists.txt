project(Creational)


add_executable(AbstractFactory Creational/AbstractFactory.cpp)
add_executable(BoostDI Creational/BoostDI.cpp)
add_executable(BoostDIDemo Creational/BoostDIDemo.cpp)
add_executable(Builder Creational/Builder.cpp)
add_executable(DIP Creational/DIP.cpp)
add_executable(Facets Creational/Facets.cpp Creational/Person.cpp Creational/PersonBuilder.cpp Creational/PersonJobBuilder.h Creational/PersonAddressBuilder.h)
add_executable(FactoryMethod Creational/FactoryMethod.cpp)
add_executable(GroovyStyle Creational/GroovyStyle.cpp)
add_executable(InnerFactory Creational/InnerFactory.cpp)
add_executable(LSP Creational/LSP.cpp)

set(Boost_DEBUG ON)



#find_package(Boost 1.81.0 REQUIRED ALL)
find_package(Boost CONFIG REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(MaybeMonad Creational/MaybeMonad.cpp)
target_link_libraries(MaybeMonad PRIVATE Boost::serialization)


add_executable(Monostate Creational/Monostate.cpp)
add_executable(OCP Creational/OCP.cpp)

add_executable(Prototype Creational/Prototype.cpp)
target_link_libraries(Prototype PRIVATE Boost::serialization)

add_executable(Serialization Creational/Serialization.cpp)
target_link_libraries(Serialization PRIVATE Boost::serialization) 
add_executable(SingletonTests Creational/SingletonTests.cpp)
add_executable(SRP Creational/SRP.cpp)
add_executable(UnknownExercise Creational/UnknownExercise.cpp)



# UT style
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(BuilderCodingExercise_UT Creational/BuilderCodingExercise.cpp)
target_link_libraries(BuilderCodingExercise_UT GTest::gtest_main)

add_executable(FactoryCodingExercise_UT Creational/FactoryCodingExercise.cpp)
target_link_libraries(FactoryCodingExercise_UT GTest::gtest_main)

add_executable(SingletonCodingExercise_UT Creational/SingletonCodingExercise.cpp)
target_link_libraries(SingletonCodingExercise_UT GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(BuilderCodingExercise_UT)

include(GoogleTest)
add_executable(PrototypeCodingExercise_UT Creational/PrototypeCodingExercise.cpp)
target_link_libraries(PrototypeCodingExercise_UT GTest::gtest_main)
