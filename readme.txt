      |\      _,,,---,,_
ZZZzz /,`.-'`'    -.  ;-;;,_
     |,4-  ) )-,_. ,\ (  `'-'
    '---''(_/--'  `-'\_)

kitty - ring 3 LD_PRELOAD rootkit

Table of Contents:
  [0x00000001] - Why I decided to post old code
  [0x00000002] - Usage
  [0x00000003] - Installation Options
  [0x00000004] - How the rootkit works
  [0x00000005] - Issues
  [0x00000006] - Future

[0x00000001]
  Why I decided to post old code:
    As of the time of making this repository, this code is 2 years old. I wrote it in 2022.
    The only reason I posted this was because I didn't want my profile to be empty until I wrote something new.
    There's probably a couple things I heavily dislike in this project but I'm not going to go and fix issues on something used as a placeholder.

[0x00000002]
  Usage:
    make - Normal Build
    make debug - Debug Build

  How to load rootkit:
    export LD_PRELOAD=$PWD/{filename}.so

[0x00000003]
  Installation Options:
    Normal Installation: Compiles the source code into one .so file called kitty.so.
    Debug Installation: Compiles the source code into one .so file called kitty_debug.so which includes debug information
                        such as the functions called and what the rootkit is doing at the moment.

[0x00000004]
  How the rootkit works:
    I will explain how this particular rootkit works, which keep in mind is very basic and doesn't even include a backdoor which is standard
    in most modern rootkits, however keep in mind this was made for fun/experience.

    The rootkit utilises something called "LD_PRELOAD". LD_PRELOAD is an environment variable that we use to load our .so file before any other library.

    In the src/ folder there is a hooks.c file in which we have a lot of functions with familiar names. How our "hooking" works is the following way:
      - Using the function dlsym() and the RTLD_NEXT pseudo-handle we obtain the address of these wrapper functions.
      - We modify the way a specific function works by adding a couple rules it has to follow.
      - We invoke the "real" function afterwards.
    
    Unfortunately for simplicity sake it does not include a backdoor (accept() is really common), and it does not hide its presence.

[0x00000005]
  Issues:
    It can be spotted using ldd (which can be circumvented via hooking execve()). 
    
    If you edit the /etc/ld.so.preload file and put the location of the .so in there, the directory where the rootkit is will be seen
    and obviously later then removed by the person you infected.
    
    Albeit if they tried to delete the rootkit .so file instead of just clearing /etc/ld.so.preload for some odd reason, they would run into issues
    as both rmdir() and unlink(at) are hooked and won't delete the kitty files. Also if you're thinking of just renaming the files and then deleting,
    that won't work either.

[0x00000006]
  Future:
    As you might have read by now, this is old code and I do not intend to update it. My old wishes will be listed below this.
    
    I am not fully satisifed with this as I have learnt a lot while writing this rootkit and reading other people's code.

    I will make another LD_PRELOAD rootkit and here are some of the features that are going to be included:
      - LDD will not show the .so after running it.
      - There will be an accept() backdoor included.
      - All important strings will be xor'd.
      - The rootkit directory will be hidden at a random location on the file system.
      - It will automatically uninstall itself for a bit if someone is trying to find it.
      - /etc/ld.so.preload will be useless as the rootkit will be loaded from somewhere else.
      - The rootkit will actually be persistent this time.
    
    As far as the hooks go, it will look a lot better, as I originally wrote them like I saw in a, now deleted, Github repository of a small rootkit made by one of my friends.
