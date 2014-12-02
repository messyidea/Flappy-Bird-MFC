##用mfc制作的flappy bird 小程序<br>

---
游戏为MFC实现，因为游戏是画面类的程序，所以主要部分放在MFC框架的View类里面。<br>

游戏主要分为3部分：startgame部分，runninggame部分和replaygame部分。<br>

①	Startgame部分：<br>
该部分主要由StartUI函数构成。此部分比较简单，只是显示了一张自己做的游戏开始界面，上面有操作的提示，然后实现了一个onlbuttondown的监听器，当用户点击屏幕后启动Startgame函数开始游戏。这种方式虽然不怎么华丽，但是比较简洁，符合游戏的整体特性。<br>
② runninggame部分：<br>
该部分主要由RuningUI函数构成。RunningUI在Ondraw()中被调用，MFC中所有的绘图函数都应该放在Ondraw()函数里面。RunningUI函数里面绘制了小鸟，水管，背景。先前Startgame函数调用后，开启了游戏进行所需要的计时器，自动控制小鸟下落，水管和背景自动移动。剩下的就只有操控了，在onlbuttondown里面添加了点击的监听器，当游戏进行并且有点击事件发生，那么小鸟将发生跳跃。<br>
当小鸟跳跃之后如果撞到地上或者撞到水管，那么游戏结束，进入replay界面。<br>
③	replaygame部分:<br>
该部分也比较简单，只是实现了一个显示游戏得分、奖牌的作用，还有一个历史最高分，数据用C++文件流写入到data文件中。当进入replaygame界面并且点击了重新开始的按钮之后，游戏会自动重新开始。若点击关闭按钮，游戏自动关闭，并进行析构释放资源。<br>

---

#流程<br>
![](https://github.com/messyidea/Flappy-mfc/raw/master/流程.png) <br>

#演示<br>
![](https://github.com/messyidea/Flappy-mfc/raw/master/1.png) <br>
![](https://github.com/messyidea/Flappy-mfc/raw/master/2.png) <br>
![](https://github.com/messyidea/Flappy-mfc/raw/master/3.png) <br>
