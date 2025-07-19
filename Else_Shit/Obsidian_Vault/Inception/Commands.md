
chroot: creates a new root to run processes inside of it. 
rlimit: kernel -> Limits the ressources of some processes

# Docker

- docker build <image_name> -> Build an image using dockerfile 
- docker run <image_name> --> Runs the container inside the names image
- docker images -> Lists all images of our system

# Docker compose

- docker compose up -> runs the compose.yml file
	-> -d: Detached mode
- docker compose logs <container_name> -> get the logs of the container
- docker compose exec <container_name> <cmd_to_run> -> executes a cmd onto a container