CXX = g++
CXXFLAGS = -I ./Datastructures/tests -I ./Algorithms/Graph-Algorithms/tests

unit_test: unit_test_driver.o

	$(CXX) unit_test_driver.o