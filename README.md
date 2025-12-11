# Sokoban-MFC

A Windows **MFC implementation** of the classic Sokoban (推箱子) puzzle game.  
This project was created as a course final project and rewritten using **Microsoft Foundation Class (MFC)** to provide a graphical Windows GUI.

玩家需操作角色推動箱子，使所有箱子抵達目的地。

---

## Features

### 完整的推箱子遊戲邏輯  
- 支援 **151 個關卡**（`map000` ~ `map150`）  
- 元件支援：
  - Wall（牆）
  - Box（箱子）
  - Destination（目的地）
  - Arrival（箱子在目的地）
  - Worker（工人）
  - Blank（空白）

### MFC 圖形介面  
- 使用 `BitBlt()` 將 **32×32 BMP 圖片**畫在遊戲視窗  
- 資料由 Document 層管理  
- 由 View 層負責繪製與事件處理（鍵盤輸入）

### 支援多種鍵盤操作  
- WASD / HJKL / 方向鍵皆可操作  
- 可以切換關卡、重新開始、上一關、下一關  

### 自動判定過關  
當所有箱子都放在目的地 → 顯示過關訊息並自動進入下一關。

---

## Controls

| Key              | Function            |
|------------------|---------------------|
| **W / ↑**        | Move Up            |
| **S / ↓**        | Move Down          |
| **A / ←**        | Move Left          |
| **D / →**        | Move Right         |
| **H / J / K / L**| Vi-style movement  |
| **R**            | Restart level      |
| **P / PageDown** | Next level         |
| **O / PageUp**   | Previous level     |

---

## Project Structure

```text
Sokoban-MFC/
│
├─ BMP/                     # All bitmap graphics (wall, box, dest, worker…)
│     arrival.bmp
│     blank.bmp
│     box.bmp
│     destination.bmp
│     wall.bmp
│     worker.bmp
│
├─ Map/                     # 151 map files (map000 ~ map150)
│     map000
│     map001
│     ...
│     map150
│
├─ src/
│     Coordinate.cpp/.h        # Coordinate struct/class
│     framework.h              # MFC framework include
│     MainFrm.cpp/.h           # Main window frame
│     pch.cpp/.h               # Precompiled headers
│     resource.h               # Resource definitions
│     targetver.h              # Windows target configuration
│
│     Sokoban_ver_MFC.cpp      # Application class
│     Sokoban_ver_MFCDoc.cpp   # Game logic (map loading, movement)
│     Sokoban_ver_MFCView.cpp  # Rendering + keyboard control
│     Sokobanver_MFC.rc        # Resource script
│     Sokobanver_MFC.aps       # Resource cache (optional)
│     Sokoban_ver_MFC.vcxproj
│     Sokoban_ver_MFC.vcxproj.filters
│
└── Sokoban_ver_MFC.sln        # Visual Studio solution file
