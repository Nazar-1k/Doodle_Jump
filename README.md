# Doodle Jump
"Doodle Jump" is an exciting arcade game in which the player controls a funny little character who constantly bounces on different platforms. The goal is to reach the highest height and score the most points while avoiding obstacles and enemies.

# Controls:
Player jumps endlessly from platform to platform. Player movement is controlled by the arrow keys, adding acceleration in the respective direction up to the maximum allowed. Additionally, the player can shoot by pressing the left mouse button.

# Smooth player transition:
If the player reaches the edge (left/right) of the window, they smoothly transition to the opposite side.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/aed8a167-f5d8-414b-9044-ddb63e1f2a93)

# Animation:

The animation consists of three states: default state, jump state, and death state. These three states are encapsulated in a structure. Using this structure, three objects are created (LeftSprite, RightSprite, ShotSprite), and depending on the game conditions, the player switches between these sprites to create a simple animation.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/0f6ca739-354c-4a56-a57a-431b0dd3c165)

The shooting animation plays until the player stops shooting, with a slight delay after the shooting ends. If the player does not control the character after shooting ends, the player will be turned in the direction of movement.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/cc29c4b7-8621-4840-96bb-f58441b89fc0)

# Shooting
When fired, a projectile (resembling an egg) is formed in the nose of the Doodle and moves at a constant linear speed. There is a delay between shots. The direction of the projectile movement is controlled by the mouse cursor if the cursor is above the player, the projectile flies towards the cursor, and if it is below it, it flies upwards, imitating the original Doodle Jump game. This is done primarily to prevent downward shooting and to add complexity to the game.

Below are two scenarios that demonstrate different shooting behavior depending on the position of the mouse cursor.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/969acedf-d44c-4fb8-8602-4e89ebc64af7)

# Platforms

In the game, there are 5 types of platforms: regular, moving, trampoline, and two types that break upon landing. However, one can rebound from landing on one platform, while falling through another.

1. Default Platform
   
![BasePlatform](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/ad5746cf-e9db-4f49-8823-11a7c68cb62e)

3. Move Platform
   
![MovePlatform](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/4b873a7d-0120-447b-b639-bbf4b649a3e3)

5. Jump Platform (The platform from which you jump provides a 300% stronger boost compared to other platforms.)
   
![JumpPlatform](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/589da2c2-6eea-4ca7-b601-310d1e2fc67a)

7. HalphCrush Platform (The platform from which you can rebound, but it breaks after jumping from it.)

![HalphCrushPlatform](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/eea3f1d7-e3b5-4761-989c-e0c2d54969d2)


9. Crush Platform (The platform from which you cannot rebound; it breaks upon collision.)

![CrushPlatformDefault](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/91cd1bb4-a3f5-44c0-92e4-20902b3ab86a)

**Platforms are generated randomly, the higher the player climbs, the fewer there will be. The minimum number of platforms depends on the height of the player's jump.**

# Enemy

The game has enemies of three different sizes that are generated on platforms at certain intervals. To defeat an enemy, you can jump on top of it. In addition, enemies move left and right, which adds to the difficulty of avoiding/killing them.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/986516bb-156f-4e51-aa28-5b454f2f7d90)

# Abilyty

In the game, there are three types of abilities: score boost, jetpack, and shield. They are generated every 1000 points.

1. Jetpack
   
![ach-jetpack](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/278d63c6-f9f8-4628-8a9a-1ddedc7c6313)

2. Score Boost
   
![ach-super-bouncer](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/ef678830-be18-4005-b1e8-681e6431b088)

3. Shield
<img src="https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/d6237c9b-e12a-40d4-9913-1bb7b414c1d7" alt="Зображення зі щитом" width="40" height="40">

# Jetpack

When the player picks up the jetpack ability, it appears on the player's back, and it lasts for a specified amount of time. During flight, a simple fire animation plays.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/6bceca33-8fbe-4012-9aeb-cf11caa371d0)

# Shield

The shield (in the form of a bubble around the player) appears when the player gains the Shield ability. It protects the player from enemies and kills them on contact. The shield does not protect against holes. This ability lasts for 30 seconds, after which the shield disappears.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/defde87c-b02f-49e7-b36d-f491e9d2dc56)

# Hole

There are two types of holes in the game, white and black. They are generated at a given interval. And they have different effects on the player.

1. Black Hole (When the player falls into the black hole, it slowly sucks the player in with a smooth animation and kills them. Afterward, the game restarts.)

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/4a304bb3-1fbe-489c-ae46-6105627f61bc)

2. White Hole (It pushes the player to the outside, and the closer to the center of the hole the player is, the stronger the repulsive force)

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/f6003572-64a6-4a23-8a41-a3229da56895)

# Background

The game has a background consisting of 3 parts: the main part (blue grid), the bottom part (grass with eggs), and the top part, which includes the score and the number of platforms passed. The background automatically adjusts to the screen size.

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/9f9549ac-cbf3-474e-8dd3-793a38dc6e84)

In the upper left corner, the points earned during the game are counted

![image](https://github.com/Nazar-1k/Doodle_Jump/assets/82716260/30b04645-6d3e-401b-8e67-4f3e9243a33d)

In the upper right corner, there is a count of the number of platforms passed, including those destroyed while jumping on them.

# Loose Condition

There are three ways to lose the game: falling below the screen, dying from an enemy, or being sucked into the black hole. After losing, the game will restart after a delay of 0.7 seconds.

# Launching the game through the console
If you want to set a specific window width and height:  
```
./"Doodle Jump" -window 600 1000
```
If you don't want to set a specific width and height, just run the program without arguments and the window will automatically be set to 600 x 1000:
       
```
./"Doodle Jump" 
```
