
# Virtualization

The actors:
- Host: Any piece of hardware --> Gives a piece of its hardwares (CPU, RAM ...)
- Hypervisor: --> Manage the Virtual Machines (VM)

## The basic idea of virtualization: 

When asked to create a VM, the hypervisor takes a section of each the available hardware 
and separates them off the host machine (virtually ofc) to create a VM. You can usually run a full OS on this VM. It will be completely isolated from the host.

Ex: When deploying something on the cloud. You create a VM on a distant server to have your program runing into it.

![[Shema virtualization.canvas]]

# Containerization

Actors:
- Host -->Basically some hardware running an OS
- Docker -->Used to manage containers (docker is just a ex)

## The idea of containerization

With a some existing commands, like chroot or rlimit, you can isolate a micro-environnement inside the host. Processes running inside share the same environnement as other processes but cannot access files outside this "box". The process being very tricky, it exists some programs that do it for you, like Docker.

![[Shema containerization.canvas]]
### Containers hystory

In the begining : chroot -> Isolate process so they can only some files (but they can do what they want with networks, processes ...)
Then: namespace + Cgroup :
	- Namespace -> allow some process to have an isolated instance of a ressource (unique process tree, filesystem mount point, routing table ...)
	- Cgroup : Control group -> gives the ability to make some groups of processes and manages their ressource usage
==> Both together ensured that groups of process can run compartimented and in parallel 
==> Form the core of container isolation

[[II. Docker]]


