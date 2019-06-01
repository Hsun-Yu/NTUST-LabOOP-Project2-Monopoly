# NTUST_LabOOP_Project2_Monopoly

 ## Distribution
- [ ]	基本規則(30%)
  見下方(Baserule)
- [X]	基本地圖(10%)
  顯示地圖(需要完成讀檔功能)
  見下方(basemap.txt)
- [X]	存/讀檔功能(20%)
  可以記錄當前所有遊戲狀態，及讀取。
  見下方(basemap.txt)
- [X]	基本操作(10%) 
  l使用方向鍵移動游標
  l使用Enter確定
- [X]	遊戲選單(5%)
  使用Esc叫出選單。

- [X]	遊戲狀態(5%)
  顯示當前角色資訊。
- [ ]	基本道具(5%)
  (需完成兩項)遙控骰子:可以指定(1~6)的步數前進。路障:放置於物件上，玩家碰到當回何停在此格。
- [X]	機會/命運(5%)
  (有一種即可)隨機獎勵/懲罰。(可參考下表)
- [ ]	銀行系統(5%)
  存款、借款。
- [ ]	股票系統(15%)
  (需完成銀行)現金可以買物產、存款可以買股票。股票須漲停跌停等等
- [ ]	美觀(10%)
  遊戲整體美觀。
- [ ]	SC(15%)
  Something cool，額外實作的特殊功能。
 ## Format of file
- base 20 4
- 00 地球 0
- 01 月球 1 2000 500 1000 3000 5000
- 02 火星 1 700 200 500 1000 3000
- 03 木星 1 750 200 600 1200 3200
- 04 命運 -1
- 05 土星 1 2000 500 1000 3000 5000
- 06 天王星 1 2000 500 1000 3000 5000
- 07 白洞 -3
- 08 海王星 1 2000 500 1000 3000 5000
- 09 冥王星 1 2000 500 1000 3000 5000
- 10 天狼星 1 2000 500 1000 3000 5000
- 11 織女星 1 2000 500 1000 3000 5000
- 12 牡羊座 1 2000 500 1000 3000 5000
- 13 金牛座 1 2000 500 1000 3000 5000
- 14 太空站 -4
- 15 雙子座 1 2000 500 1000 3000 5000
- 16 巨蟹座 1 2000 500 1000 3000 5000
- 17 獅子座 1 2000 500 1000 3000 5000
- 18 機會 -2
- 19 處女座 1 2000 500 1000 3000 5000
- 20 天秤座 1 2000 500 1000 3000 5000
- 21 黑洞 -5
- 22 射手座 1 2000 500 1000 3000 5000
- 23 摩羯座 1 2000 500 1000 3000 5000
- 24 水瓶座 1 2000 500 1000 3000 5000
- 25 雙魚座 1 2000 500 1000 3000 5000
- 26 水星 1 2000 500 1000 3000 5000
- 27 金星 1 2000 500 1000 3000 5000
- playerstate 0
- 0 00 30000 -1 01 3 02 1 03 1 05 1 06 1 -2 01 01 -3 01 -4 10000
- 1 21 30000 -1 08 1 09 1 10 1 11 1 12 1 13 1 -2 02 01 -3 02 -4 50000
- 2 24 30000 -1 15 1 16 1 17 1 19 1 20 1 -2 01 03 -3 03 -4 800
- 3 27 30000 -1 22 1 23 1 24 1 25 1 26 1 27 1 -2 01 -3 01 -4 0

- playerstate formate
- -1=local
- -2=stock
- -3=tool
- -4=bank money
  


  
 


  
 


  
 

