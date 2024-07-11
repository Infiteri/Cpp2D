@ECHO OFF

g++ -g -shared -I../TestLibrary -I../Engine/Source ../TestLibrary/*.cpp -L. -lEngine -o TestLibrary.dll 