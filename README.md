

# DGCU GPA Calculator

    
<br />

<p align="center">
  <a href="https://github.com/sAkuraOfficial/DGCU_GPA_Calculator">
    <img src="doc/images/logo.png" alt="Logo" width="150" height="150">
  </a>
  <h3 align="center">东莞城市学院绩点计算器</h3>
  <p align="center">
    <span style="display:block; margin-bottom:10px;">一款基于QT6的绩点计算器,结果可导出为Excel表</span>
    <br/>
    <img src="https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge" alt="MIT">
    <br/>
    <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="CPP">
    <img src="https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white" alt="QT">
    <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white" alt="CMAKE">
    <img src="https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white" alt="GIT">
    <br/>
    <a href="https://github.com/sAkuraOfficial/DGCU_GPA_Calculator/releases/tag/v1.0">立即下载</a>
    ·
    <a href="https://github.com/sAkuraOfficial/DGCU_GPA_Calculator/issues">报告Bug</a>
    ·
    <a href="https://github.com/sAkuraOfficial/DGCU_GPA_Calculator/issues">提出新特性</a>
  </p>
</p>

![alt text](doc/images/APP.png)
 
## 目录

- [DGCU GPA Calculator](#dgcu-gpa-calculator)
  - [目录](#目录)
    - [使用指南](#使用指南)
          - [如何下载安装](#如何下载安装)
          - [开发前的配置要求](#开发前的配置要求)
          - [编译项目](#编译项目)
    - [作者](#作者)
    - [版权说明](#版权说明)

### 使用指南

###### 如何下载安装

[国内:蓝奏云线路](https://haohao159.lanzouo.com/iYCOx256f3zc)
[国际:Github线路](https://github.com/sAkuraOfficial/DGCU_GPA_Calculator/releases/download/v1.0/installer.exe)

###### 开发前的配置要求

1. Visual Studio 2022 (可选MinGW + VS Code)
2. QT6
3. CMake
4. VCPKG
5. Git

###### 编译项目

1. 克隆项目
2. 安装仓库自带的VCPKG清单
3. 打开Visual Studio 2022, 点击`打开文件夹`, 打开本项目
4. 点击`生成`->`全部生成`即可完成编译

```sh
git clone https://github.com/sAkuraOfficial/DGCU_GPA_Calculator.git
cd ./DGCU_GPA_Calculator
vcpkg install
```

###### 打包项目

1. 开始菜单中打开`Qt 6.7.2 (MSVC 2019 64-bit)`命令行
2. 配置`MSVC`环境:
```powershell
"D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
```
3. 使用`windeployqt.exe`进行打包
```powershell
windeployqt.exe --no-quick-import --no-translations --no-system-d3d-compiler --no-system-dxc-compiler --no-opengl-sw --add-plugin-types styles,platforms,imageformats --skip-plugin-types qmltooling,generic --no-compiler-runtime --exclude-plugins qsvg,svgwidgets,qsvgicon ./DGCU_GPA_Calculator.exe
```

###### 安装包制作
1. 将打包好后的文件,放入`installer/packages/com.sAkuraOfficial.DGCU_GPA_Calculator/data`目录
2. 使用`Qt Installer Framework`进行安装包制作

命令参考:
```powershell
D:\Dev_Files\Qt\Tools\QtInstallerFramework\4.8\bin\binarycreator.exe" -c config/config.xml -p packages 东莞城市学院绩点计算器安装包.exe
```


### 作者

mchaohao159@outlook.com

### 版权说明

该项目签署了MIT 授权许可，详情请参阅 [LICENSE.txt](https://github.com/sAkuraOfficial/DGCU_GPA_Calculator/blob/master/LICENSE.txt)



