#Brian Lykes
#Lab 5

#g++ -o output1.cc 10sec.cpp
#g++ -o output2.cc 15sec.cpp
#g++ -o output3.cc 20sec.cpp
#g++ -o output4.cc 30sec.cpp

echo 10 seconds
time ./output1.cc

echo 15 seconds
time ./output2.cc

echo 20 seconds
time ./output3.cc

echo 30 seconds
time ./output4.cc
