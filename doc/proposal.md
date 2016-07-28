
Both of us are enjoy the Unix class and would like our project to involve Unix utilities in some way. We talked briefly to Professor Bualuan about our ideas, and he told us that making a new utility would be best done in C because it doesn't (naturally) lend itself to object oriented programming. Instead, we came up with a few ideas of things we could do in C++ that used existing Unix utilities to make something cool. 

The idea that struck us as being useful and relevant to both Unix and OOP was creating a FTP Gui that allowed you to drag and drop files from your computer to a remote. This would be useful in situations such as Intro to Engineering II where you had to use the annoying webfile servers, or for other engineers who aren't as adept at using the terminal but still need to access files in remote machines. Additionally, we talked to Professor Bui, who gave us the idea of a peer to peer file transfer program, or a rudimentary browser (whose framework could be obtained from QT). Since you have much more experience with estimating the difficulty and scope of these projects, we thought you could glance these over and let us know if they were feasible or not.



FTP Gui written in C++
======================
- could probably use the CkSFtp C++ library

- ability to connect to a computer and transfer files visually

- two "panes", one for destination, one for source

- a couple of switches and buttons e.g. copy or move...delete..

- beautiful GUI of course

- maybe other features? 


OOP: Each button will be an object, the windows will be objects....each file will be an instance of an object.

- File object will be the parent object of actual files, directories and binaries.

- You'll have the option of viewing the text of text files as well



Other ideas



Peer to peer file transfer utility
==================================

- can quickly send files to another person, takes out the middle man for github & other sharing

- a useful resource for when you have to share code quick

- can easily see if someone else is on, specifically target someone or several persons to send the thing to

- perhaps sync the files? rsync


Web browser
===========

- QT has a library that gets the basics done for you

- Needs to save bookmarks, write scripts, etc
 
- One idea could be to have tmux-like divisions in the browser, with each pane doing something. For example,
  the left half of the window could be a browser, the top right could be used to input and recieve wolfram alpha queries
  and the bottom right side could be used for taking notes.

- Would have to think about more ideas / but a cool way to use unix networking commands


