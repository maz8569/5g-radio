# 5g-radio
Small simulation of RLC(Radio Link Control)/MAC(Medium Access Control) Layers in C++  
Built with C++20, CMake and GoogleTest. 

RLC: SDU + PDU, segmentation and priority  
MAC: Two scheduling strategies (Priority and FIFO) grant-based PDU transmission  
Channel: Random delay and packet loss  
Has thread-safe logging for debugging  

To run tests just use 
```
cmake --build . --target check
```
