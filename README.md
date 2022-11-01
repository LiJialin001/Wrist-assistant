# Wrist-assistant
A smart watch project based on esp32



# 规范

## 命名注释
- 变量采用[匈牙利命名法](https://zh.m.wikipedia.org/zh-hans/%E5%8C%88%E7%89%99%E5%88%A9%E5%91%BD%E5%90%8D%E6%B3%95)
- 引脚号必须使用label代替

## 平台
暂时采用 ESP-IDF

## 文件树





## Git规范
### 不得push编译相关文件
### 功能修改/更新
先pull主分支，再merge新分支，更改都在自己开的分支中进行，主分支仅用于merge操作，确认不需要修改后及时删除开的分支。
### commit - m
格式为[%type] - %msg
type： 本次操作类别
- New 新增
- Del 删除
- Fix 修正
- Mix 多种操作
- msg：附加的说明信息，务必是能让其他人看懂



## log规范

使用串口实现log输出，打印的Log的级别是能真实反映此Log对应的级别，标签、Log内容具有很好的可读性

### 各个Log等级的使用
Debug
> 用于调试的信息，编译进产品，但可以在运行时关闭

Info
> 例如一些运行时的状态信息，这些状态信息在出现问题的时候能提供帮助

Warning
> 警告系统出现了异常，即将出现错误

Error
> 系统已经出现了错误



# 外设





# 工具



