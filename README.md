<img src="https://github.com/LakshyaKhatri/Assistant/blob/master/assets/logo/logo.png" alt="Assistant logo" title="Assistant" align="right" height="200" />

Assistant
=========
[![](https://img.shields.io/badge/developed%20in-C%2B%2B-blue.svg)](http://www.cplusplus.org/)
[![](https://img.shields.io/badge/build%20with-%F0%9F%96%A4-pink.svg)](https://en.wikipedia.org/wiki/Love)
[![](https://img.shields.io/badge/version-1.0-blue.svg)](https://www.youtube.com/watch?v=dVjXoSZKHDs)

A personal assistant that was developed by me when I was learning c++ programming.  
Yes! It actually speaks. :D

## What Assistant Can Do for Me?
Well well! Have a look at these features:
* Assistant can actually talk to you.
* Ask your Assistant to perform basic mathematical operations.
* It can play songs for you.
* Don't you know what day is today? Ask your Assistant then.
* Not Satisfyied? You can add your own functionalities too.
* And, Assistant is not married yet!

## Demo
Click to play video:

[![Demo](https://github.com/LakshyaKhatri/Assistant/blob/master/assets/demo_image.png)](https://www.youtube.com/watch?v=dVjXoSZKHDs&t=6s)
## Dependencies
* Currently Assistant works only on *Windows 10* version of windows platform.
* For linux you need to install [Espeak](http://espeak.sourceforge.net/). Just type these commands in the terminal:  
```sh
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install espeak
```

## Installation & Usage
* **For Windows:** 
  1. Download the repository.
  2. Go to the *windows/* directory in the project.
  3. Start main.exe.
  4. Have fun.
  
* **For Linux:** 
  1. Download the repository.
  2. make sure you have installed all the dependencies.
  3. Go to *linux/* directory in the project from terminal.
  4. type `./main` in the terminal.
  5. Have fun in linux too.
  
## How to Add/Delete/Change Commands?
**Genral Commands:**
  * If you are using Windows then start `createCommandFile.exe`.
  * If you are on Linux then go in terminal and type `./createCommandFile`.
  * Choose the option for whatever editing you need and press enter.
  * Perform the edting.

> *__Note:__*  
> 1. *Do not add any punctuation marks at the end of the orders. Assistant will automatically handle them.*
> 2. *You need to add punctuations marks in the respnses for explaining proper expressions to the Assistant for speaking.*  

**Math Opearions:**  
All the steps are same but instead of `createCommandFile.exe` use `mathCommandFile.exe`  and in linux use `./mathCommandFile` instead of `./createCommandFile`.  

**Advanced Operations:**  
Advance operaions include playing music and telling dates. You can add keywords for trigerring your advance commands and then edit the respond in `AdvanceCommandFile.cpp`.

## Contribution
You can fork the repository and make any changes you want. I would love to see the changes ♡.  


-----------------------------------------------------------
