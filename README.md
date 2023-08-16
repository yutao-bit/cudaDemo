# cudaDemo
A simple cross-platform cuda demo for maxtrix multiply
# 参考：
https://zhuanlan.zhihu.com/p/34587739 
https://cuda-tutorial.readthedocs.io/en/latest/tutorials/tutorial01/

# 流程记录
平台：windows10，vscode，cmake
## 官网安装CUDA Toolkit
## cmakelist文件配置：
project(CUDADemo CUDA)#最后步骤发现vscode 中cmake build all异常后添加，之后build正常
find_package(CUDA)#自动找到nvcc，并设置CUDA_INCLUDE_DIRS，CUDA_LIBRARIES
include_directories(${CUDA_INCLUDE_DIRS})#可以包含cuda_runtime.h
## 问题定位
核函数写在main文件里，.cpp后缀
运行 nvcc main.cu -o main  提示找不到cl.exe（C/C++编译器），添加以下编译器PATH并重启vscode，可以找到了
添加PATH：C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64
提示<<<>>>无法识别，因为这是核函数标识，C++编译器无法解析，上步不应该使用cl编译器，因为核函数写在main文件里，.cpp后缀改成了.cu
运行 nvcc main.cu -o main 编译成功，生成了可执行文件
## 运行 nvprof .\main.exe无反应
感觉nvprof在nvcc附近，nvcc下找到nvprof.exe双击后提示：找不到cupti64_2023.2.1.dll，而nvcc双击后无提示直接结束运行
google发现这个dll就在临近目录：CUDA\v12.2\extras\CUPTI\lib64，添加到PATH中，并且重启VSCODE后nvprof命令正常
cmake build all有问题，怀疑是自动使用了C++的编译器，因为前两步的指令正常是shell中手敲的，cmakelist文件修改：project(CUDADemo CUDA)，后可以使用vscode cmake进行正常构建，编译，运行
# 小结
环境变量变化需要重启vscode？是的，很多问题靠的都是自然而然的直觉，相关性。
