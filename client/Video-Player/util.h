#ifndef UTIL_H
#define UTIL_H


#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QIcon>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>



//从文件路径中提取文件名
inline QString getFileName(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}


//封装日志宏
#define TAG QString("[%1:%2").arg(getFileName(__FILE__),QString::number(__LINE__))
//noquote是qDebug()中的成员函数，制定输出时候去掉引号
#define LOG() qDebug().noquote()<<TAG


//读文件操作，从指定文件中，读取所有二进制内容，将其保存在QByteArray
static inline QByteArray loadFileToByteArray(const QString& fileName)
{
    QFile file(fileName);
    bool ok=file.open(QFile::ReadOnly);
    if(!ok)
    {
        LOG()<<"文件打开失败";
        return QByteArray();
    }
    QByteArray content = file.readAll();
    file.close();
    return content;
}

//写文件操作，讲QByteArray中的内容写入到指定文件中
static inline void writeByteArrayToFile(const QString fileName, const QByteArray& content)
{
    QFile file(fileName);
    bool ok=file.open(QFile::WriteOnly);
    if(!ok)
    {
        LOG()<<"文件打开失败";
        return;
    }
    file.write(content);
    file.flush();
    file.close();
}


static inline QIcon makeCircleIcon(const QByteArray& imageData, int radius)
{
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    if(pixmap.isNull())
    {
        return QIcon();
    }

    // 图片：40*20-->宽高比：2:1，Qt::IgnoreAspectRatio作用：忽略缩放过程中的宽高比  60*60-->1:1
    // 此处忽略没有任何问题，因为头像18*18，现在想起放到到60*60，宽高比没有发生变化
    // Qt::SmoothTransformation: 平滑的转换算法，缩放之后的图片质量更高，缺陷：可能会牺牲一些速度
    pixmap = pixmap.scaled(radius*2, radius*2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


    // 将pixmap裁剪成原型的
    // 先要创建绘图设备(画布)--透明
    QPixmap output = QPixmap(pixmap.size());
    output.fill(Qt::transparent);   // 将绘图设备的背景设置成透明
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);

    // 创建圆形裁剪路径
    QPainterPath path;
    path.addEllipse(0, 0, radius*2, radius*2);
    // 设置裁剪路径，裁剪路径的作用：限制绘图操作的范围，直摇头在裁剪路径内的区域才会被裁剪
    painter.setClipPath(path);

    painter.drawPixmap(0, 0, pixmap);

    QIcon icon(output);
    return icon;
}


#endif // UTIL_H
