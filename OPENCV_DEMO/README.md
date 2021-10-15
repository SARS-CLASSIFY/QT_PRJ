# QT5.9_OPENCV_DEMO

- WIN10平台QT5.9 opencv3.4.2调用示例

- OPENCV_DEMO为示例程序

- install文件夹下为cmake编译好的opencv3.4.2文件使用需添加系统环境变量

  ```
  *\install\x64\mingw\bin
  ```

  qt.pro文件中添加如下代码

  ```c++
  INCLUDEPATH += *\install\include\
                 *\install\include\opencv2\
                 *\install\include\opencv
  
  LIBS += -L *\install\x86\mingw\lib\libopencv_*.a
  ```

- [https://blog.csdn.net/Mr_robot_strange/article/details/110677323](详细移植步骤)

