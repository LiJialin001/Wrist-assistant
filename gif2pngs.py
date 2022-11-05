from PIL import Image  # 导入PIL的Image包
import os
gifFileName = "/Users/lijialin/Desktop/icon/icons8-activity.gif"  # 把gif图赋值给gifFileName
im = Image.open(gifFileName)  # 使用Image的open函数打开test.gif图像
pngDir = gifFileName[:-4]  # 倒着从gifFileName中的倒数第四个开始取字符（跳过.gif），赋值给pngDir，作为文件夹的名字
os.mkdir(pngDir)  # 用图片名创建一个文件夹，用来存放每帧图片，名字为pngDir的值
try:
  while True:  # 死循环
    current = im.tell()  # 用tell函数保存当前帧图片，赋值给current
    im.save(pngDir+'/'+str(current)+'.png')  # 调用save函数保存该帧图片
    im.seek(current+1)  # 调用seek函数获取下一帧图片，参数变为current帧图片+1
    # 这里再次进入循环，当为最后一帧图片时，seek会抛出异常，代码执行except
except EOFError:
    pass  # 最后一帧时，seek抛出异常，进入这里，pass跳过
