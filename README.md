Assignment（工作分配）
===

可以用來隨機分配工作！

使用說明
---
請創建一個檔案叫做input.txt （可以把input_example.txt改名即可）
把input.txt按照指定格式打好：
```
rooms:
房號1 人名1
房號2 人名2

works:
工作1
工作2

dates:
10/09（五）
10/23（五）
11/06（五）
11/20（五）
12/04（五）
12/18（五）
01/01（五）
01/15（五）

header:
人\deadline

notes:
浴室跟廁所請選當週最髒的掃
記得填一下聚會出席表
```

編譯
```
make

或者

g++ -o assignment assignment.cpp
```

執行
```
Linux/Mac:
./assignment [讀入檔名（預設為input.txt）] [輸出檔名（預設為output.csv）]

Windows:
assignment.exe [讀入檔名（預設為input.txt）] [輸出檔名（預設為output.csv）]
```

用Excel開啟輸出結果output.csv即可