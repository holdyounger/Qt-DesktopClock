![Alt](https://repobeats.axiom.co/api/embed/de530e946e79af1ebe07f180d49cb3a3de2ee74a.svg "Repobeats analytics image")

# OneForYou❤️
> 不局限与知乎上文案对我的吸引，想整理并能在生活工作中随时看到，因此想做一款桌面显示的软件
> 编译环境： Qt5.9.9 MSVC 2017 64bit

> 想法来自知乎、各公众号、句读等与文案相关的场景。借以整理
>
> [点这里㊙](https://www.yuque.com/docs/share/78da571b-0bd6-428e-93db-b5673b487d30?#%20%E3%80%8AOneForYou%E3%80%8B)

适用🤔：


- 代码逻辑简单
- 适合新手完
- 适合`qss`学习
- 有建议可以随时提

Release：

> [V1.1.0](#V1.1.0)




## ✉️文案

### 文案类型

| **文本类型** | **彩虹屁**🌈 | **情绪**😄 | **鸡汤**🐤 | **情话**💌 | **文案**📑 |
| ------------ | ----------- | --------- | --------- | --------- | --------- |
|              |             |           |           |           |           |

| **文本来源** | **知乎** | **句读** | **小红书** | **每日诗词** | 每日一言 | **自定义**（暂时还未实现） |
| ------------ | -------- | -------- | ---------- | ------------ | -------- | -------------------------- |
|              |          |          |            |              |          |                            |

## 📊程序数据来源

> 目前是从CSV文件读取内容展示在界面

- [x] CSV数据

- [x] API

最终是保存到SQLite中

- [ ] SQLite

## 💄界面

![img](ReadMe.assets/window.png)

![img](ReadMe.assets/windowhover.png)



## 四、🚀功能 

## 1. ⏬双击切换

在界面双击即可切换文案

![img](ReadMe.assets/doubleclick.gif)

## 2. 🍼更换源

![img](ReadMe.assets/source.gif)

## 3. 🌈更换颜色

1. 更换文案颜色

![img](ReadMe.assets/fontautocolor.gif)

![img](ReadMe.assets/fontcustomcolor.gif)

1. 更换时钟颜色

![img](ReadMe.assets/timecolor.gif)

## 4. 🕓更换切换时间

![img](ReadMe.assets/timechange.gif)

## 5. 😉隐藏界面 

点击界面，按`ESC`即可隐藏。

# V1.1.0

## 功能添加

> 将展示过的句子保存到数据库中并展示
