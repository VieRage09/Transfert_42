FROM debian:12.10

WORKDIR /app

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y mariadb-server 

COPY db_conf.sh .

RUN chmod +x db_conf.sh && rm -rf /var/lib/mysql/* 
# mariadb-server will create the /var/lib/mysql directory when installed
# We delete it to ensure a clean start and being able to check for previous initialization

EXPOSE 3306
# Not needed but informative (docker compose network handle internal access)

ENTRYPOINT ["./db_conf.sh"]

