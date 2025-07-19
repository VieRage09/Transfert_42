common language = one or more processes that run in back-ground rather than under user's control

---
# Basic use

-> Display notification
-> Clock synchronization 
-> mail servers
-> can be used as HTTP server
etc...
==> Usually answer network requests, hardware activity or other programs
server programs' name usually ends with a d for daemon
# Daemon on UNIX

-> Process which has init (process 1) as a parent process
You can use fork and die so init "adopts" the orphaned process that you launched