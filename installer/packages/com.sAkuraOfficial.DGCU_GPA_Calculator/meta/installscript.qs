function Component() {
    // 构造函数
}

Component.prototype.createOperations = function() {
    component.createOperations();  // 调用基类的创建操作函数

    // 获取安装目标目录
    var targetDir = installer.value("TargetDir");
    // 定义快捷方式的路径
    var desktopPath = installer.value("HomeDir") + "/Desktop/东莞城市学院绩点计算器.lnk";

    // 定义快捷方式的命令
    var executablePath = targetDir + "/DGCU_GPA_Calculator.exe";  // 替换为你的可执行文件路径

    // 创建快捷方式
    component.addOperation("CreateShortcut",
                           executablePath,
                           desktopPath,
                           "workingDirectory=" + targetDir,
                           "description=My Application",
                           "iconPath=" + targetDir + "/DGCU_GPA_Calculator.exe");  // 替换为你的图标路径
}
