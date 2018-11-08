# Project Proposal

### Summary

I plan on making a 2d top-down RPG-style game. I am not 100% decided yet on the exact nature of the game but the genre is specific enough that the initial implementations will largely be similar regardless of the actual content. 

##### Where I want the game to go

I'm considering one of three paths. Whichever way I go, it'll be pretty graphics-intensive so I plan on starting on that right away. Story writing will depend on the game type. I will need to write up a baseline way to animate sprites, display windows, and (for two of the three) process movement, and handle collisions. These tasks are common among all the ideas and will also take up around 1/3 of the development time.

**A growing/gardening sim**

Plenty of these around, the advantage to this is that much of the gameplay will rely on waiting around for things to happen. Plants don't move much so there isn't anything to animate. There are plenty of opportunities to scale back, too, since if I was running out of time I could always just remove the top-down RPG aspect and just have screens with the plants growing realtime, based off the local clock.

**A quest-based game**

Easy to extend, easy to scale back. Main challenge would be that I'd have to implement dialogue, too, but that shouldn't be too bad. Quests might not be super fun in repetition, but the goal isn't to make an amazing game but rather to have something technically impressive.

**A debate or courtroom sim**

Here, this would take away from the 2d top down RPG aspect a bit. Think an Ace Attorney knockoff with a lot worse writing. Main challenge would be the sheer bulk of dialogue but this way there should be less graphical assets. Solving mysteries is always fun though, and this is probably the less boring of the three alternatives.

### Possible Libraries

##### [json](https://github.com/nlohmann/json)

This library handles processing jsons, and has a really easy way to save/load jsons from streams (like file streams). This is really useful if I want my game to be able to have save states or just in general remember where the player left off last time they opened the game.

##### [keyczar](https://github.com/google/keyczar)

Of course, a JSON isn't the most *secure* way to store save data. So if I implement saves I most likely will need to use some sort of encryption/decryption thing in order to prevent players from going in and giving themselves a million dollars and an Infinity Sword +1. This library, keyczar, offers a pretty simple way to encrypt and decrypt files, so I plan on using it for that purpose.

##### [tinyc2](https://github.com/RandyGaul/cute_headers)

Finally, this library (or rather, header file?) can handle most 2D collisions, and so is perfect for preventing the player from doing things like going through walls.

##### end notes

Other than those 3, I think the only other thing I'd use is oF's native sound library, and I've already used that in my snake game so it should be all good. I think what I mainly need to be careful of is making sure that I can get these 3 libraries interfacing with each other correctly.

### Other Resources

Free SFX generator: http://www.superflashbros.net/as3sfxr/

Free (with credit) background music repository: http://soundimage.org/

Free art: Paint Tool SAI and my hand

### Replacing openFrameworks?

This is extremely unlikely but I am *considering* possibly replacing openFrameworks with olcPixelGameEngine instead. It's mostly that PixelGameEngine allows for better rendering of images while preserving their resolution and not anti-aliasing them to blurry oblivion. However, given that I'm currently only familiar with openFrameworks, I don't *think* I'll change to using this but I will look into the possibility.

https://github.com/OneLoneCoder/olcPixelGameEngine/wiki
