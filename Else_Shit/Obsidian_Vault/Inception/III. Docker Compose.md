A tool to create multi-container application where services can talk to one and other easily and efficiently

# 1. Docker compose file

-->  Named compose.yml

Lets take an example : we want a database and a web service
```
services:
	db:
		image: name of the image we want to use for our database
		// Here it must be created from a dockerfile before
		environnement:
			Whatever env variables we need (cf 2.)
		volumes:
			- name of the volume to mount to the container:/path where the volume gets mounted to onto the container 
			//Whatever volume we want to use cf ()
		healthcheck:
			// How we run the tests to make sure the services are running etc ...
	web:
		build: path of the dockerfile that creates the image for web service
		command: cmd that will be ran after image is built
		volumes:
			- ./test (example here)
		ports:
			- 241:444
			// Forwards the local port 241 to the port 444 of the container
		depends_on:
			db:
				condition: service_healthy
		// Make sure that all the services are running seemlessly (Web can't work w/o the database)
```

# 2. Environnement

In order to load some env variables to the container, docker compose use a .env file where you can store them (instead of defining them inside compose.yml)

# 3. Volumes

Because containers are ephemeral, you want a place to store some data so you can save some stuff
You can choose to mount the project directory for ex. This is handy when you want to change some files. (You may have to rebuild the image ?)

# 4. How the services communicate ?

There is a DNS inside the docker compose environnement that maps all the services and associates them to IPs. If the web service wants to connect to db service it only has to know wich port to use and its name.