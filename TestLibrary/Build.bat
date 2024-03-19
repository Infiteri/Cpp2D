@ECHO OFF

g++ -g -shared -ITestLibrary -IEngine/Source TestLibrary/*.cpp -LBin -lEngine -o Bin/TestLibrary.dll 