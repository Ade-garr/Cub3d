### Welcome to my Cub3D repository 👋

⭐️ This project is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. Exploring ray-casting, the goal is be to make a dynamic view inside a maze, in which you can move freely.

<p align="center">
	<img src="./cub3D.gif" >
</p>

## 💡 Usage

Install the minilibx on your system :

```
cd minilibx-linux
make
sudo cp libmlx.a /usr/local/lib
sudo cp mlx.h /usr/local/include
cd ..
```

Then run the following commands :

```
make bonus
./Cub3D maps/map1.cub
```

Feel free to change the maze and other parameters in the .cub files !

## 🔑 Controls
<kbd>Z</kbd> <kbd>Q</kbd> <kbd>S</kbd> <kbd>D</kbd> / <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> : Move and Strafe<br>
<kbd>Shift</kbd> : sprint (beware your endurance bar!)<br>
<kbd>Ctrl</kbd> : crouch<br>
<kbd>Esc</kbd> : quit<br>


⚠️ Subject given slightly differs from actual project.<br>
⚠️ System required : Linux