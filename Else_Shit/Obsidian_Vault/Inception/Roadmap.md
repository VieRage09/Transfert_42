# I. Install VM 
- [x] 
#### 1. Pick between Alpine and Debian
###### Alpine
-> Lightweight
-> Less packages
-> package manager => apk
-> Focused on security
###### Debian
-> Uses more ressources
-> More packages
-> package manager => apt

==>  Alpine is very suitable for containerized deployments

##### Choice = Debian
-> Even if Alpine is best suited for that, debian is easier (i know it better than alpine) and the GUI makes it possible to work only from the VM. (I think i can put a GUI on alpine but its not automatic like Debian)  ==>  For the base VM
-> Alpine for images for containers

---
# II. Create dockerfiles for services

-> Guided tuto for that : https://medium.com/@afatir.ahmedfatir/unveiling-42-the-network-inception-a-dive-into-docker-and-docker-compose-cfda98d9f4ac

### 1. MariaDB

##### a. Write dockerfile
- [x] Pick images for container
-->  Debian:bookworm = latest release to be able to use mariadb -e that allows us to script configuration of mdb
##### b. Write configuration script
- [x] 
### 2.NGINX

Dockerfile: alpine:3.19 -> Latest stable version

Write nginx.conf file setting up the server name ssl protocol and where to find the authentification public and private key for TSL1.3, listenning port (443), wordpress directory

### 3. Wordpress

Dockerfile: alpine:3.19 -> Same as nginx
Write wp_conf.sh: Scripts used to install wordpress and run php-fpm

---
# III. Get a bigger picture

-> To truely understand interactions between services and set up properly the docker compose file

MariaDB:
- Used to manage the datas of the web database that are stored inside mdb volume
- Communicates with wordpress container via port 3306
Nginx:
- Used as a reverse proxy --> only access to our server
- Also IS the web server
- Uses tls protocol
- Communicates to php/wordpress the request via port 9000
- linked to wp volume
Wordpress:
- Get requests from nginx 
- uses php via php-fpm do execute some code or retrive and store data in the db
	-> Generates an html file and sends it to nginx

gpt =>

	{Client} → HTTPS (TLS 1.3)
     ↓
	{Nginx} → Decides route
     ↓      ↘
	{Static?} → Serve directly
	{Dynamic?} → Forward to PHP-FPM (FastCGI)
     ↓
	{PHP-FPM} → Run WordPress
     ↓
	{WordPress} → Query MariaDB
     ↓
	{MariaDB} → Return data
     ↑
	{WordPress} → Build HTML
     ↑
	{PHP-FPM} → Send output
     ↑
	{Nginx} → Serve to client

# IV. Create docker compose file

