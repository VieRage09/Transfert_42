 
DockerHub: Kind of a repo of images
Docker provides an easy setup to work on project w/o having to handle all the dependencies
# Dockerfile

A configuration file. Docker will use its instructions to create an image that will run a container, that will run our desired command.
You can add anything (like install new programs..) to your image w/o installing it to your host os.

### What is an image ?

An imutable file system built by the dockerfile. It will run our container which will run our command. 
The image has a name and a tag, usually name:tag (Default tag is "latest").

![[Shema Docker.canvas]]

# I want to change something

Images are imutable, wich means that if you want to change a slight thing (in the script for example), you need to build you image again (with a new tag mate).

[[III. Docker Compose]]
